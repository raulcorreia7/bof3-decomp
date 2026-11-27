#include "engine/slus/slus.h"

/* calls UI_MessageLayoutChoicePanel, then increments the panel task's state byte.
 */
/* func_80159964 */
MATCH void UI_MessageOpenChoicePanel(void) {
    UI_MessageLayoutChoicePanel();
    g_UIPanelCurrent->state += 1;
}
