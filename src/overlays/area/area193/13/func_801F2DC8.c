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

    selection        = D_801490C7;
    table            = *(struct MessageSelections*)D_801F2C04;
    g_MessageRequest = table.pair[selection].first;
    /* FAKE: Retail stores the first field before it loads the second. */
    MATCH_FAKE_BARRIER();
    g_SceneEventStep = table.pair[selection].second;
}
