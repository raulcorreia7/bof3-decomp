#include "engine/slus/slus.h"

/* returns the index of the first empty record at g_Actors, or 0xFF
 * when all 0x1E records are occupied.
 */
MATCH s32 Actor_FindFree(void) {
    s32 index;
    s32 offset;

    index = 0;
    while ((index & 0xFF) < 30U) {
        offset = (index & 0xFF) * ACTOR_SIZE;
        if (((u8*)g_Actors)[offset] == 0) {
            return index & 0xFF;
        }
        index++;
    }
    return 0xFF;
}
