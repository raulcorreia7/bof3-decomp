#ifndef AREA_MAP_H
#define AREA_MAP_H

#include "common/handler.h"
#include "types.h"

typedef enum AreaId {
    AREA_ID_DESERT_OF_DEATH_MAP = 189,
} AreaId;

/* One entry of the per-map table the field loader walks: a load handler, the
 * step table, the color-matrix input, a handler table and the completion
 * callback. Only this prefix is modelled; unk_0C points to 6-byte records.
 *
 * func_8019FAA0 reads the entry handler, flag, matrix and callback from
 * g_AreaLoads[g_GameAreaId]. Message_DispatchAnswerStep and func_80151710 read the same
 * bank's step table at +0x34; func_801ACE10 reads the handler table at +0x3C.
 * The callback is at +0x40: the retail code of func_8019FAA0 loads it with
 * `lw 0x40`, and the area 0 row in emi/world00/area000/13 ends at +0x44. */
#define GAME_TABLE_ENTRY_SIZE 0x44

/* `flag_32` bit 4: the entry's communication map. func_801976EC loads
 * EMI_SLOT_COMMU00 and calls func_801F03D0 for it. */
typedef enum AreaLoadFlags {
    AREA_LOAD_FLAG_FAIRY_VILLAGE = 1 << 4,
} AreaLoadFlags;

typedef struct AreaLoad {
    /* 0x00 */ void* handler; /* passed to Area_RunSetupStream by func_8019FAA0 */
    /* 0x04 */ u8    pad_04[0x08];
    /* 0x0C */ u8*   unk_0C;
    /* 0x10 */ u8    pad_10[0x22];
    /* 0x32 */ u8    flag_32; /* AreaLoadFlags */
    u8               pad_33;
    /* 0x34 */ Callback*
        steps; /* indexed by D_801490BC.step_id (ids below 0x80) in Message_DispatchAnswerStep/func_80151710 */
    /* 0x38 */ void*    matrix;   /* SetColorMatrix input in func_8019FAA0 */
    /* 0x3C */ void*    unk_3C;   /* word table func_801ACE10 indexes and calls */
    /* 0x40 */ Callback callback; /* called after loading the map in func_8019FAA0 */
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
