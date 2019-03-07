#include "MainGameScene.h"
#include "SceneManager.h"
#include "Graphics.h"
#include "GlobalData.h"
#include "DifficultySelect.h"
#include "Texture2D.h"
#include "Sound.h"
#include <cassert>

#pragma comment(lib,"winmm.lib")


const D3DCOLOR MainGameScene::ColorWhite = D3DCOLOR_ARGB(255, 255, 255, 255);
const D3DCOLOR MainGameScene::ColorCandidate = D3DCOLOR_ARGB(128, 194, 244, 66);
const D3DCOLOR MainGameScene::ColorCornFlowerBlue = D3DCOLOR_XRGB(100, 149, 237);

const char MainGameScene::NormalWeightOpening[8][8] =
{
	 30, -12,  0,  -1,  -1,  0, -12,  30,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	 30, -12,  0  ,-1,  -1,  0, -12,  30,
};

const char MainGameScene::NormalWeightMiddle[8][8] =
{
	 30, -12,  0,  -1,  -1,  0, -12,  30,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	 30, -12,  0  ,-1,  -1,  0, -12,  30,
};

const char MainGameScene::NormalWeightFinal[8][8] =
{
	 30, -12,  0,  -1,  -1,  0, -12,  30,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	 30, -12,  0  ,-1,  -1,  0, -12,  30,
};

const char MainGameScene::HardWeightOpening[8][8] =
{
	 30, -12,  0,  -1,  -1,  0, -12,  30,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	 30, -12,  0  ,-1,  -1,  0, -12,  30,
};

const char MainGameScene::HardWeightMiddle[8][8] =
{
	 30, -20,  -1,  -1,  -1,  -1, -20,  30,
	-20, -15,  -3,  -3,  -3,  -3, -15, -20,
	 -1,  -3,   0,  -1,  -1,   0,  -3,  -1,
	 -1,  -3,  -1,  -1,  -1,  -1,  -3,  -1,
	 -1,  -3,  -1,  -1,  -1,  -1,  -3,  -1,
	 -1,  -3,   0,  -1,  -1,   0,  -3,  -1,
	-20, -15,  -3,  -3,  -3,  -3, -15, -20,
	 30, -20,  -1  ,-1,  -1,  -1, -20,  30,
};

const char MainGameScene::HardWeightFinal[8][8] =
{
	 30, -12,  0,  -1,  -1,  0, -12,  30,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	 -1,  -3, -1,  -1,  -1, -1,  -3,  -1,
	  0,  -3,  0,  -1,  -1,  0,  -3,   0,
	-12, -15, -3,  -3,  -3, -3, -15, -12,
	 30, -12,  0  ,-1,  -1,  0, -12,  30,
};

const int8_t MainGameScene::DirectionXTable[8]{ 0, +1, +1, +1, 0, -1, -1, -1 };
const int8_t MainGameScene::DirectionYTable[8]{ -1, -1, 0, +1, +1, +1, 0, -1 };

MainGameScene::MainGameScene(const char * sceneName)
	: Scene(sceneName)
	, m_gameState(GameState::PlaceDisk)
{
}


MainGameScene::~MainGameScene()
{
}

void MainGameScene::OnCreate()
{
	Scene::OnCreate();

	// �e�N�X�`�����̃��[�h
	Graphics * g = Graphics::GetInstance();
	m_texWallPaper = g->LoadTexture("Assets/Common/wallpaper.png");
	m_texBoard = g->LoadTexture("Assets/MainGame/board.png");
	m_texBlackOthelloStone = g->LoadTexture("Assets/MainGame/kurokoma.png");
	m_texWhiteOthelloStone = g->LoadTexture("Assets/MainGame/sirokoma.png");
	m_texYourTurn = g->LoadTexture("Assets/MainGame/playerturn.png");
	m_texComTurn = g->LoadTexture("Assets/MainGame/comturn.png");
	m_texFrame = g->LoadTexture("Assets/Common/frame.png");
	m_texNumberList = g->LoadTexture("Assets/Common/Numberlist.png");
	m_texPlayerIcom = g->LoadTexture("Assets/Common/playericom.png");
	m_texAiIcom = g->LoadTexture("Assets/Common/enemyicom.png");
	m_texBlackStone = g->LoadTexture("Assets/Common/reversikuro.png");
	m_texWhiteStone = g->LoadTexture("Assets/Common/reversi-siro.png");
}


