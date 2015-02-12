/******************************************************************************
 *
 * Copyright (c) 1997-1999 Palm Computing, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: ExgLib.h
 *
 * Description:
 *		Include file the Exchange Library interface. The Exchange Library is a
 *		generic interface to any number of librarys. Any Exchange Library
 *		MUST have entrypoint traps in exactly the order listed here.
 *		The System Exchange manager functions call these functions when 
 *		applications make calls to the Exchange manager. Applications will
 *		usually not make direct calls to this API.
 *
 * History:
 *   	5/23/97 Created by Gavin Peacock
 *
 *****************************************************************************/

#ifndef __EXGLIB_H__
#define __EXGLIB_H__

#include <PalmTypes.h>
#include <LibTraps.h>
#include <ExgMgr.h>

// special exchange mgr event key
#define exgIntDataChr 0x01ff

//-----------------------------------------------------------------------------
// 	Obx library call ID's. Each library call gets the trap number:
//   exgTrapXXXX which serves as an index into the library's dispatch table.
//   The constant sysLibTrapCustom is the first available trap number after
//   the system predefined library traps Open,Close,Sleep & Wake.
//
// WARNING!!! This order of these traps MUST match the order of the dispatch
//  table in and Exchange library!!!
//-----------------------------------------------------------------------------

#ifdef __GNUC__

#define exgLibTrapHandleEvent		(sysLibTrapCustom)
#define exgLibTrapConnect			(sysLibTrapCustom+1)
#define exgLibTrapAccept			(sysLibTrapCustom+2)
#define exgLibTrapDisconnect		(sysLibTrapCustom+3)
#define exgLibTrapPut				(sysLibTrapCustom+4)
#define exgLibTrapGet				(sysLibTrapCustom+5)
#define exgLibTrapSend				(sysLibTrapCustom+6)
#define exgLibTrapReceive			(sysLibTrapCustom+7)
#define exgLibTrapControl			(sysLibTrapCustom+8)
#define exgLibReserved1				(sysLibTrapCustom+9)
#define exgLibTrapLast				(sysLibTrapCustom+10)

#else

#pragma mark Traps
typedef enum {
	exgLibTrapHandleEvent = sysLibTrapCustom,
	exgLibTrapConnect,
	exgLibTrapAccept,
	exgLibTrapDisconnect,
	exgLibTrapPut,
	exgLibTrapGet,
	exgLibTrapSend,
	exgLibTrapReceive,
	exgLibTrapControl,
	exgLibReserved1,
	exgLibTrapLast
	} ExgLibTrapNumberEnum;

#endif


/************************************************************
 * Net Library procedures.
 *************************************************************/ 
#pragma mark Functions
#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------
// Library initialization, shutdown, sleep and wake
//--------------------------------------------------
// Open the library - enable server for receiving data.
Err		ExgLibOpen (UInt16 libRefnum)
			SYS_TRAP(sysLibTrapOpen);
					
Err		ExgLibClose (UInt16 libRefnum)
			SYS_TRAP(sysLibTrapClose);
					
Err		ExgLibSleep (UInt16 libRefnum)
			SYS_TRAP(sysLibTrapSleep);
					
Err		ExgLibWake (UInt16 libRefnum)
			SYS_TRAP(sysLibTrapWake);
					
//	MemHandle events that this library needs. This will be called by
//	sysHandle event when certain low level events are triggered.					
Err		ExgLibHandleEvent(UInt16 libRefnum,void *eventP)
			SYS_TRAP(exgLibTrapHandleEvent);
						
//  Establish a new connection 						
Err	 	ExgLibConnect(UInt16 libRefNum,ExgSocketPtr exgSocketP)
			SYS_TRAP(exgLibTrapConnect);

// Accept a connection request from remote end
Err		ExgLibAccept(UInt16 libRefnum,ExgSocketPtr exgSocketP)
			SYS_TRAP(exgLibTrapAccept);

// Disconnect
Err		ExgLibDisconnect(UInt16 libRefnum,ExgSocketPtr exgSocketP,Err error)
			SYS_TRAP(exgLibTrapDisconnect);

// Initiate a Put command. This passes the name and other information about
// an object to be sent
Err		ExgLibPut(UInt16 libRefnum,ExgSocketPtr exgSocketP)
			SYS_TRAP(exgLibTrapPut);

// Initiate a Get command. This requests an object from the remote end.
Err		ExgLibGet(UInt16 libRefNum,ExgSocketPtr exgSocketP)
			SYS_TRAP(exgLibTrapGet);

// Send data to remote end - called after a Put command
UInt32 	ExgLibSend(UInt16 libRefNum, ExgSocketPtr exgSocketP, const void * const bufP, const UInt32 bufLen, Err *errP)
			SYS_TRAP(exgLibTrapSend);

// Receive data from remote end -- called after Accept
UInt32 	ExgLibReceive(UInt16 libRefNum, ExgSocketPtr exgSocketP, void *bufP, const UInt32 bufSize, Err *errP)
			SYS_TRAP(exgLibTrapReceive);

// Send various option commands to the Exg library
Err 	ExgLibControl(UInt16 libRefNum, UInt16 op, void *valueP, UInt16 *valueLenP)
			SYS_TRAP(exgLibTrapControl);

						
#ifdef __cplusplus
}
#endif

#endif  // __EXGLIB_H__

