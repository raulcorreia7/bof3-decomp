#ifndef SYSTEM_CD_FORMAT_H
#define SYSTEM_CD_FORMAT_H

#include "types.h"

/* The retail disc's file list: 887 u32 start LBAs in ISO record order, held
 * at 0x80182444. A slot id is an archive's index in that list; the entry slot
 * inside an archive is a different number: the TOC index. The names are the
 * disc names (@source: wiki:formats/emi#disc-slot-ids). */
typedef u32 DiscLba;

/* A loader slot id indexes the disc file table at 0x80182444. A family base
 * is the slot of its first file; the file at base + n is the n-th of its
 * numbered series (ENEMY000, BGM000, PL012, AREA000, ...). */
typedef enum EmiSlotId {
    /* BATTLE */
    EMI_SLOT_BATL_DRA     = 0,
    EMI_SLOT_BATL_END     = 1,
    EMI_SLOT_BATL_OVR     = 2,
    EMI_SLOT_BATL_RE2     = 3,
    EMI_SLOT_BATL_RET     = 4,
    EMI_SLOT_BATL_SE      = 5,
    EMI_SLOT_BATTLE       = 6,
    EMI_SLOT_BATTLE2      = 7,
    EMI_SLOT_COMN_SE      = 8,
    /* numbered series */
    EMI_SLOT_ENEMY        = 0x9,
    EMI_SLOT_BGM          = 0xD1,
    EMI_SLOT_MAGIC        = 0x122,
    EMI_SLOT_MAGIC_STREAM = 0x1B2,
    EMI_SLOT_BOSS         = 0x1B3,
    EMI_SLOT_BPLD         = 0x1DB,
    EMI_SLOT_BPLU         = 0x1EE,
    EMI_SLOT_PL           = 0x26A,
    EMI_SLOT_PLP          = 0x27D,
    EMI_SLOT_SCENA        = 0x295,
    EMI_SLOT_AREA         = 0x2AB,
    /* ETC */
    EMI_SLOT_A085SE2      = 0x254,
    EMI_SLOT_A108SE2      = 0x255,
    EMI_SLOT_AFLDKWA      = 0x256,
    EMI_SLOT_BATE         = 0x257,
    EMI_SLOT_COMMU00      = 0x258,
    EMI_SLOT_COMMU01      = 0x259,
    EMI_SLOT_COMMU02      = 0x25A,
    EMI_SLOT_COMMU02B     = 0x25B,
    EMI_SLOT_COMMU03      = 0x25C,
    EMI_SLOT_COMMU04      = 0x25D,
    EMI_SLOT_COMMU05      = 0x25E,
    EMI_SLOT_DEMO         = 0x25F,
    EMI_SLOT_ENDKANJI     = 0x260,
    EMI_SLOT_FIRST        = 0x261,
    EMI_SLOT_GAME         = 0x262,
    EMI_SLOT_MTEST        = 0x263,
    EMI_SLOT_RTEST        = 0x264,
    EMI_SLOT_SHISU        = 0x265,
    EMI_SLOT_SHOP         = 0x266,
    EMI_SLOT_SISYOU       = 0x267,
    EMI_SLOT_START        = 0x268,
    EMI_SLOT_STATUS       = 0x269,
} EmiSlotId;

/* The family argument of EMI_StreamFamilyArchive selects the numbered series that the
 * index counts into. */
typedef enum EmiFamily {
    EMI_FAMILY_PL   = 0,
    EMI_FAMILY_BPLD = 1,
    EMI_FAMILY_BPLU = 2,
    EMI_FAMILY_PLP  = 3,
} EmiFamily;

#endif
