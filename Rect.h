#pragma once

class Rect
{
public:
	int left;
	int top;
	int right;
	int bottom;

public:
	// �f�t�H���g�R���X�g���N�^
	Rect() {}

	// �R���X�g���N�^
	Rect(int left, int top, int right, int bottom)
		: left(left), top(top), right(right), bottom(bottom)
	{
	}
};
