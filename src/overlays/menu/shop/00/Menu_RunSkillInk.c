#include "shop_00.h"

/* func_801DF978 */
MATCH void Menu_RunSkillInk(void) {
    SYS_DISPATCH_BYTE(g_SkillInkSteps, g_MenuStep.sub_step);
}
