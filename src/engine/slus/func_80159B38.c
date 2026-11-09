#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4). */
MATCH void func_80159B38(void) {
    Slus_DrawPanelBox();
    func_8015A098();
    func_8015A1D8();
}
