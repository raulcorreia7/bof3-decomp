#include "area174_13.h"

/* func_801F4F28 */
MATCH void Scene_WaitEmi(void) {
    if (!EMI_IsReady()) {
        g_ScriptState->cursor -= 2;
    }
}