void MainGameScene::OnStart()
{
	Scene::OnStart();

	// BGM�����[�h���čĐ��J�n
	m_bgmID = OpenSound("Assets/Sound/BGM/adventurers.WAV");
	PlaySound2(m_bgmID, -1);

	// SE�̃��[�h����
	m_sePlaceDiskID = OpenSound("Assets/Sound/BGM/SePut.wav");

	//�Ֆʂɉ����΂�u���Ă��Ȃ���Ԃɂ���
	for (int y = 0; y < BoardCellY; y++)
	{
		for (int x = 0; x < BoardCellX; x++)
		{
			m_board[y][x] = EMPTY;
		}
	}

	// �J�n���̍���/���΂�u��
	m_board[3][4] = DARK;
	m_board[4][3] = DARK;
	m_board[3][3] = LIGHT;
	m_board[4][4] = LIGHT;

	m_turn = DARK;
	m_previousLButtonPressed = false;
	m_gameState = GameState::TurnStart;

	m_continuousPassCountDark = 0;
	m_continuousPassCountLight = 0;
	m_continuousPassCountWhole = 0;

	CountPlacedDisks(m_placedDiskInfo);
	SearchPlaceable(m_turn, m_placeable);
}


int MainGameScene::SearchPlaceable(int turn, bool placeable[8][8])
{
	int count = 0;
	for (int8_t y = 0; y < BoardCellY; y++)
	{
		for (int8_t x = 0; x < BoardCellX; x++)
		{
			placeable[y][x] = false;

			// �΂��܂��u����Ă��Ȃ��ꏊ��T���B
			if (m_board[y][x] == EMPTY)
			{
				PlaceableResult result;
				if (IsPlaceable(turn, { x, y }, &result))
				{
					placeable[y][x] = true;
					count++;
				}
			}
		}
	}

	return count;
}


void MainGameScene::CountPlacedDisks(PlacedDiskInfo & info)
{
	info.lightDistCount = 0;
	info.darkDistCount = 0;
	for (int y = 0; y < BoardCellY; y++)
	{
		for (int x = 0; x < BoardCellX; x++)
		{
			if (m_board[y][x] == DARK)
				info.darkDistCount++;
			else if (m_board[y][x] == LIGHT)
				info.lightDistCount++;
		}
	}
}

//�R�}�̌���\������B
void MainGameScene::DrawNumbers(int x, int y, int value)
{
	char number[MaxDigits];
	int digit = 0;

	//�ꌅ�����o��
	//0�������ꍇ
	if (value == 0)
	{
		number[0] = 0;
		digit = 1;
	}
	//0�ȊO�������ꍇ
	else
	{
		while (value != 0)
		{
			number[digit] = value % 10;
			value = value / 10;
			digit += 1;
		}
	}

	Graphics * g = Graphics::GetInstance();
	for (int i = digit - 1; i >= 0; i--)
	{
		g->DrawSprite(x - i * NumberWidth, y, NumberWidth, 88, m_texNumberList, 118 * number[i], 0, 100, 176, ColorWhite);
	}
}


bool MainGameScene::IsPlaceable(int turn, const Point<int8_t> & basePosition, PlaceableResult * nullableResult)
{
	if (m_board[basePosition.y][basePosition.x] != EMPTY)
		return false;

	if (nullableResult)
	{
		nullableResult->totalFlipableDiskCount = 0;
		nullableResult->basePosition = basePosition;
	}

	// ������ɂ��Ђ�����Ԃ���΂̐�
	int count[8];
	int total = 0;

	for (int dir = 0; dir < NumDirection; dir++)
	{
		Point<int8_t> position(basePosition);
		count[dir] = 0;

		while (1)
		{
			position.x += DirectionXTable[dir];
			position.y += DirectionYTable[dir];

			if (position.x >= BoardCellX || position.y >= BoardCellY || position.x < 0 || position.y < 0)
			{
				// �I�Z���Ղ͈̔͊O
				count[dir] = 0;
				break;
			}

			if (m_board[position.y][position.x] == -turn)
			{
				// ����̐΂�����������
				count[dir]++;
			}
			else if (m_board[position.y][position.x] == turn)
			{
				//�����̐΂�����������
				break;
			}
			else
			{
				//�󂫂�����������
				count[dir] = 0;
				break;
			}
		}

		total += count[dir];
	}

	if (nullableResult)
	{
		for (int dir = 0; dir < NumDirection; dir++)
		{
			nullableResult->countPerDirection[dir] = count[dir];
		}
		nullableResult->totalFlipableDiskCount = total;
	}

	return (total > 0);
}


