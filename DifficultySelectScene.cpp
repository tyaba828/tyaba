#include "DifficultySelectScene.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "Utility.h"
#include "Rect.h"
#include "Point.h"
#include "GlobalData.h"
#include "Sound.h"

#pragma comment(lib,"winmm.lib")

const Rect DifficultySelectScene::NomalButtonRect = Rect(260, 370, 550, 415);
const Rect DifficultySelectScene::HardButtonRect = Rect(730, 370, 1020, 415);

const D3DCOLOR DifficultySelectScene::ColorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);

DifficultySelectScene::DifficultySelectScene(const char * sceneName)
	: Scene(sceneName)
{
}


DifficultySelectScene::~DifficultySelectScene()
{
}


void DifficultySelectScene::OnCreate()
{
	Scene::OnCreate();

	// �e�N�X�`�����̃��[�h
	Graphics * g = Graphics::GetInstance();
	m_texBackGraund = g->LoadTexture("Assets/Common/background.jpeg");
	m_texNormalButton = g->LoadTexture("Assets/DifficultySelect/normal-button.png");
	m_texHardButton = g->LoadTexture("Assets/DifficultySelect/hard-button.png");
	m_texReversiKun = g->LoadTexture("Assets/Common/reversi-kun.png");
}


void DifficultySelectScene::OnStart()
{
	Scene::OnStart();

	//BGM�̃��[�h
	bgmID = OpenSound("Assets/Sound/BGM/holidays.wav");
	PlaySound2(bgmID);

	//SE�̃��[�h
	seDecideDifficultID = OpenSound("Assets/Sound/BGM/DecideDifficult.wav");

	bool mustTransitNextScene;

	// ���̃V�[���̍ŏ���1�x������肽������
	GlobalData::GetInstance()->SetDifficultySelect(DifficultySelect::Unselected);
	//waitTime��3�b��������
	waitTime = ThreeSeconds;
}


void DifficultySelectScene::OnRender()
{
	IDirect3DDevice9 * d3dDevice = Graphics::GetInstance()->GetD3DDevice();
	d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 149, 237), 1.0, 0);
	d3dDevice->BeginScene();

	Scene::OnRender();

	// �`��
	Graphics * g = Graphics::GetInstance();
	g->DrawSprite(0, 0, 1280, 720, m_texBackGraund, 0, 0, 513, 216, ColorWhite);
	g->DrawSprite(1095, 580, 141, 141, m_texReversiKun, 0, 0, 566, 566, ColorWhite);

	if (m_difficultySelect == DifficultySelect::Normal)
		g->DrawSprite(200, 345, 410, 80, m_texNormalButton, 0, 0, 310, 50, ColorWhite);
	else
		g->DrawSprite(250, 365, 310, 50, m_texNormalButton, 0, 0, 310, 50, ColorWhite);
	if (m_difficultySelect == DifficultySelect::Hard)
		g->DrawSprite(670, 345, 410, 80, m_texHardButton, 0, 0, 310, 50, ColorWhite);
	else
		g->DrawSprite(720, 365, 310, 50, m_texHardButton, 0, 0, 310, 50, ColorWhite);

	d3dDevice->EndScene();
	d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}


void DifficultySelectScene::OnUpdate(float deltaTime)
{
	Scene::OnUpdate(deltaTime);

	// �}�E�X�J�[�\���̍��W
	const POINT cursor = GlobalData::GetInstance()->GetMousePosition();

	// �X�V
	
	if (PointInRect(NomalButtonRect, Point(cursor.x, cursor.y)))
	{
		m_difficultySelect = DifficultySelect::Normal;
	}
	else if (PointInRect(HardButtonRect, Point(cursor.x, cursor.y)))
	{
		m_difficultySelect = DifficultySelect::Hard;
	}
	else
	{
		m_difficultySelect = DifficultySelect::Unselected;
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		switch (m_difficultySelect)
		{
		case DifficultySelect::Normal:
			// �u��Փx�m�[�}���v�ɑJ�ڂ���
			PlaySound2(seDecideDifficultID, 1, true);
			SceneManager::GetInstance()->ReserveNextScene("���C���Q�[�����");
			GlobalData::GetInstance()->SetDifficultySelect(DifficultySelect::Normal);
			break;

		case DifficultySelect::Hard:
			// �u��Փx�n�[�h�v�ɑJ�ڂ���
			PlaySound2(seDecideDifficultID, 1, true);
			SceneManager::GetInstance()->ReserveNextScene("���C���Q�[�����");
			GlobalData::GetInstance()->SetDifficultySelect(DifficultySelect::Hard);
			break;
		}
	}
}


void DifficultySelectScene::OnStop()
{
	CloseSound(bgmID);

	Scene::OnStop();
}


void DifficultySelectScene::OnDestroy()
{
	delete m_texBackGraund;
	delete m_texNormalButton;
	delete m_texHardButton;
	delete m_texReversiKun;

	Scene::OnDestroy();
}
