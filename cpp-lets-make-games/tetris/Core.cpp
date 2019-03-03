#include "pch.h"
#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

Core * Core::pInst = nullptr;

Core::Core()
{
	srand((unsigned int)time(0));
}

Core::~Core()
{
	ShapeManager::destroyInst();
	StageManager::destroyInst();
}

bool Core::init()
{
	// �ܼ� �ڵ� ����
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (consoleHandle == INVALID_HANDLE_VALUE) return false;

	if (!StageManager::getInst()->init()) return false;

	return true;
}

void Core::run()
{
	while (true) {
		system("cls");
		ShapeManager::getInst()->update();
		StageManager::getInst()->run();
		ShapeManager::getInst()->render();
		Sleep(100);
	}
}

void Core::setConsolePos(int y, int x)
{
	COORD coord;
	coord.Y = y;
	coord.X = (x + 1) * 2;  // �� ����. �� ĭ�� 2����Ʈ
	SetConsoleCursorPosition(consoleHandle, coord);
}
