#include "area104_14.h"

#include "overlays/area/Area_UpdateTorchGauge.h"

MATCH void func_801F564C(void) {
    AREA_UPDATE_TORCH_GAUGE(!(D_80146871 & 0x40), (D_80145E9A == 0), func_801F555C, func_801F5418);
}
