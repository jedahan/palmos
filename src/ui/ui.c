/*****************************************************************************\
*                                                                             *
* Project       : Mobile development tutorial                                 *
* Application   : Demonstration of database development                       *
* Component     : Main                                                        *
* Author        : Eric Poncet (mobile.eric-poncet.com)                        *
* Creation      : 07/10/2000                                                  *
*                                                                             *
*******************************************************************************
*                                                                             *
* History       :                                                             *
*                                                                             *
\*****************************************************************************/


#include "ui.h"
#include <PalmTypes.h>
#include <PalmCompatibility.h>
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>


#define ROM_VERSION_REQUIRED	0x02000000		// This application requires PalmOS 2.0 or later


UInt32		romVersion;
MemHandle	funFontH, reverseFontH, smileyFontH;
ProgressPtr	prg = NULL;
Int32		count = 0, max = 0;


static void SetSelector(UInt16 formID, UInt16 fieldID, MemPtr str)
{
	FormPtr 	frm;
	ControlPtr	ctl;
	UInt16		obj;
	
	frm = FrmGetFormPtr(formID);
	obj = FrmGetObjectIndex(frm, fieldID);
	ctl = (ControlPtr)FrmGetObjectPtr(frm, obj);
	CtlSetLabel(ctl, str);
}


static void SetList(UInt16 formID, UInt16 popupID, UInt16 listID, Int16 item)
{
	FormPtr 	frm;
	ListPtr		lst;
    ControlPtr  pop;
    Char        *txt;

	frm = FrmGetFormPtr(formID);
    pop = (ControlPtr)FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, popupID));
	lst = (ListPtr)FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, listID));

	LstSetSelection(lst, item);

    txt = LstGetSelectionText(lst, item);
    CtlSetLabel(pop, txt);
}


static void SetField(UInt16 formID, UInt16 fieldID, MemPtr str)
{
	FormPtr 	frm;
	FieldPtr	fld;
	UInt16		obj;
	CharPtr		p;
	VoidHand	h;
	
	frm = FrmGetFormPtr(formID);
	obj = FrmGetObjectIndex(frm, fieldID);
	fld = (FieldPtr)FrmGetObjectPtr(frm, obj);
	h = (VoidHand)FldGetTextHandle(fld);
	if (h == NULL)
	{
		h = MemHandleNew (FldGetMaxChars(fld)+1);
		ErrFatalDisplayIf(!h, "No Memory");
	}
	
	p = (CharPtr)MemHandleLock(h);
	StrCopy(p, str);
	MemHandleUnlock(h);
	
	FldSetTextHandle(fld, (Handle)h);
}


static Boolean MainFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
		    RectangleType		rCircle = { {15, 23}, {130, 130} },
		    					rRect = { {35, 44}, {90, 90} };
			IndexedColorType	foreColor, backColor, textColor;
			FontID				saveFont;
			Char				s[40];
			
			FrmDrawForm(FrmGetActiveForm());
			foreColor = WinSetForeColor(UIColorGetTableEntryIndex(UIObjectFrame));
			WinDrawRectangle(&rCircle, 65);
			WinSetForeColor(UIColorGetTableEntryIndex(UIFieldBackground));
			WinDrawRectangle(&rRect, 4);

			saveFont = FntSetFont(2);
			textColor = WinSetTextColor(UIColorGetTableEntryIndex(UIFieldText));
			backColor = WinSetBackColor(UIColorGetTableEntryIndex(UIFieldBackground));
			WinSetUnderlineMode(noUnderline);
			StrCopy(s, "Tap menu"); 		WinDrawChars(s, StrLen(s), 50, 50);			
			StrCopy(s, "and"); 				WinDrawChars(s, StrLen(s), 68, 70);			
			StrCopy(s, "select UI object");	WinDrawChars(s, StrLen(s), 40, 90);			
			StrCopy(s, "to test"); 			WinDrawChars(s, StrLen(s), 62, 110);			

			// Restore former values
			WinSetForeColor(foreColor);
			WinSetBackColor(backColor);
			WinSetTextColor(textColor);
			FntSetFont(saveFont);
			handled = true;
			break;
		}
	
	    default:
			break;
    }

    return handled;
}


