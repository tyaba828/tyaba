#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <cstdint>

class Texture2D
{
private:
	IDirect3DTexture9 * m_nativeTexture;
	uint32_t m_originalWidth;
	uint32_t m_originalHeight;
	uint32_t m_surfaceWidth;
	uint32_t m_surfaceHeight;

public:
	// �R���X�g���N�^
	Texture2D(IDirect3DTexture9 * nativeTexture, uint32_t originalWidth, uint32_t originalHeight);

	// �f�X�g���N�^
	~Texture2D();

	// Direct3D�e�N�X�`�����擾���܂��B
	IDirect3DTexture9 * GetNativeTexture() const;

	// �摜�̉������擾���܂��B
	uint32_t GetOriginalWidth() const { return m_originalWidth; }

	// �摜�̍������擾���܂��B
	uint32_t GetOriginalHeight() const { return m_originalHeight; }

	// ���x��0�T�[�t�F�C�X�̉������擾���܂��B
	uint32_t GetSurfaceWidth() const { return m_surfaceWidth; }

	// ���x��0�T�[�t�F�C�X���擾���܂��B
	uint32_t GetSurfaceHeight() const { return m_surfaceHeight; }
};