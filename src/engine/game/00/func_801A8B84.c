#include "game_00.h"

MATCH s8 func_801A8B84(s32 handler_x, s32 handler_y) {
    s32 kind;

    kind = LOHU(g_GameAreaId);
    switch (kind) {
        case AREA_ID_MOMO_TOWER_FIRST_FLOOR:
            return func_801F3400();
        case AREA_ID_MOMO_TOWER_TOP:
            return func_801F4C28();
        case AREA_ID_RELAY_POINT_A_PLATFORM:
            return func_801F4140();
        case AREA_ID_CAER_XHAN_LIFT_AREA:
            return func_801F4108();
        case AREA_ID_MYRIA_STATION_WORKERS:
            return func_801F48B4();
        case AREA_ID_MYRIA_STATION_HEAL:
            return func_801F3A28();
        case AREA_ID_MYRIA_STATION_PLANT_ROOM:
            return func_801F3EBC();
        case AREA_ID_MYRIA_STATION_AFTER_SAMPLES:
            return func_801F4DF8();
        default:
            return 0;
    }
}