static Boolean FontFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
			FrmDrawForm(FrmGetActiveForm());
			handled = true;
			break;
	
	    default:
			break;
    }

    return handled;
}


static Boolean BitmapFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
			if (romVersion < 0x04000000)					// 16K bitmaps require OS >= 4.0
			{												// if OS older, remove 16K formbitmap object
		    	FormPtr		frm = FrmGetActiveForm();
				UInt16		obj = FrmGetObjectIndex(frm, Color16KBitmap);
				FrmRemoveObject(&frm, obj);
				
				frm = FrmGetActiveForm();					// refresh pointer that may have changed after FrmRemoveObject
				FrmNewLabel(&frm, Color16KBitmap, "Need OS4+", 110, 115, 0);
			}
			FrmDrawForm(FrmGetActiveForm());
			handled = true;
			break;
	
	    default:
			break;
    }

    return handled;
}


static Boolean SelectorFormHandleEvent(EventPtr event)
{
	static Int16		month = 0, day = 0, year = 0, hour = -1, minute = 0;
	static TimeType		start = {0, 0}, end = {0, 0};
    Boolean				handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
			FrmDrawForm(FrmGetActiveForm());
			handled = true;
			break;
		}
	
	    case ctlSelectEvent:
			switch (event->data.ctlSelect.controlID)
			{
				case SelectorDay:
					if (day == 0)				// first pick
					{
			 			DateTimeType	dt;

						TimSecondsToDateTime(TimGetSeconds(), &dt);	//get today date
						day = dt.day;
						month = dt.month;
						year = dt.year;
			 		}
					if (SelectDay(selectDayByDay, &month, &day, &year, "Pick a day!"))
					{
						char	str[40];

						DateToAscii(month, day, year, PrefGetPreference(prefDateFormat), str);
						SetSelector(SelectorForm, SelectorDay, str);
					}
					break;
					
				case SelectorTime:
					if (hour == -1)				// first pick
					{
			 			DateTimeType	dt;

						TimSecondsToDateTime(TimGetSeconds(), &dt);	//get today date
						hour = dt.hour;
						minute = dt.minute;
			 		}
					if (SelectOneTime(&hour, &minute, "Pick a time!"))
					{
						char			str[40];

						TimeToAscii(hour, minute, PrefGetPreference(prefTimeFormat), str);
						SetSelector(SelectorForm, SelectorTime, str);
					}
					break;

				case SelectorStartEnd:
					if (SelectTime(&start, &end, (TimeToInt(start) == noTime), "Pick a start and an end!", 25, 0, 0))
					{
						char	str[40];

						if (TimeToInt(start) == noTime)
							StrCopy(str, "Not a Clue!");
						else
						if (start.hours == 25)		// all day
							StrCopy(str, "Damn Long!");
						else StrPrintF(str, "%d:%02d->%d:%02d", start.hours%12, start.minutes, end.hours%12, end.minutes);
						SetSelector(SelectorForm, SelectorStartEnd, str);
					}
					break;

				default:
					break;
			}
			break;
	
	    default:
			break;
    }

    return handled;
}


