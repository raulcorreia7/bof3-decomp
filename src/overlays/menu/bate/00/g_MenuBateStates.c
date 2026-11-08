#include "bate_00.h"

void func_801D0DD8(void);
/* func_801D0E04 */
void MenuBate_ResetPanels(void);
void func_801D0E38(void);
void func_801D2070(void);

Callback g_MenuBateStates[MENU_BATE_STEP_COUNT] = {func_801D0DD8, MenuBate_ResetPanels, func_801D0E38, func_801D2070};
