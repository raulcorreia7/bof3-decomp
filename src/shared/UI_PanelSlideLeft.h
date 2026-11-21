/* Slide the master panel 32 pixels left and clamp its x at 152. Members: func_800B254C (battle), func_8019973C (game), func_801EA070 (start), and the start copy UI_PanelSlideLeft2. */
/* The statements of UI_PanelSlideLeft. */
#define MENU_SLIDE_PANEL_LEFT()                 \
    do {                                        \
        MenuPanelTask* task = g_UiPanelCurrent; \
        s16            val;                     \
                                                \
        val         = task->pos.x - 32;         \
        task->pos.x = val;                      \
        if (val < 152) {                        \
            task->pos.x = 152;                  \
            task->state = 0;                    \
        }                                       \
    } while (0)
