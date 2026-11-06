#include "engine/slus/slus.h"

/* resolves the area message bank slot for the requested index into
 * the shared handle pair, runs the front-end reset, then latches the raw index
 * in the area request slot.
 */
/* func_80150224 */
MATCH void Message_StartAreaMessage(s32 message_index) { /* func_80150224 */
    u32 handle;

    handle = *(u16*)(SLUS_LOAD_ADDRESS + (s16)message_index * 2);
    handle += SLUS_LOAD_ADDRESS;
    g_MessageScript = handle;
    D_801490B0 = (u8*)handle;
    UI_ResetMessage();
    g_MessageRequest = message_index;
}
