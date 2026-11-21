#include "slus.h"

const MessageStateSteps g_UiMessageStateSteps = {{
    UI_MessageRunScript,
    UI_MessageTickChoiceTimer,
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
    UI_MessageUpdateChoiceInput,
    func_80151334,
    UI_MessageDispatchAnswerStep,
    UI_MessageRestartRequest,
    func_80151480,
}};

const MessageChoiceSteps D_80149A9C = {{
    UI_MessageClosePanel,
    func_801515F4,
    UI_MessageScrollChoice,
    func_80151710,
    func_801517AC,
    func_8015102C,
}};
