/* Choose one random selectable battler id: collect the active slots 3-10 except excluded_slot, then return a random member. Readers: func_801E2948, func_801E2D4C and func_801E30B8 pass the chosen slot plus three; func_800AB0B8 passes the command slot plus three. */
/* func_800AB760 (battle), func_801E29B4 (battle) */
MATCH u8 Battle_PickRandomTarget(u8 excluded_slot) {
    u8  choices[8];
    u8  count;
    u8  slot;
    s32 random_value;

    count = 0u;
    slot  = 3u;
    do {
        if ((Battle_SlotIsBlocked(slot) == 0u) && (excluded_slot != slot)) {
            choices[count] = slot;
            count += 1u;
        }
        slot += 1u;
    } while (slot < 11u);

    random_value = rand();

    return choices[random_value % count];
}
