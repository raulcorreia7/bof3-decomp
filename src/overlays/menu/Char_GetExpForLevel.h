/* Sum the first count u16 entries at 8-byte stride of one 0x318-byte row of the level-growth table, returning -1 for a count of 100 or more and 0 for an empty count. */
/* func_801D1C44 (sisyou), func_801D4FD0 (bate), func_801D5F78 (shisu), func_801DAA78 (shop), func_801DDF70 (start) */
MATCH s32 Char_GetExpForLevel(s32 character, s32 level) {
    /* FAKE: unused volatile pins the 8B dead frame. */
    volatile s32 unused;
    u32          temp;
    s32          count;
    s32          total;
    s32          base;

    temp = (u32)(level & BYTE_MASK);
    if (temp >= 0x64) {
        return -1;
    }
    count = 0;
    total = 0;
    if (temp == 0) {
        goto done;
    }
    base = (character & BYTE_MASK) * 0x318;
again:
    total += (s32) * (u16*)((u8*)&g_LevelGrowth + (base + ((count & BYTE_MASK) * 8)));
    count += 1;
    if ((u32)(count & BYTE_MASK) < temp) {
        goto again;
    }
done:
    return total;
}
