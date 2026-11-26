/* Once the script stream reports ready (Script_AnimStepOnce), sets the work flag 0x20, starts the tint at zero and steps the handler. */
/* func_801EFF28 (magic001), func_801F0024 (magic056) */
MATCH void Effect_PrimeTintOnScriptReady(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->header.step += 1;
    }
}
