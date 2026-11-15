#include "game_00.h"

typedef struct GameScriptState {
    u8  unk_00;
    u8  unk_01;
    u8  unk_02;
    u8  pad_03[4];
    u8  unk_07;
    u8  route_08;
    u8  pad_09;
    u16 cursor;
} GameScriptState;

MATCH u8 func_801A8D38(void* sub, s32 target) {
    u8 script;
    u8 value;
    u8 sel;

    sel           = g_Task->direction_08;
    g_ScriptState = (void*)sub;
    sel           = func_801A8F94(sub, (u8*)target, sel);
    script        = ((u8*)target)[((GameScriptState*)sub)->cursor];
    switch (script & 0xF0) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
            value = ((u8*)target)[((GameScriptState*)sub)->cursor];
            sel   = (u8)(value - 0x10) >> 3;
            value &= 7;
            ((GameScriptState*)sub)->unk_07 = value;
            if (value != 0) {
                if (Actor_GetOwner() != 2) {
                    Area_MoveActorRoute(sub, sel);
                } else {
                    Area_SetFacingOffsetX(sel);
                }
            }
            break;
        case 0x50:
            ((GameScriptState*)sub)->unk_01 = script & 0xF;
            break;
        case 0x60:
            sel = func_801ABA24(sub, target, sel);
            break;
        case 0x80:
            sel = func_801AB458(sub, (const u8*)target, sel);
            break;
        case 0x90:
            sel = func_801AB8B0(sub, (u8*)target, sel);
            break;
        case 0xA0:
            ((GameScriptState*)sub)->cursor--;
            break;
        case 0xC0:
            sel = func_801AAB00(sub, target, sel);
            break;
        case 0xD0:
            sel = func_801AA470(sub, target, sel);
            break;
        case 0xE0:
            sel = func_801A9944(sub, target, sel);
            break;
        case 0xF0:
            sel = func_801A9DE8(sub, (const u8*)target, sel);
            break;
    }
    ((GameScriptState*)sub)->cursor++;
    return sel;
}
