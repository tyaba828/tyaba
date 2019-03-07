#pragma once
#include "Scene.h"
#include <D3D9.h>

// �O���錾
class Texture2D;

class ResultScene : public Scene
{
private:
	// �����Ƀ����o�ϐ�

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

	//��
	static const D3DCOLOR ColorWhite;

public:
	// �R���X�g���N�^
	ResultScene(const char * sceneName);

	// ���z�f�X�g���N�^
	virtual ~ResultScene();

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