void MainGameScene::FlipDisks(const PlaceableResult & result)
{
	for (int dir = 0; dir < NumDirection; dir++)
	{
		Point<int8_t> position(result.basePosition);

		for (int i = 0; i < result.countPerDirection[dir]; i++)
		{
			position.x += DirectionXTable[dir];
			position.y += DirectionYTable[dir];
			//1��-1��-1���|���Z����ƂЂ�����Ԃ���B
			m_board[position.y][position.x] *= -1;
		}
	}
}



//�Q�[���̐i�s�x�ɂ���ďd�ݕ\��ς���
char MainGameScene::GetWeight(int x, int y)
{
	const int totalDiskCount = m_placedDiskInfo.darkDistCount + m_placedDiskInfo.lightDistCount;

	if (GlobalData::GetInstance()->GetDifficultySelect() == DifficultySelect::Normal)
	{
		if (totalDiskCount < NormalDifficultyOpeningBoundary)
			return NormalWeightOpening[y][x];
		else if (totalDiskCount < NormalDifficultyMiddleStageBoundary)
			return NormalWeightMiddle[y][x];
		else
			return NormalWeightFinal[y][x];
	}
	else
	{
		if (totalDiskCount < HardDifficultyOpeningBoundary)
			return HardWeightOpening[y][x];
		else if (totalDiskCount < HardDifficultyMiddleStageBoundary)
			return HardWeightMiddle[y][x];
		else
			return HardWeightFinal[y][x];
	}
}



void MainGameScene::OnRender()
{
	IDirect3DDevice9 * d3dDevice = Graphics::GetInstance()->GetD3DDevice();
	d3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, ColorCornFlowerBlue, 1.0, 0);
	d3dDevice->BeginScene();

	Scene::OnRender();

	// �`��
	Graphics * g = Graphics::GetInstance();
	//�w�i
	g->DrawSprite(0, 0, 1280, 720, m_texWallPaper, 0, 0, 3840, 2697, ColorWhite);
	//�v���C���[���̕\��
	g->DrawSprite(10, 390, 300, 300, m_texFrame, 0, 0, 680, 480, ColorWhite);
	g->DrawSprite(90, 420, 128, 128, m_texPlayerIcom, 0, 0, 128, 128, ColorWhite);
	g->DrawSprite(30, 575, 111, 75, m_texBlackStone, 0, 0, 222, 150, ColorWhite);
	//�v���C���[�̐΂̐�
	DrawNumbers(200, 558, m_placedDiskInfo.darkDistCount);
	//CPU���̕\��
	g->DrawSprite(950, 390, 300, 300, m_texFrame, 0, 0, 680, 480, ColorWhite);
	g->DrawSprite(1025, 420, 128, 128, m_texAiIcom, 0, 0, 128, 128, ColorWhite);
	g->DrawSprite(980, 558, 111, 75, m_texWhiteStone, 0, 0, 222, 150, ColorWhite);
	//CPU�̐΂̐�
	DrawNumbers(1150, 558, m_placedDiskInfo.lightDistCount);
	//�ǂ���̎�Ԃ�
	if (m_turn == DARK)
	{
		g->DrawSprite(10, 30, 300, 100, m_texFrame, 0, 0, 680, 480, ColorWhite);
		g->DrawSprite(10, 28, 320, 130, m_texYourTurn, 0, 0, 925, 360, ColorWhite);
	}
	else
	{
		g->DrawSprite(950, 30, 300, 100, m_texFrame, 0, 0, 680, 480, ColorWhite);
		g->DrawSprite(950, 28, 320, 130, m_texComTurn, 0, 0, 925, 360, ColorWhite);
	}
	//�I�Z���Ղ̕`��
	g->DrawSprite(BoardOffsetX, BoardOffsetY, 486, 486, m_texBoard, 0, 0, 486, 487, ColorWhite);
	//�΂��u����ꏊ�̐F��ς���B
	for (int y = 0; y < BoardCellY; y++)
	{
		for (int x = 0; x < BoardCellX; x++)
		{
			if (m_placeable[y][x])
			{
				g->FillRect(BoardOffsetX + CandidateOffsetX + StoneWidth * x, BoardOffsetY + CandidateOffsetY + StoneWidth * y, 58, 58, ColorCandidate);
			}
		}
	}
	//�΂̕`��
	for (int y = 0; y < BoardCellY; y++)
	{
		for (int x = 0; x < BoardCellX; x++)
		{
			if (m_board[y][x] == DARK)
			{
				g->DrawSprite(BoardOffsetX + CellOffsetX + x * StoneWidth, BoardOffsetY + CellOffsetY + y * StoneWidth, 31, 31, m_texBlackOthelloStone, 0, 0, 31, 31, ColorWhite);
			}
			else if (m_board[y][x] == LIGHT)
			{
				g->DrawSprite(BoardOffsetX + CellOffsetX + x * StoneWidth, BoardOffsetY + CellOffsetY + y * StoneWidth, 31, 31, m_texWhiteOthelloStone, 0, 0, 31, 31, ColorWhite);
			}
		}
	}

	d3dDevice->EndScene();
	d3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void MainGameScene::Wait(float seconds, GameState destination)
{
	m_waitTimeSeconds = seconds;
	m_destination = destination;
	m_gameState = GameState::WaitTime;
}


