#ifndef OVERLAY_WORLD04_AREA167_13_H
#define OVERLAY_WORLD04_AREA167_13_H

/* The world04/area167/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The game mode the trigger records of this payload match. */
/* The payload includes per-state handler tables. */
extern u8 D_801F4A68[];
/* The effect's restart y and bottom y for each side. */
extern u8 D_801F4AC4[][2];
/* Trigger records at the tail of the payload: two match bytes, a mode nibble and a flag bit. */
extern u8 D_801F68B4[];

#define AREA167_ENTRY_TABLE(type, offset, index) AREA_PAYLOAD_FIELD(D_801F4A68, type, offset, index)

/* The per-sprite-row screen scale of the quad's far edge: a signed byte a row. */
#define AREA_ROW_SCALE_OFFSET                    0x34

/* Clear the message request; when the selection is idle, hand the scene to its script with result 0x60. */
#define AREA167_START_SCRIPT_ON_IDLE() \
    MESSAGE_REQUEST_CLEAR();           \
    if (MENU_SELECTION_IDLE()) {       \
        Game_SetScriptActive();        \
        g_ScriptVars[3]        = 0x60; \
        g_SceneEventState.mode = 0x20; \
        g_SceneEventState.step = 0xA;  \
    }

#endif
