#include "Bullet.h"
#include "..\Resource\Texture.h"
#include "..\Collider\ColliderCircle.h"

Bullet::Bullet() :
	m_dist(0.f), m_distMax(5000.f)
{
}

Bullet::Bullet(const Bullet & bullet) :
	DynamicObject(bullet)
{
	m_dist = bullet.m_dist;
	m_distMax = bullet.m_distMax;
}

Bullet::~Bullet()
{
}

void Bullet::Hit(float deltaTime, Collider * pSrc, Collider * pDest)
{
	if (GetTag() == "PlayerBullet" && pDest->GetObj()->GetTag() == "Minion" ||
		GetTag() == "MinionBullet" && pDest->GetObj()->GetTag() == "Player")
		Die();
}

Bullet * Bullet::Clone()
{
	return new Bullet(*this);
}

bool Bullet::Init()
{
	SetSize(BULLET_WIDTH, BULLET_HEIGHT);
	SetSpeed(BULLET_SPEED);
	SetTexture("Bullet", BULLET_TEXTURE);

	ColliderCircle * pCollCircle = AddCollider<ColliderCircle>("Bullet");
	pCollCircle->SetCircle(POSITION(0.f, 0.f), BULLET_RADIUS);

	SAFE_RELEASE(pCollCircle);

	return true;
}

int Bullet::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	MoveAngle(deltaTime);

	m_dist += GetSpeed() * deltaTime;

	if (m_dist > m_distMax)
		Die();

	return 0;
}

int Bullet::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Bullet::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Bullet::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);

	//POSITION pos = m_pos - m_size * m_pivot;
	//Ellipse(hDC, (int)pos.x, (int)pos.y, (int)(pos.x + m_size.x), (int)(pos.y + m_size.y));
}
