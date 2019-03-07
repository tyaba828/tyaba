#pragma once
#include "Scene.h"
#include "DifficultySelect.h"
#include "Rect.h"
#include <D3D9.h>

// �O���錾
class Texture2D;

class DifficultySelectScene : public Scene
{
private:
	// �����Ƀ����o�ϐ�
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

	//��
	static const D3DCOLOR ColorWhite;

public:
	// �R���X�g���N�^
	DifficultySelectScene(const char * sceneName);

	// ���z�f�X�g���N�^
	virtual ~DifficultySelectScene();

	// ���̃V�[�����쐬���ꂽ���ɂP�񂾂��Ăяo����܂��B
	virtual void OnCreate() override;

	// ���̃V�[�����J�n����钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnStart() override;

	// ���̃V�[���������_�����O����K�v������ۂɌĂяo����܂��B
	// (60fps�̃Q�[���ł����1�b�Ԃ�60��Ăяo�����\��������܂�)
	virtual void OnRender() override;

	// ���̃V�[�����X�V����K�v������ۂɌĂяo����܂��B
	// (60fps�̃Q�[���ł����1�b�Ԃ�60��Ăяo�����\��������܂�)
	virtual void OnUpdate(float deltaTime) override;

	// ���̃V�[�����I������钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnStop() override;

	// ���̃V�[�����j������钼�O�ɂP�񂾂��Ăяo����܂��B
	virtual void OnDestroy() override;
};