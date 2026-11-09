/* Copy the field focus point into the work position. */
/* func_801F2EC4 (area149), func_801F39D4 (area148), func_801F4434 (area167) */
MATCH void Actor_PlaceAtFocus(void) {
    u8* work;

    work                   = (u8*)g_Task;
    FIELD(s32, work, 0x34) = D_80147A8C;
    FIELD(s32, work, 0x38) = g_AreaFocusY;
    FIELD(s32, work, 0x3C) = D_80147A94;
}
