#include "Graphics.h"
#include "Texture2D.h"
#include <cassert>
#include <cstdio>

// ���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// �ÓI�����o�ϐ��̎��̂�錾
Graphics * Graphics::s_instance = nullptr;

Graphics::Graphics()
	: m_hWnd(nullptr)
{
}

Graphics::~Graphics()
{
}


void Graphics::Startup(HWND hWnd, uint32_t resolutionX, uint32_t resolutionY)
{
	assert(s_instance == nullptr);
	s_instance = new Graphics();
	s_instance->CreateDevice(hWnd, resolutionX, resolutionY);
}


void Graphics::Shutdown()
{
	assert(s_instance != nullptr);
	delete s_instance;
	s_instance = nullptr;
}


IDirect3DDevice9 * Graphics::GetD3DDevice() const
{
	return m_d3dDevice;
}

Texture2D * Graphics::LoadTexture(const char * path)
{
	IDirect3DTexture9 * texture;
	D3DXIMAGE_INFO imageInfo;
	
	HRESULT hr = D3DXCreateTextureFromFileEx(
		m_d3dDevice,				// Direct3D�f�o�C�X
		path,						// �e�N�X�`���t�@�C���̃p�X
		0,							// �e�N�X�`���̉���(0�̏ꍇ���ׂāj
		0,							// �e�N�X�`���̍���(0�̏ꍇ���ׂāj
		1,							// �~�b�v���x��
		0,							// �e�N�X�`���̗��p���@
		D3DFMT_UNKNOWN,				// �s�N�Z���t�H�[�}�b�g
		D3DPOOL_DEFAULT,			// �ǂ��̃������ɒu�����H
		D3DX_FILTER_NONE,			// �g��t�B���^
		D3DX_FILTER_NONE,			// �~�b�v�t�B���^
		D3DCOLOR_ARGB(0, 0, 0, 0),	// �J���[�L�[ (���ߐF)
		&imageInfo,					// �摜�̏ڍ׏��
		nullptr,					// 1,2,4,8�r�b�g�C���[�W�p�p���b�g
		&texture);					// �e�N�X�`�����󂯎��ϐ�

	if (FAILED(hr))
	{
		char msg[1024];
		sprintf_s(msg, "\"%s\"�̓ǂݍ��݂Ɏ��s���܂���", path);
		MessageBox(nullptr, msg, "LoadTexture()�֐����G���[", MB_OK);
	}

	Texture2D * texture2D = new Texture2D(texture, imageInfo.Width, imageInfo.Height);
	return texture2D;
}



void Graphics::DrawSprite(float dx, float dy, float dw, float dh, Texture2D * texture, float sx, float sy, float sw, float sh, D3DCOLOR color)
{
	// ���_1����\���\����
	struct VERTEX
	{
		float x, y, z;		// ��ɕK�{
		float rhw;			// w�̋t�� (2D�̎��̂ݕK�v)
		D3DCOLOR color;		// ���_�J���[
		float u, v;			// �e�N�X�`�����W (UV���W�n)
	};

	dx -= 0.5f;
	dy -= 0.5f;

	const uint32_t surfaceW = texture->GetSurfaceWidth();
	const uint32_t surfaceH = texture->GetSurfaceHeight();

	// ���_�^�̔z��ŗp�ӂ���K�v������B
	// DirectX�ň������_�̓�������ŘA�����Ă���K�v������B
	VERTEX v[4];

	// ���_�͉E���Ŕz�u���Ȃ��ƃ|���S���������Ȃ��B
	v[0].x = dx;
	v[0].y = dy;
	v[0].z = 0.0f;
	v[0].rhw = 1.0f;
	v[0].color = color;
	v[0].u = sx / surfaceW;
	v[0].v = sy / surfaceH;

	v[1].x = dx + dw;
	v[1].y = dy;
	v[1].z = 0.0f;
	v[1].rhw = 1.0f;
	v[1].color = color;
	v[1].u = (sx + sw) / surfaceW;
	v[1].v = sy / surfaceH;

	v[2].x = dx;
	v[2].y = dy + dh;
	v[2].z = 0.0f;
	v[2].rhw = 1.0f;
	v[2].color = color;
	v[2].u = sx / surfaceW;
	v[2].v = (sy + sh) / surfaceH;

	v[3].x = dx + dw;
	v[3].y = dy + dh;
	v[3].z = 0.0f;
	v[3].rhw = 1.0f;
	v[3].color = color;
	v[3].u = (sx + sw) / surfaceW;
	v[3].v = (sy + sh) / surfaceH;

	// ���_1�����ǂ�ȗv�f�������Ă��邩��DirectX�ɋ�����
	m_d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// �\�肽���e�N�X�`����DirectX�ɋ�����
	m_d3dDevice->SetTexture(0, texture->GetNativeTexture());

	// �v���~�e�B�u�`�施�߂�DirectX�ɔ��s����B
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(VERTEX));
}


