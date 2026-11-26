#include "engine/game/00/game_00.h"

#define SP_VALUES ((u8*)&D_1F800004 - 4)
#define SP_SLOTS  ((u8*)&D_1F800004)
#define SP_TAKEN  ((u8*)&D_1F800008)

/* func_801BE1B0 */
#ifdef NON_MATCHING
NON_MATCHING s32 Scene_SetupParty(u32 scene) {
    u8** lists;
    u8*  ids;
    u8   command;
    s32  cmds;
    u32  type;
    u8   count;
    u8   size;
    s32  i;
    s32  j;

    lists   = FIELD(u8*, GAME_TILE_RUN(g_GameAreaId), 0x14);
    ids     = lists[(u8)scene];
    cmds    = *ids++;
    command = cmds;
    type    = command & 0xC0;
    count   = cmds & 0xF;
    if (type == 0) {
        size = g_PartySize;
        if (size != count)
            return 1;
        for (i = 0; i < size; i++)
            SP_TAKEN[i] = g_PartyFieldOrder[i];
        for (i = 0; i < count; i++) {
            if (ids[i] != 0x80) {
                for (j = 0; j < g_PartySize; j++) {
                    if (g_Game.members[j].chr.character_id == ids[i]) {
                        SP_VALUES[i] = (u8)g_Game.members[j].unk_2C.value;
                        SP_SLOTS[i]  = j;
                        SP_TAKEN[j]  = 0xFF;
                        break;
                    }
                }
                if (j == g_PartySize)
                    return 1;
            } else {
                for (j = 0; j < g_PartySize; j++) {
                    if (SP_TAKEN[j] != GAME_NONE) {
                        SP_VALUES[i] = (u8)g_Game.members[j].unk_2C.value;
                        SP_SLOTS[i]  = j;
                        SP_TAKEN[j]  = 0xFF;
                        break;
                    }
                }
            }
        }
        for (i = 0; i < (u8)count; i++)
            g_PartyFieldOrder[i] = g_Game.members[SP_SLOTS[i]].chr.character_id;
        for (i = 0; i < (u8)count - 1; i++) {
            if (i != SP_SLOTS[i]) {
                Party_MemberSwap((u8)i, SP_SLOTS[i], 0);
                for (j = i; j < (u8)count; j++) {
                    if (i == SP_SLOTS[j]) {
                        SP_SLOTS[j] = SP_SLOTS[i];
                        break;
                    }
                }
            }
        }
        ids += count;
    } else if (type == 0x80) {
        if (g_PartySize < (u32)count)
            return 1;
    }
    func_801BE574(g_PartySize, ids);
    ids += count;
    command &= 0x30;
    if (command & 0x20)
        g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
    if (command == 0x30)
        ((void (*)(u8))Area_ScrollStartRoute)(*ids);
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    g_AreaWalkFlags |= AREA_WALK_MAP_LOADING;
    return 0;
}
#else
INCLUDE_ASM(Scene_SetupParty);
#endif
