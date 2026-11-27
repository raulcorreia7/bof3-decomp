#include "slus.h"

const struct MenuPanelModes g_UIMessagePanelModes = {{
    UI_MessageUpdateWindow,
    UI_MessageUpdateChoicePanel,
    UI_MessageUpdatePresetPanel,
}};
const struct MenuPanelSteps g_UIMessageWindowSteps = {{
    UI_MessageOpenPanel,
    UI_MessageGrowPanel,
    UI_MessageDrawPanel,
    UI_MessageShrinkPanel,
    UI_PanelClose,
}};
const struct MenuPanelSteps g_UIMessageChoiceSteps = {{
    UI_MessageOpenChoicePanel,
    UI_MessageGrowPanel,
    UI_MessageDrawChoicePanel,
    UI_MessageShrinkPanel,
    UI_MessageReleasePanel,
}};
const struct MenuPanelSteps g_UIMessagePresetSteps = {{
    UI_MessageOpenPresetPanel,
    UI_MessageGrowPanel,
    UI_MessageDrawPresetPanel,
    UI_MessageShrinkPanel,
    UI_MessageReleasePanel,
}};
