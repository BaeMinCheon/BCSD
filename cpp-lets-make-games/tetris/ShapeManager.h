#pragma once
#include "value.h"

class ShapeManager
{
	class Shape * pCurShape;  // ���� ���� ����
	class Shape * pNextShape;  // ������ ���� ����
	int speed;

	// �̱��� �ν��Ͻ�
	static ShapeManager * pInst;

	ShapeManager();
	~ShapeManager();

public:

	static ShapeManager * getInst() {
		if (!pInst) pInst = new ShapeManager;

		return pInst;
	}
	static void destroyInst() {
		SAFE_DELETE(pInst);
	}

	bool init();
	void run();
	void update();
	void render();
	class Shape * createRandomShape();
	class Shape * createShape(SHAPE_TYPE shapeType);
};
