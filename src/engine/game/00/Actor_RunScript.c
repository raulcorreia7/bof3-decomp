#include "game_00.h"

/* func_801A8D38 */
MATCH u8 Actor_RunScript(void* sub, s32 target) {
    u8 script;
    u8 value;
    u8 sel;

    sel           = g_Task->direction;
    g_ScriptState = (void*)sub;
    sel           = Actor_RunFlowOps(sub, (u8*)target, sel);
    script        = ((u8*)target)[((ScriptState*)sub)->cursor];
    switch (script & 0xF0) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
            value = ((u8*)target)[((ScriptState*)sub)->cursor];
            sel   = (u8)(value - 0x10) >> 3;
            value &= 7;
            ((ScriptState*)sub)->unk_07 = value;
            if (value != 0) {
                if (Actor_GetOwner() != 2) {
                    Area_MoveActorRoute(sub, sel);
                } else {
                    Area_SetFacingOffsetX(sel);
                }
            }
            break;
        case 0x50:
            ((ScriptState*)sub)->unk_01 = script & 0xF;
            break;
        case 0x60:
            sel = Actor_RunFaceOps(sub, target, sel);
            break;
        case 0x80:
            sel = Actor_RunStageOps(sub, (const u8*)target, sel);
            break;
        case 0x90:
            sel = Actor_RunSpawnOps(sub, (u8*)target, sel);
            break;
        case 0xA0:
            ((ScriptState*)sub)->cursor--;
            break;
        case 0xC0:
            sel = Actor_RunAppearanceOps(sub, target, sel);
            break;
        case 0xD0:
            sel = Actor_RunWaitOps(sub, target, sel);
            break;
        case 0xE0:
            sel = Actor_RunControlOps(sub, target, sel);
            break;
        case 0xF0:
            sel = Actor_RunMotionOps(sub, (const u8*)target, sel);
            break;
    }
    ((ScriptState*)sub)->cursor++;
    return sel;
}
