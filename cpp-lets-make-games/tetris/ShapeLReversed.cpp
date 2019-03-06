#include "pch.h"
#include "ShapeLReversed.h"

ShapeLReversed::ShapeLReversed()
{
}

ShapeLReversed::~ShapeLReversed()
{
}

bool ShapeLReversed::init()
{
	if (!Shape::init()) return false;

	// �����
	// �����
	// �����
	// �����
	shape[2][0] = '1';
	shape[3][0] = '1';
	shape[3][1] = '1';
	shape[3][2] = '1';
	widthCount = 3;

	return true;
}

void ShapeLReversed::rotate()
{
	++dir;
	dir %= RD_END;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			shape[i][j] = '0';
		}
	}

	switch (dir) {
	case RD_UP:
		// �����
		// �����
		// �����
		// �����
		shape[2][0] = '1';
		shape[3][0] = '1';
		shape[3][1] = '1';
		shape[3][2] = '1';
		widthCount = 3;
		break;
	case RD_RIGHT:
		// �����
		// �����
		// �����
		// �����
		shape[1][0] = '1';
		shape[1][1] = '1';
		shape[2][0] = '1';
		shape[3][0] = '1';
		widthCount = 2;
		break;
	case RD_DOWN:
		// �����
		// �����
		// �����
		// �����
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[2][2] = '1';
		shape[3][2] = '1';
		widthCount = 3;
		break;
	case RD_LEFT:
		// �����
		// �����
		// �����
		// �����
		shape[1][1] = '1';
		shape[2][1] = '1';
		shape[3][0] = '1';
		shape[3][1] = '1';
		widthCount = 2;
		break;
	}
}
