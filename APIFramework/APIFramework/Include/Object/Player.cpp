#include "Player.h"
#include "..\Core\Core.h"
#include "..\Core\InputManager.h"
#include "..\Collider\ColliderRect.h"

Player::Player() :
	m_fireTime(0.f), m_firePeriod(0.1f)
{
}

Player::Player(const Player & player) :
	DynamicObject(player)
{
	m_fireTime = player.m_fireTime;
	m_firePeriod = player.m_firePeriod;
}

Player::~Player()
{
}

void Player::Fire()
{
	if (m_fireTime <= m_firePeriod)
		return;

	m_fireTime = 0.f;
	float theta = -0.1f * PI;
	for (int i = 0; i < 3; ++i)
	{
		Object * pBullet = Object::CloneObject("Bullet", "PlayerBullet", m_pLayer);

		POSITION pos;
		pos.x = m_pos.x + m_size.x * (1.f - m_pivot.x);
		pos.y = m_pos.y + m_size.y * (0.5f - m_pivot.y);

		pBullet->SetPos(pos.x, pos.y);
		((DynamicObject *)pBullet)->SetAngle(theta);

		theta += 0.1f * PI;

		SAFE_RELEASE(pBullet);
	}
}

void Player::CollisionBullet(float deltaTime, Collider * pSrc, Collider * pDest)
{
	if (pDest->GetObj()->GetTag() == "MinionBullet")
		MessageBox(NULL, L"�浹�߽��ϴ�", L"�浹", MB_OK);
}

Player * Player::Clone()
{
	return new Player(*this);
}

bool Player::Init()
{
	SetPos(100.f, 100.f);
	SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	SetSpeed(PLAYER_SPEED);
	SetTexture("Player", PLAYER_TEXTURE_NORMAL);

	ColliderRect * pCollRect = AddCollider<ColliderRect>("Player");
	pCollRect->SetRect(-MINION_WIDTH * 0.5f, -MINION_HEIGHT * 0.5f, MINION_WIDTH * 0.5f, MINION_HEIGHT * 0.5f);
	pCollRect->AddCollisionFunc(CS_ENTER, this, &Player::CollisionBullet);

	return true;
}

void Player::Input(float deltaTime)
{
	DynamicObject::Input(deltaTime);

	if (KEYPRESS("MoveUp"))
	{
		MoveY(deltaTime, MD_BACK);
	}
	if (KEYPRESS("MoveDown"))
	{
		MoveY(deltaTime, MD_FRONT);
	}
	if (KEYPRESS("MoveLeft"))
	{
		MoveX(deltaTime, MD_BACK);
	}
	if (KEYPRESS("MoveRight"))
	{
		MoveX(deltaTime, MD_FRONT);
	}
	if (KEYPRESS("Fire"))
	{
		Fire();
	}
	if (KEYPRESS("Slow"))
		SetSpeed(PLAYER_SPEED_SLOW);
	else
		SetSpeed(PLAYER_SPEED);
}

int Player::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// �̵� ����
	m_pos.x = (m_pos.x <= 0) ? 0.f : (m_pos.x >= GET_RESOLUTION.w) ? (float)GET_RESOLUTION.w : m_pos.x;
	m_pos.y = (m_pos.y <= 0) ? 0.f : (m_pos.y >= GET_RESOLUTION.h) ? (float)GET_RESOLUTION.h : m_pos.y;

	// �߻� ����
	m_fireTime += deltaTime;

	return 0;
}

int Player::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Player::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Player::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);
}
