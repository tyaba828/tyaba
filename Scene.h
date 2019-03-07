#pragma once
#include <string>

// �V�[�����N���X
class Scene
{
private:
	// �V�[���̎��ʖ�
	std::string m_sceneName;

	// �V�[���̏ڍא����e�L�X�g
	std::string m_descption;

	// 
	bool m_isCreated;

	friend class SceneManager;

private:
	// 
	bool IsCreated() const { return m_isCreated; }

public:
	// �R���X�g���N�^
	Scene(const char * sceneName);

	// ���z�f�X�g���N�^
	virtual ~Scene();

	// �V�[���̎��ʖ����擾���܂��B
	const std::string & GetSceneName() { return m_sceneName; }

	// �V�[���̏ڍא����e�L�X�g���擾���܂��B
	const std::string & GetDescption() { return m_descption; }

	// ���̃V�[�����쐬���ꂽ���ɂP�񂾂��Ăяo����܂��B
	virtual void OnCreate();

	// ���̃V�[�����J�n����钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnStart();

	// ���̃V�[���������_�����O����K�v������ۂɌĂяo����܂��B
	// (60fps�̃Q�[���ł����1�b�Ԃ�60��Ăяo�����\��������܂�)
	virtual void OnRender();

	// ���̃V�[�����X�V����K�v������ۂɌĂяo����܂��B
	// (60fps�̃Q�[���ł����1�b�Ԃ�60��Ăяo�����\��������܂�)
	virtual void OnUpdate(float deltaTime);

	// ���̃V�[�����I������钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnStop();

	// ���̃V�[�����j������钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnDestroy();
};
