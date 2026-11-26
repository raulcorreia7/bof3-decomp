#include "slus.h"

const MessageChoiceSteps g_UiMessageChoiceModes = {{
    UI_MessageChoiceIdle,
    UI_MessageUpdateChoice,
    func_80151A98,
    func_80151A98,
    (Callback)0x80151C00u,
    func_80151D3C,
}};
