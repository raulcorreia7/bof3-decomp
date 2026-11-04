#include "engine/slus/slus.h"

/* while bit 2 of g_AreaDrawFlags is set, walks the bundle record list at g_AreaMapBundle.list_base_22 (four-byte units): the
 * opcode (low seven bits of +3) selects the handler in D_8017F8FC and the word count at +2 advances; stops at a zero
 * terminator.
 */
MATCH void Area_RunBundleRecords(void) {
    u8* record;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) != 0) {
        record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.list_base_22 * 4;
        while (*(u32*)record != 0) {
            D_8017F8FC[record[3] & 0x7F](record);
            record += record[2] * 4;
        }
    }
}
