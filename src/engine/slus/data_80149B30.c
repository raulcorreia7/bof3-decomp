#include "slus.h"

const struct MenuPanelModes g_MessagePanelModes = {{
    Menu_UpdateMessageWindow,
    Menu_UpdateMessageChoice,
    Menu_UpdateMessagePreset,
}};
const struct MenuPanelSteps g_MessageWindowSteps = {{
    Menu_OpenMessagePanel,
    Menu_GrowMessagePanel,
    Menu_DrawMessagePanel,
    Menu_ShrinkMessagePanel,
    Menu_ClosePanel,
}};
const struct MenuPanelSteps g_MessageChoiceSteps = {{
    Menu_OpenMessageChoice,
    Menu_GrowMessagePanel,
    Menu_DrawMessageChoice,
    Menu_ShrinkMessagePanel,
    Menu_ReleaseMessagePanel,
}};
const struct MenuPanelSteps g_MessagePresetSteps = {{
    Menu_OpenMessagePreset,
    Menu_GrowMessagePanel,
    Menu_DrawMessagePreset,
    Menu_ShrinkMessagePanel,
    Menu_ReleaseMessagePanel,
}};