static void DisplayStringTable(Int8 item)
{
    RectangleType		rRect = { {4, 60}, {152, 96} };
	IndexedColorType	foreColor, backColor, textColor;
	FontID				saveFont;
	Char 				str[40];
	UInt8				count, i;
	Boolean				valid = ((item >= 0) && (item <= StringTableMaxItem));
	
	FrmDrawForm(FrmGetActiveForm());
	
	foreColor = WinSetForeColor(UIColorGetTableEntryIndex(UIFieldText));
	backColor = WinSetBackColor(UIColorGetTableEntryIndex(UIFieldText));
	WinDrawRectangle(&rRect, 4);

	if (valid)
	{
		Short	strTbl = (StringTableArdipithecusStr + item);
		
		saveFont = FntSetFont(0);
		textColor = WinSetTextColor(UIColorGetTableEntryIndex(UIFieldBackground));
	
		for (count = 0; true; count++)																// pass 1: let's count # of strings
			if (StrLen(SysStringByIndex(strTbl, count, str, sizeof(str))) <= 3)						// only got prefix?
				break;																				// exit loop
	
		for (i = 0; i < count; i++)																	// pass 2: letz get'em stringz!
		{
			SysStringByIndex(strTbl, i, str, sizeof(str));
			WinDrawChars(str, StrLen(str), 10, (64 - 10 + ((i+1)*(96 / (count+1)))));
		}

		WinSetTextColor(textColor);
		FntSetFont(saveFont);
	}

	// Restore former values
	WinSetForeColor(foreColor);
	WinSetBackColor(backColor);

	if (valid)
		SetList(StringTableForm, StringTablePopup, StringTableList, item);
}


static Boolean StringTableFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
	    	DisplayStringTable(-1);
			handled = true;
			break;
		}
	
		case popSelectEvent:
			if (event->data.popSelect.listID == StringTableList)
			{
				DisplayStringTable(event->data.popSelect.selection);
				handled = true;
			}
			break;
			
	    default:
			break;
    }

    return handled;
}


static Boolean GraffitiFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
	    	FormPtr		frm = FrmGetActiveForm();
			UInt16		obj = FrmGetObjectIndex(frm, GraffitiField);

			FrmDrawForm(frm);
			FrmSetFocus(frm, obj);
			handled = true;
			break;
		}
	
	    default:
			break;
    }

    return handled;
}


static Boolean ScrollFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
		    RectangleType	rectField = { {35, 55}, {90, 70} }, rectBar = { {126, 55}, {9, 70} };
		    Char			str[32], strField[255];
		    register UInt8	i;

			StrCopy(strField, "");
			for (i = 0; true; i++)
			{
				if (i > 0)
					StrCat(strField, "\n");
				SysStringByIndex(ScrollStr, i, str, sizeof(str));
				if (StrLen(str) == 0)
					break;
				StrCat(strField, str);
			}
			SetField(ScrollForm, ScrollField, strField);
			FrmDrawForm(FrmGetActiveForm());
			WinDrawGrayRectangleFrame(simpleFrame, &rectField);
			WinDrawGrayRectangleFrame(simpleFrame, &rectBar);
			handled = true;
			break;
		}
	
	    case sclRepeatEvent:
	    {
	    	UInt16			newValue = event->data.sclRepeat.newValue;
			FormPtr 		frm = FrmGetActiveForm();
			FieldPtr		fld = (FieldPtr)FrmGetObjectPtr(frm, FrmGetObjectIndex(frm, ScrollField));
	    	static UInt16	curValue = 0;

			if (newValue > curValue)
	    		FldScrollField(fld, newValue-curValue, winDown);
	    		else FldScrollField(fld, curValue-newValue, winUp);
	    	curValue = newValue;
			break;
		}
	
	    default:
			break;
    }

    return handled;
}


static void DrawShape(UInt16 undraw, UInt16 draw)
{
    RectangleType		rShape = { {40, 75}, {80, 80} };
	IndexedColorType	foreColor;
	
	foreColor = WinSetForeColor(UIColorGetTableEntryIndex(UIFormFill));
	WinDrawRectangle(&rShape, SliderMax-undraw);

	WinSetForeColor(foreColor);
	WinDrawRectangle(&rShape, SliderMax-draw);
}


