#include "engine/slus/slus.h"

/* func_80152470 */
/* Stores the answer message of choice slot 3 (row 6). */
MATCH void UI_MessageAnswerSet3(void) {
    SLUS_SELECT_ANSWER_MESSAGE(6, 0x3C, 0x46);
}
