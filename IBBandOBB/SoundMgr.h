#pragma once
// FMOD ��� ���̺귯���� ����ϱ� ���� ����� ���̺귯���� �߰��Ѵ�.
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
	// �̱���
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
	FMOD_SYSTEM*	m_pSystem;	// ���� �ý��� �Ѱ� ������
	FMOD_CHANNEL*	m_pChannelArr[CHANNEL_END]; // ���带 ����ϱ� ���� ä�� �迭
												// FMOD_SOUND:���� ���ҽ� ������ ���� ���� Ÿ��
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;
};

