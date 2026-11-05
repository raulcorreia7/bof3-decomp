#include "battle_15.h"

extern void Battle_Unk0E1BitModify(u8* record, s32 bit, u8 set);
extern u8   Battle_Unk0E1BitTest(volatile u8* entry, s32 bit_index);

/* walks the four battle event packets of the current enemy kind and
 * applies the ones whose trigger test passes, then hands the frame to the
 * event dispatcher.
 */
MATCH void func_8009BBE8(void) {
    BattleEventPacket* packet;
    u8                 i;

    for (i = 0; i < 4; i++) {
        packet =
            (BattleEventPacket*)(MEM_PTR(u8, 0x800E407Cu) + (u32)g_BattleCurrentEnemy->kind * 0x88u + (u32)i * 0x10u);
        switch (packet->kind) {
            case 0:
                if (func_8009C8AC(1) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 1:
                if (func_8009C8AC(2) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 2:
                if (func_8009C8AC(4) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 3:
                if (func_8009C8AC(8) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 4:
                if (func_8009C8AC(0x10) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 5:
                if (func_8009C8AC(0x20) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 6:
                if (func_8009C8AC(0x40) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 7:
                if (func_8009C8AC(0x100) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 8:
                if (func_8009C8AC(0x80) != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 9:
                if (LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY && g_BattleCurrentEnemy->hp_change != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 10:
                if (LOBU(g_BattleActionType) == BATTLE_ACTION_ATTACK && g_BattleCurrentEnemy->hp_change != 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 22:
                if (g_BattleCurrentEnemy->status & STATUS_BLIND) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 23:
                if (g_BattleCurrentEnemy->status & STATUS_POISONED) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 24:
                if (g_BattleCurrentEnemy->drops[0].rate_02 == 0) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
            case 33:
                if (func_8009C8AC(1) != 0) {
                    func_8009C994(g_BattleCurrentEnemy, packet);
                }
                break;
            case 34:
                if (func_8009C8AC(2) != 0) {
                    func_8009C994(g_BattleCurrentEnemy, packet);
                }
                break;
            case 35:
                if (func_8009C8AC(4) != 0) {
                    func_8009C994(g_BattleCurrentEnemy, packet);
                }
                break;
            case 36:
                if (LOBU(g_BattleActionType) == BATTLE_ACTION_ATTACK && g_BattleCurrentEnemy->hp_change != 0) {
                    func_8009C994(g_BattleCurrentEnemy, packet);
                }
                break;
            case 37:
                if ((s32)g_BattleCurrentEnemy->hp <= (s32)g_BattleCurrentEnemy->hp_change) {
                    if (Battle_Unk0E1BitTest(g_BattleCurrentEnemy, i) == 0) {
                        func_8009C994(g_BattleCurrentEnemy, packet);
                        Battle_Unk0E1BitModify(g_BattleCurrentEnemy, i, 1);
                    }
                }
                break;
        }
    }
    func_8009CFEC();
}
