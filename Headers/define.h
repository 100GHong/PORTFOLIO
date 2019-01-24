#pragma once

#define NO_COPY(CLASSNAME)							\
	private:										\
	CLASSNAME(const CLASSNAME&);					\
	CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)				\
	NO_COPY(CLASSNAME)								\
	private:										\
	static CLASSNAME*	m_pInstance;				\
	public:											\
	static CLASSNAME*	GetInstance( void );		\
	static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
	CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
	CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
	if(NULL == m_pInstance) {						\
	m_pInstance = new CLASSNAME;					\
	}												\
	return m_pInstance;								\
	}												\
	void CLASSNAME::DestroyInstance( void ) {		\
	if(NULL != m_pInstance)	{						\
	delete m_pInstance;								\
	m_pInstance = NULL;								\
	}												\
	}

#define ERR_MSG(Message)		MessageBox(g_hWnd, Message, L"System Error", NULL)
#define ERROR_CHECK(x)			(x != 0)
#define GET_TIME				CTimeMgr::GetInstance()->GetTime()

#define GAME_PORT_FIRST			6658
#ifndef CONCATENATE
#define CONCATENATE( arg1, arg2 )   _CONCATENATE1( arg1, arg2 )
#define _CONCATENATE1( arg1, arg2 )  _CONCATENATE2( arg1, arg2 )
#define _CONCATENATE2( arg1, arg2 )  arg1##arg2
#endif