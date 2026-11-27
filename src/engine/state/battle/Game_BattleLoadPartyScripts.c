#include "engine/game/00/game_00.h"

/* func_801BEE5C */
MATCH bool Game_BattleLoadPartyScripts(void) {
    s32 slot;
    s32 off;
    u8  count;
    s32 initial_count;
    s32 phase2_count;
    s32 index;
    s32 type;
    u8  sel;
    s32 scan;
    u16 flags;
    u8* rec;
    u8* phase2_rec;
    /* FAKE: pin base to v0 for copy. */
    FAKE_REG(u8*, phase2_base, "v0");
    u8*  tbl;
    u8*  base;
    u16* source;
    u16* destination;
    s32  neg;
    /* FAKE: unused frame, 24 bytes. */
    FAKE_STACK_PADS(u8, 24);

    slot          = 0;
    initial_count = g_Game.party_size;
    if (initial_count <= 0)
        goto phase2; /* no active slot to update, stage the idle records */
    count = initial_count;
    scan  = 0;
scan_loop:
    if ((&D_80145E9B)[scan] != 0)
        goto found; /* the scan found an active record */
    slot++;
    scan += BATTLE_PARTY_STRIDE;
    if (slot < count)
        goto scan_loop; /* the next record is still active */
found:
    if (slot >= g_Game.party_size)
        goto phase2; /* no live record within the capacity */
    if (g_Game.party_size == 0)
        return 0;
    slot = 0;
    off  = 0;
    do {
        rec            = (u8*)g_Game.members + off;
        g_Game.current = rec;
        SELF_SET(rec);
        type  = rec[0x13C];
        flags = g_Characters[type].status;
        if ((flags & 0x4000) != 0) {
            Script_Stage(rec[0x4B], 0, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0xA00);
            SELF(Actor)->param.unk_0B = 0;
        } else {
            sel = rec[0x08];
            if ((sel & BYTE_MASK) == s_RouteIndexByMode[g_Battle.scroll_dir]) {
                if (rec[0x0B] != 0) {
                    Script_Stage(sel, 0, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0xA00);
                    SELF(Actor)->param.unk_0B = 0;
                }
            } else {
                rec[0x08] = (sel + rec[0x0B]) & 0x7;
                Script_Stage(SELF(Actor)->direction, 0, MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0xA00);
            }
            Script_AnimStepLoop();
        }
        off += BATTLE_PARTY_STRIDE;
    } while (++slot < g_Game.party_size);
    return 0;
phase2:
    if ((g_Battle.outcome.options & 0x4) != 0)
        return 1;
    phase2_count = g_Game.party_size;
    slot         = 0;
    if (phase2_count <= 0)
        return 1;
    tbl = (u8*)GAME_PALETTE_STAGE;
    neg = -0x40;
    off = 0;
    do {
        index       = 0;
        phase2_base = (u8*)g_Game.members + off;
        phase2_rec  = phase2_base;
        g_GameState = phase2_rec;
        SELF_SET(phase2_rec);
        do {
            base               = (u8*)((phase2_rec[0x05] << 6) + (u32)tbl);
            source             = (u16*)base;
            destination        = source + 0x60;
            destination[index] = source[index];
            index++;
        } while (index < 32);
        off += BATTLE_PARTY_STRIDE;
        Actor_SetSemiTransparent();
        SELF(Actor)->param.unk_0B     = 0;
        SELF(Actor)->tint.bytes.rgb.r = neg;
        SELF(Actor)->tint.bytes.rgb.g = neg;
        SELF(Actor)->tint.bytes.rgb.b = neg;
        SELF(Actor)->tint.bytes.flags = 1;
        slot++;
    } while (slot < g_Game.party_size);
    return 1;
}
