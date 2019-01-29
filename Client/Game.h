#pragma once
#include "Scene.h"
#include "Stage.h"
class CLobby;
class CStage1;
class CStage2;
class CStage3;
class CBubble;

class CGame :
	public CScene
{
private:
	CStage*				m_pLobby = nullptr;
	CStage*				m_pStage1 = nullptr;
	CStage*				m_pStage2 = nullptr;
	CStage*				m_pStage3 = nullptr;
	int					m_iCurStage = 0;
	CObj*				m_pIbb = nullptr;
	CObj*				m_pObb = nullptr;
	D3DXVECTOR3			m_vMouse;
	list<CBubble*>		m_Effectlist;

private:
	void			CameraProgress(void);

public:
	void			SetStage(int& rNum) { m_iCurStage = rNum; }
	const CStage*	GetStage(int _istage) {
		switch (_istage)
		{
		case 0: return m_pLobby; break;
		case 1: return m_pStage1; break;
		case 2: return m_pStage2; break;
		case 3: return m_pStage3; break;
		}
	}

public:
	CGame();
	virtual ~CGame();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

