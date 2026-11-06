#ifndef AREA_MAP_H
#define AREA_MAP_H

#include "common/handler.h"
#include "types.h"

typedef enum AreaId {
    AREA_ID_DAUNA_MINE_ADULT           = 1,
    AREA_ID_DAUNA_MINE_WORKER          = 2,
    AREA_ID_DAUNA_MINE_INTRO           = 4,
    AREA_ID_CEDAR_WOODS_BEFORE_NUE     = 9,
    AREA_ID_DAUNA_MINE_WHELP           = 24,
    AREA_ID_MCNEIL_MANOR_COURTYARD     = 26,
    AREA_ID_MCNEIL_MANOR               = 27,
    AREA_ID_TITLE_INTRO                = 31,
    AREA_ID_MOMO_TOWER_FIRST_FLOOR     = 40,
    AREA_ID_MOMO_TOWER_OUTSIDE         = 42,
    AREA_ID_RHAPALA_CHECKPOINT         = 46,
    AREA_ID_PLANT                      = 49,
    AREA_ID_DURANDAL                   = 59,
    AREA_ID_MOUNT_LEVETT               = 70,
    AREA_ID_MOUNT_BOUMORE_SECOND       = 71,
    AREA_ID_STEEL_BEACH                = 75,
    AREA_ID_LIGHTHOUSE_OUTSIDE         = 76,
    AREA_ID_BEYD_TRAINING              = 92,
    AREA_ID_MOUNT_ZUBLO_ENTRANCE       = 97,
    AREA_ID_DEIS_ROOM                  = 98,
    AREA_ID_WYNDIA_BASEMENT_TELEPORTER = 100,
    AREA_ID_MOUNT_ZUBLO_GISSHAN        = 103,
    AREA_ID_TIDAL_CAVES_OUTSIDE        = 105,
    AREA_ID_TIDAL_CAVES_INNER          = 106,
    AREA_ID_DAUNA_MINE_ZOMBIE_DRAGON   = 108,
    AREA_ID_RELAY_POINT_A_PORTAL       = 112,
    AREA_ID_EMITAI_HOUSE               = 116,
    AREA_ID_HIDDEN_FACTORY_ENTRANCE    = 117,
    AREA_ID_HIDDEN_FACTORY_ROOMS       = 118,
    AREA_ID_STEEL_BEACH_MAP            = 121,
    AREA_ID_BOAT_AFTER_BLACK_SHIP      = 133,
    AREA_ID_BLACK_SHIP_EARLY           = 135,
    AREA_ID_FACTORY_BLOCK_ROOM         = 140,
    AREA_ID_DRAGNIER_SURFACE           = 143,
    AREA_ID_COLONY_OUTSIDE             = 145,
    AREA_ID_CONTAINER_YARD             = 146,
    AREA_ID_OASIS                      = 150,
    AREA_ID_MYRIA_STATION_HE_SHELLS    = 170,
    AREA_ID_MYRIA_STATION_PLANT_ROOM   = 171,
    AREA_ID_EDEN_TEEPO_FIGHT           = 172,
    AREA_ID_MYRIA_STATION_MYRIA_ROOM   = 174,
    AREA_ID_FAIRY_VILLAGE_DOLPHIN      = 175,
    AREA_ID_ADULT_CAMP                 = 187,
    AREA_ID_BLACK_SHIP                 = 188,
    AREA_ID_DESERT_OF_DEATH_MAP        = 189,
    AREA_ID_DESERT_ENTRANCE_CAMP       = 193,
    AREA_ID_DESERT_MANMO               = 196,
    AREA_ID_MYRIA_STATION_CHIMERA      = 197,
    AREA_ID_END_GAME_SAVE              = 199,
} AreaId;

#define GAME_TABLE_ENTRY_SIZE 0x44

typedef enum AreaLoadFlags {
    AREA_LOAD_FLAG_FAIRY_VILLAGE = 1 << 4,
} AreaLoadFlags;

typedef struct AreaLoad {
    /* 0x00 */ void*     handler;
    /* 0x04 */ u8        pad_04[0x08];
    /* 0x0C */ u8*       unk_0C;
    /* 0x10 */ u8        pad_10[0x22];
    /* 0x32 */ u8        flag_32;
    u8                   pad_33;
    /* 0x34 */ Callback* steps;
    /* 0x38 */ void*     matrix;
    /* 0x3C */ void*     unk_3C;
    /* 0x40 */ Callback  callback;
} AreaLoad;

ASSERT_SIZE(AreaLoad, GAME_TABLE_ENTRY_SIZE);
ASSERT_OFFSET(AreaLoad, handler, 0x00);
ASSERT_OFFSET(AreaLoad, unk_0C, 0x0C);
ASSERT_OFFSET(AreaLoad, flag_32, 0x32);
ASSERT_OFFSET(AreaLoad, steps, 0x34);
ASSERT_OFFSET(AreaLoad, matrix, 0x38);
ASSERT_OFFSET(AreaLoad, unk_3C, 0x3C);
ASSERT_OFFSET(AreaLoad, callback, 0x40);

#endif
