#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <unordered_map>
#include <cassert>

static HWND hSoundWnd = nullptr;

// 1�ȕ�
struct Sound
{
	unsigned short soundID;
	int loopTimes;
	bool autoClose;
};

// �Đ����̋�
std::unordered_map<unsigned short, Sound *> playing;


static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		break;

	case MM_MCINOTIFY:
	{
		if (wParam == MCI_NOTIFY_SUCCESSFUL)
		{
			unsigned short soundID = (unsigned short)lParam;

			auto found = playing.find(soundID);
			assert(found != playing.end());

			Sound * sound = (*found).second;
			
			if (sound->loopTimes < 0)
			{
				PlaySound2(soundID, sound->loopTimes);
			}
			else if (sound->loopTimes > 1)
			{
				PlaySound2(soundID, sound->loopTimes - 1);
			}
			else
			{
				if (sound->autoClose)
				{
					CloseSound(soundID);
				}
				else
				{
					playing.erase(found);
				}
			}
		}
	}
	break;

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0L);
}


void StartupSoundSystem()
{
	assert(!hSoundWnd);

	// �E�B���h�E�N���X�̓o�^
	WNDCLASS wcex;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "�T�E���h�E�B���h�E�N���X";
	if (!RegisterClass(&wcex))
	{
		assert(0);
		return;
	}

	// �T�E���h�p�E�B���h�E�̍쐬
	hSoundWnd = CreateWindow(wcex.lpszClassName, "�T�E���h�E�B���h�E", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wcex.hInstance, nullptr);
	if (!hSoundWnd)
	{
		MessageBox(nullptr, "�T�E���h�E�B���h�E�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
	}
}


void ShutdownSoundSystem()
{
	assert(hSoundWnd);
	DestroyWindow(hSoundWnd);
	hSoundWnd = nullptr;
}


unsigned short OpenSound(const char * path)
{
	MCI_OPEN_PARMS mciOpen;
	memset(&mciOpen, 0, sizeof(mciOpen));
	mciOpen.lpstrDeviceType = (const char *)MCI_DEVTYPE_WAVEFORM_AUDIO;
	mciOpen.lpstrElementName = path;

	if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE_ID | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&mciOpen))
	{
		MessageBox(nullptr, "�T�E���h�̍Đ��Ɏ��s���܂����B", "�G���[", MB_OK);
	}

	return mciOpen.wDeviceID;
}

void PlaySound2(unsigned short soundID, int loopTimes, bool autoClose)
{
	assert(hSoundWnd);

	if (loopTimes == 0)
		return;

	auto found = playing.find(soundID);
	if (found == playing.end())
	{
		// �V�K�o�^
		Sound * sound = new Sound();
		sound->soundID = soundID;
		sound->loopTimes = loopTimes;
		sound->autoClose = autoClose;
		playing.insert({ soundID, sound });
	}
	else
	{
		(*found).second->loopTimes = loopTimes;
		(*found).second->autoClose = autoClose;
	}

	MCI_PLAY_PARMS mciPlay;
	mciPlay.dwFrom = 0;		// �Đ��������Ȃ̎n��
	mciPlay.dwTo = 0;		// �Đ��������Ȃ̏I���
	mciPlay.dwCallback = (DWORD_PTR)hSoundWnd;
	mciSendCommand(soundID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD_PTR)&mciPlay);
}


void StopSound(unsigned short soundID)
{
	mciSendCommand(soundID, MCI_STOP, 0, 0);

	auto found = playing.find(soundID);
	if (found != playing.end())
	{
		delete (*found).second;
		playing.erase(found);
	}
}

void CloseSound(unsigned short soundID)
{
	mciSendCommand(soundID, MCI_CLOSE, 0, 0);

	auto found = playing.find(soundID);
	if (found != playing.end())
	{
		delete (*found).second;
		playing.erase(found);
	}
}
