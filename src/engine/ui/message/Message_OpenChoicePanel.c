#include "engine/slus/slus.h"

/* calls Message_LayoutChoicePanel, then increments the panel task's state byte.
 */
/* func_80159964 */
MATCH void Message_OpenChoicePanel(void) {
    Message_LayoutChoicePanel();
    g_MenuCurrentPanel->state += 1;
}
