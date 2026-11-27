#include "engine/slus/slus.h"

/* resolves the requested area resource into the shared handle pair,
 * latches the raw request id in the area request slot, then resets the
 * front-end state block.
 */
/* func_80150284 */
MATCH void UI_MessageRequest(s32 request_id) {
    u8* handle;

    handle             = UI_MessageGetText(request_id & HALF_MASK);
    g_UIMessageScript  = handle;
    D_801490B0         = handle;
    g_UIMessageRequest = request_id;
    UI_MessageReset();
}
