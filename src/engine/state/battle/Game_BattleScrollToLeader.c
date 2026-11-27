#include "engine/game/00/game_00.h"

/* func_801BF8E0 */
MATCH void Game_BattleScrollToLeader(void) {
    s32 count;
    s32 limit;
    s32 tmp;
    s32 index;
    s32 src;
    s32 dst;
    /* FAKE: dx pinned to a0, retail's register for the x delta; pure-C best 81.82%. */
    FAKE_REG(s32, dx, "a0");
    s32  dy;
    s32  member_offset;
    s16  ret;
    s32  adx;
    s32* px;
    s32* py;
    s32  x;
    s32  y;
    u8   key;

    index = 0;
    limit = g_Game.party_size;
    if (limit > 0) {
        count = limit;
        src   = 0;
        dst   = 0;
        do {
            index++;
            tmp                                                  = *(s32*)((u8*)g_AreaEncounterPlacement.party + src);
            *((s32*)((u8*)&g_Game.members[0].pos.x.fixed + dst)) = tmp;
            tmp                                                  = *(s32*)((u8*)&g_AreaEncounterPlacement.party[0].y + src);
            *((s32*)((u8*)&g_Game.members[0].pos.y.fixed + dst)) = tmp;
            src += 2 * sizeof(s32);
            dst += BATTLE_PARTY_STRIDE;
        } while (index < count);
    }
    index = 0;
    limit = g_Game.party_size;
    if (limit > 0) {
        key = g_PartyFieldOrder[0];
        src = limit;
        dst = 0;
    loop:
        if (key != FIELD(u8, &g_Game.members[0].chr.character_id, dst)) {
            index++;
            dst += BATTLE_PARTY_STRIDE;
            if (index < src) {
                goto loop;
            }
        }
    }
    if (!(g_Battle.outcome.options & 0x2)) {
        member_offset     = index * BATTLE_PARTY_STRIDE;
        px                = &g_AreaScrollTargetX;
        dx                = *px;
        x                 = *((s32*)((u8*)&g_Game.members[0].pos.x.fixed + member_offset));
        y                 = *((s32*)((u8*)&g_Game.members[0].pos.y.fixed + member_offset));
        g_AreaCameraSpeed = 0x20;
        dx -= x;
        *px = x;
        py  = &g_AreaScrollTargetY;
        adx = abs(dx);
        dy  = abs(*py - y);
        *py = *((s32*)((u8*)&g_Game.members[0].pos.y.fixed + member_offset));
        adx = MAX(adx, dy);
        {
            Coord sample_x = {g_AreaScrollTargetX};
            Coord sample_y = {g_AreaScrollTargetY};

            ret = Area_HeightSample(sample_x.fixed, sample_y.fixed) - g_AreaCameraHeight;
        }
        adx = (u32)adx >> 13;
        adx &= BYTE_MASK;
        if (adx != 0) {
            g_AreaCameraHeightDelta = ret / adx;
        } else {
            g_AreaCameraHeightDelta = 0;
        }
    }
}
