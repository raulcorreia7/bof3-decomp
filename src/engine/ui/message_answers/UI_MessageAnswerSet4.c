#include "engine/slus/slus.h"

/* func_801524C0 */
/* Stores the answer message of choice slot 4 (row 8). */
MATCH void UI_MessageAnswerSet4(void) {
    SLUS_SELECT_ANSWER_MESSAGE(8, 0x1E, 0x32);
}
