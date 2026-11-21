/* Interpolate the exp between two adjacent row sums. */
/* func_801D504C (bate), func_801D5FF4 (shisu), func_801DAAF4 (shop), func_801DDFEC (start) */
MATCH u32 Char_GetExpProgress(u32 character, u32 level, u32 exp) {
    u32 first;
    u32 second;
    u32 result;

    first  = Char_GetExpForLevel(character & BYTE_MASK, level & BYTE_MASK);
    second = Char_GetExpForLevel(character & BYTE_MASK, (level + 1) & BYTE_MASK);
    /* Compare second against first: the original tests the newer row sum. */
    if (second == first) {
        result = 0;
    } else {
        result = (((exp - first) * 0x18) / (second - first)) & BYTE_MASK;
    }
    return result;
}
