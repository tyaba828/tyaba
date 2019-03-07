#include "GlobalData.h"
#include <cassert>

GlobalData * GlobalData::s_instance = nullptr;

GlobalData::GlobalData(HWND hWnd)
	: m_hWnd(hWnd)
	, m_difficultySelect(DifficultySelect::Unselected)
	, m_blackStoneCount(0)
	, m_whiteStoneCount(0)
{
}


void GlobalData::Startup(HWND hWnd)
{
	assert(!s_instance);
	s_instance = new GlobalData(hWnd);
}


void GlobalData::Shutdown()
{
	assert(s_instance);
	delete s_instance;
	s_instance = nullptr;
}


GlobalData * GlobalData::GetInstance()
{
	return s_instance;
}

void GlobalData::SetDifficultySelect(DifficultySelect difficultySelect)
{
	m_difficultySelect = difficultySelect;
}

DifficultySelect GlobalData::GetDifficultySelect()const
{
	return m_difficultySelect;
}

void GlobalData::SetBlackStoneCount(int count)
{
	m_blackStoneCount = count;
}

int GlobalData::GetBlackStoneCount()const
{
	return m_blackStoneCount;
}

void GlobalData::SetWhiteStoneCount(int count)
{
	m_whiteStoneCount = count;
}

void GlobalData::SetClientSize(SIZE clientSize)
{
	m_clientSize = clientSize;
}

SIZE GlobalData::GetClientSize() const
{
	return m_clientSize;
}

POINT GlobalData::GetMousePosition() const
{
	//マウス座標
	POINT cursor;
	::GetCursorPos(&cursor);

	// スクリーン座標からクライアント座標に変換する。
	::ScreenToClient(m_hWnd, &cursor);

	SIZE clientSize = GlobalData::GetInstance()->GetClientSize();
	const float rateX = clientSize.cx / 1280.0f;
	const float rateY = clientSize.cy / 720.0f;

	cursor.x = cursor.x / rateX;
	cursor.y = cursor.y / rateY;
	return cursor;
}

int GlobalData::GetWhiteStoneCount()const
{
	return m_whiteStoneCount;
}


