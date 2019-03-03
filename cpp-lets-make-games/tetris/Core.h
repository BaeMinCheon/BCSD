#pragma once
#include "value.h"

class Core
{
	// �̱��� �ν��Ͻ�
	static Core * pInst;
	
	// Ŀ�� ����
	HANDLE consoleHandle;

	Core();
	~Core();

public:

	static Core * getInst() {
		if (!pInst) pInst = new Core;
		
		return pInst;
	}
	
	static void destroyInst() {
		SAFE_DELETE(pInst);
	}

	bool init();
	void run();
	void setConsolePos(int y, int x);
};
