/***********************************************************************
 *
 * Copyright (c) 1994-1999 3Com Corporation or its subsidiaries.
 * All rights reserved.
 *
 * PROJECT:  Pilot
 * FILE:     Chars.h
 * AUTHOR:   Roger Flores: November 3, 1994
 *
 * DECLARER: UI
 *
 * DESCRIPTION:
 *        This file defines the characters in fonts.
 *
 **********************************************************************/
#ifndef __CHARS_H__
#define __CHARS_H__

// Standard Unicode 2.0 names for the ascii characters. These exist in
// all of the text fonts, no matter what character encoding is being
// used by PalmOS.

#define	chrNull						0x0000
#define	chrStartOfHeading			0x0001
#define	chrStartOfText				0x0002
#define	chrEndOfText				0x0003
#define	chrEndOfTransmission		0x0004
#define	chrEnquiry					0x0005
#define	chrAcknowledge				0x0006
#define	chrBell						0x0007
#define	chrBackspace				0x0008
#define	chrHorizontalTabulation	0x0009
#define	chrLineFeed					0x000A
#define	chrVerticalTabulation	0x000B
#define	chrFormFeed					0x000C
#define	chrCarriageReturn			0x000D
#define	chrShiftOut					0x000E
#define	chrShiftIn					0x000F
#define	chrDataLinkEscape			0x0010
#define	chrDeviceControlOne		0x0011
#define	chrDeviceControlTwo		0x0012
#define	chrDeviceControlThree	0x0013
#define	chrDeviceControlFour		0x0014
#define	chrNegativeAcknowledge	0x0015
#define	chrSynchronousIdle		0x0016
#define	chrEndOfTransmissionBlock 0x0017
#define	chrCancel					0x0018
#define	chrEndOfMedium				0x0019
#define	chrSubstitute				0x001A
#define	chrEscape					0x001B
#define	chrFileSeparator			0x001C
#define	chrGroupSeparator			0x001D
#define	chrRecordSeparator		0x001E
#define	chrUnitSeparator			0x001F
#define	chrSpace						0x0020
#define	chrExclamationMark		0x0021
#define	chrQuotationMark			0x0022
#define	chrNumberSign				0x0023
#define	chrDollarSign				0x0024
#define	chrPercentSign				0x0025
#define	chrAmpersand				0x0026
#define	chrApostrophe				0x0027
#define	chrLeftParenthesis		0x0028
#define	chrRightParenthesis		0x0029
#define	chrAsterisk					0x002A
#define	chrPlusSign					0x002B
#define	chrComma						0x002C
#define	chrHyphenMinus				0x002D
#define	chrFullStop					0x002E
#define	chrSolidus					0x002F
#define	chrDigitZero				0x0030
#define	chrDigitOne					0x0031
#define	chrDigitTwo					0x0032
#define	chrDigitThree				0x0033
#define	chrDigitFour				0x0034
#define	chrDigitFive				0x0035
#define	chrDigitSix					0x0036
#define	chrDigitSeven				0x0037
#define	chrDigitEight				0x0038
#define	chrDigitNine				0x0039
#define	chrColon						0x003A
#define	chrSemicolon				0x003B
#define	chrLessThanSign			0x003C
#define	chrEqualsSign				0x003D
#define	chrGreaterThanSign		0x003E
#define	chrQuestionMark			0x003F
#define	chrCommercialAt			0x0040
#define	chrCapital_A				0x0041
#define	chrCapital_B				0x0042
#define	chrCapital_C				0x0043
#define	chrCapital_D				0x0044
#define	chrCapital_E				0x0045
#define	chrCapital_F				0x0046
#define	chrCapital_G				0x0047
#define	chrCapital_H				0x0048
#define	chrCapital_I				0x0049
#define	chrCapital_J				0x004A
#define	chrCapital_K				0x004B
#define	chrCapital_L				0x004C
#define	chrCapital_M				0x004D
#define	chrCapital_N				0x004E
#define	chrCapital_O				0x004F
#define	chrCapital_P				0x0050
#define	chrCapital_Q				0x0051
#define	chrCapital_R				0x0052
#define	chrCapital_S				0x0053
#define	chrCapital_T				0x0054
#define	chrCapital_U				0x0055
#define	chrCapital_V				0x0056
#define	chrCapital_W				0x0057
#define	chrCapital_X				0x0058
#define	chrCapital_Y				0x0059
#define	chrCapital_Z				0x005A
#define	chrLeftSquareBracket		0x005B
// #define	chrReverseSolidus		0x005C (not in Japanese fonts)
#define	chrRightSquareBracket	0x005D
#define	chrCircumflexAccent		0x005E
#define	chrLowLine					0x005F
#define	chrGraveAccent				0x0060
#define	chrSmall_A					0x0061
#define	chrSmall_B					0x0062
#define	chrSmall_C					0x0063
#define	chrSmall_D					0x0064
#define	chrSmall_E					0x0065
#define	chrSmall_F					0x0066
#define	chrSmall_G					0x0067
#define	chrSmall_H					0x0068
#define	chrSmall_I					0x0069
#define	chrSmall_J					0x006A
#define	chrSmall_K					0x006B
#define	chrSmall_L					0x006C
#define	chrSmall_M					0x006D
#define	chrSmall_N					0x006E
#define	chrSmall_O					0x006F
#define	chrSmall_P					0x0070
#define	chrSmall_Q					0x0071
#define	chrSmall_R					0x0072
#define	chrSmall_S					0x0073
#define	chrSmall_T					0x0074
#define	chrSmall_U					0x0075
#define	chrSmall_V					0x0076
#define	chrSmall_W					0x0077
#define	chrSmall_X					0x0078
#define	chrSmall_Y					0x0079
#define	chrSmall_Z					0x007A
#define	chrLeftCurlyBracket		0x007B
#define	chrVerticalLine			0x007C
#define	chrRightCurlyBracket		0x007D
#define	chrTilde						0x007E
#define	chrDelete					0x007F


