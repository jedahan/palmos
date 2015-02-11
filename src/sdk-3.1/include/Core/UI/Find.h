/***********************************************************************
 *
 * Copyright (c) 1994-1999 3Com Corporation or its subsidiaries.
 * All rights reserved.
 *
 * PROJECT:  Pilot
 * FILE:     Find.h
 * AUTHOR:	 Art Lamb: August 29, 1994
 *
 * DECLARER: UI
 *
 * DESCRIPTION:
 *	  This file defines field structures and routines.
 *
 ***********************************************************************/
#ifndef __FIND_H__
#define __FIND_H__

#define maxFinds			9
#define maxFindStrLen	16

typedef struct {
	Word				appCardNo;			// card number of the application
	LocalID			appDbID;				// LocalID of the application
	Boolean			foundInCaller;		// true if found in app that called Find

	Word				dbCardNo;			// card number of the database record was found in
	LocalID			dbID;					// LocalID of the database record was found in
	Word 				recordNum;			// index of record that contain a match
	Word				matchPos;			// postion in record of the match.
	Word				matchFieldNum;		// field number
	DWord				matchCustom;			// app specific data
	} FindMatchType;

typedef FindMatchType * FindMatchPtr;

typedef struct {

	// These fields are used by the applications.
	Word				dbAccesMode;		// read mode and maybe show secret
	Word 				recordNum;			// index of last record that contained a match
	Boolean			more;					// true of more matches to display
	Char				strAsTyped [maxFindStrLen+1];	// search string as entered
	Char				strToFind [maxFindStrLen+1];	// search string is lower case


	// The lineNumber field can be modified by the app. The continuation field can
	// be tested by the app. All other fields are private to the Find routine and
	// should NOT be accessed by applications.
	Word				numMatches;			// # of matches
	Word				lineNumber;			// next line in the results tabel
	Boolean			continuation;		// true if contining search of same app
	Boolean			searchedCaller;	// true after we've searched app that initiated the find

	LocalID			callerAppDbID;		// dbID of app that initiated search
	Word				callerAppCardNo;	// cardNo of app that initiated search

	LocalID			appDbID;				// dbID of app that we're currently searching
	Word				appCardNo;			// card number of app that we're currently searching
	
	Boolean			newSearch;			// true for first search
	DmSearchStateType	searchState;	// search state
	FindMatchType	match [maxFinds];
} FindParamsType;

typedef FindParamsType * FindParamsPtr;


// Param Block passsed with the sysAppLaunchCmdGoto Command
typedef struct {
	Word				searchStrLen;		// length of search string.
	Word				dbCardNo;			// card number of the database	
	LocalID			dbID;					// LocalID of the database
	Word 				recordNum;			// index of record that contain a match
	Word				matchPos;			// postion in record of the match.
	Word				matchFieldNum;		// field number string was found int
	DWord				matchCustom;			// application specific info
	} GoToParamsType;

typedef GoToParamsType * GoToParamsPtr;


//----------------------------------------------------------
//	Find Functions
//----------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void Find (GoToParamsPtr goToP)
			SYS_TRAP(sysTrapFind);
		

Boolean FindStrInStr (const CharPtr strToSearch, const CharPtr strToFind, 
	const WordPtr posP)
			SYS_TRAP(sysTrapFindStrInStr);

Boolean FindSaveMatch (const FindParamsPtr findParams, const Word recordNum, 
	const Word pos, const Word fieldNum, const DWord appCustom, 
	const Word cardNo, const LocalID dbID)
			SYS_TRAP(sysTrapFindSaveMatch);

void FindGetLineBounds (const FindParamsPtr findParams, const RectanglePtr r)
			SYS_TRAP(sysTrapFindGetLineBounds);

Boolean FindDrawHeader (const FindParamsPtr findParams, const CharPtr title)
			SYS_TRAP(sysTrapFindDrawHeader);

#ifdef __cplusplus 
}
#endif

#endif __FIND_H__