void Graphics::FillRect(float dx, float dy, float dw, float dh, D3DCOLOR color)
{
	struct FILLVERTEX
	{
		float x, y, z;		// ��ɕK�{
		float rhw;			// w�̋t�� (2D�̎��̂ݕK�v)
		D3DCOLOR color;		// ���_�J���[
	};

	dx -= 0.5f;
	dy -= 0.5f;

	const FILLVERTEX v[4] =
	{
		{ dx,    dy,    0, 1, color },
		{ dx+dw, dy,    0, 1, color },
		{ dx,    dy+dh, 0, 1, color },
		{ dx+dw, dy+dh, 0, 1, color },
	};

	m_d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_d3dDevice->SetTexture(0, nullptr);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FILLVERTEX));
}


void Graphics::RenderAxisGrid()
{
	struct LineVertex
	{
		float x, y, z;
		D3DCOLOR color;
	};

	const LineVertex line[6] =
	{
		{ 0,0,0, 0xffff0000 },	// x���n�_
		{ 20,0,0, 0xffff0000 },	// x���I�_

		{ 0,0,0,  0xff008000 },	// y���n�_
		{ 0,20,0, 0xff008000 },	// y���I�_

		{ 0,0,0,  0xff0000ff },	//z���n�_
		{ 0,0,20, 0xff0000ff },	//z���I�_
	};

	m_d3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_d3dDevice->SetTexture(0, nullptr);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 3, line, sizeof(LineVertex));

	LineVertex grid[31 * 2 * 2];

	int index = 0;
	for (int i = -15; i <= 15; i++)
	{
		grid[index++] = { -15, 0, (float)i, 0xff000000 };	// x���n�_
		grid[index++] = { +15, 0, (float)i, 0xff000000 };	// x���I�_
	}

	for (int i = -15; i <= 15; i++)
	{
		grid[index++] = { (float)i, 0, -15, 0xff000000 };	// z���n�_
		grid[index++] = { (float)i, 0, +15, 0xff000000 };	// z���I�_
	}

	m_d3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_d3dDevice->SetTexture(0, nullptr);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_LINELIST, 31 * 2, grid, sizeof(LineVertex));
}

void Graphics::CreateDevice(HWND hWnd, uint32_t resolutionX, uint32_t resolutionY)
{
	m_hWnd = hWnd;

	// Direct3D�I�u�W�F�N�g�̏�����
	IDirect3D9 * d3dObject;
	if (!(d3dObject = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		assert(0);
		return;
	}

	//�v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.BackBufferWidth = resolutionX;	// �o�b�N�o�b�t�@�̐��������𑜓x
	d3dpp.BackBufferHeight = resolutionY;	// �o�b�N�o�b�t�@�̉��������𑜓x
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = TRUE;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.Flags = 0;

	if (FAILED(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
	{
		if (FAILED(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
		{
			if (FAILED(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
			{
				if (FAILED(d3dObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice)))
				{
					MessageBox(nullptr, "Direct3D�̏������Ɏ��s���܂���", "�G���[", MB_OK);
					d3dObject->Release();
					return;
				}
			}
		}
	}

	// Direct3D�I�u�W�F�N�g�̉��
	d3dObject->Release();

	// �����v�Z��ON/OFF
	// �����v�ZON�A���A���C�g�Ȃ��̏ꍇ�͍��ŕ`�悳���
	// �����v�ZOFF�̏ꍇ�͔��܂��̓e�N�X�`���̐F�ŕ`�悳���
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���u�����f�B���O��ON/OFF
	m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�o�b�t�@��ON/OFF
	// 3D�̏ꍇ�͗L���ɂ���ׂ�
	// 2D�̏ꍇ�͖����ł�OK
	m_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// 3D�̏ꍇ�͕ϊ��s����ݒ肵�Ă����ׂ�

	// ���[���h�ϊ��s���ݒ肷��B
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	m_d3dDevice->SetTransform(D3DTS_WORLD, &world);

	// �r���[�ϊ��s���ݒ肷��B
	D3DXMATRIX view;
	D3DXMatrixLookAtLH(&view, &D3DXVECTOR3(5, 5, -10), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	m_d3dDevice->SetTransform(D3DTS_VIEW, &view);

	// �v���W�F�N�V�����ϊ��s���ݒ肷��B
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection, D3DXToRadian(45), (float)resolutionX / resolutionY, 0.1f, 10000.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &projection);

	// �r���[�|�[�g��ݒ肷��B
	D3DVIEWPORT9 viewport;
	memset(&viewport, 0, sizeof(viewport));
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = resolutionX;
	viewport.Height = resolutionY;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	m_d3dDevice->SetViewport(&viewport);
}
