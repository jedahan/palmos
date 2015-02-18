#include "giraffe.h"
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>
#define MAX_STRING_LENGTH 1000

// many thanks to 
// https://github.com/Gaoithe/bgttoolbox/blob/bc47eb94b70ce1712d073ad3a92e7f69c5927341/jcoPalm/MusicScreen/MusicScreen.c
const void DEBUGBOX(char *ARGSTR1, char *ARGSTR2) {
  char buf[MAX_STRING_LENGTH];
  int l=0;
  l+=StrPrintF(buf+l, "%s %s:%d\n", __FUNCTION__, __FILE__, __LINE__);
  FrmCustomAlert(alertInfo, buf, ARGSTR1, ARGSTR2);
}

const void showKey(Char letter){
  char buf[8];
  StrPrintF(buf, "char %c\n",letter);
  DEBUGBOX("keyDownEvent\n", buf);
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags) {
  short err;
  EventType e;
  FormType *pfrm;
  UInt16 obj;
  UInt16 offset;
  Char *text;
  FieldType *pfld;
  Char *sentence = "zaza";
  UInt16 x;
  UInt16 y;
  UInt16 dx;
  Char letter[2];
  RectangleType rect;

  MemHandle *mInput;
  Char *pInput;
  MemHandle *mOutput;
  Char *pOutput;

  // Make sure only react to NormalLaunch, not Reset, Beam, Find, GoTo...
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    FrmGotoForm(Giraffe);
    offset=0;
    x = 20;
    y = 120;
    dx = 1;
    while(1){
      EvtGetEvent(&e, 100);
      if (SysHandleEvent(&e)) { continue; }
      if (MenuHandleEvent(NULL, &e, &err)) { continue; }
      switch (e.eType) {

        case keyDownEvent:
          if(e.data.keyDown.chr == sentence[offset]){
            offset++;
            StrPrintF(letter, "%c", sentence[offset]);
            if(offset == StrLen(sentence)){ showKey('!'); }
          }
          break;

        case ctlSelectEvent:
          if (e.data.ctlSelect.controlID == Ok) {
            goto _quit;
	  }
          goto _default;
          break;

        case frmLoadEvent:
          FrmSetActiveForm(FrmInitForm(e.data.frmLoad.formID));
          break;

        case frmOpenEvent:
          pfrm = FrmGetActiveForm();
          StrPrintF(letter, "%c", sentence[offset]);
          FrmDrawForm(pfrm);
          break;

        case appStopEvent:
          goto _quit;

        case nilEvent:
          if(offset < StrLen(sentence)){
            WinDrawChars(letter, 1, x, y);
            x = x + dx;
            if(x > 150 || x < 20){
              dx *= -1;
            }
          }
        default:
        _default:
          if (FrmGetActiveForm())
            FrmHandleEvent(FrmGetActiveForm(), &e);
      }
    }

    _quit:
      FrmCloseAllForms();
						
  }
  return 0;
}

