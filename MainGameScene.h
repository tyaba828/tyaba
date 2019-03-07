#pragma once
#include "Scene.h"
#include <D3D9.h>

// 前方宣言
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

	// ここにメンバ変数
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
	static const D3DCOLOR ColorWhite;				// 白
	static const D3DCOLOR ColorCandidate;			// 石が置ける場所の色
	static const D3DCOLOR ColorCornFlowerBlue;		// コーンフラワーブルー
	static const char NormalWeightOpening[8][8];	// 難易度ノーマル序盤の重み表
	static const char NormalWeightMiddle[8][8];		// 難易度ノーマル中盤の重み表
	static const char NormalWeightFinal[8][8];		// 難易度ノーマル終盤の重み表
	static const char HardWeightOpening[8][8];		// 難易度ハード序盤の重み表
	static const char HardWeightMiddle[8][8];		// 難易度ハード中盤の重み表
	static const char HardWeightFinal[8][8];		// 難易度ハード終盤の重み表
	static const int8_t DirectionXTable[8];
	static const int8_t DirectionYTable[8];
	static constexpr int8_t EMPTY =  0;
	static constexpr int8_t DARK  =  1;
	static constexpr int8_t LIGHT = -1;

	int8_t m_board[BoardCellY][BoardCellX];			// オセロ盤
	int8_t m_turn;
	int m_thinkTime;
	float m_waitTimeSeconds;
	uint16_t m_bgmID;
	uint16_t m_sePlaceDiskID;
	int8_t m_continuousPassCountDark;				//黒石側のパス回数
	int8_t m_continuousPassCountLight;				//白石側のパス回数
	int8_t m_continuousPassCountWhole;				//全体としてのパス回数

	struct PlaceableResult
	{
		int totalFlipableDiskCount;		// 全方向のひっくり返せる石の数
		int countPerDirection[8];		// 一方向につきひっくり返せる石の数
		Point<int8_t> basePosition;		// 基準点 (石を置いた位置) 
	};

	PlaceableResult m_placeableResult;


	bool m_previousLButtonPressed;

	enum class GameState
	{
		TurnStart,	//ターン開始時に一度だけ入る
		PlaceDisk,	//石を置く
		WaitTime,	//待ち時間
		FlipDisk,	//石をひっくり返す
		TurnOver,	//ターンを変更する
	};

	GameState m_gameState;
	GameState m_destination;

	// 置かれている石の情報
	struct PlacedDiskInfo
	{
		uint8_t lightDistCount;	// 白石の個数
		uint8_t darkDistCount;	// 黒石の個数
	};

private:
	// 石を置ける場所を全て探し出し、その個数を返す。
	int SearchPlaceable(int turn, bool placeable[8][8]);
	bool m_placeable[8][8];

	// 現在盤上に置かれている石の総数を数えます。
	PlacedDiskInfo m_placedDiskInfo;
	void CountPlacedDisks(PlacedDiskInfo & info);

	// 整数値を描画します。 
	void DrawNumbers(int x, int y, int value);

	// 各々のターンで一方向につきひっくり返せる石の数を調べる
	bool IsPlaceable(int turn, const Point<int8_t> & basePosition, PlaceableResult * nullableResult);

	// 石をひっくり返します。
	void FlipDisks(const PlaceableResult & result);

	// 重み表
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
	// コンストラクタ
	MainGameScene(const char * sceneName);

	// 仮想デストラクタ
	virtual ~MainGameScene();

	// このシーンが作成された時に１回だけ呼び出されます。
	virtual void OnCreate() override;

	// このシーンが開始される直前に１回だけ呼び出されます。
	virtual void OnStart() override;

	// このシーンをレンダリングする必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnRender() override;

	// このシーンを更新する必要がある際に呼び出されます。
	// (60fpsのゲームであれば1秒間に60回呼び出される可能性があります)
	virtual void OnUpdate(float deltaTime) override;

	// このシーンが終了される直前に１回だけ呼び出されます。
	virtual void OnStop() override;

	// このシーンが破棄される直前に１回だけ呼び出されます。
	virtual void OnDestroy() override;
};