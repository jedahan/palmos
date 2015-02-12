/******************************************************************************
 *
 * Copyright (c) 1998-1999 Palm Computing, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: HostControl.h
 *
 * History:
 *		August 17, 1998	Created by Roger Flores/Douglas Anderson
 *
 *****************************************************************************/

#ifndef __HOSTCONTROL_H__
#define __HOSTCONTROL_H__

#include <PalmTypes.h>
#include <CoreTraps.h>

/*
	Set the base value for selectors. Note that this value MUST be
	two bytes long and have the high byte be non-zero. The reason
	for this has to do with the way SysGremlins was originally
	declared. It took a GremlinsSelector enumerated value. Originally,
	there was only one value, and it was zero. The way the 68K compiler
	works, it decides that GremlinsSelectors are only one byte long,
	so a call to SysGremlins would push one byte onto the stack. Because
	all values on the stack need to be word-aligned, the processor
	subtracts 1 from the stack before pushing on the byte. Therefore,
	the stack looks like:

			previous contents
			garbage byte
			selector
			return address

	With this setup, we have two choices: leave the selector size at
	one byte and limit ourselves to 256 functions, or define the selector
	to be a two byte value, with the first 256 values (all those with 0x00
	in the upper byte) to be GremlinIsOn. The latter sounds preferable, so
	we start the new selectors at 0x0100.
*/

#define hostSelectorBase	0x0100

#ifdef __GNUC__

	// Host information selectors

#define hostSelectorGetHostVersion			0x0100
#define hostSelectorGetHostID					0x0101
#define hostSelectorGetHostPlatform			0x0102
#define hostSelectorIsSelectorImplemented	0x0103
#define hostSelectorGestalt					0x0104
#define hostSelectorIsCallingTrap			0x0105

	// Profiler selectors

#define hostSelectorProfileInit				0x0200
#define hostSelectorProfileStart				0x0201
#define hostSelectorProfileStop				0x0202
#define hostSelectorProfileDump				0x0203
#define hostSelectorProfileCleanup			0x0204

	// Std C Library wrapper selectors

#define hostSelectorErrNo						0x0300

#define hostSelectorFClose						0x0301
#define hostSelectorFEOF						0x0302
#define hostSelectorFError						0x0303
#define hostSelectorFFlush						0x0304
#define hostSelectorFGetC						0x0305
#define hostSelectorFGetPos					0x0306
#define hostSelectorFGetS						0x0307
#define hostSelectorFOpen						0x0308
#define hostSelectorFPrintF					0x0309		/* Floating point not yet supported in Poser */
#define hostSelectorFPutC						0x030A
#define hostSelectorFPutS						0x030B
#define hostSelectorFRead						0x030C
#define hostSelectorRemove						0x030D		/* Not yet implemented in Poser */
#define hostSelectorRename						0x030E		/* Not yet implemented in Poser */
#define hostSelectorFReopen					0x030F		/* Not yet implemented in Poser */
#define hostSelectorFScanF						0x0310		/* Not yet implemented */
#define hostSelectorFSeek						0x0311
#define hostSelectorFSetPos					0x0312
#define hostSelectorFTell						0x0313
#define hostSelectorFWrite						0x0314
#define hostSelectorTmpFile					0x0315
#define hostSelectorTmpNam						0x0316		/* Not yet implemented in Poser */
#define hostSelectorGetEnv						0x0317

#define hostSelectorMalloc						0x0318		/* Not yet implemented in Poser */
#define hostSelectorRealloc					0x0319		/* Not yet implemented in Poser */
#define hostSelectorFree						0x031A		/* Not yet implemented in Poser */

	// Gremlin selectors

#define hostSelectorGremlinIsRunning		0x0400
#define hostSelectorGremlinNumber			0x0401
#define hostSelectorGremlinCounter			0x0402
#define hostSelectorGremlinLimit				0x0403
//#define hostSelectorGremlinApp				0x0404

	// Database selectors

#define hostSelectorImportFile				0x0500
#define hostSelectorExportFile				0x0501

	// Preferences selectors

#define hostSelectorSetDebugOption			0x0600		/* Not yet implemented */
#define hostSelectorSetWindowScale			0x0601		/* Not yet implemented */
#define hostSelectorSetWindowBackground	0x0602		/* Not yet implemented */

	// Logging selectors

#define hostSelectorLogFile					0x0700
#define hostSelectorSetLogFileSize			0x0701

#define hostSelectorLastTrapNumber			0x0702

typedef UInt16 HostControlTrapNumber;

#else

#define hostSelectorChunk	0x0100
#define hostSection(x)		(hostSelectorBase + (hostSelectorChunk * (x)))

