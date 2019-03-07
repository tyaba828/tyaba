#pragma once
#include "Scene.h"
#include <D3D9.h>
#include "Rect.h"

// �O���錾
class Texture2D;

// �^�C�g�����
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

	//��
	static const D3DCOLOR ColorWhite;

public:
	// �R���X�g���N�^
	TitleScene(const char * sceneName);

	// ���z�f�X�g���N�^
	virtual ~TitleScene();

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