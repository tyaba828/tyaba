#pragma once
#include "Scene.h"
#include <D3D9.h>
#include "Rect.h"

// 前方宣言
class Texture2D;

// タイトル画面
class TitleScene : public Scene
{
private:
	Texture2D * m_texBackgraund;
	Texture2D * m_texTitleBoard;
	Texture2D * m_texStartButton;
	Texture2D * m_texExitButton;
	Texture2D * m_texReversiKun;

	unsigned short bgmID;

	enum class TitleMenu
	{
		Start,
		Exit,
		Unselected,
	};

	TitleMenu m_titleMenu;

	static const Rect StartButtonRect;
	static const Rect ExitButtonRect;

	//白
	static const D3DCOLOR ColorWhite;

public:
	// コンストラクタ
	TitleScene(const char * sceneName);

	// 仮想デストラクタ
	virtual ~TitleScene();

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