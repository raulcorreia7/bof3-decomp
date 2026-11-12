/* Clears the effect slot table, copies the selected battler's pose into the effect and spawns the image's hidden child effects. */
/* func_801EED04 (magic158), func_801EED04 (magic166) */
MATCH void func_801EED04(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           i;
    u8           none;
    u8           slot;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    battler            = g_BattleSelectedActor;
    g_Task->facing     = battler->facing;
    /* kept: the facing store makes retail reread the work cell; one local for the whole copy merges the two loads. */
    work               = g_Task;
    work->pos.x        = battler->pos.x;
    work->pos.y        = battler->pos.y;
    work->pos.z        = battler->pos.z;
    work->param.unk_0B = 0;
    g_Task->header.mode++;
    /* kept: the GAME_NONE local holds 0xFF in a callee-saved register across the spawn loop; the literal is reloaded each pass. */
    for (i = 0, none = GAME_NONE; i < BMAGIC_EFFECT_SPAWN_COUNT; i++) {
        slot = BMagic_AllocEffect();
        if (slot != none) {
            BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09 = RANDOM_MASK(0x1F) + 1;
            g_Task->param.unk_0B++;
        }
    }
    SND_QueueSelectionFx(0x100);
}
