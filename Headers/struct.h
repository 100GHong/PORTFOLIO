#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3					vPos;
	D3DXVECTOR3					vSize;
	D3DXVECTOR3					vScale;
	D3DXMATRIX					matWorld;
	UINT						iType;
	WCHAR						ObjKey[MIN_STR];
	WCHAR						StateKey[MIN_STR];
}INFO;

typedef struct tagServerData
{
	float			fPosX;
	float			fPosY;
	char			cState;// 0x00000000.  MSB가 state, LSB가 frame
}SData;

typedef struct tagClientData
{
	USHORT		m_iKey;
	POINT		m_vMouse;
}CData;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;
	D3DXIMAGE_INFO			tImgInfo;
}TEXINFO;

typedef struct tagRect
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	RECTTYPE		eType;
}tRECT;

typedef struct tagBackOBJ
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vScale;
	int				iDrawID;
	BACKTYPE		eType;
}bOBJ;

typedef struct tagMonsterData
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vScale;
	POINT			ptStart;
	POINT			ptEnd;
	MONSTERTYPE		eType;
}MON;

typedef struct tagSupport
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vScale;
	SUPPORTTYPE		eType;
}SUP;

typedef struct tagTexturePath
{
	std::wstring		wstrObjKey;		// 이미지 종류
	std::wstring		wstrStateKey;	// 이미지 상태
	std::wstring		wstrPath;		// 이미지 경로
	int					iCount;		    // 이미지 개수

	tagTexturePath() : wstrObjKey(L""), wstrStateKey(L""), 
		wstrPath(L""), iCount(0)
	{}
}IMGPATH;

typedef struct tagFrame
{
	float	fFrame;
	float	fCount;
	float	fMax;

	tagFrame(void) {}
	tagFrame(float _fFrame, float _fCount, float _fMax)
		: fFrame(_fFrame), fCount(_fCount), fMax(_fMax)
	{

	}
}FRAME;

typedef struct tagAStarNode
{
	float				fCost;
	int					iIndex;
	tagAStarNode*		pParent;
}NODE;