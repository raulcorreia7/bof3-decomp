#include "magic054_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC2C(void) {
    Magic054Steps table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

/* Spawns one effect slot per living battler on the selected side, marks each slot busy, and
 * otherwise applies the encounter 0x37 damage flags and advances the local work. */
MATCH void func_801EEC98(void) {
    PartyMember* member;
    PartyMember* saved;
    u32          index;
    u8           i;

    if (g_Battle.encounter == 0x37) {
        func_800A9610(g_Battle.target_selector, 0x10);
        TASK(PartyMember)->header.mode = 3;
        TASK(PartyMember)->unk_09      = 0x1E;
        return;
    }
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            BattleWorkImage* image;
            BattleWorkImage* slot;
            PartyMember*     work;

            if (func_801DB524((u8)(i + 3)) != 0) {
                continue;
            }
            func_801E24F8((u8)(i + 3), 4);
            index                                      = func_801E590C(1, 0x2C);
            image                                      = (BattleWorkImage*)&g_BattleEnemyBattlers[i];
            slot                                       = (BattleWorkImage*)&D_801EC330[index & BYTE_MASK];
            *slot                                      = *image;
            work                                       = TASK(PartyMember);
            D_801EC330[index & BYTE_MASK].unk_06       = 1;
            D_801EC330[index & BYTE_MASK].header.mode  = 0;
            D_801EC330[index & BYTE_MASK].header.step  = 0;
            D_801EC330[index & BYTE_MASK].effect_type  = 0x2C;
            D_801EC330[index & BYTE_MASK].unk_0B       = i;
            D_801EC330[index & BYTE_MASK].target.party = work;
            TASK(PartyMember)->param.unk_0B++;
            g_BattleEnemyBattlers[i].header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
    } else {
        for (i = 0; i < 3; i++) {
            BattleWorkImage* image;
            BattleWorkImage* slot;
            PartyMember*     work;

            if (func_801DB524(i) != 0) {
                continue;
            }
            member = &g_Game.members[i];
            saved  = TASK(PartyMember);
            TASK_SET(member);
            Script_Select((u8)(member->facing + 0x10));
            TASK_SET(saved);

            index                                      = func_801E590C(1, 0x2C);
            image                                      = (BattleWorkImage*)member;
            slot                                       = (BattleWorkImage*)&D_801EC330[index & BYTE_MASK];
            *slot                                      = *image;
            work                                       = TASK(PartyMember);
            D_801EC330[index & BYTE_MASK].unk_06       = 1;
            D_801EC330[index & BYTE_MASK].header.mode  = 0;
            D_801EC330[index & BYTE_MASK].header.step  = 0;
            D_801EC330[index & BYTE_MASK].effect_type  = 0x2C;
            D_801EC330[index & BYTE_MASK].unk_0B       = i;
            D_801EC330[index & BYTE_MASK].target.party = work;
            TASK(PartyMember)->param.unk_0B++;
            g_Game.members[i].header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
    }
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

#include "overlays/bmagic/shared/Effect_CountDownAndMarkDamaged.h"

/* func_801EF158 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF19C(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF238(void) {
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_BattleEnemyBattlers[TASK(PartyMember)->param.unk_0B].pos.z.fixed;
    } else {
        TASK(PartyMember)->pos.x.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_Game.members[TASK(PartyMember)->param.unk_0B].pos.z.fixed;
    }
    TASK(PartyMember)->scale.x = 0x10000;
    TASK(PartyMember)->scale.y = 0x10000;
    TASK(PartyMember)->unk_48  = 2;
    TASK(PartyMember)->unk_0C  = -0xC60;
    TASK(PartyMember)->unk_10  = 0x1080;
    TASK(PartyMember)->unk_18  = 0x60;
    TASK(PartyMember)->unk_1C  = -0x80;
    TASK(PartyMember)->header.step++;
}

MATCH void func_801EF3A4(void) {
    Script_AnimStepLoop();
    TASK(PartyMember)->unk_0C += TASK(PartyMember)->unk_18;
    TASK(PartyMember)->unk_10 += TASK(PartyMember)->unk_1C;
    TASK(PartyMember)->scale.x += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->scale.y += TASK(PartyMember)->unk_10;
    if (TASK(PartyMember)->unk_0C == 0) {
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF43C(void) {
    u8 timer;

    Script_AnimStepLoop();
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->unk_18 = 0x60;
        TASK(PartyMember)->unk_1C = -0x80;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* work;

    Script_AnimStepLoop();
    work = TASK(PartyMember);
    work->unk_0C += work->unk_18;
    work->unk_10 += work->unk_1C;
    work->scale.x += work->unk_0C;
    work->scale.y += work->unk_10;
    if (work->unk_0C == 0xC00) {
        work->header.step++;
    }
}

MATCH void func_801EF534(void) {
    u8 value;
    u8 value2;

    if (Script_AnimStepOnce() & BYTE_MASK) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            value2                                     = TASK(PartyMember)->param.unk_0B;
            g_BattleEnemyBattlers[value2].header.flags = g_BattleEnemyBattlers[value2].header.flags & 0xBF;
        } else {
            value                              = TASK(PartyMember)->param.unk_0B;
            g_Game.members[value].header.flags = g_Game.members[value].header.flags & ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"
