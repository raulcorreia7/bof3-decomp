#include "slus.h"

const MessageStateSteps g_MessageStateSteps = {{
    func_8015083C,
    UI_TickChoiceTimer,
    func_80150E48,
    func_80150F3C,
    func_801510DC,
    func_80151538,
    func_80151820,
    func_80151844,
}};

const MessageStateSteps D_80149A7C = {{
    func_80150F8C,
    func_8015115C,
    func_801511C8,
    UI_UpdateChoiceInput,
    func_80151334,
    Message_DispatchAnswerStep,
    Message_RestartRequest,
    func_80151480,
}};

const MessageChoiceSteps D_80149A9C = {{
    UI_ClosePanel,
    func_801515F4,
    UI_ScrollChoice,
    func_80151710,
    func_801517AC,
    func_8015102C,
}};
