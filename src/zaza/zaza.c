#include "zaza.h"
#include <System/SystemPublic.h>
#include <UI/UIPublic.h>
#define MAX_STRING_LENGTH 1000

UInt16 offset = 0;
Char *sentence = "zaza";

// many thanks to 
// https://github.com/Gaoithe/bgttoolbox/blob/bc47eb94b70ce1712d073ad3a92e7f69c5927341/jcoPalm/MusicScreen/MusicScreen.c
const void DEBUGBOX(char *ARGSTR1, char *ARGSTR2) {
  char buf[MAX_STRING_LENGTH];
  int l=0;
  l+=StrPrintF(buf+l, "%s %s:%d\n", __FUNCTION__, __FILE__, __LINE__);
  FrmCustomAlert(Alert, buf, ARGSTR1, ARGSTR2);
}

const void showKey(Char letter){
  char buf[8];
  StrPrintF(buf, "char %c\n",letter);
  DEBUGBOX("keyDownEvent\n", buf);
}

typedef struct {
  UInt16 x;
  UInt16 y;
  UInt16 dx;
  UInt16 dy;
  Char letter[4];
} Sprite;

typedef Sprite *SpritePtr;

Sprite nextLetter = {20, 120, 1, 0, NULL};

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
    default:
      break;
  }
  return handled;
}

static Boolean AppHandleEvent(EventPtr event){
  FormPtr pfrm;
  Int16 formId;
  Boolean handled = false;
  switch (event->eType){
    case frmLoadEvent:
      formId = event->data.frmLoad.formID;
      pfrm = FrmInitForm(formId);
      FrmSetActiveForm(pfrm);
      switch (formId){
        case GraffitiForm:
          FrmSetEventHandler(pfrm, GraffitiFormHandleEvent);
          handled = true;
          break;
        case WinForm:
          FrmSetEventHandler(pfrm, WinFormHandleEvent);
          handled = true;
          break;
        default:
          break;
      }
      break;
    case menuEvent:
      MenuEraseStatus(NULL);
      switch (event->data.menu.itemID) {
        case MainOptionsAboutCmd:
          FrmAlert(HelpAlert);
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

static void AppEventLoop(void){
  EventType event;
  short error;
  do {
    EvtGetEvent(&event, 100);
    if (MenuHandleEvent(NULL, &event, &error)) { continue; }
    if (AppHandleEvent(&event)){ continue; }
    if (SysHandleEvent(&event)) { continue; }
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
    FrmGotoForm(GraffitiForm);
    AppEventLoop();
    FrmCloseAllForms();
  }
  return 0;
}
