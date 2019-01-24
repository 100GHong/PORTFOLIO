#pragma once
#include "Thread.h"
#include "Include.h"
#include "Socket.h"

class ClisteningThread : public CThread
{
private:
	CSocket			m_sListeningSocket;
public:
	virtual void ThreadRun() override;
	void		 Update(DWORD dwElapsedTime);

public:
	ClisteningThread();
	virtual ~ClisteningThread();
};