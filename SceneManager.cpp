#include "SceneManager.h"
#include "Scene.h"
#include <cassert>

// 静的メンバ変数の実体を宣言
SceneManager * SceneManager::s_instance = nullptr;

SceneManager::SceneManager()
	: m_currScene(nullptr)
	, m_nextScene(nullptr)
{
}

SceneManager::~SceneManager()
{

}


void SceneManager::Startup()
{
	assert(s_instance == nullptr);
	s_instance = new SceneManager();
}


void SceneManager::Shutdown()
{
	assert(s_instance != nullptr);
	delete s_instance;
	s_instance = nullptr;
}


void SceneManager::RegisterScene(Scene * scene)
{
	const std::string & sceneName = scene->GetSceneName();
	if (Scene * found = FindSceneByName(sceneName))
	{
		assert(!"既に同名のシーンが登録されています。");
	}
	m_scenes.insert({ sceneName, scene });
}


void SceneManager::Run(const char * firstSceneName)
{
	m_currScene = FindSceneByName(firstSceneName);
	assert(m_currScene);
	if (!m_currScene->IsCreated())
	{
		m_currScene->OnCreate();
		m_currScene->m_isCreated = true;
	}
	m_currScene->OnStart();
	m_nextScene = m_currScene;
}


void SceneManager::ReserveNextScene(const char * nextSceneName)
{
	m_nextScene = FindSceneByName(nextSceneName);
	assert(m_currScene);
}


void SceneManager::TransitScene()
{
	if (m_nextScene != m_currScene)
	{
		m_currScene->OnStop();
		if (!m_nextScene->IsCreated())
		{
			m_nextScene->OnCreate();
			m_nextScene->m_isCreated = true;
		}
		m_nextScene->OnStart();
		m_currScene = m_nextScene;
	}
}


void SceneManager::RenderCurrentScene()
{
	m_currScene->OnRender();
}


void SceneManager::UpdateCurrentScene(float deltaTime)
{
	m_currScene->OnUpdate(deltaTime);
}


Scene * SceneManager::FindSceneByName(const std::string & sceneName) const
{
	auto found = m_scenes.find(sceneName);
	if (found != m_scenes.end())
	{
		return  (*found).second;
	}
	return nullptr;
}
