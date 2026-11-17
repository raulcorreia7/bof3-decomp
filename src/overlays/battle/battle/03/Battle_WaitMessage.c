#include "battle_03.h"

/* func_801EA848 */
MATCH void Battle_WaitMessage(void) {
    if (D_801EC328 != D_801EBF04) {
        BATTLE_PANEL_TASK->state++;
        D_801EC2E4 = 1;
    }
}
