#pragma once
#include "Stage.h"
class CStage1 :
	public CStage
{
private:
	void			LoadData(void);
	void			RenderBack(void);

public:
	void			CollisionCheck(void);

public:
	CStage1();
	virtual ~CStage1();

	// CStage��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};

