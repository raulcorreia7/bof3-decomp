#include "engine/slus/slus.h"

/* calls func_8015A554, then increments the panel task's state byte.
 */
MATCH void func_80159964(void) {
    func_8015A554();
    g_MenuCurrentPanel->state += 1;
}
