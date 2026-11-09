#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4). */
MATCH void func_8015999C(void) {
    Slus_DrawPanelBox();
    UI_DrawTextRows();
    func_8015A264();
}