typedef enum
{
	// Host information selectors

	hostSelectorGetHostVersion = hostSection(0),
	hostSelectorGetHostID,
	hostSelectorGetHostPlatform,
	hostSelectorIsSelectorImplemented,
	hostSelectorGestalt,
	hostSelectorIsCallingTrap,

	// Profiler selectors

	hostSelectorProfileInit = hostSection(1),
	hostSelectorProfileStart,
	hostSelectorProfileStop,
	hostSelectorProfileDump,
	hostSelectorProfileCleanup,

	// Std C Library wrapper selectors

	hostSelectorErrNo = hostSection(2),

	hostSelectorFClose,
	hostSelectorFEOF,
	hostSelectorFError,
	hostSelectorFFlush,
	hostSelectorFGetC,
	hostSelectorFGetPos,
	hostSelectorFGetS,
	hostSelectorFOpen,
	hostSelectorFPrintF,		// Floating point not yet supported in Poser
	hostSelectorFPutC,
	hostSelectorFPutS,
	hostSelectorFRead,
	hostSelectorRemove,		// Not yet implemented in Poser
	hostSelectorRename,		// Not yet implemented in Poser
	hostSelectorFReopen,		// Not yet implemented in Poser
	hostSelectorFScanF,		// Not yet implemented
	hostSelectorFSeek,
	hostSelectorFSetPos,
	hostSelectorFTell,
	hostSelectorFWrite,
	hostSelectorTmpFile,
	hostSelectorTmpNam,		// Not yet implemented in Poser
	hostSelectorGetEnv,

	hostSelectorMalloc,		// Not yet implemented in Poser
	hostSelectorRealloc,		// Not yet implemented in Poser
	hostSelectorFree,			// Not yet implemented in Poser
	
	// Gremlin selectors

	hostSelectorGremlinIsRunning = hostSection(3),
	hostSelectorGremlinNumber,
	hostSelectorGremlinCounter,
	hostSelectorGremlinLimit,
//	hostSelectorGremlinApp,

	// Database selectors

	hostSelectorImportFile = hostSection(4),
	hostSelectorExportFile,

	// Preferences selectors

	hostSelectorSetDebugOption = hostSection(5),	// Not yet implemented
	hostSelectorSetWindowScale,							// Not yet implemented
	hostSelectorSetWindowBackground,					// Not yet implemented

	// Logging selectors

	hostSelectorLogFile = hostSection(6),
	hostSelectorSetLogFileSize,

	hostSelectorLastTrapNumber
} HostControlTrapNumber;

#endif


typedef struct HostControlParamsType
{
	long unused;
} HostControlParamsType;



typedef struct HostFILE
{
	long	_field;
} HostFILE;



typedef long	HostBool;
typedef long	HostErr;
typedef long	HostID;
typedef long	HostPlatform;
typedef long	HostBG;

#ifndef hostErrorClass
	#define	hostErrorClass				0x1C00	// Host Control Manager
#else
	#if hostErrorClass != 0x1C00
		#error "You cannot change hostErrorClass without telling us."
	#endif
#endif

enum	// HostErr values
{
	hostErrNone = 0,

	hostErrBase = hostErrorClass,

	hostErrUnknownGestaltSelector,

	hostErrDiskError,

	hostErrOutOfMemory,
	hostErrMemReadOutOfRange,
	hostErrMemWriteOutOfRange,
	hostErrMemInvalidPtr,

	hostErrInvalidParameter
};


enum	// HostID values
{
	hostIDPalmOS,
	hostIDPalmOSEmulator,	// The Copilot thingy
	hostIDPalmOSSimulator	// The Mac libraries you link with thingy
};


enum	// HostPlatform values
{
	hostPlatformPalmOS,
	hostPlatformWindows,
	hostPlatformMacintosh,
	hostPlatformUnix
};


enum	// HostBG values
{
	hostBGGray,
	hostBGWhite
};

#define HOST_TRAP(selector) \
	_SYSTEM_API(_CALL_WITH_16BIT_SELECTOR)(_SYSTEM_TABLE, sysTrapHostControl, \
														selector)

