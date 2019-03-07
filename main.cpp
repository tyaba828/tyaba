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
	// ウィンドウクラスの登録
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
	wcex.lpszClassName = "リバーシ";
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

	// ウィンドウサイズを計算する
	SIZE windowSize;
	windowSize.cx = rect.right - rect.left;
	windowSize.cy = rect.bottom - rect.top;

	// ウィンドウ位置を計算する (センタリング)
	POINT windowPos;
	windowPos.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2;
	windowPos.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;

	// ゲーム用ウィンドウの作成
	HWND hWnd;
	hWnd = CreateWindow(
		wcex.lpszClassName,
		"リバーシ",
		WS_OVERLAPPEDWINDOW,
		windowPos.x,		// 初期座標　横
		windowPos.y,		// 初期座標　縦
		windowSize.cx,		// 初期の大きさ　縦
		windowSize.cy,		// 初期の大きさ　横
		nullptr,
		nullptr,
		wcex.hInstance,
		nullptr);

	if (!hWnd)
	{
		MessageBox(nullptr, "ウィンドウの作成に失敗しました", "エラー", MB_OK);
		return 0;
	}

	// グラフィックスサブシステムの初期化
	Graphics::Startup(hWnd, 1280, 720);
	GlobalData::Startup(hWnd);
	StartupSoundSystem();

	// シーン管理サブシステムの初期化
	SceneManager::Startup();
	SceneManager::GetInstance()->RegisterScene(new TitleScene("タイトル画面"));
	SceneManager::GetInstance()->RegisterScene(new DifficultySelectScene("難易度選択画面"));
	SceneManager::GetInstance()->RegisterScene(new MainGameScene("メインゲーム画面"));
	SceneManager::GetInstance()->RegisterScene(new ResultScene("リザルト画面"));
	SceneManager::GetInstance()->Run("タイトル画面");

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
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
			// 現在アクティブなシーンをレンダリング
			SceneManager::GetInstance()->RenderCurrentScene();

			// 現在アクティブなシーンを更新
			SceneManager::GetInstance()->UpdateCurrentScene(1.0f / 60);

			// 必要であれば次のシーンへ遷移します。
			SceneManager::GetInstance()->TransitScene();
		}
	}

	ShutdownSoundSystem();
	SceneManager::Shutdown();
	GlobalData::Shutdown();
	Graphics::Shutdown();

	return (msg.wParam);
}