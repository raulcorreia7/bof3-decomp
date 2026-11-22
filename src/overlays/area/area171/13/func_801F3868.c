#include "area171_13.h"

MATCH void func_801F3868(void) {
    PartyMember* saved;
    PartyMember* record;
    u32          index;
    s32          i;
    u8           bounds;
    u8           type;

    g_GameFlags &= 0xDFFF;
    saved = TASK(PartyMember);
    i     = 0;
    if (g_PartySize != 0) {
        do {
            index       = i & 0xFF;
            record      = &g_Game.members[index];
            g_GameState = record;
            TASK_SET(record);
            if ((bounds = func_801F379C((u8)index)) == 0xFF) {
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
                saved->param.unk_0B |= BIT(index);
                g_AreaWalkFlags |= BIT(index);
                g_GameState->u.field.counter.unsigned_value = 2;
                TASK(PartyMember)->unk_09                   = 0;
                TASK(PartyMember)->facing                   = D_801F4188[bounds].unk_04;
                Script_Request(TASK(PartyMember)->facing);
                goto next_record;
            }
            if (TASK(PartyMember)->unk_09 == 0) {
                func_801C2538();
                if (index == 0) {
                    func_801C2710();
                }
            } else {
                type = D_801F4188[bounds].unk_04;
                if (TASK(PartyMember)->facing != type) {
                    TASK(PartyMember)->facing = type;
                    TASK(PartyMember)->unk_0C = -TASK(PartyMember)->unk_0C;
                    TASK(PartyMember)->unk_10 = -TASK(PartyMember)->unk_10;
                    TASK(PartyMember)->unk_14 = -TASK(PartyMember)->unk_14;
                    TASK(PartyMember)->unk_09 = 8 - TASK(PartyMember)->unk_09;
                }
            }
            func_801B0DFC();
            TASK(PartyMember)->unk_09--;
            Script_AnimStepLoop();
            g_GameFlags |= 0x2000;
        next_record:
            i++;
        } while ((u32)(i & 0xFF) < g_PartySize);
    }
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameFlags &= 0xDFFF;
    }
    TASK_SET(saved);
}
