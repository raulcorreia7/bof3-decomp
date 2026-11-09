#include "engine/slus/slus.h"

/* while bit 2 of g_AreaDrawFlags is set, walks the bundle record list at g_AreaMapBundle.list_base_22 (four-byte units). */
MATCH void Area_RunBundleRecords(void) {
    u8* record;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) != 0) {
        record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.list_base_22 * 4;
        while (*(u32*)record != 0) {
            g_BundleRecordOpcodes[record[3] & 0x7F](record);
            record += record[2] * 4;
        }
    }
}
