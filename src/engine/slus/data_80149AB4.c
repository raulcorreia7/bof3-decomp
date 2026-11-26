#include "slus.h"

const MessageChoiceSteps g_UiMessageChoiceModes = {{
    UI_MessageChoiceIdle,
    UI_MessageUpdateChoice,
    UI_MessageChoiceRampRun,
    UI_MessageChoiceRampRun,
    (Callback)0x80151C00u,
    UI_MessageChoiceShiftRun,
}};
