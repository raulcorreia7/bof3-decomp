#include "battle_03.h"

/* writes the shared sprite value into the selected 0xC-byte palette fade
 * row, then restarts the stance when the enemy re-selected it and the step
 * byte's 0x40 bit is clear.
 */
MATCH void func_801E38C0(void) {
    s32          offset;
    PaletteFade* entry;
    u8           sprite;
    u8           value;

    offset                                     = SELF(PartyMember)->unk_07 * sizeof(PaletteFade);
    entry                                      = (PaletteFade*)((u8*)g_PaletteFades + offset);
    sprite                                     = g_Battle.unk_24[4];
    entry->offset.b                            = sprite;
    entry->offset.g                            = sprite;
    *((u8*)&g_PaletteFades->offset.r + offset) = sprite;
    if ((g_Battle.selection_latch == 0) || (((value = g_BattleActorTurn->command.target) != SELF(PartyMember)->slot) && ((value & BATTLE_TARGET_ENEMY_SIDE) == 0))) {
        GFX_PaletteFreeFade(SELF(PartyMember)->unk_07);
        SELF(PartyMember)->header.step = 0;
    }
}
