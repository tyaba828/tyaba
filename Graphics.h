#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <cstdint>
#include "Texture2D.h"

// �O���錾
class Texture2D;

// �O���t�B�b�N�֘A (�V���O���g��)
//  �E�p���֎~
//  �E�����֎~
//  �E�R�s�[�֎~
//  �E���[�u�֎~
class Graphics final
{
private:
	// �B���Graphics�^�C���X�^���X
	static Graphics * s_instance;

	HWND m_hWnd;

	// Direct3D�f�o�C�X
	IDirect3DDevice9 * m_d3dDevice;

private:
	// �R���X�g���N�^
	Graphics();

	// �f�X�g���N�^
	~Graphics();

	// �R�s�[�R���X�g���N�^
	Graphics(const Graphics &) = delete;

	// ���[�u�R���X�g���N�^
	Graphics(const Graphics &&) = delete;

	// ������Z�q
	Graphics & operator =(const Graphics &) = delete;

public:
	// Graphics�T�u�V�X�e�������������܂��B
	static void Startup(HWND hWnd, uint32_t resolutionX, uint32_t resolutionY);

	// Graphics�T�u�V�X�e�����I�����܂��B
	static void Shutdown();

	// �B��̃C���X�^���X���擾���܂��B
	static Graphics * GetInstance() { return s_instance; }

	// �E�B���h�E�n���h�����擾���܂��B
	HWND GetHWnd() const { return m_hWnd; }

	// Direct3D�f�o�C�X���擾���܂��B
	IDirect3DDevice9 * GetD3DDevice() const;

	// �e�N�X�`�������[�h���܂��B
	Texture2D * LoadTexture(const char * path);

	// 2D�X�v���C�g��`�悵�܂��B
	void DrawSprite(float dx, float dy, float dw, float dh, Texture2D * texture, float sx, float sy, float sw, float sh, D3DCOLOR color);

	// ��`�̈��P�F�œh��Ԃ��܂��B
	void FillRect(float dx, float dy, float dw, float dh, D3DCOLOR color);

	// �O���b�h����`�悵�܂��B
	void RenderAxisGrid();

private:
	// Direct3D�f�o�C�X���쐬���܂��B
	void CreateDevice(HWND hWnd, uint32_t resolutionX, uint32_t resolutionY);
};





