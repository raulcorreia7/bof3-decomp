#include "engine/slus/slus.h"

/* resolves the requested area resource into the shared handle pair,
 * latches the raw request id in the area request slot, then resets the
 * front-end state block.
 */
/* func_80150284 */
MATCH void Message_Request(s32 request_id) { /* func_80150284 */
    u8* handle;

    handle           = Message_GetText(request_id & HALF_MASK);
    g_MessageScript  = handle;
    D_801490B0       = handle;
    g_MessageRequest = request_id;
    UI_ResetMessage();
}
