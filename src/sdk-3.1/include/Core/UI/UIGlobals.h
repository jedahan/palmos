/***********************************************************************
 *
 * Copyright (c) 1994-1999 3Com Corporation or its subsidiaries.
 * All rights reserved.
 *
 * PROJECT:  Pilot
 * FILE:     Global.h
 * AUTHOR:   Art Lamb: September 12, 1994
 *
 * DECLARER: UI
 *
 * DESCRIPTION:
 * 	This file defines global variables used by the UI routines.
 *
 * HISTORY:
 *		5/5/98	art	Added a global variable for the virtual fonts. 
 *
 **********************************************************************/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__


#define 	UIDefNumSysFonts  	8		// PalmOS 3.0 has eight system fonts
#define	UIDefNumAppFonts		4		// Space is initially allocated for four app fonts

#define 	eventQueueSize	10


typedef struct UIGlobalsType {

	// Global variables used by the window routines.
	WinHandle			activeWindow;
	WinHandle			displayWindow;
	WinHandle			drawWindow;
	WinHandle			firstWindow;
	WinHandle			exitWindowID;
	WinHandle			enterWindowID;
	WinHandle			exitedWindowID;
	GraphicStateType	gState;
	
	
	// Global variables used by the event routines.
	EventStoreType*	eventQ;
	Word					eventQIndex;
	Word					eventQLength;
	SWord      			lastScreenX;
	SWord      			lastScreenY;
	Boolean    			lastPenDown;
	SDWord				needNullTickCount;		// We want a null Evt when ticks reaches this value
	
	
	// Global variables used by the font routins.
	FontPtr 				uiCurrentFontPtr;
	FontTablePtr		uiSysFontTablePtr;		// new for 3.0
	FontTablePtr		uiAppFontTablePtr;		// new for 3.0
	Word					uiNumSysFonts;				// new for 3.0
	Word					uiNumAppFonts;				// new for 3.0
	FontTablePtr		uiFontListPtr;				// new for 3.1
	DWord					uiUnused2;					// reserved for 3.2 (new "rootWindow" global)
	FontID  				uiCurrentFontID;
	
	
	// Global variables used by the form routines.
	FormPtr 				currentForm;
	
	
	// Global variables used by the insertion point routines.
	Boolean				insPtIsEnabled;
	Boolean				insPtOn;
	PointType			insPtLoc;
	SWord					insPtHeight;
	SDWord				insPtLastTick;
	WinHandle			insPtBitsBehind;
	
	// Global variables used by the clipboard routines.
	ClipboardItem 		clipboard[numClipboardForamts];
	
	// Globals used by the Memory Manager
	MenuBarPtr			uiCurrentMenu;
	Word					uiCurrentMenuRscID;
	
	// Global variables used by the field routines.
	FieldUndoType 		undoGlobals;

	// Global variables used by the Griffiti shift state indicator routines.
	Byte					gsiState;
	Boolean				gsiIsEnabled;
	PointType			gsiLocation;

	// Numeric decimal seperator, used in the field routines.
	Char					uiDecimalSeparator;
	
	} UIGlobalsType;
typedef UIGlobalsType* 	UIGlobalsPtr;


#define	ActiveWindow			((UIGlobalsPtr)GUIGlobalsP)->activeWindow
#define	DisplayWindow			((UIGlobalsPtr)GUIGlobalsP)->displayWindow
#define	DrawWindow				((UIGlobalsPtr)GUIGlobalsP)->drawWindow
#define	FirstWindow				((UIGlobalsPtr)GUIGlobalsP)->firstWindow
#define	ExitWindowID			((UIGlobalsPtr)GUIGlobalsP)->exitWindowID
#define	EnterWindowID			((UIGlobalsPtr)GUIGlobalsP)->enterWindowID
#define	ExitedWindowID			((UIGlobalsPtr)GUIGlobalsP)->exitedWindowID
#define	GState					((UIGlobalsPtr)GUIGlobalsP)->gState

#define	EventQ					((UIGlobalsPtr)GUIGlobalsP)->eventQ
#define	EventQIndex				((UIGlobalsPtr)GUIGlobalsP)->eventQIndex
#define	EventQLength			((UIGlobalsPtr)GUIGlobalsP)->eventQLength
#define	LastScreenX				((UIGlobalsPtr)GUIGlobalsP)->lastScreenX
#define	LastScreenY				((UIGlobalsPtr)GUIGlobalsP)->lastScreenY
#define	LastPenDown				((UIGlobalsPtr)GUIGlobalsP)->lastPenDown
#define	NeedNullTickCount		((UIGlobalsPtr)GUIGlobalsP)->needNullTickCount

// UIFontTable no longer exists; use UISysFontPtr and UIAppFontPtr
#define	UICurrentFontPtr		((UIGlobalsPtr)GUIGlobalsP)->uiCurrentFontPtr
#define	UISysFontTablePtr		((UIGlobalsPtr)GUIGlobalsP)->uiSysFontTablePtr
#define	UIAppFontTablePtr		((UIGlobalsPtr)GUIGlobalsP)->uiAppFontTablePtr
#define	UISysFontPtr			(((UIGlobalsPtr)GUIGlobalsP)->uiSysFontTablePtr)
#define	UIAppFontPtr			(((UIGlobalsPtr)GUIGlobalsP)->uiAppFontTablePtr)
#define	UIFontListPtr			(((UIGlobalsPtr)GUIGlobalsP)->uiFontListPtr)
#define	UINumSysFonts			((UIGlobalsPtr)GUIGlobalsP)->uiNumSysFonts
#define	UINumAppFonts			((UIGlobalsPtr)GUIGlobalsP)->uiNumAppFonts
#define	UICurrentFontID		((UIGlobalsPtr)GUIGlobalsP)->uiCurrentFontID

#define	CurrentForm				((UIGlobalsPtr)GUIGlobalsP)->currentForm

#define	InsPtIsEnabled			((UIGlobalsPtr)GUIGlobalsP)->insPtIsEnabled
#define	InsPtOn					((UIGlobalsPtr)GUIGlobalsP)->insPtOn
#define	InsPtLoc					((UIGlobalsPtr)GUIGlobalsP)->insPtLoc
#define	InsPtHeight				((UIGlobalsPtr)GUIGlobalsP)->insPtHeight
#define	InsPtLastTick			((UIGlobalsPtr)GUIGlobalsP)->insPtLastTick
#define	InsPtBitsBehind		((UIGlobalsPtr)GUIGlobalsP)->insPtBitsBehind

#define	Clipboard				((UIGlobalsPtr)GUIGlobalsP)->clipboard

#define	UICurrentMenu			((UIGlobalsPtr)GUIGlobalsP)->uiCurrentMenu
#define	UICurrentMenuRscID	((UIGlobalsPtr)GUIGlobalsP)->uiCurrentMenuRscID
#define	UndoGlobals				((UIGlobalsPtr)GUIGlobalsP)->undoGlobals

#define	GsiState					((UIGlobalsPtr)GUIGlobalsP)->gsiState
#define	GsiIsEnabled			((UIGlobalsPtr)GUIGlobalsP)->gsiIsEnabled
#define	GsiLocation				((UIGlobalsPtr)GUIGlobalsP)->gsiLocation

#define	UIDecimalSeparator	((UIGlobalsPtr)GUIGlobalsP)->uiDecimalSeparator


#endif //__GLOBAL_H__


