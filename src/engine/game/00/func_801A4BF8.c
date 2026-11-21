#include "game_00.h"

MATCH u8* func_801A4BF8(u8* script) {
    switch (script[0] >> 4) {
        case 0xE:
            Actor_Create(script);
            break;
        case 0xD:
            func_801A72E8(script);
            break;
        case 0xC:
            func_801A72B0(script);
            break;
        case 0x5:
            func_801A6F58(script);
            break;
        case 0xB:
            func_801A6C98(script);
            break;
        case 0xA:
            func_801A68C0(script);
            break;
        case 0x6:
            Actor_SpawnPartyFromRecord(script);
            break;
        case 0x7:
            func_801A623C(script);
            break;
        case 0x9:
            func_801A7330(script);
            break;
        case 0x4:
            func_801A5EFC(script);
            break;
        case 0x3:
            func_801A5B78(script);
            break;
        case 0x2:
            func_801A57F0(script);
            break;
        case 0x8:
            func_801A5400(script);
            break;
        case 0x1:
            func_801A50C0(script);
            break;
        case 0x0:
        default:
            Actor_SpawnFromRecord(script);
            break;
    }
    return script + s_ScriptOpcodeLengths[script[0] >> 4];
}
