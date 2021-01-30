// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com


#include "common/common.h"
#include "server/kbemain.h"
#include "machine.h"

#undef DEFINE_IN_INTERFACE
#include "baseappmgr/baseappmgr_interface.h"
#define DEFINE_IN_INTERFACE
#include "baseappmgr/baseappmgr_interface.h"

#undef DEFINE_IN_INTERFACE
#include "cellappmgr/cellappmgr_interface.h"
#define DEFINE_IN_INTERFACE
#include "cellappmgr/cellappmgr_interface.h"

#undef DEFINE_IN_INTERFACE
#include "cellapp/cellapp_interface.h"
#define DEFINE_IN_INTERFACE
#include "cellapp/cellapp_interface.h"

#undef DEFINE_IN_INTERFACE
#include "baseapp/baseapp_interface.h"
#define DEFINE_IN_INTERFACE
#include "baseapp/baseapp_interface.h"

#undef DEFINE_IN_INTERFACE
#include "dbmgr/dbmgr_interface.h"
#define DEFINE_IN_INTERFACE
#include "dbmgr/dbmgr_interface.h"

#undef DEFINE_IN_INTERFACE
#include "loginapp/loginapp_interface.h"
#define DEFINE_IN_INTERFACE
#include "loginapp/loginapp_interface.h"

#undef DEFINE_IN_INTERFACE
#include "tools/logger/logger_interface.h"
#define DEFINE_IN_INTERFACE
#include "tools/logger/logger_interface.h"

#undef DEFINE_IN_INTERFACE
#include "tools/interfaces/interfaces_interface.h"
#define DEFINE_IN_INTERFACE
#include "tools/interfaces/interfaces_interface.h"

#undef DEFINE_IN_INTERFACE
#include "tools/bots/bots_interface.h"
#define DEFINE_IN_INTERFACE
#include "tools/bots/bots_interface.h"

using namespace KBEngine;

int KBENGINE_MAIN(int argc, char* argv[])
{
	sleep(10000);

#if KBE_PLATFORM != PLATFORM_WIN32
	/*
	每个进程在运行时系统不会无限制的允许单个进程不断的消耗资源，因此都会设置资源限制。
	Linux系统中使用resource limit来表示，每个进程都可以设置不同的资源限制，当前进程和其以后fork的子进程会遵循此限制，
	而其他进程不受当前进程条件的影响。最后还有一点，如果读取和设置的rlimit中的值为RLIM_INFINITY宏，那么表示是无限制。
	https://blog.csdn.net/rikeyone/article/details/88798384
	*/
	rlimit rlimitData = { RLIM_INFINITY, RLIM_INFINITY };
	setrlimit(RLIMIT_CORE, &rlimitData);
#endif
	
	ENGINE_COMPONENT_INFO& info = g_kbeSrvConfig.getKBMachine();
	int ret = kbeMainT<Machine>(argc, argv, MACHINE_TYPE, info.externalTcpPorts_min, 
		info.externalTcpPorts_max, -1, -1, "", 0, 0, info.internalInterface);
	return ret; 
}
