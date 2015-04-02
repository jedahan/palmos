#include "IntExp.h"
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>

UInt16 offset = 0;
Char *sentence = "palmpilot";
Int16 formId;
Int16 prevFormId;

typedef struct {
  UInt16 x;
  UInt16 y;
  UInt16 dx;
  UInt16 dy;
  Char letter[9];
} Sprite;

typedef Sprite *SpritePtr;

Sprite nextLetter = {20, 120, 2, 0, NULL};

const void updateSprite(SpritePtr sprite){
  sprite->x += sprite->dx;
  sprite->y += sprite->dy;
  if(sprite->x > 150 || sprite->x < 20){ sprite->dx *= -1; }
  if(sprite->y > 150 || sprite->y < 20){ sprite->dy *= -1; }
  StrPrintF(sprite->letter, " %c ", sentence[offset]);
}

const void drawSprite(SpritePtr sprite){
  WinDrawChars(sprite->letter, 3, sprite->x, sprite->y);
}

static Boolean GraffitiFormHandleEvent(EventPtr event){
  Boolean handled = false;
  switch (event->eType) {
    case frmOpenEvent:
      FrmDrawForm(FrmGetActiveForm());
      handled = true;
      break;
    case keyDownEvent:
      if(event->data.keyDown.chr == sentence[offset]){
        offset++;
        if(offset == StrLen(sentence)){ FrmGotoForm(WinForm); }
      }
      handled = true;
      break;
    case nilEvent: {
      if(offset < StrLen(sentence)){
        updateSprite(&nextLetter);
        drawSprite(&nextLetter);
      }
      handled = true;
      break;
    }
    default:
      break;
  }
  return handled;
}

static Boolean WinFormHandleEvent(EventPtr event){
  Boolean handled = false;
  switch (event->eType) {
    case frmOpenEvent:
      FrmDrawForm(FrmGetActiveForm());
      handled = true;
      break;
    case ctlSelectEvent:
      if (event->data.ctlSelect.controlID == DoneButton){
        FrmGotoForm(HelpForm);
        handled = true;
      }
    default:
      break;
  }
  return handled;
}

static Boolean GraffitiHelpFormHandleEvent(EventPtr event){
  Boolean handled = false;
  switch (event->eType) {
    case frmOpenEvent:
      FrmDrawForm(FrmGetActiveForm());
      handled = true;
      break;
    case keyDownEvent:
      FrmGotoForm(prevFormId);
      handled = true;
      break;
    default:
      break;
  }
  return handled;
}


static Boolean HelpFormHandleEvent(EventPtr event){
  Boolean handled = false;
  switch (event->eType) {
    case frmOpenEvent:
      FrmDrawForm(FrmGetActiveForm());
      handled = true;
      break;
    case keyDownEvent:
      FrmGotoForm(GraffitiForm);
      handled = true;
      break;
    default:
      break;
  }
  return handled;
}

static Boolean AppHandleEvent(EventPtr event){
  FormPtr pfrm;
  Boolean handled = false;
  switch (event->eType){
    case frmLoadEvent:
      prevFormId = formId;
      formId = event->data.frmLoad.formID;
      pfrm = FrmInitForm(formId);
      FrmSetActiveForm(pfrm);
      switch (formId){
       case GraffitiForm:
          FrmSetEventHandler(pfrm, GraffitiFormHandleEvent);
          handled = true;
          break;
        case HelpForm:
          offset = 0;
          FrmSetEventHandler(pfrm, HelpFormHandleEvent);
          handled = true;
          break;
        case WinForm:
          FrmSetEventHandler(pfrm, WinFormHandleEvent);
          handled = true;
          break;
        case GraffitiHelpForm:
          FrmSetEventHandler(pfrm, GraffitiHelpFormHandleEvent);
          handled = true;
          break;
        default:
          break;
      }
      break;
    case menuEvent:
      MenuEraseStatus(NULL);
      switch (event->data.menu.itemID) {
        case MainMenuGraffitiHelpCmd:
          FrmGotoForm(GraffitiHelpForm);
          handled = true;
          break;
         case MainMenuRestartCmd:
          FrmGotoForm(HelpForm);
          handled = true;
          break;
        default:
          break;
      }
      break;
    case keyDownEvent:
      if (event->data.keyDown.chr == vchrHardPower){
        FrmGotoForm(HelpForm);
      }
      break;
    default:
      break;
  }
  return handled;
}

static void AppEventLoop(void){
  EventType event;
  short error;
  UInt16 nilEvents;
  do {
    EvtGetEvent(&event, 25);
    if (MenuHandleEvent(NULL, &event, &error)) { nilEvents=0; continue; }
    if (AppHandleEvent(&event)){ if(event.eType!=nilEvent){nilEvents=0;} continue; }
    if (SysHandleEvent(&event)) { nilEvents=0; continue; }
    if (event.eType == nilEvent){
      nilEvents++;
      if(nilEvents++ > 40 * 60){
        nilEvents = 0;
        if(FrmGetActiveFormID()!=HelpForm){
          FrmGotoForm(HelpForm);
        }
        continue;
      }
    }
    FrmDispatchEvent(&event);
  } while (event.eType != appStopEvent);
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags) {
  short err;
  EventType e;
  UInt16 obj;
  FieldType *pfld;

  // Make sure only react to NormalLaunch, not Reset, Beam, Find, GoTo...
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    FrmGotoForm(HelpForm);
    AppEventLoop();
    FrmCloseAllForms();
  }
  return 0;
}
