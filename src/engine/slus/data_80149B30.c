#include "slus.h"

const struct MenuPanelModes g_MessagePanelModes = {{
    Message_UpdateWindow,
    Message_UpdateChoicePanel,
    Message_UpdatePresetPanel,
}};
const struct MenuPanelSteps g_MessageWindowSteps = {{
    Message_OpenPanel,
    Message_GrowPanel,
    Message_DrawPanel,
    Message_ShrinkPanel,
    Menu_ClosePanel,
}};
const struct MenuPanelSteps g_MessageChoiceSteps = {{
    Message_OpenChoicePanel,
    Message_GrowPanel,
    Message_DrawChoicePanel,
    Message_ShrinkPanel,
    Message_ReleasePanel,
}};
const struct MenuPanelSteps g_MessagePresetSteps = {{
    Message_OpenPresetPanel,
    Message_GrowPanel,
    Message_DrawPresetPanel,
    Message_ShrinkPanel,
    Message_ReleasePanel,
}};
