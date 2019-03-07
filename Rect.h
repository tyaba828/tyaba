#pragma once

class Rect
{
public:
	int left;
	int top;
	int right;
	int bottom;

public:
	// デフォルトコンストラクタ
	Rect() {}

	// コンストラクタ
	Rect(int left, int top, int right, int bottom)
		: left(left), top(top), right(right), bottom(bottom)
	{
	}
};
