#include "area030_04.h"

/* When the state byte is clear and the flag byte is 1, seeds the
 * work counter, queues SE 0x102, and bumps the work phase. */
/* func_801D9FE8 */
MATCH void Fishing_ReadyPrompt(void) {
    if (g_SpawnedActors[3].header.mode == 0 && g_SpawnedActors[1].header.mode == 1) {
        SELF(FishingState)->timer = 4;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SELF(FishingState)->sub_index += 1;
    }
    Fishing_DrawDimScreen();
}
