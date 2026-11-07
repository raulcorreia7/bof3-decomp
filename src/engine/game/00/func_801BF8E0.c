#include "game_00.h"

MATCH void func_801BF8E0(void) {
    s32 count;
    s32 limit;
    s32 tmp;
    s32 index;
    s32 src;
    s32 dst;
    /* FAKE: dx pinned to a0, retail's register for the x delta; pure-C best 81.82%. */
    MATCH_REG(s32, dx, "a0");
    s32  dy;
    s32  row;
    s16  ret;
    s32  adx;
    s32* px;
    s32* py;
    s32  x;
    s32  y;
    u8   key;
    /* FAKE: retail frame reserves 16 bytes no statement uses; pure-C best 95.04%. */
    STACK_PADS(u8, 16);

    index = 0;
    limit = g_PartySize;
    if (limit > 0) {
        count = limit;
        src   = 0;
        dst   = 0;
        do {
            index++;
            tmp                               = *(s32*)((u8*)g_EncounterParty + src);
            *((s32*)((u8*)&D_80145EC4 + dst)) = tmp;
            tmp                               = *(s32*)((u8*)&g_EncounterParty[0].y + src);
            *((s32*)((u8*)&D_80145EC8 + dst)) = tmp;
            src += 2 * sizeof(s32);
            dst += BATTLE_PARTY_STRIDE;
        } while (index < count);
    }
    index = 0;
    limit = g_PartySize;
    if (limit > 0) {
        key = g_PartyFieldOrder[0];
        /* src doubles as the bound: retail keeps both in a0 (a separate local 89.26%). */
        src = limit;
        dst = 0;
    loop:
        if (key != (&D_80145F09)[dst]) {
            index++;
            dst += BATTLE_PARTY_STRIDE;
            if (index < src) {
                /* Retail tests the key at the loop head; a do/while measures 67.46%. */
                goto loop;
            }
        }
    }
    if (!(g_BattleOptions & 2)) {
        row              = index * BATTLE_PARTY_STRIDE;
        px               = &g_AreaScrollTargetX;
        dx               = *px;
        x                = *((s32*)((u8*)&D_80145EC4 + row));
        y                = *((s32*)((u8*)&D_80145EC8 + row));
        g_AreaCameraStep = 0x20;
        dx -= x;
        *px = x;
        py  = &g_AreaScrollTargetY;
        adx = abs(dx);
        dy  = abs(*py - y);
        *py = *((s32*)((u8*)&D_80145EC8 + row));
        adx = MAX(adx, dy);
        ret = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) - g_AreaCameraHeight;
        adx = (u32)adx >> 13;
        adx &= BYTE_MASK;
        if (adx != 0) {
            g_AreaCameraHeightStep = ret / adx;
        } else {
            g_AreaCameraHeightStep = 0;
        }
    }
}
