#include "engine/slus/slus.h"

/* maps panel coordinates px/py into the map bundle (x = g_AreaTileOriginX + px/2 + py, y = g_AreaTileOriginY + px/2. */
MATCH void Area_GetCell(s32 px, s32 py, AreaCell* out) {
    AreaMapBundle* bundle;
    s32            width;
    s32            x2;
    s32            x;
    s32            y;
    u16            value;

    x = g_AreaTileOriginX + (px + 1) / 2 + py;
    y = g_AreaTileOriginY + px / 2 - py;

    if (x > 0) {
        bundle = (AreaMapBundle*)MAP_BUNDLE_BASE;
        width  = bundle->width;
        if (x < width - 1) {
            if (y > 0) {
                if (y < g_AreaMapBundle.height - 1) {
                    value =
                        *(u16*)((u8*)bundle + ((g_AreaMapBundle.grid_off4_02 * 4) + (x2 = x * 2) + (y * width * 2)));
                    if (value != 0) {
                        out->tile_x = x;
                        out->tile_y = y;
                        return;
                    }
                }
            }
        }
    }
    out->tile_x = 0;
    out->tile_y = 0;
}
