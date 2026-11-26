#include "engine/slus/slus.h"

/* func_80152420 */
/* Stores the answer message of choice slot 2 (row 4). */
MATCH void UI_MessageAnswerSet2(void) {
    SLUS_SELECT_ANSWER_MESSAGE(4, 0x1E, 0x32);
}
