/* When the effect ticker runs down, marks the selected battlers as damaged (Battle_MarkDamaged with g_Battle.target_selector) and steps the handler. */
/* func_801EF05C (magic054), func_801EEE38 (magic103) */
MATCH void Effect_Hit(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        SELF(PartyMember)->header.mode += 1;
    }
}
