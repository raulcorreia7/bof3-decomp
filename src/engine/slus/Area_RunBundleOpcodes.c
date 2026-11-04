#include "engine/slus/slus.h"

/* mirrors bit 0 of D_80146871 into D_8014933C, walks the bundle's opcode list g_AreaMapBundle.list_base_20 through the
 * D_8017F8F0 handlers (opcode = low six bits of byte +3, byte +2 the stride), marks the palette dirty via
 * func_801580A4, then walks g_AreaMapBundle.object_list_28 through func_801576FC; both stop at a zero terminator.
 */
MATCH void Area_RunBundleOpcodes(void) {
    u8* record;

    record     = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.list_base_20 * 4;
    D_8014933C = D_80146871 & 1;
    while (*(u32*)record != 0) {
        D_8017F8F0[record[3] & 0x3F](record);
        record += record[2] * 4;
    }
    Area_CyclePalette();
    record = (u8*)MAP_BUNDLE_BASE + g_AreaMapBundle.object_list_28 * 4;
    while (*(u32*)record != 0) {
        func_801576FC(record);
        record += *(u16*)(record + 2) * 4 + 4;
    }
}
