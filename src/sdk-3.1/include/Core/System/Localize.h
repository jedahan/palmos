/*******************************************************************
 *
 * Copyright (c) 1994-1999 3Com Corporation or its subsidiaries.
 * All rights reserved.
 *
 * FileName:
 *		Localize.c
 *
 * Description:
 *		Functions to localize data.
 *
 * History:
 *   	8/28/96  Roger - Initial version
 *
 *******************************************************************/

#ifndef __LOCALIZE_H__
#define __LOCALIZE_H__


// Include elementary types
#include <Common.h>					// Basic types
#include <SysTraps.h>				// Trap Numbers.


#ifdef __cplusplus
extern "C" {
#endif


void 		LocGetNumberSeparators(NumberFormatType numberFormat, 
				Char *thousandSeparator, Char *decimalSeparator)
							SYS_TRAP(sysTrapLocGetNumberSeparators);



#ifdef __cplusplus 
}
#endif


#endif	// __LOCALIZE_H__


