#pragma once
#include <string>
#include <unordered_map>

// 前方宣言
class Scene;

// シーン管理クラス
class SceneManager
{
private:
	static SceneManager * s_instance;
	std::unordered_map<std::string, Scene *> m_scenes;

	Scene * m_currScene;
	Scene * m_nextScene;

private:
	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();

	// コピーコンストラクタ
	SceneManager(const SceneManager &) = delete;

	// ムーブコンストラクタ
	SceneManager(const SceneManager &&) = delete;

	// 代入演算子
	SceneManager & operator =(const SceneManager &) = delete;

public:
	// SceneManagerサブシステムを初期化します。
	static void Startup();

	// SceneManagerサブシステムを終了します。
	static void Shutdown();

	// 唯一のインスタンスを取得します。
	static SceneManager * GetInstance() { return s_instance; }

	// シーンを登録します。
	void RegisterScene(Scene * scene);

	// 最初のシーン指定してゲームを開始します。
	void Run(const char * firstSceneName);

	// 次のシーンを予約します。
	void ReserveNextScene(const char * nextSceneName);

	// 次のシーンに遷移します。
	void TransitScene();

	// 現在アクティブなシーンをレンダリングします。
	void RenderCurrentScene();

	// 現在アクティブなシーンを更新します。
	void UpdateCurrentScene(float deltaTime);

private:
	// シーン識別名からシーンオブジェクトを検索します。
	Scene * FindSceneByName(const std::string & sceneName) const;
};

