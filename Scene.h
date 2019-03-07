#pragma once
#include <string>

// シーン基底クラス
class Scene
{
private:
	// シーンの識別名
	std::string m_sceneName;

	// シーンの詳細説明テキスト
	std::string m_descption;

	// 
	bool m_isCreated;

	friend class SceneManager;

private:
	// 
	bool IsCreated() const { return m_isCreated; }

public:
	// コンストラクタ
	Scene(const char * sceneName);

	// 仮想デストラクタ
	virtual ~Scene();

	// シーンの識別名を取得します。
	const std::string & GetSceneName() { return m_sceneName; }

	// シーンの詳細説明テキストを取得します。
	const std::string & GetDescption() { return m_descption; }

	// このシーンが作成された時に１回だけ呼び出されます。
	virtual void OnCreate();

	// このシーンが開始される直前に１回だけ呼び出されます。
	virtual void OnStart();

	// このシーンをレンダリングする必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnRender();

	// このシーンを更新する必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnUpdate(float deltaTime);

	// このシーンが終了される直前に１回だけ呼び出されます。
	virtual void OnStop();

	// このシーンが破棄される直前に１回だけ呼び出されます。
	virtual void OnDestroy();
};