static Boolean SliderFormHandleEvent(EventPtr event)
{
    Boolean			handled = false;
   	static UInt16	curValue = 0;

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
			FrmDrawForm(FrmGetActiveForm());
			DrawShape(curValue, curValue);
			handled = true;
			break;
		}
	
	    case ctlRepeatEvent:
	    {
	    	UInt16	newValue = event->data.ctlRepeat.value;

			if (newValue != curValue)
			{
				DrawShape(curValue, newValue);
		    	curValue = newValue;
		    }
			break;
		}
	
	    default:
			break;
    }

    return handled;
}


Boolean ProgressCallback(PrgCallbackDataPtr data)
{
	switch (data->stage)
	{
		case 0:
			StrCopy(data->textP, "Connecting");
			break;

		case 1:
		{
			Char	str[40];
			StrCopy(str, "Loading ");
			StrCat(str, (Char*)(data->userDataP));
			StrCat(str, " file");
			StrCat(str, data->message);
			StrCopy(data->textP, str);
			break;
		}

		default:
			StrCopy(data->textP, "Finishing");
			break;
	}
	
	return true;
}


static Boolean ProgressFormHandleEvent(EventPtr event)
{
    Boolean				handled = false;
    static Char			fileSize[10];

    switch (event->eType)
    {
	    case frmOpenEvent:
			FrmDrawForm(FrmGetActiveForm());
			handled = true;
			break;

	    case ctlSelectEvent:
			switch (event->data.ctlSelect.controlID)
			{
				case ProgressQuick:
					count = 0;
					max = 0x0006;
					StrCopy(fileSize, "tiny");
					if ((prg = PrgStartDialog("Quick Task", &ProgressCallback, (void*)fileSize)) == NULL)
						FrmCustomAlert(ErrorAlert, "Unable to start progress dialog", "", "");
					handled = true;
					break;
					
				case ProgressSlow:
					count = 0;
					max = 0x0012;
					StrCopy(fileSize, "huge");
					if ((prg = PrgStartDialog("Slow Task", &ProgressCallback, (void*)fileSize)) == NULL)
						FrmCustomAlert(ErrorAlert, "Unable to start progress dialog", "", "");
					handled = true;
					break;
					
				default:
					break;
			}
			break;
	
	    default:
			break;
    }

    return handled;
}


void DrawGadget(RectangleType* rect, Boolean change)
{
	static UInt16		pos = 0;
	static Boolean		up = true;
	IndexedColorType	foreColor;
	RectangleType		inside;
	
	if (change)
		up = !up;
		
	WinDrawRectangleFrame(simpleFrame, rect);

	RctCopyRectangle(rect, &inside);
	if (up)
	{
		inside.topLeft.y += (GadgetHeight-pos);		// compute top of rect
		inside.extent.y = pos;						// compute height of rect
	}
	else inside.extent.y -= pos;

	foreColor  = WinSetForeColor(UIColorGetTableEntryIndex(up ? UIFormFrame : UIFormFill));
	WinDrawRectangle(&inside, 0);
	WinSetForeColor(foreColor);
	
	if (up)
		if (pos < GadgetHeight)
			pos += 2;
			else
			{
				IndexedColorType	textColor = WinSetTextColor(UIColorGetTableEntryIndex(UIFormFill));
				IndexedColorType	backColor = WinSetBackColor(UIColorGetTableEntryIndex(UIFormFrame));
				WinDrawChars("Full :)", 7, rect->topLeft.x+10, rect->topLeft.y+2);
				WinSetTextColor(textColor);
				WinSetTextColor(backColor);
				up = !up;
			}
		else
		if (pos > 0)
			pos -= 2;
			else
			{
				IndexedColorType	textColor = WinSetTextColor(UIColorGetTableEntryIndex(UIFormFrame));
				IndexedColorType	backColor = WinSetBackColor(UIColorGetTableEntryIndex(UIFormFill));
				WinDrawChars("Empty :(", 8, rect->topLeft.x+2, rect->topLeft.y+rect->extent.y-14);
				WinSetTextColor(textColor);
				WinSetTextColor(backColor);
				up = !up;
			}
}


