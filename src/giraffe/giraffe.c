#include "giraffe.h"
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
  FrmCustomAlert(alertInfo, buf, ARGSTR1, ARGSTR2);
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
  Char letter[2];
} Sprite;

typedef Sprite *SpritePtr;

const void updateSprite(SpritePtr sprite){
  sprite->x += sprite->dx;
  sprite->y += sprite->dy;
  if(sprite->x > 150 || sprite->x < 20){ sprite->dx *= -1; }
  if(sprite->y > 150 || sprite->y < 20){ sprite->dy *= -1; }
  StrPrintF(sprite->letter, "%c", sentence[offset]);
}

const void drawSprite(SpritePtr sprite){
  UInt16 width = FntCharsWidth( sprite->letter, StrLen( sprite->letter ) );
  IndexedColorType saveColor;
  RectangleType rect = { {sprite->x - 1, sprite->y - 1}, { width+2, 10} };

  saveColor = WinSetForeColor(UIColorGetTableEntryIndex(UIFieldBackground));
  WinSetForeColor(0);
  WinDrawRectangle(&rect, 0);
  WinSetForeColor(saveColor);
  WinDrawChars(sprite->letter, 1, sprite->x, sprite->y);
}

UInt32 PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags) {
  short err;
  EventType e;
  FormType *pfrm;
  UInt16 obj;
  FieldType *pfld;
  Sprite nextLetter = {20, 120, 1, 0, NULL};

  // Make sure only react to NormalLaunch, not Reset, Beam, Find, GoTo...
  if (cmd == sysAppLaunchCmdNormalLaunch) {
    FrmGotoForm(Giraffe);
    while(1){
      EvtGetEvent(&e, 100);
      if (SysHandleEvent(&e)) { continue; }
      if (MenuHandleEvent(NULL, &e, &err)) { continue; }
      switch (e.eType) {

        case keyDownEvent:
          if(e.data.keyDown.chr == sentence[offset]){
            offset++;
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
          FrmDrawForm(pfrm);
          break;

        case appStopEvent:
          goto _quit;

        case nilEvent:
          if(offset < StrLen(sentence)){
            updateSprite(&nextLetter);
            drawSprite(&nextLetter);
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