#ifdef __cplusplus
extern "C" {
#endif


long				HostGetHostVersion			(void)												HOST_TRAP (hostSelectorGetHostVersion);
HostID			HostGetHostID					(void)												HOST_TRAP (hostSelectorGetHostID);
HostPlatform	HostGetHostPlatform			(void)												HOST_TRAP (hostSelectorGetHostPlatform);
HostBool			HostIsSelectorImplemented	(long selector)									HOST_TRAP (hostSelectorIsSelectorImplemented);
HostErr			HostGestalt						(long gestSel, long* response)				HOST_TRAP (hostSelectorGestalt);
HostBool			HostIsCallingTrap				(void)												HOST_TRAP (hostSelectorIsCallingTrap);

HostErr			HostProfileInit				(long maxCalls, long maxDepth)				HOST_TRAP (hostSelectorProfileInit);
HostErr			HostProfileStart				(void)												HOST_TRAP (hostSelectorProfileStart);
HostErr			HostProfileStop				(void)												HOST_TRAP (hostSelectorProfileStop);
HostErr			HostProfileDump				(const char *filename)							HOST_TRAP (hostSelectorProfileDump);
HostErr			HostProfileCleanup			(void)												HOST_TRAP (hostSelectorProfileCleanup);

long				HostErrNo						(void)												HOST_TRAP (hostSelectorErrNo);

long				HostFClose						(HostFILE* f)										HOST_TRAP (hostSelectorFClose);
long				HostFEOF							(HostFILE* f)										HOST_TRAP (hostSelectorFEOF);
long				HostFError						(HostFILE* f)										HOST_TRAP (hostSelectorFError);
long				HostFFlush						(HostFILE* f)										HOST_TRAP (hostSelectorFFlush);
long				HostFGetC						(HostFILE* f)										HOST_TRAP (hostSelectorFGetC);
long				HostFGetPos						(HostFILE* f, long* posP)						HOST_TRAP (hostSelectorFGetPos);
char*				HostFGetS						(char *s, long n, HostFILE* f)				HOST_TRAP (hostSelectorFGetS);
HostFILE*		HostFOpen						(const char *name, const char *mode)		HOST_TRAP (hostSelectorFOpen);
long				HostFPrintF						(HostFILE* f, const char *fmt, ...)			HOST_TRAP (hostSelectorFPrintF);
long				HostFPutC						(long c, HostFILE* f)							HOST_TRAP (hostSelectorFPutC);
long				HostFPutS						(const char *s, HostFILE* f)					HOST_TRAP (hostSelectorFPutS);
long				HostFRead						(void *buffer, long size, long count, HostFILE* f)
																												HOST_TRAP (hostSelectorFRead);
long				HostRemove						(const char *name)								HOST_TRAP (hostSelectorRemove);
long				HostRename						(const char *oldName, const char *newName) HOST_TRAP (hostSelectorRename);
HostFILE*		HostFReopen						(const char *name, const char *mode, HostFILE *f)
																												HOST_TRAP (hostSelectorFReopen);
long				HostFScanF						(HostFILE* f, const char *fmt, ...)			HOST_TRAP(hostSelectorFScanF);
long				HostFSeek						(HostFILE* f, long offset, long origin)	HOST_TRAP (hostSelectorFSeek);
long				HostFSetPos						(HostFILE* f, long* pos)						HOST_TRAP (hostSelectorFSetPos);
long				HostFTell						(HostFILE* f)										HOST_TRAP (hostSelectorFTell);
long				HostFWrite						(const void *buffer, long size, long count, HostFILE* f)
																												HOST_TRAP (hostSelectorFWrite);
HostFILE*		HostTmpFile						(void)												HOST_TRAP (hostSelectorTmpFile);
char*				HostTmpNam						(char *name)										HOST_TRAP (hostSelectorTmpNam);
char*				HostGetEnv						(const char *name)								HOST_TRAP (hostSelectorGetEnv);

void*				HostMalloc						(long size)											HOST_TRAP (hostSelectorMalloc);
void*				HostRealloc						(void *p, long size)								HOST_TRAP (hostSelectorRealloc);
void				HostFree							(void *p)											HOST_TRAP (hostSelectorFree);

HostBool			HostGremlinIsRunning			(void)												HOST_TRAP (hostSelectorGremlinIsRunning);
long				HostGremlinNumber				(void)												HOST_TRAP (hostSelectorGremlinNumber);
long				HostGremlinCounter			(void)												HOST_TRAP (hostSelectorGremlinCounter);
long				HostGremlinLimit				(void)												HOST_TRAP (hostSelectorGremlinLimit);

HostErr			HostImportFile					(const char *fileName, long cardNum)		HOST_TRAP (hostSelectorImportFile);
HostErr			HostExportFile					(const char *fileName, long cardNum, const char *dbName)
																												HOST_TRAP (hostSelectorExportFile);

HostBool			HostSetDebugOption			(HostBool newSetting)							HOST_TRAP (hostSelectorSetDebugOption);
long				HostSetWindowScale			(long newScale)									HOST_TRAP (hostSelectorSetWindowScale);
HostBG			HostSetWindowBackground		(HostBG newBackground)							HOST_TRAP (hostSelectorSetWindowBackground);

HostFILE*		HostLogFile						(void)												HOST_TRAP (hostSelectorLogFile);
void				HostSetLogFileSize			(long)												HOST_TRAP (hostSelectorSetLogFileSize);

#ifdef __cplusplus 
}
#endif


#endif /* __HOSTCONTROL_H__ */

