#include "engine/slus/slus.h"

/* calls Menu_LayoutMessageChoice, then increments the panel task's state byte.
 */
/* func_80159964 */
MATCH void Menu_OpenMessageChoice(void) {
    Menu_LayoutMessageChoice();
    g_MenuCurrentPanel->state += 1;
}
