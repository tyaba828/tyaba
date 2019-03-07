#include "ResultScene.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "Utility.h"
#include "Texture2D.h"
#include "GlobalData.h"
#include "Sound.h"

#pragma comment(lib,"winmm.lib")

const D3DCOLOR ResultScene::ColorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);


ResultScene::ResultScene(const char * sceneName)
	: Scene(sceneName)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::OnCreate()
{
	Scene::OnCreate();
	Graphics * g = Graphics::GetInstance();
	m_texWallPaper = g->LoadTexture("Assets/Common/wallpaper.png");
	m_texFrame = g->LoadTexture("Assets/Common/frame.png");
	m_texNumberList = g->LoadTexture("Assets/Common/Numberlist.png");
	m_texPlayerIcom = g->LoadTexture("Assets/Common/playericom.png");
	m_texAiIcom = g->LoadTexture("Assets/Common/enemyicom.png");
	m_texBlackStone = g->LoadTexture("Assets/Common/reversikuro.png");
	m_texWhiteStone = g->LoadTexture("Assets/Common/reversi-siro.png");
	m_texVictoryImage = g->LoadTexture("Assets/Result/victoryimage.png");
	m_texLoseImage = g->LoadTexture("Assets/Result/loseimage.png");
	m_texDrawImage = g->LoadTexture("Assets/Result/drawimage.png");
}

void ResultScene::OnStart()
{
	Scene::OnStart();

	//BGMのロード
	bgmID = OpenSound("Assets/Sound/BGM/WinFanfare.WAV");
	PlaySound2(bgmID);

	//waitTimeに５秒を教える
	waitTime = FiveSeconds;
}

//コマの個数を表示する。
void ResultScene::DrawNumbers(int x, int y, int value)
{
	char number[16];
	int digit = 0;

	//一桁を取り出す
	//0だった場合
	if (value == 0)
	{
		number[0] = 0;
		digit = 1;
	}
	//0以外だった場合
	else
	{
		while (value != 0)
		{
			number[digit] = value % 10;
			value = value / 10;
			digit += 1;
		}
	}

	Graphics * g = Graphics::GetInstance();
	for (int i = digit - 1; i >= 0; i--)
	{
		g->DrawSprite(x - i * NumberWidth, y, NumberWidth, 88, m_texNumberList, 118 * number[i], 0, 100, 176, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void ResultScene::OnRender()
{
	IDirect3DDevice9 * d3dDevice = Graphics::GetInstance()->GetD3DDevice();
	d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 149, 237), 1.0, 0);
	d3dDevice->BeginScene();

	Scene::OnRender();

	Graphics * g = Graphics::GetInstance();
	//背景
	g->DrawSprite(0, 0, 1280, 720, m_texWallPaper, 0, 0, 3840, 2697, ColorWhite);

	int blackStoneCount = GlobalData::GetInstance()->GetBlackStoneCount();
	int whiteStoneCount = GlobalData::GetInstance()->GetWhiteStoneCount();

	//リザルト画像表示
	if (blackStoneCount > whiteStoneCount)
	{
		g->DrawSprite(440, 160, 400, 400, m_texVictoryImage, 0, 0, 592, 417, ColorWhite);

	}

	else if (blackStoneCount == whiteStoneCount)
	{
		g->DrawSprite(440, 160, 400, 400, m_texDrawImage, 0, 0, 155, 180, ColorWhite);

	}

	else if (blackStoneCount < whiteStoneCount)
	{
		g->DrawSprite(0, 0, 400, 400, m_texLoseImage, 0, 0, 592, 417, ColorWhite);

	}
	//プレイヤー情報の表示
	g->DrawSprite(10, 390, 300, 300, m_texFrame, 0, 0, 680, 480, ColorWhite);
	g->DrawSprite(90, 420, 128, 128, m_texPlayerIcom, 0, 0, 128, 128, ColorWhite);
	g->DrawSprite(30, 575, 111, 75, m_texBlackStone, 0, 0, 222, 150, ColorWhite);
	DrawNumbers(200, 558, blackStoneCount);
	//CPU情報の表示
	g->DrawSprite(950, 390, 300, 300, m_texFrame, 0, 0, 680, 480, ColorWhite);
	g->DrawSprite(1025, 420, 128, 128, m_texAiIcom, 0, 0, 128, 128, ColorWhite);
	g->DrawSprite(980, 558, 111, 75, m_texWhiteStone, 0, 0, 222, 150, ColorWhite);
	DrawNumbers(1150, 558, whiteStoneCount);

	d3dDevice->EndScene();
	d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void ResultScene::OnUpdate(float deltaTime)
{
	Scene::OnUpdate(deltaTime);

	//waitTimeから1秒間ずつに60を引いて0になったならタイトル画面に戻る
	waitTime--;
	if (waitTime == 0)
	{
		SceneManager::GetInstance()->ReserveNextScene("タイトル画面");

	}
}

void ResultScene::OnStop()
{
	CloseSound(bgmID);

	Scene::OnStop();
}

void ResultScene::OnDestroy()
{
	delete m_texWallPaper;
	delete m_texFrame;
	delete m_texNumberList;
	delete m_texPlayerIcom;
	delete m_texAiIcom;
	delete m_texBlackStone;
	delete m_texWhiteStone;
	delete m_texVictoryImage;
	delete m_texLoseImage;
	delete m_texDrawImage;

	Scene::OnDestroy();
}
