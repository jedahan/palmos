#include "giraffe.h"
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags) {
  short err;
  EventType e;
  FormType *pfrm;
  UInt16 obj;

  // Make sure only react to NormalLaunch, not Reset, Beam, Find, GoTo...
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    FrmGotoForm(Giraffe);
    while(1){
      EvtGetEvent(&e, 100);
      if (SysHandleEvent(&e)) { continue; }
      if (MenuHandleEvent((void *)0, &e, &err)) { continue; }
      switch (e.eType) {

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
          FrmSetFocus(pfrm, obj);
          break;

        case menuEvent:
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