void MainGameScene::TurnStartPlayer()
{
	// �I������
	CountPlacedDisks(m_placedDiskInfo);
	if ((m_placedDiskInfo.darkDistCount + m_placedDiskInfo.lightDistCount) == MassNumOfOthelloBoard)
	{
		TransitToResultScene();
	}
	else if (SearchPlaceable(DARK, m_placeable) == 0)
	{
		if (++m_continuousPassCountDark >= 3)
		{
			TransitToResultScene();
		}
		else if (++m_continuousPassCountWhole >= 2)
		{
			TransitToResultScene();
		}
		else
		{
			//�u����ꏊ������������pass������B
			MessageBox(nullptr, "�v���C���[��pass���܂����B", "���b�Z�[�W", MB_OK);
			m_turn = -m_turn;
			m_gameState = GameState::TurnStart;
		}
	}
	else
	{
		m_gameState = GameState::PlaceDisk;
	}
}


void MainGameScene::TurnStartAI()
{
	// �I������
	CountPlacedDisks(m_placedDiskInfo);
	if ((m_placedDiskInfo.darkDistCount + m_placedDiskInfo.lightDistCount) == MassNumOfOthelloBoard)
	{
		TransitToResultScene();
	}
	else if (SearchPlaceable(LIGHT, m_placeable) == 0)
	{
		if (++m_continuousPassCountLight >= 3)
		{
			TransitToResultScene();
		}
		else if (++m_continuousPassCountWhole >= 2)
		{
			TransitToResultScene();
		}
		else
		{
			//�u����ꏊ������������pass������B
			MessageBox(nullptr, "AI��pass���܂����B", "���b�Z�[�W", MB_OK);
			m_turn = -m_turn;
			m_gameState = GameState::TurnStart;
		}
	}
	else
	{
		m_thinkTime = rand() % 121 + 60;
		m_gameState = GameState::PlaceDisk;
	}
}

void MainGameScene::PlaceDiskPlayer()
{
	HWND hWnd = Graphics::GetInstance()->GetHWnd();

	// �}�E�X�J�[�\���̍��W
	const POINT cursor = GlobalData::GetInstance()->GetMousePosition();

	//�}�X�P�ʂ̑傫���ɕϊ�����
	const int8_t cellx = (int8_t)((cursor.x - BoardOffsetX) / WidthOfCell);
	const int8_t celly = (int8_t)((cursor.y - BoardOffsetY) / HeightOfCell);

	// �}�E�X�J�[�\���̈ʒu(�N���C�A���g���W)��\������B
	char text[256];
	sprintf(text, "���o�[�V");
	//sprintf_s(text, "(%4d,%4d)��(%4d,%4d)", cursor.x, cursor.y, cellx, celly);
	SetWindowText(hWnd, text);

	//�v���C���[�̃^�[��
	//�N���b�N�������ɍ��΂�u��
	bool currLButtonPressed = (GetKeyState(VK_LBUTTON) & 0x8000) == 0x8000;

	//�N���b�N���Ă���Œ���������
	if (m_previousLButtonPressed)
	{
		m_previousLButtonPressed = currLButtonPressed;
		return;
	}

	//�N���b�N���Ă��Ȃ�������
	m_previousLButtonPressed = currLButtonPressed;
	if (!currLButtonPressed)
		return;

	//�΂�u�����Ƃ��Ă���ꏊ���I�Z���Ղ̊O���ǂ���
	if (cellx < 0 || celly < 0 || cellx >= BoardCellX || celly >= BoardCellY)
		return;

	//�΂����ɒu����Ă���
	if (m_board[celly][cellx] != EMPTY)
		return;

	//����̐΂����߂�ꏊ���ǂ���
	if (IsPlaceable(m_turn, { cellx, celly }, &m_placeableResult))
	{
		m_board[celly][cellx] = m_turn;
		m_continuousPassCountDark = 0;
		m_continuousPassCountWhole = 0;
		PlaySound2(m_sePlaceDiskID);
		Wait(1.0f, GameState::FlipDisk);
	}
}