// Special meanings given to characters by the PalmOS
#define	chrPageUp					chrVerticalTabulation		// 0x000B
#define	chrPageDown					chrFormFeed						// 0x000C
#define	chrOtaSecure				chrDeviceControlFour			// 0x0014
#define	chrOta						chrNegativeAcknowledge		// 0x0015
#define	chrCommandStroke			chrSynchronousIdle			// 0x0016
#define	chrShortcutStroke			chrEndOfTransmissionBlock	// 0x0017
#define	chrEllipsis					chrCancel						// 0x0018
#define	chrNumericSpace			chrEndOfMedium					// 0x0019
#define	chrLeftArrow				chrFileSeparator				// 0x001C
#define	chrRightArrow				chrGroupSeparator				// 0x001D
#define	chrUpArrow					chrRecordSeparator			// 0x001E
#define	chrDownArrow				chrUnitSeparator				// 0x001F


//  The following are key codes used for virtual events, like
//   low battery warnings, etc. These keyboard events MUST
//   have the commandKeyMask bit set in the modifiers in order
//   to be recognized.
#define	vchrLowBattery				0x0101		// Display low battery dialog
#define	vchrEnterDebugger			0x0102		// Enter Debugger
#define	vchrNextField				0x0103		// Go to next field in form
#define	vchrStartConsole			0x0104		// Startup console task
#define	vchrMenu						0x0105		// Ctl-A
#define	vchrCommand					0x0106		// Ctl-C
#define	vchrConfirm					0x0107		// Ctl-D
#define	vchrLaunch					0x0108		// Ctl-E
#define	vchrKeyboard				0x0109		// Ctl-F popup the keyboard in appropriate mode
#define	vchrFind						0x010A
#define	vchrCalc						0x010B
#define	vchrPrevField				0x010C
#define	vchrAlarm					0x010D		// sent before displaying an alarm
#define	vchrRonamatic				0x010E		// stroke from graffiti area to top half of screen
#define	vchrGraffitiReference	0x010F		// popup the Graffiti reference
#define	vchrKeyboardAlpha			0x0110		// popup the keyboard in alpha mode
#define	vchrKeyboardNumeric		0x0111		// popup the keyboard in number mode
#define	vchrLock						0x0112		// switch to the Security app and lock the device
#define	vchrBacklight				0x0113		// toggle state of backlight
#define	vchrAutoOff					0x0114		// power off due to inactivity timer
// Added for PalmOS 3.0
#define	vchrExgTest					0x0115		// put exchange Manager into test mode (&.t)
#define	vchrSendData				0x0116		// Send data if possible
#define	vchrIrReceive				0x0117		// Initiate an Ir receive manually (&.i)
// Added for PalmOS 3.1
#define	vchrTsm1						0x0118		// Text Services silk-screen button
#define	vchrTsm2						0x0119		// Text Services silk-screen button
#define	vchrTsm3						0x011A		// Text Services silk-screen button
#define	vchrTsm4						0x011B		// Text Services silk-screen button	


// The application launching buttons generate the following
// key codes and will also set the commandKeyMask bit in the 
// modifiers field
#define	vchrHardKeyMin				0x0200
#define	vchrHardKeyMax				0x02FF

#define	vchrHard1					0x0204
#define	vchrHard2					0x0205
#define	vchrHard3					0x0206
#define	vchrHard4					0x0207
#define	vchrHardPower				0x0208
#define	vchrHardCradle				0x0209			// Button on cradle pressed
#define	vchrHardCradle2			0x020A			// Button on cradle pressed and hwrDockInGeneric1
																// input on dock asserted (low).
#define	vchrHardContrast			0x020B			// Sumo's Contrast button



