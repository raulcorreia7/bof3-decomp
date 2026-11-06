#include "game_00.h"

MATCH s8 func_801A8728(s32 entry_x, s32 entry_y) {
    s32 shifted_result;

    if (!(func_801A8A98(entry_x, entry_y) & BYTE_MASK)) {
        switch (g_GameAreaId) {
            case 0x24:
                shifted_result = func_801F2C64(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MOMO_TOWER_OUTSIDE:
                shifted_result = func_801F4A18(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_RHAPALA_CHECKPOINT:
                shifted_result = func_801F2CE4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_PLANT:
                shifted_result = func_801F2CC0(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_DURANDAL:
                shifted_result = func_801F2E80(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_STEEL_BEACH:
                shifted_result = func_801F3F68(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_LIGHTHOUSE_OUTSIDE:
                shifted_result = func_801F2C04() << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MOUNT_ZUBLO_ENTRANCE:
                shifted_result = func_801F2C98(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_WYNDIA_BASEMENT_TELEPORTER:
                shifted_result = func_801F3A6C(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_TIDAL_CAVES_OUTSIDE:
                shifted_result = func_801F3210(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_TIDAL_CAVES_INNER:
                shifted_result = func_801F3CD4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_RELAY_POINT_A_PORTAL:
                shifted_result = func_801F3944(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_EMITAI_HOUSE:
                shifted_result = func_801F2DB4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_BLACK_SHIP_EARLY:
                shifted_result = func_801F5208(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_FACTORY_BLOCK_ROOM:
                shifted_result = func_801F42F4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_DRAGNIER_SURFACE:
                shifted_result = func_801F3D78(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_COLONY_OUTSIDE:
                shifted_result = func_801F43DC(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_CONTAINER_YARD:
                shifted_result = func_801F2C9C(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_OASIS:
                shifted_result = func_801F2F58(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MYRIA_STATION_HE_SHELLS:
                shifted_result = func_801F53A4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MYRIA_STATION_PLANT_ROOM:
                shifted_result = func_801F3CF0(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_EDEN_TEEPO_FIGHT:
                shifted_result = func_801F4CC4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MYRIA_STATION_MYRIA_ROOM:
                shifted_result = func_801F4FA4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_FAIRY_VILLAGE_DOLPHIN:
                shifted_result = func_801F3F2C(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB0:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB1:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB2:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB3:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB4:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB5:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB6:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB7:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB8:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xB9:
                shifted_result = func_801F33E4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xBF:
                shifted_result = func_801F3658(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case 0xC0:
                shifted_result = func_801F3118(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_DESERT_ENTRANCE_CAMP:
                shifted_result = func_801F315C(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            case AREA_ID_MYRIA_STATION_CHIMERA:
                shifted_result = func_801F41F4(entry_x, entry_y) << 0x18;
                goto return_result; /* shared return */
            return_result:
                return shifted_result >> 0x18;
            default:
                return 0;
        }
    } else {
        return 1;
    }
}
