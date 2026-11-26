#include "boss033_16.h"

MATCH void func_800C1F88(void) {
    Actor* work;
    u32    offset;
    u32    value;

    work = SELF(PartyMember);
    if (work->pos.z.fixed < work->gravity) {
        work->pos.z.fixed = work->pos.z.fixed + 0x01000000;
    } else {
        if (g_Battle.target_selector >= 3u) {
            work->pos.x.fixed = g_AreaScrollTargetX + ((s8*)g_BattleScrollDeltas)[g_Battle.scroll_dir * 2];
            offset            = g_Battle.scroll_dir * 2;
        } else {
            work->direction ^= 2u;
            value             = g_AreaScrollTargetX + ((s8*)g_BattleScrollDeltas)[(g_Battle.scroll_dir ^ 0x2) * 2];
            work              = SELF(PartyMember);
            work->pos.x.fixed = value;
            offset            = (g_Battle.scroll_dir ^ 0x2) * 2;
        }
        work->pos.y.fixed = g_AreaScrollTargetY + ((s8*)g_BattleScrollDeltas)[offset + 1];
        Script_Select(4);
        SELF(PartyMember)->header.step++;
    }
    Script_AnimStepOnce();
}
