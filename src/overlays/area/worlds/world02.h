#ifndef WORLD02_FAMILY_H
#define WORLD02_FAMILY_H

#include "overlays/area/area.h"
#include "overlays/area/shared/UI_MessageShowParty.h"
#include "overlays/area/shared/WorldAreaRequest.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* Clear the message request, then store the script result the UI message choice selects.
 * A statement macro; the two arguments are the case 0 and case 1 results. */
#define AREA_SET_MESSAGE_CHOICE_RESULT(choice_zero, choice_one) \
    MESSAGE_REQUEST_CLEAR();                                    \
    switch (g_UIMessageChoice) {                                \
        case 0:                                                 \
            g_ScriptVars[0] = (choice_zero);                    \
            break;                                              \
        case 1:                                                 \
            g_ScriptVars[0] = (choice_one);                     \
            break;                                              \
    }

/* The per-actor 16-byte turn records. */

extern Callback D_801F5750[];

#endif
