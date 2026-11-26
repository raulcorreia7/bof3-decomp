#include "area118_13.h"

MATCH void func_801F4CD0(void) {
    PartyMember* saved;
    PartyMember* record;
    u32          index;
    s32          i;
    u8           bounds;
    u8           type;

    g_GameFlags &= 0xDFFF;
    saved = SELF(PartyMember);
    i     = 0;
    if (g_PartySize != 0) {
        do {
            index       = i & 0xFF;
            record      = &g_Game.members[index];
            g_GameState = record;
            SELF_SET(record);
            if ((bounds = func_801F4C08((u8)index)) == 0xFF) {
                if (((saved->param.unk_0B >> index) & 1) != 0) {
                    saved->param.unk_0B &= ~BIT(index);
                    g_AreaWalkFlags &= ~BIT(index);
                }
                goto next_record;
            }
            if (((saved->param.unk_0B >> index) & 1) == 0) {
                if ((((g_GameFlags | g_AreaWalkFlags) >> index) & 1) != 0) {
                    goto next_record;
                }
                g_GameState->u.field.counter.unsigned_value = 2;
                SELF(PartyMember)->unk_09                   = 0;
                saved->param.unk_0B |= BIT(index);
                g_AreaWalkFlags |= BIT(index);
                SELF(PartyMember)->facing = D_801F5998[bounds * 6];
                if (SYS_TestFlag(g_SceneEventFlags, D_801F5999[bounds * 6]) != 0) {
                    SELF(PartyMember)->facing ^= 4;
                }
                Script_Request(SELF(PartyMember)->facing);
                goto next_record;
            }
            if (SELF(PartyMember)->unk_09 == 0) {
                func_801C2538();
                if (index == 0) {
                    func_801C2710();
                }
            } else {
                type = D_801F5994[bounds * 6 + 4];
                if (SYS_TestFlag(g_SceneEventFlags, D_801F5999[bounds * 6]) != 0) {
                    type ^= 4;
                }
                if (SELF(PartyMember)->facing != type) {
                    SELF(PartyMember)->facing = type;
                    SELF(PartyMember)->unk_0C = -SELF(PartyMember)->unk_0C;
                    SELF(PartyMember)->unk_10 = -SELF(PartyMember)->unk_10;
                    SELF(PartyMember)->unk_14 = -SELF(PartyMember)->unk_14;
                    SELF(PartyMember)->unk_09 = 8 - SELF(PartyMember)->unk_09;
                }
            }
            func_801B0DFC();
            SELF(PartyMember)->unk_09--;
            Script_AnimStepLoop();
            g_GameFlags |= 0x2000;
        next_record:
            i++;
        } while ((u32)(i & 0xFF) < g_PartySize);
    }
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameFlags &= 0xDFFF;
    }
    SELF_SET(saved);
}
