#pragma once
// FMOD 상용 라이브러리르 사용하기 위해 헤더와 라이브러리를 추가한다.
#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")


#pragma once
#include "Include.h"
class CSoundMgr
{
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize();
	void Update();
	void Release();

public:
	void LoadSoundFile();
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopSoundAll();
	void SetVolume(CHANNELID eID, float fVolume);

public:
	// 싱글톤
	static CSoundMgr* GetInst()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr;

		return m_pInstance;
	}

	void DestroyInst()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSoundMgr* m_pInstance;
	FMOD_SYSTEM*	m_pSystem;	// 사운드 시스템 총괄 관리자
	FMOD_CHANNEL*	m_pChannelArr[CHANNEL_END]; // 사운드를 재생하기 위한 채널 배열
												// FMOD_SOUND:사운드 리소스 정보를 갖는 사운드 타입
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;
};