// Old names for some of the characters.
#define	nullChr						chrNull							// 0x0000
#define	backspaceChr				chrBackspace					// 0x0008
#define	tabChr						chrHorizontalTabulation		// 0x0009
#define	linefeedChr					chrLineFeed						// 0x000A
#define	pageUpChr					chrPageUp						// 0x000B
#define	pageDownChr					chrPageDown						// 0x000C
#define	crChr							chrCarriageReturn				// 0x000D
#define	returnChr					chrCarriageReturn				// 0x000D
#define	escapeChr					chrEscape						// 0x001B
#define	leftArrowChr				chrLeftArrow					// 0x001C
#define	rightArrowChr				chrRightArrow					// 0x001D
#define	upArrowChr					chrUpArrow						// 0x001E
#define	downArrowChr				chrDownArrow					// 0x001F
#define	spaceChr						chrSpace							// 0x0020
#define	quoteChr						chrQuotationMark				// 0x0022 '"'
#define	commaChr						chrComma							// 0x002C ','
#define	periodChr					chrFullStop						// 0x002E '.'
#define	colonChr						chrColon							// 0x003A ':'
#define	lowBatteryChr				vchrLowBattery					// 0x0101
#define	enterDebuggerChr			vchrEnterDebugger				// 0x0102
#define	nextFieldChr				vchrNextField					// 0x0103
#define	startConsoleChr			vchrStartConsole				// 0x0104
#define	menuChr						vchrMenu							// 0x0105
#define	commandChr					vchrCommand						// 0x0106
#define	confirmChr					vchrConfirm						// 0x0107
#define	launchChr					vchrLaunch						// 0x0108
#define	keyboardChr					vchrKeyboard					// 0x0109
#define	findChr						vchrFind							// 0x010A
#define	calcChr						vchrCalc							// 0x010B
#define	prevFieldChr				vchrPrevField					// 0x010C
#define	alarmChr						vchrAlarm						// 0x010D
#define	ronamaticChr				vchrRonamatic					// 0x010E
#define	graffitiReferenceChr		vchrGraffitiReference		// 0x010F
#define	keyboardAlphaChr			vchrKeyboardAlpha				// 0x0110
#define	keyboardNumericChr		vchrKeyboardNumeric			// 0x0111
#define	lockChr						vchrLock							// 0x0112
#define	backlightChr				vchrBacklight					// 0x0113
#define	autoOffChr					vchrAutoOff						// 0x0114
#define	exgTestChr					vchrExgTest						// 0x0115
#define	sendDataChr					vchrSendData					// 0x0116
#define	irReceiveChr				vchrIrReceive					// 0x0117
#define	hardKeyMin					vchrHardKeyMin					// 0x0200
#define	hardKeyMax					vchrHardKeyMax					// 0x02FF
#define	hard1Chr						vchrHard1						// 0x0204
#define	hard2Chr						vchrHard2						// 0x0205
#define	hard3Chr						vchrHard3						// 0x0206
#define	hard4Chr						vchrHard4						// 0x0207
#define	hardPowerChr				vchrHardPower					// 0x0208
#define	hardCradleChr				vchrHardCradle					// 0x0209
#define	hardCradle2Chr				vchrHardCradle2				// 0x020A
#define	hardContrastChr			vchrHardContrast				// 0x020B

// Macros to determine correct character code to use for drawing numeric space
// and horizontal ellipsis.

#define	ChrNumericSpace(chP)															\
	do {																						\
		ULong attribute;																	\
		if ((FtrGet(sysFtrCreator, sysFtrNumROMVersion, &attribute) == 0)	\
		&& (attribute >= sysMakeROMVersion(3, 1, 0, 0, 0))) {					\
			*(chP) = chrNumericSpace;													\
		} else {																				\
			*(chP) = 0x80;																	\
		}																						\
	} while (0)

#define	ChrHorizEllipsis(chP)														\
	do {																						\
		ULong attribute;																	\
		if ((FtrGet(sysFtrCreator, sysFtrNumROMVersion, &attribute) == 0)	\
		&& (attribute >= sysMakeROMVersion(3, 1, 0, 0, 0))) {					\
			*(chP) = chrEllipsis;														\
		} else {																				\
			*(chP) = 0x85;																	\
		}																						\
	} while (0)

// Characters in the 9 point symbol font.  Resource ID 9003
enum symbolChars {
	symbolLeftArrow = 3,
	symbolRightArrow,
	symbolUpArrow,
	symbolDownArrow,
	symbolSmallDownArrow,
	symbolSmallUpArrow,
	symbolMemo = 9,
	symbolHelp,
	symbolNote,
	symbolNoteSelected,
	symbolCapsLock,
	symbolNumLock,
	symbolShiftUpper,
	symbolShiftPunc,
	symbolShiftExt,
	symbolShiftNone,
	symbolNoTime,
	symbolAlarm,
	symbolRepeat,
	symbolCheckMark,
	// These next four characters were moved from the 0x8D..0x90
	// range in the main fonts to the 9pt Symbol font in PalmOS 3.1
	symbolDiamondChr,
	symbolClubChr,
	symbolHeartChr,
	symbolSpadeChr
	};

// Character in the 7 point symbol font.  Resource ID 9005
enum symbol7Chars {
	symbol7ScrollUp = 1,
	symbol7ScrollDown,
	symbol7ScrollUpDisabled,
	symbol7ScrollDownDisabled
	};

//	Characters in the 11 point symbol font.  Resource ID 9004
enum symbol11Chars {
	symbolCheckboxOff = 0,
	symbolCheckboxOn,
	symbol11LeftArrow,
	symbol11RightArrow
	};


#endif // __CHARS_H__
