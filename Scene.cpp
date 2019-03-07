#include "Scene.h"

Scene::Scene(const char * sceneName)
	: m_sceneName(sceneName)
	, m_isCreated(false)
{
}

Scene::~Scene()
{
}

void Scene::OnCreate()
{
}

void Scene::OnStart()
{
}

void Scene::OnRender()
{
}

void Scene::OnUpdate(float deltaTime)
{
}

void Scene::OnStop()
{
}

void Scene::OnDestroy()
{
}
