#pragma once
#include <string>
#include <unordered_map>

// �O���錾
class Scene;

// �V�[���Ǘ��N���X
class SceneManager
{
private:
	static SceneManager * s_instance;
	std::unordered_map<std::string, Scene *> m_scenes;

	Scene * m_currScene;
	Scene * m_nextScene;

private:
	// �R���X�g���N�^
	SceneManager();

	// �f�X�g���N�^
	~SceneManager();

	// �R�s�[�R���X�g���N�^
	SceneManager(const SceneManager &) = delete;

	// ���[�u�R���X�g���N�^
	SceneManager(const SceneManager &&) = delete;

	// ������Z�q
	SceneManager & operator =(const SceneManager &) = delete;

public:
	// SceneManager�T�u�V�X�e�������������܂��B
	static void Startup();

	// SceneManager�T�u�V�X�e�����I�����܂��B
	static void Shutdown();

	// �B��̃C���X�^���X���擾���܂��B
	static SceneManager * GetInstance() { return s_instance; }

	// �V�[����o�^���܂��B
	void RegisterScene(Scene * scene);

	// �ŏ��̃V�[���w�肵�ăQ�[�����J�n���܂��B
	void Run(const char * firstSceneName);

	// ���̃V�[����\�񂵂܂��B
	void ReserveNextScene(const char * nextSceneName);

	// ���̃V�[���ɑJ�ڂ��܂��B
	void TransitScene();

	// ���݃A�N�e�B�u�ȃV�[���������_�����O���܂��B
	void RenderCurrentScene();

	// ���݃A�N�e�B�u�ȃV�[�����X�V���܂��B
	void UpdateCurrentScene(float deltaTime);

private:
	// �V�[�����ʖ�����V�[���I�u�W�F�N�g���������܂��B
	Scene * FindSceneByName(const std::string & sceneName) const;
};

