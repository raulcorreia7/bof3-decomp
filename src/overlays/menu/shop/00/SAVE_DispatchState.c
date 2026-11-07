#include "shop_00.h"

/* Handler table for the shop's active mode, indexed by the shared
 * shop-state byte D_80148652. */

MATCH void SAVE_DispatchState(void) {
    SYS_DISPATCH_BYTE(g_SaveStateFuncs, D_80148652);
}
