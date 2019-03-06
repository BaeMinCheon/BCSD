#include "pch.h"
#include "StageManager.h"
#include "Stage.h"
#include "ShapeManager.h"
#include "Rectangle.h"
#include "ShapeI.h"
#include "ShapeL.h"
#include "ShapeLReversed.h"
#include "ShapeS.h"
#include "ShapeT.h"
#include "ShapeZ.h"

ShapeManager *ShapeManager::pInst = nullptr;

ShapeManager::ShapeManager() :
	pCurShape(nullptr), pNextShape(nullptr), speed(0)
{
	pCurShape = createRandomShape();
	pCurShape->setPos(0, 4);

	pNextShape = createRandomShape();
}

ShapeManager::~ShapeManager()
{
	SAFE_DELETE(pCurShape);
	SAFE_DELETE(pNextShape);
}

bool ShapeManager::init()
{
	return false;
}

void ShapeManager::run()
{
}

void ShapeManager::update()
{
	Stage * pStage = StageManager::getInst()->getCurStage();

	// speed�� stage.speed�� �����ϸ�
	++speed;
	if (pStage->getSpeed() == speed) {
		// ���� �Ʒ��� ����
		// �ٴڿ� ���� ��� ���������� �ݿ��ϰ� ���� ������ ���� ��������
		if (pCurShape->moveDown()) {
			pStage->addBlock(pCurShape);

			SAFE_DELETE(pCurShape);

			pCurShape = pNextShape;
			pCurShape->setPos(0, 4);

			pNextShape = createRandomShape();
		}
		speed = 0;
	}

	if (GetAsyncKeyState('A') & 0x8000) {
		pCurShape->moveLeft();
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		pCurShape->moveRight();
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		pCurShape->moveDown();
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		pCurShape->rotate();
	}
}

void ShapeManager::render()
{
	// ���� ���� render
	pCurShape->render();

	// ���� ���� render
	pNextShape->setPos(4, 12);
	pNextShape->renderNext();
}

Shape * ShapeManager::createRandomShape()
{
	int type = rand() % ST_END;

	return createShape((SHAPE_TYPE)type);
}

Shape * ShapeManager::createShape(SHAPE_TYPE shapeType)
{
	Shape * pShape = nullptr;

	switch (shapeType) {
	case ST_RECT:
		pShape = new class Rectangle;
		break;
	case ST_I:
		pShape = new class ShapeI;
		break;
	case ST_L:
		pShape = new class ShapeL;
		break;
	case ST_L_REVERSED:
		pShape = new class ShapeLReversed;
		break;
	case ST_S:
		pShape = new class ShapeS;
		break;
	case ST_T:
		pShape = new class ShapeT;
		break;
	case ST_Z:
		pShape = new class ShapeZ;
		break;
	}

	if (!pShape->init()) return nullptr;

	return pShape;
}
