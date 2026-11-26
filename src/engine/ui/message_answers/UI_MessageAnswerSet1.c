#include "engine/slus/slus.h"

/* func_801523D0 */
/* Stores the answer message of choice slot 1 (row 2). */
MATCH void UI_MessageAnswerSet1(void) {
    SLUS_SELECT_ANSWER_MESSAGE(2, 0x1E, 0x28);
}
