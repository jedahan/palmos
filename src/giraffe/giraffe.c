#include "giraffe.h"
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>
#define MAX_STRING_LENGTH 1000

// many thanks to 
// https://github.com/Gaoithe/bgttoolbox/blob/bc47eb94b70ce1712d073ad3a92e7f69c5927341/jcoPalm/MusicScreen/MusicScreen.c
void DEBUGBOX(char *ARGSTR1, char *ARGSTR2) {
  char buf[MAX_STRING_LENGTH];
  int l=0;
  l+=StrPrintF(buf+l, "%s %s:%d\n", __FUNCTION__, __FILE__, __LINE__);
  FrmCustomAlert(alertInfo, buf, ARGSTR1, ARGSTR2);
}

void showKey(Char letter){
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

  MemHandle *mInput;
  Char *pInput;
  MemHandle *mOutput;
  Char *pOutput;

  // Make sure only react to NormalLaunch, not Reset, Beam, Find, GoTo...
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    FrmGotoForm(Giraffe);
    offset=0;
    while(1){
      EvtGetEvent(&e, 100);
      if (SysHandleEvent(&e)) { continue; }
      if (MenuHandleEvent((void *)0, &e, &err)) { continue; }
      switch (e.eType) {

        case keyDownEvent:
          if(e.data.keyDown.chr == sentence[offset]){
            offset++;
            if(offset == 4){ showKey('!'); }
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
          obj = FrmGetObjectIndex(pfrm, GraffitiField);
          FrmDrawForm(pfrm);
          break;

        case appStopEvent:
          goto _quit;

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

