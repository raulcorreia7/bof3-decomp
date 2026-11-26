#ifndef SYSTEM_CD_FORMAT_H
#define SYSTEM_CD_FORMAT_H

#include "types.h"

/* The retail disc's file list: 887 u32 start LBAs in ISO record order plus
 * the start LBA of CD audio track 2, held at 0x80182444. A slot id is an
 * archive's index in that list; the entry slot inside an archive is a
 * different number: the TOC index. The names are the
 * disc names (@source: wiki:formats/emi#disc-slot-ids). */
typedef u32 DiscLba;

/* The first slot of each disc folder. */
typedef enum EMIDir {
    EMI_DIR_BATTLE   = 0,
    EMI_DIR_BENEMY   = 9,
    EMI_DIR_BGM      = 209,
    EMI_DIR_BMAGIC   = 290,
    EMI_DIR_BMAG_XA  = 434,
    EMI_DIR_BOSS     = 435,
    EMI_DIR_BPLCHAR  = 475,
    EMI_DIR_ETC      = 596,
    EMI_DIR_PLCHAR   = 618,
    EMI_DIR_SCENARIO = 656,
    EMI_DIR_SCE_XA   = 681,
    EMI_DIR_WORLD00  = 683,
    EMI_DIR_WORLD01  = 721,
    EMI_DIR_WORLD02  = 759,
    EMI_DIR_WORLD03  = 797,
    EMI_DIR_WORLD04  = 835,
    EMI_DIR_LOGO     = 883,
    EMI_DIR_SYSCNF   = 885,
    EMI_DIR_SLUS     = 886,
} EMIDir;

