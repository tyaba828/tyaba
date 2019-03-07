#pragma once
#include "Scene.h"
#include "DifficultySelect.h"
#include "Rect.h"
#include <D3D9.h>

// 前方宣言
class Texture2D;

class DifficultySelectScene : public Scene
{
private:
	// ここにメンバ変数
	Texture2D * m_texBackGraund;
	Texture2D * m_texNormalButton;
	Texture2D * m_texHardButton;
	Texture2D * m_texReversiKun;

	DifficultySelect m_difficultySelect;

	bool mustTransitNextScene;
	int waitTime;
	static const int ThreeSeconds = 60 * 3;

	unsigned short bgmID;
	unsigned short seDecideDifficultID;

	static const Rect NomalButtonRect;
	static const Rect HardButtonRect;

	//白
	static const D3DCOLOR ColorWhite;

public:
	// コンストラクタ
	DifficultySelectScene(const char * sceneName);

	// 仮想デストラクタ
	virtual ~DifficultySelectScene();

	// このシーンが作成された時に１回だけ呼び出されます。
	virtual void OnCreate() override;

	// このシーンが開始される直前に１回だけ呼び出されます。
	virtual void OnStart() override;

	// このシーンをレンダリングする必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnRender() override;

	// このシーンを更新する必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnUpdate(float deltaTime) override;

	// このシーンが終了される直前に１回だけ呼び出されます。
	virtual void OnStop() override;

	// このシーンが破棄される直前に１回だけ呼び出されます。
	virtual void OnDestroy() override;
};