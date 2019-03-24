#include "Texture.h"
#include "..\Core\PathManager.h"

Texture::Texture() :
	m_hMemDC(NULL), m_hasColorKey(true), m_colorKey(COLORKEY_DEFAULT)
{
}

Texture::~Texture()
{
	// ���� ���� ����
	SelectObject(m_hMemDC, m_hBitmapOld);

	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

bool Texture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & key, const wchar_t * pFileName, const string & pathKey)
{
	// �޸� DC
	m_hMemDC = CreateCompatibleDC(hDC);

	// ���� ���
	const wchar_t * pPath = GET_SINGLE(PathManager)->FindPath(pathKey);
	wstring strPath;
	
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// �� ��Ʈ�� ������ DC�� �����ϰ� ���� ��Ʈ�� ���� ����
	m_hBitmapOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	// �ڵ鿡�� ��Ʈ�� ���� Get
	GetObject(m_hBitmap, sizeof(m_bitmapInfo), &m_bitmapInfo);

	return true;
}