/* A loader slot id indexes the disc file table at 0x80182444. */
typedef enum EMISlotId {
    EMI_SLOT_BATL_DRA   = EMI_DIR_BATTLE,
    EMI_SLOT_BATL_END   = EMI_DIR_BATTLE + 1,
    EMI_SLOT_BATL_OVR   = EMI_DIR_BATTLE + 2,
    EMI_SLOT_BATL_RE2   = EMI_DIR_BATTLE + 3,
    EMI_SLOT_BATL_RET   = EMI_DIR_BATTLE + 4,
    EMI_SLOT_BATL_SE    = EMI_DIR_BATTLE + 5,
    EMI_SLOT_BATTLE     = EMI_DIR_BATTLE + 6,
    EMI_SLOT_BATTLE2    = EMI_DIR_BATTLE + 7,
    EMI_SLOT_COMN_SE    = EMI_DIR_BATTLE + 8,
    /* numbered series */
    EMI_SLOT_ENEMY      = EMI_DIR_BENEMY,
    EMI_SLOT_BGM        = EMI_DIR_BGM,
    EMI_SLOT_KAIZAR_D   = EMI_DIR_BMAGIC,     /* KAIZAR_D: the Kaizar dragon form archive, D set */
    EMI_SLOT_KAIZAR_F   = EMI_DIR_BMAGIC + 1, /* KAIZAR_F */
    EMI_SLOT_KAIZAR_N   = EMI_DIR_BMAGIC + 2, /* KAIZAR_N */
    EMI_SLOT_MAGIC_BASE = EMI_DIR_BMAGIC + 2, /* MAGIC series base: MAGICnnn is base + nnn up to MAGIC006, then the numbers skip */
    EMI_SLOT_MAGIC_XA   = EMI_DIR_BMAG_XA,
    EMI_SLOT_BOSS       = EMI_DIR_BOSS,
    EMI_SLOT_BPLD       = EMI_DIR_BPLCHAR,
    EMI_SLOT_BPLU       = EMI_DIR_BPLCHAR + 19,
    EMI_SLOT_BRTD247    = EMI_DIR_BPLCHAR + 38, /* BRTD247, BRTD457, BRTD467, BRTD478: the dragon form's D set, chosen by scroll direction */
    EMI_SLOT_BRTD457    = EMI_DIR_BPLCHAR + 39,
    EMI_SLOT_BRTD467    = EMI_DIR_BPLCHAR + 40,
    EMI_SLOT_BRTD478    = EMI_DIR_BPLCHAR + 41,
    EMI_SLOT_BRTU247    = EMI_DIR_BPLCHAR + 42, /* BRTU247, BRTU457, BRTU467, BRTU478: the U set */
    EMI_SLOT_BRTU457    = EMI_DIR_BPLCHAR + 43,
    EMI_SLOT_BRTU467    = EMI_DIR_BPLCHAR + 44,
    EMI_SLOT_BRTU478    = EMI_DIR_BPLCHAR + 45,
    EMI_SLOT_REID00     = EMI_DIR_BPLCHAR + 97, /* REID00, REID01, REIU00, REIU01: the Rei character archives, D and U sets */
    EMI_SLOT_REID01     = EMI_DIR_BPLCHAR + 98,
    EMI_SLOT_REIU00     = EMI_DIR_BPLCHAR + 99,
    EMI_SLOT_REIU01     = EMI_DIR_BPLCHAR + 100,
    EMI_SLOT_RTD00      = EMI_DIR_BPLCHAR + 101, /* RTD00, RTD01, RTU00, RTU01: the RT character archives, D and U sets */
    EMI_SLOT_RTD01      = EMI_DIR_BPLCHAR + 102,
    EMI_SLOT_RTU00      = EMI_DIR_BPLCHAR + 103,
    EMI_SLOT_RTU01      = EMI_DIR_BPLCHAR + 104,
    EMI_SLOT_A085SE2    = EMI_DIR_ETC,
    EMI_SLOT_A108SE2    = EMI_DIR_ETC + 1,
    EMI_SLOT_AFLDKWA    = EMI_DIR_ETC + 2,
    EMI_SLOT_BATE       = EMI_DIR_ETC + 3,
    EMI_SLOT_COMMU00    = EMI_DIR_ETC + 4,
    EMI_SLOT_COMMU01    = EMI_DIR_ETC + 5,
    EMI_SLOT_COMMU02    = EMI_DIR_ETC + 6,
    EMI_SLOT_COMMU02B   = EMI_DIR_ETC + 7,
    EMI_SLOT_COMMU03    = EMI_DIR_ETC + 8,
    EMI_SLOT_COMMU04    = EMI_DIR_ETC + 9,
    EMI_SLOT_COMMU05    = EMI_DIR_ETC + 10,
    EMI_SLOT_DEMO       = EMI_DIR_ETC + 11,
    EMI_SLOT_ENDKANJI   = EMI_DIR_ETC + 12,
    EMI_SLOT_FIRST      = EMI_DIR_ETC + 13,
    EMI_SLOT_GAME       = EMI_DIR_ETC + 14,
    EMI_SLOT_MTEST      = EMI_DIR_ETC + 15, /* MTEST, RTEST: unreferenced; their 2,404 B entry is data, not code */
    EMI_SLOT_RTEST      = EMI_DIR_ETC + 16,
    EMI_SLOT_SHISU      = EMI_DIR_ETC + 17,
    EMI_SLOT_SHOP       = EMI_DIR_ETC + 18,
    EMI_SLOT_SISYOU     = EMI_DIR_ETC + 19,
    EMI_SLOT_START      = EMI_DIR_ETC + 20,
    EMI_SLOT_STATUS     = EMI_DIR_ETC + 21,
    /* numbered series */
    EMI_SLOT_PL         = EMI_DIR_PLCHAR,
    EMI_SLOT_PLP        = EMI_DIR_PLCHAR + 19,
    EMI_SLOT_SCE15EF0   = EMI_DIR_SCENARIO + 1,
    EMI_SLOT_SCENA      = EMI_DIR_SCENARIO + 5,
    EMI_SLOT_S_XA00     = EMI_DIR_SCE_XA,
    EMI_SLOT_VOICE      = EMI_DIR_SCE_XA + 1,
    EMI_SLOT_AREA       = EMI_DIR_WORLD00,
    /* the disc files; the table adds one entry past them */
    EMI_SLOT_COUNT      = 887,
} EMISlotId;

/* The family argument of EMI_ArchiveLoadFamily selects the numbered series that the index counts into. */
typedef enum EMIFamily {
    EMI_FAMILY_PL   = 0,
    EMI_FAMILY_BPLD = 1,
    EMI_FAMILY_BPLU = 2,
    EMI_FAMILY_PLP  = 3,
} EMIFamily;

#endif