static Boolean GadgetFormHandleEvent(EventPtr event)
{
    Boolean					handled = false;
    static RectangleType	rect = { {0, 0}, {0, 0} };

    switch (event->eType)
    {
	    case frmOpenEvent:
	    {
			FormPtr			frm = FrmGetActiveForm();
			UInt16			objIndex = FrmGetObjectIndex(frm, GadgetGadget);
			RectangleType	rect2;
			
			FrmDrawForm(FrmGetActiveForm());

			FrmGetObjectBounds(frm, objIndex, &rect);	// dynamically get gadget's coordinates and size

			RctCopyRectangle(&rect, &rect2);

			rect2.topLeft.x -= 1;
			rect2.topLeft.y -= 1;
			rect2.extent.x += 2;
			rect2.extent.y += 2;
			WinDrawGrayRectangleFrame(simpleFrame, &rect2);	// draw dotted frame 1 pix around gadget

			rect2.topLeft.x -= 1;
			rect2.topLeft.y -= 1;
			rect2.extent.x += 2;
			rect2.extent.y += 2;
			WinDrawGrayRectangleFrame(simpleFrame, &rect2);	// draw dotted frame 1 pix around gadget

			DrawGadget(&rect, false);						// draw Mr gadget in person!
			handled = true;
			break;
		}
	
	 	case penDownEvent:
			if (RctPtInRectangle(event->screenX, event->screenY, &rect))
			{
				DrawGadget(&rect, true);
				handled=true;
			}
	 		break;

		case nilEvent:
			DrawGadget(&rect, false);
			break;
			
	    default:
			break;
    }

    return handled;
}


static Boolean AppHandleEvent(EventPtr event)
{
    FormPtr	frm;
    Int		formId;
    Boolean	handled = false;

    if (event->eType == frmLoadEvent)
    {
		formId = event->data.frmLoad.formID;
		frm = FrmInitForm(formId);
		FrmSetActiveForm(frm);
		switch (formId)
		{
			case MainForm:
				FrmSetEventHandler(frm, MainFormHandleEvent);
				handled = true;
				break;
				
			case FontForm:
				FrmSetEventHandler(frm, FontFormHandleEvent);
				handled = true;
				break;
				
			case BitmapForm:
				FrmSetEventHandler(frm, BitmapFormHandleEvent);
				handled = true;
				break;
				
			case SelectorForm:
				FrmSetEventHandler(frm, SelectorFormHandleEvent);
				handled = true;
				break;
				
			case StringTableForm:
				FrmSetEventHandler(frm, StringTableFormHandleEvent);
				handled = true;
				break;
				
			case GraffitiForm:
				FrmSetEventHandler(frm, GraffitiFormHandleEvent);
				handled = true;
				break;
				
			case ScrollForm:
				FrmSetEventHandler(frm, ScrollFormHandleEvent);
				handled = true;
				break;
				
			case SliderForm:
				FrmSetEventHandler(frm, SliderFormHandleEvent);
				handled = true;
				break;
				
			case ProgressForm:
				FrmSetEventHandler(frm, ProgressFormHandleEvent);
				handled = true;
				break;
				
			case GadgetForm:
				FrmSetEventHandler(frm, GadgetFormHandleEvent);
				handled = true;
				break;
				
			default:
				break;
		}
    }
	else
    if (event->eType == menuEvent)
	{
		MenuEraseStatus(NULL);
		switch (event->data.menu.itemID)
		{
			case MainObjectFontCmd:
				FrmGotoForm(FontForm);
			    handled = true;
			    break;

			case MainObjectBitmapCmd:
				FrmGotoForm(BitmapForm);
			    handled = true;
			    break;

			case MainObjectSelectorCmd:
				FrmGotoForm(SelectorForm);
			    handled = true;
			    break;

			case MainObjectStringTableCmd:
				FrmGotoForm(StringTableForm);
			    handled = true;
			    break;

			case MainObjectGraffitiCmd:
				FrmGotoForm(GraffitiForm);
			    handled = true;
			    break;

			case MainObjectScrollCmd:
				FrmGotoForm(ScrollForm);
			    handled = true;
			    break;

			case MainObjectSliderCmd:
				FrmGotoForm(SliderForm);
			    handled = true;
			    break;

			case MainObjectProgressCmd:
				FrmGotoForm(ProgressForm);
			    handled = true;
			    break;

			case MainObjectGadgetCmd:
				FrmGotoForm(GadgetForm);
			    handled = true;
			    break;

			case MainOptionsHelpCmd:
			    FrmAlert(HelpAlert);
			    handled = true;
			    break;
			    
			case MainOptionsAboutCmd:
			    FrmAlert(AboutAlert);
			    handled = true;
			    break;
			    
			default:
				break;
		}
	}
	else
    if (event->eType == nilEvent)
    {
    	if (prg)
    	{
	    	if ((++count > max) || (PrgUserCancel(prg)))
	    	{
	    		PrgStopDialog(prg, false);
	    		prg = NULL;
	    	}
	    	else 
	    	{
	    		Char	dots[10];
	    		UInt16	i= 0, stage = (count <= (max/5)) ? 0 : ((count >= (max*9/10)) ? 2 : 1);
    			StrCopy(dots, "");
	    		if (stage == 1)
	    			while (i++ < ((count-(max/5))%5))
	    				StrCat(dots, ".");
	    		PrgUpdateDialog(prg, 0, stage, dots, true);
	    	}
			handled = true;
		}
	}
	
    return handled;
}


