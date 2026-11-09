/* Round a sprite cell coordinate scaled by the work scale. */
/* func_800C3254 (boss055), func_8014CE48 (slus), func_801F3DCC (area198) */
MATCH s32 Area_RoundSpriteCoordinate(s32 pair, s32 step) {
    s32 high;

    if ((step >= 0) && ((u16)pair != 0)) {
        high = pair >> 16;
        pair &= HALF_MASK;
        pair |= (high + 1) << 16;
    }
    return pair >> 16;
}
