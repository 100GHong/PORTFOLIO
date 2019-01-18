#pragma once
#include "Stage.h"
class CLobby :
	public CStage
{
private:
	void			LoadData(void);
	void			RenderBack(void);

public:
	void			CollisionCheck(void);

public:
	CLobby();
	virtual ~CLobby();

	// CStage��(��) ���� ��ӵ�
	virtual HRESULT Initialize(void) override;
	virtual int Progress(void) override;
	virtual void Render(void) override;
	virtual void Release(void) override;
};