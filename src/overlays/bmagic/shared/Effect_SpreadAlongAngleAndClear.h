/* Moves the effect outward along its angle, raises it, and clears the actor when the counter ends; verify every image after a change. */
MATCH void Effect_SpreadAlongAngleAndClear(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = SELF(PartyMember)->param.unk_0B & 0xF;
    SELF(PartyMember)->unk_0C += 1;
    *angle_cell                    = phase << 8;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * SELF(PartyMember)->unk_0C;
    if (SELF(PartyMember)->unk_20 < SELF(PartyMember)->unk_14) {
        b                         = SELF(PartyMember)->unk_14 - SELF(PartyMember)->unk_20;
        SELF(PartyMember)->unk_14 = b;
        SELF(PartyMember)->pos.z.fixed += b;
    }
    if (g_FrameCount & 0x1) {
        count                     = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}