void MainGameScene::WaitTime()
{
	m_waitTimeSeconds -= 1.0f / 60;
	if (m_waitTimeSeconds <= 0)
	{
		m_gameState = m_destination;
	}
}

void MainGameScene::FlipDisk()
{
	// ���񂾐΂��Ђ�����Ԃ�����
	FlipDisks(m_placeableResult);

	m_gameState = GameState::TurnOver;
}

void MainGameScene::TurnOverPlayer()
{
	m_turn = -m_turn;
	m_gameState = GameState::TurnStart;
}

void MainGameScene::PlaceDiskAI()
{
	m_thinkTime--;
	if (m_thinkTime > 0)
		return;

	// AI�̃^�[��
	int8_t max_x;
	int8_t max_y;
	char max_weight = MinWeight;


	for (int8_t y = 0; y < BoardCellY; y++)
	{
		for (int8_t x = 0; x < BoardCellX; x++)
		{
			//�΂�u����ꏊ��T��
			if (m_placeable[y][x])
			{
				//�΂�u����ꏊ�ł̏d�ݕ\���l����ԍ����ꏊ���o����
				const char weight = GetWeight(x, y);
				if (weight > max_weight)
				{
					max_x = x;
					max_y = y;
					max_weight = weight;
				}
			}
		}
	}

	//����̐΂����߂�ꏊ���ǂ���
	if (!IsPlaceable(m_turn, { max_x, max_y }, &m_placeableResult))
	{
		assert(0);
	}

	m_board[max_y][max_x] = m_turn;

	PlaySound2(m_sePlaceDiskID);

	Wait(1.0f, GameState::FlipDisk);
}


void MainGameScene::TurnOverAI()
{
	m_turn = -m_turn;
	m_gameState = GameState::TurnStart;
}

void MainGameScene::TransitToResultScene()
{
	GlobalData::GetInstance()->SetBlackStoneCount(m_placedDiskInfo.darkDistCount);
	GlobalData::GetInstance()->SetWhiteStoneCount(m_placedDiskInfo.lightDistCount);
	SceneManager::GetInstance()->ReserveNextScene("���U���g���");
}

void MainGameScene::OnUpdate(float deltaTime)
{
	Scene::OnUpdate(deltaTime);

	switch (m_gameState)
	{
	case GameState::TurnStart:
		(m_turn == DARK) ? TurnStartPlayer() : TurnStartAI();
		break;

	case GameState::PlaceDisk:
		(m_turn == DARK) ? PlaceDiskPlayer() : PlaceDiskAI();
		break;

	case GameState::WaitTime:
		WaitTime();
		break;

	case GameState::FlipDisk:
		FlipDisk();
		break;

	case GameState::TurnOver:
		(m_turn == DARK) ? TurnOverPlayer() : TurnOverAI();
		break;
	}
}

void MainGameScene::OnStop()
{
	CloseSound(m_bgmID);
	CloseSound(m_sePlaceDiskID);

	Scene::OnStop();
}

void MainGameScene::OnDestroy()
{
	delete m_texWallPaper;
	delete m_texBoard;
	delete m_texBlackOthelloStone;
	delete m_texWhiteOthelloStone;
	delete m_texYourTurn;
	delete m_texComTurn;
	delete m_texFrame;
	delete m_texNumberList;
	delete m_texPlayerIcom;
	delete m_texAiIcom;
	delete m_texBlackStone;
	delete m_texWhiteStone;

	Scene::OnDestroy();
}

