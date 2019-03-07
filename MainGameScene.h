#pragma once
#include "Scene.h"
#include <D3D9.h>

// �O���錾
class Texture2D;


template<typename T>
class Point
{
public:
	T x;
	T y;

public:
	Point() {}
	Point(const T & x, const T & y) : x(x), y(y) {}
};


class MainGameScene : public Scene
{
private:
	Texture2D * m_texWallPaper;
	Texture2D * m_texBoard;
	Texture2D * m_texBlackOthelloStone;
	Texture2D * m_texWhiteOthelloStone;
	Texture2D * m_texYourTurn;
	Texture2D * m_texComTurn;
	Texture2D * m_texFrame;
	Texture2D * m_texNumberList;
	Texture2D * m_texPlayerIcom;
	Texture2D * m_texAiIcom;
	Texture2D * m_texBlackStone;
	Texture2D * m_texWhiteStone;

	// �����Ƀ����o�ϐ�
	static constexpr int BoardOffsetX = 397;
	static constexpr int BoardOffsetY = 117;
	static constexpr int CellOffsetX = 15;
	static constexpr int CellOffsetY = 15;
	static constexpr int CandidateOffsetX = 3;
	static constexpr int CandidateOffsetY = 3;
	static constexpr int BoardCellX = 8;
	static constexpr int BoardCellY = 8;
	static constexpr int NumDirection = 8;
	static constexpr int MaxDigits = 16;
	static constexpr int NormalDifficultyOpeningBoundary = 21;
	static constexpr int NormalDifficultyMiddleStageBoundary = 42;
	static constexpr int HardDifficultyOpeningBoundary = 21;
	static constexpr int HardDifficultyMiddleStageBoundary = 42;
	static constexpr int NumberWidth = 50;
	static constexpr int StoneWidth = 60;
	static constexpr int MinWeight = -128;
	static constexpr int MassNumOfOthelloBoard = 64;
	static constexpr int HeightOfCell = 61;
	static constexpr int WidthOfCell = 61;
	static const D3DCOLOR ColorWhite;				// ��
	static const D3DCOLOR ColorCandidate;			// �΂��u����ꏊ�̐F
	static const D3DCOLOR ColorCornFlowerBlue;		// �R�[���t�����[�u���[
	static const char NormalWeightOpening[8][8];	// ��Փx�m�[�}�����Ղ̏d�ݕ\
	static const char NormalWeightMiddle[8][8];		// ��Փx�m�[�}�����Ղ̏d�ݕ\
	static const char NormalWeightFinal[8][8];		// ��Փx�m�[�}���I�Ղ̏d�ݕ\
	static const char HardWeightOpening[8][8];		// ��Փx�n�[�h���Ղ̏d�ݕ\
	static const char HardWeightMiddle[8][8];		// ��Փx�n�[�h���Ղ̏d�ݕ\
	static const char HardWeightFinal[8][8];		// ��Փx�n�[�h�I�Ղ̏d�ݕ\
	static const int8_t DirectionXTable[8];
	static const int8_t DirectionYTable[8];
	static constexpr int8_t EMPTY =  0;
	static constexpr int8_t DARK  =  1;
	static constexpr int8_t LIGHT = -1;

	int8_t m_board[BoardCellY][BoardCellX];			// �I�Z����
	int8_t m_turn;
	int m_thinkTime;
	float m_waitTimeSeconds;
	uint16_t m_bgmID;
	uint16_t m_sePlaceDiskID;
	int8_t m_continuousPassCountDark;				//���Α��̃p�X��
	int8_t m_continuousPassCountLight;				//���Α��̃p�X��
	int8_t m_continuousPassCountWhole;				//�S�̂Ƃ��Ẵp�X��

	struct PlaceableResult
	{
		int totalFlipableDiskCount;		// �S�����̂Ђ�����Ԃ���΂̐�
		int countPerDirection[8];		// ������ɂ��Ђ�����Ԃ���΂̐�
		Point<int8_t> basePosition;		// ��_ (�΂�u�����ʒu) 
	};

	PlaceableResult m_placeableResult;


	bool m_previousLButtonPressed;

	enum class GameState
	{
		TurnStart,	//�^�[���J�n���Ɉ�x��������
		PlaceDisk,	//�΂�u��
		WaitTime,	//�҂�����
		FlipDisk,	//�΂��Ђ�����Ԃ�
		TurnOver,	//�^�[����ύX����
	};

	GameState m_gameState;
	GameState m_destination;

	// �u����Ă���΂̏��
	struct PlacedDiskInfo
	{
		uint8_t lightDistCount;	// ���΂̌�
		uint8_t darkDistCount;	// ���΂̌�
	};

private:
	// �΂�u����ꏊ��S�ĒT���o���A���̌���Ԃ��B
	int SearchPlaceable(int turn, bool placeable[8][8]);
	bool m_placeable[8][8];

	// ���ݔՏ�ɒu����Ă���΂̑����𐔂��܂��B
	PlacedDiskInfo m_placedDiskInfo;
	void CountPlacedDisks(PlacedDiskInfo & info);

	// �����l��`�悵�܂��B 
	void DrawNumbers(int x, int y, int value);

	// �e�X�̃^�[���ň�����ɂ��Ђ�����Ԃ���΂̐��𒲂ׂ�
	bool IsPlaceable(int turn, const Point<int8_t> & basePosition, PlaceableResult * nullableResult);

	// �΂��Ђ�����Ԃ��܂��B
	void FlipDisks(const PlaceableResult & result);

	// �d�ݕ\
	char GetWeight(int x, int y);

	void Wait(float seconds, GameState destination);

	void TurnStartPlayer();
	void TurnStartAI();
	void PlaceDiskPlayer();
	void PlaceDiskAI();
	void WaitTime();
	void FlipDisk();
	void TurnOverPlayer();
	void TurnOverAI();
	void TransitToResultScene();

public:
	// �R���X�g���N�^
	MainGameScene(const char * sceneName);

	// ���z�f�X�g���N�^
	virtual ~MainGameScene();

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