#ifndef BATTLE_BMAGIC_H
#define BATTLE_BMAGIC_H

#include "battle/handlers.h"
#include "sys/emi.h"
#include "types.h"

/* A battle-effect module's head. The id word is the value the type-0 EMI
 * loader compares with the archive TOC; the three state callbacks follow and
 * the module entry copies them and indexes them with the shared spad step
 * byte. The rest of the head is per-module data measured from its own bytes. */
typedef struct MagicModule {
    EmiModuleId         id;    /* 0x00; 0x144-0x1BF */
    BattleHandlerTable3 steps; /* 0x04 */
} MagicModule;

ASSERT_SIZE(MagicModule, 0x10);

/* The effect-module entry points, in address order: battle/battle/03 runs a
 * module through these steps. */
void func_801EEC04(void);
void func_801EEC58(void);
void func_801EED70(void);
void func_801EED7C(void);
void func_801EED98(void);
void func_801EEDA0(void);
void func_801EEDA4(void);
void func_801EEDE4(void);
void func_801EEDF0(void);
void func_801EEE00(void);
void func_801EEE04(void);
void func_801EEE18(void);
void func_801EEE2C(void);
void func_801EEE38(void);
void func_801EEE4C(void);
void func_801EEE58(void);
void func_801EEE5C(void);
void func_801EEE64(void);
void func_801EEE68(void);
void func_801EEE70(void);
void func_801EEE90(void);
void func_801EEE94(void);
void func_801EEE9C(void);
void func_801EEEA0(void);
void func_801EEEA4(void);
void func_801EEEBC(void);
void func_801EEEC0(void);
void func_801EEED0(void);
void func_801EEED4(void);
void func_801EEEE0(void);
void func_801EEEE4(void);
void func_801EEF08(void);
void func_801EEF30(void);
s32  func_801EEF3C(void);
void func_801EEF48(void);
void func_801EEF60(void);
void func_801EEF64(void);
void func_801EEF6C(void);
void func_801EEF70(void);
void func_801EEF74(void);
void func_801EEF78(void);
void func_801EEF80(void);
void func_801EEF84(void);
void func_801EEF9C(void);
void func_801EEFB0(void);
void func_801EEFC0(void);
void func_801EEFD0(void);
void func_801EEFD4(void);
void func_801EEFD8(void);
void func_801EEFDC(void);
void func_801EEFF4(void);
void func_801EEFF8(void);
void func_801EF000(void);
void func_801EF004(void);
void Effect_StartPlaying(void);
void func_801EF010(void);
void func_801EF014(void);
void func_801EF02C(void);
void func_801EF04C(void);
void func_801EF054(void);
void func_801EF064(void);
void func_801EF080(void);
void func_801EF09C(void);
void func_801EF0A8(void);
void func_801EF0C0(void);
void func_801EF0D0(void);
void func_801EF0DC(void);
void func_801EF108(void);
void func_801EF114(void);
void func_801EF158(void);
void func_801EF16C(void);
void func_801EF190(void);
void func_801EF1B0(void);
void func_801EF1E0(void);
void func_801EF20C(void);
void func_801EF210(void);
void func_801EF268(void);
void func_801EF278(void);
void func_801EF2CC(void);
void func_801EF2D0(void);
void func_801EF2D8(void);
void func_801EF310(void);
void func_801EF330(void);
void func_801EF398(void);
void func_801EF3F8(void);
void func_801EF4C4(void);
void func_801EF4E0(void);
void func_801EF56C(void);
void func_801EF668(void);
void func_801EF73C(void);
void func_801EF75C(void);
void func_801EF774(void);
void func_801EF78C(void);
void func_801EF8CC(void);
void func_801EF9E4(void);
void func_801EF9F0(void);
void func_801EFAB8(void);
void func_801EFF44(void);
void func_801F0018(void);
void func_801F0250(void);

#endif
