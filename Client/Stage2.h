#pragma once
#include "Stage.h"
class CStage2 :
	public CStage
{
private:
	void			LoadData(void);
	void			RenderBack(void);

public:
	void			CollisionCheck(void);	

public:
	CStage2();
	virtual ~CStage2();

	// CStage을(를) 통해 상속됨
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

