#include "area193_13.h"

MATCH void func_801F2DC8(void) {
    struct SelectionPair {
        u16 first;
        u16 second;
    };

    struct MessageSelections {
        struct SelectionPair pair[3];
    } table;

    s32 selection;

    selection          = g_UIMessageChoice;
    table              = *(struct MessageSelections*)D_801F2C04;
    g_UIMessageRequest = table.pair[selection].first;
    /* FAKE: Retail stores the first field before it loads the second. */
    FAKE_BARRIER();
    g_SceneEventState.step = table.pair[selection].second;
}
