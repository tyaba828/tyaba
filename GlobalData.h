#pragma once
#include "DifficultySelect.h"
#include <windows.h>
class GlobalData
{
private:
	HWND m_hWnd;
	DifficultySelect m_difficultySelect;
	int m_blackStoneCount;
	int m_whiteStoneCount;
	SIZE m_clientSize;

	static GlobalData * s_instance;



private:
	GlobalData(HWND hWnd);
	~GlobalData() = default;
	GlobalData(const GlobalData &) = delete;
	GlobalData(GlobalData &&) = delete;
	void operator =(const GlobalData &) = delete;
	void operator =(GlobalData &&) = delete;

public:
	static void Startup(HWND hWnd);
	static void Shutdown();
	static GlobalData * GetInstance();

	void SetDifficultySelect(DifficultySelect difficultySelect);
	DifficultySelect GetDifficultySelect()const;

	void SetBlackStoneCount(int count);
	int GetBlackStoneCount()const;

	void SetWhiteStoneCount(int count);
	int GetWhiteStoneCount()const;

	void SetClientSize(SIZE clientSize);
	SIZE GetClientSize()const;

	POINT GetMousePosition() const;
};