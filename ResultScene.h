#pragma once
#include "Scene.h"
#include <D3D9.h>

// 前方宣言
class Texture2D;

class ResultScene : public Scene
{
private:
	// ここにメンバ変数

	Texture2D * m_texWallPaper;
	Texture2D * m_texFrame;
	Texture2D * m_texNumberList;
	Texture2D * m_texPlayerIcom;
	Texture2D * m_texAiIcom;
	Texture2D * m_texBlackStone;
	Texture2D * m_texWhiteStone;
	Texture2D * m_texVictoryImage;
	Texture2D * m_texLoseImage;
	Texture2D * m_texDrawImage;

	int waitTime;
	void DrawNumbers(int x, int y, int value);

	unsigned short bgmID;

	static const int FiveSeconds = 60 * 5;
	static const int NumberWidth = 50;

	//白
	static const D3DCOLOR ColorWhite;

public:
	// コンストラクタ
	ResultScene(const char * sceneName);

	// 仮想デストラクタ
	virtual ~ResultScene();

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