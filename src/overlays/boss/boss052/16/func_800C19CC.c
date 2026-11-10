#include "boss052_16.h"

typedef struct WorkChunk {
    u32 w0;
    u32 w1;
    u32 w2;
    u32 w3;
} WorkChunk;

MATCH void func_800C19CC(void) {
    u32        slot;
    WorkChunk* src;
    WorkChunk* dst;
    WorkChunk* end;
    u32        enemy;
    u8         battler;
    u32        off;

    if ((*(u32*)g_Task & 0x00FFFF00) != 0x00010700) {
        return;
    }
    if (((u8*)g_Task)[9] != 0) {
        return;
    }
    slot    = Battle_AllocEffect(3, 4);
    off     = (slot & 0xFF) * 0x78;
    battler = g_Battle.active_battler;
    enemy   = (u32)battler - 3;
    dst     = (WorkChunk*)((u8*)g_BattleEffects + off);
    src     = (WorkChunk*)((u8*)g_BattleEnemyBattlers + enemy * 0x118);
    end     = src + 7;
    do {
        *dst++ = *src++;
    } while (src != end);
    dst->w0 = src->w0;
    FAKE_BARRIER();
    {
        u32 idx                            = slot & 0xFF;
        g_BattleEffects[idx].header.mode   = 0;
        g_BattleEffects[idx].header.step   = 0;
        g_BattleEffects[idx].unk_06        = 3;
        g_BattleEffects[idx].handler_index = 4;
        g_BattleEffects[idx].arg.unk_09    = 0;
        g_BattleEffects[idx].unk_29        = 3;
    }
}
