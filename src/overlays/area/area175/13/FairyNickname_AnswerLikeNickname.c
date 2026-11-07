#include "area175_13.h"

/* func_801F3DB8 */
MATCH void FairyNickname_AnswerLikeNickname(void) {
    u8 selection;

    /* The caller stores the selected slot as an unsigned byte. */
    selection = MEM(u8, &g_MessageChoice);
    MESSAGE_REQUEST_CLEAR();
    D_801F2945 = selection;
}
