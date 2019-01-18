#pragma once
#include "Obj.h"
class CObb :
	public CObj
{
private:
	FRAME			m_tFrame;
	float			m_fXSpeed = 0.f;
	DWORD			m_dwState = 0;
	float			m_fCollisionTime;
	float			m_fGravityTime;
	D3DXVECTOR3		m_vCollisionPos = { 0.f, 0.f, 0.f };
	D3DXVECTOR3		m_vDir = { 0.f, 0.f, 0.f };
	float			m_fGravity;
	float			m_fJumpTime;
	int				m_iHoleState = 0;
	bool				m_bOnJump = false;
	bool				m_bOnIbb = false;

private:
	void			WorldMatrix(void);
	void			FrameMove(void);
	void			Move(void);
	void			CCDCheck(void);

public:
	void				CheckDirection(void);
	const D3DXVECTOR3&	GetDir(void) { return m_vDir; }
	void				SetState(DWORD dwState) { m_dwState = dwState; }
	DWORD				GetState(void) { return m_dwState; }
	void				SetHoleState(int _istate);
	void				SetCollison(float ftime, D3DXVECTOR3 vcolpos, int inum);
	const float&		GetCollisionTime(void) { return m_fCollisionTime; }
	void				SetXdir(float _fX) { m_vDir.x = _fX; }
	void				SetXPos(float _fX) { m_tInfo.vPos.x += _fX; }
	void				SetYdir(float _fY) { m_vDir.y = _fY; }
	void				SetYPos(float _fY) { m_tInfo.vPos.y += _fY; }
	float			GetGravity(void) { return m_fGravity; }
	void				SetOnJump(bool _jump) { m_bOnJump = _jump; }
	void				SetOnIbb(void) { m_bOnIbb = true; }
	bool				GetOnJump(void) { return m_bOnJump; }

public:
	CObb();
	~CObb();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

