// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <thread>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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

// 경로 관련 함수들
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