// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <thread>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <process.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>
#include <functional>
#include <cstdlib>

// ��� ���� �Լ���
#include <shlwapi.h>

#include <fstream>

#include "Device.h"
#include "TextureMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
//#include "ObjFactory.h"
//#include "ObjMgr.h"
#include "SoundMgr.h"
#include <io.h>
//
//#ifdef _DEBUG
//#include <iostream>
//#include <stdio.h>
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#endif
//
//#ifdef	_DEBUG
//#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#endif // _DEBUG