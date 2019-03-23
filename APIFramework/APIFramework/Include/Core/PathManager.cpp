#include "PathManager.h"

DEFINE_SINGLE(PathManager);

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

bool PathManager::Init()
{
	wchar_t strPath[MAX_PATH] = { };

	GetModuleFileName(NULL, strPath, MAX_PATH);

	// ���� ���� �̸� ����
	for (int i = lstrlen(strPath) - 1; i >= 0; --i)
	{
		if (strPath[i] == '/' || strPath[i] == '\\')
		{
			memset(strPath + (i + 1), 0, sizeof(wchar_t) * (MAX_PATH - (i + 1)));
			break;
		}
	}

	m_mapPath.insert(make_pair(PATH_ROOT, strPath));

	// Textures �н� ����
	if (!CreatePath(PATH_TEXTURE, L"textures\\"))
		return false;

	return true;
}

bool PathManager::CreatePath(const string & key, const wchar_t * pPath, const string & baseKey)
{
	const wchar_t * pBasePath = FindPath(baseKey);
	wstring strPath;

	if (pBasePath)
		strPath = pBasePath;

	strPath += pPath;

	m_mapPath.insert(make_pair(key, strPath));

	return true;
}

const wchar_t * PathManager::FindPath(const string & key)
{
	unordered_map<string, wstring>::iterator iter = m_mapPath.find(key);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second.c_str();
}
