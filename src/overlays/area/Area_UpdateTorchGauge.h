/* Updates the torch gauge while the area draw flag is set. */
/* func_801F564C (area104), func_801F5B90 (area121) */
#define AREA_UPDATE_TORCH_GAUGE(is_idle, timer_zero, draw_icon, set_value) \
    s32 value;                                                              \
    s32 flag;                                                               \
                                                                            \
    if (g_AreaDrawFlags & 0x1B) {                                           \
        if (is_idle) {                                                      \
            if (timer_zero) {                                               \
                draw_icon(0xDC, 0x10, 0);                                   \
                set_value(0x40, 0);                                         \
                flag  = 1;                                                  \
                value = 0x40;                                               \
                value -= g_Game.members[0].param.unk_0B;                    \
                value &= 0xFF;                                              \
            } else {                                                        \
                if (g_FrameCount & 2) {                                     \
                    draw_icon(0xDC, 0x10, 1);                               \
                } else {                                                    \
                    draw_icon(0xDC, 0x10, 2);                               \
                }                                                           \
                value = 0x40;                                               \
                flag  = 0;                                                  \
            }                                                               \
        } else {                                                            \
            draw_icon(0xDC, 0x10, 0);                                       \
            set_value(0x40, 0);                                             \
            value = 0x40;                                                   \
            flag  = 1;                                                      \
        }                                                                   \
        set_value(value, flag);                                             \
    }
