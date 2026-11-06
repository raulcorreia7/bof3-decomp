#ifndef AREA_MAP_H
#define AREA_MAP_H

#include "common/handler.h"
#include "types.h"

typedef enum AreaId {
    AREA_ID_DESERT_OF_DEATH_MAP = 189,
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
