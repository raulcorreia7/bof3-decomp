/* Returns the first party member whose offset position lies within its reach of (x, y), or -1. */
/* Area_FindMemberAt (area086, area112) */
MATCH s8 Area_FindMemberAt(s32 x, s32 y) {
    s32 i;
    s32 sx;
    s32 sy;
    s32 px;
    s32 py;
    s32 reach;

    for (i = 0; i < g_PartySize; i++) {
        if (g_Game.members[i].header.flags != 0) {
            sx    = g_Game.members[i].unk_0C * g_Game.members[i].unk_09;
            sy    = g_Game.members[i].unk_10 * g_Game.members[i].unk_09;
            px    = g_Game.members[i].pos.x.fixed + sx;
            py    = g_Game.members[i].pos.y.fixed + sy;
            reach = (g_Game.members[i].speed + 2) << 15;
            if (abs(px - (x << 16)) < reach && abs(py - (y << 16)) < reach) {
                return i;
            }
        }
    }
    return -1;
}
