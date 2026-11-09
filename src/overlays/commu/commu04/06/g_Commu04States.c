#include "commu04_06.h"

void Fairy_EndCommuScene(void);
void func_801D0C5C(void);
void func_801D0C98(void);
void func_801D0CF4(void);
void func_801D0D4C(void);
void func_801D11DC(void);
void func_801D12C8(void);
void func_801D1568(void);
void func_801D1628(void);

Callback  g_Commu04States[2]     = {func_801D0C5C, Fairy_EndCommuScene};
Callback  g_Commu04Step0Funcs[7] = {func_801D0C98, func_801D0CF4, func_801D0D4C, func_801D11DC, func_801D12C8, func_801D1568, func_801D1628};
static u8 s_gap_801D1774[4]      = {0x00, 0x00, 0x00, 0x00};
