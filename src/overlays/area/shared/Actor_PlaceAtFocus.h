/* Copy the field focus point into the work position. */
/* func_801F2EC4 (area149), func_801F39D4 (area148), func_801F4434 (area167) */
MATCH void Actor_PlaceAtFocus(void) {
    u8* work;

    work                   = SELF(u8);
    FIELD(s32, work, 0x34) = g_AreaFocus.x.fixed;
    FIELD(s32, work, 0x38) = g_AreaFocus.y.fixed;
    FIELD(s32, work, 0x3C) = g_AreaFocus.z.fixed;
}
