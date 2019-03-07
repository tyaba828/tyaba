#include "TitleScene.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "Texture2D.h"
#include "Rect.h"
#include "Point.h"
#include "Utility.h"
#include "Sound.h"
#include "GlobalData.h"

#pragma comment(lib,"winmm.lib")

const Rect TitleScene::StartButtonRect = Rect(260, 605, 550, 645);
const Rect TitleScene::ExitButtonRect = Rect(730, 605, 1020, 645);

const D3DCOLOR TitleScene::ColorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);


TitleScene::TitleScene(const char * sceneName)
	: Scene(sceneName)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::OnCreate()
{
	Scene::OnCreate();

	// テクスチャの読み込み
	Graphics * g = Graphics::GetInstance();
	m_texBackgraund = g->LoadTexture("Assets/Common/background.jpeg");
	m_texTitleBoard = g->LoadTexture("Assets/Title/title-board.png");
	m_texStartButton = g->LoadTexture("Assets/Title/start-button.png");
	m_texExitButton = g->LoadTexture("Assets/Title/exit-button.png");
	m_texReversiKun = g->LoadTexture("Assets/Common/reversi-kun.png");
}


void TitleScene::OnStart()
{
	Scene::OnStart();

	//BGMのロード
	bgmID = OpenSound("Assets/Sound/BGM/holidays.wav");
	PlaySound2(bgmID);

	// 決定音


	m_titleMenu = TitleMenu::Unselected;
}


void TitleScene::OnRender()
{
	IDirect3DDevice9 * d3dDevice = Graphics::GetInstance()->GetD3DDevice();
	d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 149, 237), 1.0, 0);
	d3dDevice->BeginScene();

	Scene::OnRender();

	Graphics * g = Graphics::GetInstance();
	g->DrawSprite(0, 0, 1280, 720, m_texBackgraund, 0, 0, 513, 216, ColorWhite);
	g->DrawSprite(0, -100, 1280, 720, m_texTitleBoard, 0, 0, 628, 300, ColorWhite);

	if (m_titleMenu == TitleMenu::Start)
		g->DrawSprite(200, 580, 410, 80, m_texStartButton, 0, 0, 310, 50, ColorWhite);
	else
		g->DrawSprite(250, 600, 310, 50, m_texStartButton, 0, 0, 310, 50, ColorWhite);

	if (m_titleMenu == TitleMenu::Exit)
		g->DrawSprite(670, 580, 410, 80, m_texExitButton, 0, 0, 310, 50, ColorWhite);
	else
		g->DrawSprite(720, 600, 310, 50, m_texExitButton, 0, 0, 310, 50, ColorWhite);

	g->DrawSprite(1095, 580, 141, 141, m_texReversiKun, 0, 0, 566, 566, ColorWhite);

	d3dDevice->EndScene();
	d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void TitleScene::OnUpdate(float deltaTime)
{
	Scene::OnUpdate(deltaTime);

	// マウスカーソルの座標
	const POINT cursor = GlobalData::GetInstance()->GetMousePosition();

	if (PointInRect(StartButtonRect, Point(cursor.x, cursor.y)))
	{
		m_titleMenu = TitleMenu::Start;
	}

	else if (PointInRect(ExitButtonRect, Point(cursor.x, cursor.y)))
	{
		m_titleMenu = TitleMenu::Exit;
	}
	else
	{
		m_titleMenu = TitleMenu::Unselected;
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		switch (m_titleMenu)
		{
		case TitleMenu::Start:
			// 「難易度選択画面」に遷移する
			SceneManager::GetInstance()->ReserveNextScene("難易度選択画面");
			break;

		case TitleMenu::Exit:
			// ウィンドウを破棄する
			DestroyWindow(Graphics::GetInstance()->GetHWnd());
			break;
		}
	}
}


void TitleScene::OnStop()
{
	CloseSound(bgmID);

	Scene::OnStop();
}


void TitleScene::OnDestroy()
{
	delete m_texBackgraund;
	delete m_texTitleBoard;
	delete m_texStartButton;
	delete m_texExitButton;
	delete m_texReversiKun;

	Scene::OnDestroy();
}
