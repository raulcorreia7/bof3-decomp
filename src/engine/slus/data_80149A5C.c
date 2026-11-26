#include "slus.h"

const MessageStateSteps g_UiMessageStateSteps = {{
    UI_MessageRunScript,
    UI_MessageTickChoiceTimer,
    UI_MessageRunEnd,
    UI_MessageRunPage,
    UI_MessageRunChoice,
    UI_MessageRunScrollChoice,
    UI_MessageResumeScript,
    UI_MessageRunBoxEnd,
}};

const MessageStateSteps g_UiMessageChoiceStateSteps = {{
    UI_MessageWaitInput,
    UI_MessageOpenChoice,
    UI_MessageWaitChoiceReady,
    UI_MessageUpdateChoiceInput,
    UI_MessageToggleChoiceWindow,
    UI_MessageDispatchAnswerStep,
    UI_MessageRestartRequest,
    UI_MessageEndAfterChoice,
}};

const MessageChoiceSteps g_UiMessageScrollStateSteps = {{
    UI_MessageClosePanel,
    UI_MessageWaitChoiceOpen,
    UI_MessageScrollChoice,
    UI_MessageRunStepCloseChoice,
    UI_MessageWaitChoiceClosed,
    func_8015102C,
}};