static Err AppStart()
{
	FontPtr	funFont, reverseFont, smileyFont;
	Err		retcode = 0;

	funFont = MemHandleLock(funFontH = DmGetResource('NFNT', FunFont));
	FntDefineFont(FunFontID, funFont);

	reverseFont = MemHandleLock(reverseFontH = DmGetResource('NFNT', ReverseFont));
	FntDefineFont(ReverseFontID, reverseFont);

	smileyFont = MemHandleLock(smileyFontH = DmGetResource('NFNT', SmileyFont));
	FntDefineFont(SmileyFontID, smileyFont);

	FrmGotoForm(MainForm);
	
	return retcode;
}


static void AppEventLoop(void)
{
	EventType	event;
	short		error;

    do
    {
		EvtGetEvent(&event, 100);

		if (SysHandleEvent(&event))
			continue;
			
		if (MenuHandleEvent((void *)0, &event, &error))
			continue;

		if (AppHandleEvent(&event))
			continue;

		if (prg)								// progress dialog running?
			if (PrgHandleEvent(prg, &event))
				continue;

		FrmDispatchEvent(&event);
    }
    while (event.eType != appStopEvent);
}


static Err AppStop()
{
	Err		retcode;
	
    FrmCloseAllForms();
    
	MemHandleUnlock(funFontH);
	MemHandleUnlock(reverseFontH);
	MemHandleUnlock(smileyFontH);

    return retcode;
}


UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	UInt32		rom;

	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &rom);	// Minimal ROM version requirement
	if (rom < ROM_VERSION_REQUIRED)					
	{
		FrmAlert(RomIncompatibleAlert);
		return(sysErrRomIncompatible);
	}

	if (cmd == sysAppLaunchCmdNormalLaunch)						// Normal launch
	{
		Err retcode;

		romVersion = rom;				// assign global here, in a launch section where this is allowed
		
		if ((retcode = AppStart()) != 0)
			return(retcode);
		AppEventLoop();
		if ((retcode = AppStop()) != 0)
			return(retcode);
	}

	return 0;
}
