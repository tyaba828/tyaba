#include <windows.h>
#include "Graphics.h"
#include "Sound.h"
#include "SceneManager.h"
#include <cstdint>
#include <cassert>
#include "TitleScene.h"
#include "DifficultySelectScene.h"
#include "GlobalData.h"
#include "MainGameScene.h"
#include "ResultScene.h"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);

		SIZE clientSize;
		clientSize.cx = clientRect.right - clientRect.left;
		clientSize.cy = clientRect.bottom - clientRect.top;
		GlobalData::GetInstance()->SetClientSize(clientSize);
	}
	break;

	default:
		return(DefWindowProc(hWnd, msg, wParam, lParam));
	}

	return (0L);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR lpszCmdLine, int nCmdShow)
{
	// �E�B���h�E�N���X�̓o�^
	WNDCLASS wcex;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "���o�[�V";
	if (!RegisterClass(&wcex))
	{
		assert(0);
		return 0;
	}

	RECT rect;
	rect.left = 0;
	rect.right = 1280;
	rect.top = 0;
	rect.bottom = 720;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�T�C�Y���v�Z����
	SIZE windowSize;
	windowSize.cx = rect.right - rect.left;
	windowSize.cy = rect.bottom - rect.top;

	// �E�B���h�E�ʒu���v�Z���� (�Z���^�����O)
	POINT windowPos;
	windowPos.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2;
	windowPos.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;

	// �Q�[���p�E�B���h�E�̍쐬
	HWND hWnd;
	hWnd = CreateWindow(
		wcex.lpszClassName,
		"���o�[�V",
		WS_OVERLAPPEDWINDOW,
		windowPos.x,		// �������W�@��
		windowPos.y,		// �������W�@�c
		windowSize.cx,		// �����̑傫���@�c
		windowSize.cy,		// �����̑傫���@��
		nullptr,
		nullptr,
		wcex.hInstance,
		nullptr);

	if (!hWnd)
	{
		MessageBox(nullptr, "�E�B���h�E�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return 0;
	}

	// �O���t�B�b�N�X�T�u�V�X�e���̏�����
	Graphics::Startup(hWnd, 1280, 720);
	GlobalData::Startup(hWnd);
	StartupSoundSystem();

	// �V�[���Ǘ��T�u�V�X�e���̏�����
	SceneManager::Startup();
	SceneManager::GetInstance()->RegisterScene(new TitleScene("�^�C�g�����"));
	SceneManager::GetInstance()->RegisterScene(new DifficultySelectScene("��Փx�I�����"));
	SceneManager::GetInstance()->RegisterScene(new MainGameScene("���C���Q�[�����"));
	SceneManager::GetInstance()->RegisterScene(new ResultScene("���U���g���"));
	SceneManager::GetInstance()->Run("�^�C�g�����");

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// ���݃A�N�e�B�u�ȃV�[���������_�����O
			SceneManager::GetInstance()->RenderCurrentScene();

			// ���݃A�N�e�B�u�ȃV�[�����X�V
			SceneManager::GetInstance()->UpdateCurrentScene(1.0f / 60);

			// �K�v�ł���Ύ��̃V�[���֑J�ڂ��܂��B
			SceneManager::GetInstance()->TransitScene();
		}
	}

	ShutdownSoundSystem();
	SceneManager::Shutdown();
	GlobalData::Shutdown();
	Graphics::Shutdown();

	return (msg.wParam);
}