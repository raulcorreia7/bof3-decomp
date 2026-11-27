#include "slus.h"

const MessageChoiceSteps g_UIMessageChoiceModes = {{
    UI_MessageChoiceIdle,
    UI_MessageUpdateChoice,
    UI_MessageChoiceRampRun,
    UI_MessageChoiceRampRun,
    (Callback)0x80151C00u,
    UI_MessageChoiceShiftRun,
}};
