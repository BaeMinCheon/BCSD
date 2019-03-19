#pragma once
#include "..\Game.h"

class Scene
{
protected:

	list<class Layer *> m_LayerList;

	friend class SceneManager;

	Scene();
	virtual ~Scene() = 0;  // ���� ���� �Լ� (=> �߻� Ŭ����)

public:

	static bool LayerSort(class Layer * pL1, class Layer * pL2);

	virtual bool Init();

	class Layer * CreateLayer(const string & tag, int zOrder = 0);
};
