#ifndef SCENARIO_OVERLAY_H
#define SCENARIO_OVERLAY_H

#include "sys/emi.h"
#include "types.h"

/* The EMI TOC caches the first payload word for scenario overlays. */
typedef struct SceneOverlayHeader {
    /* 0x00; 0x105-0x11D */ EMIModuleId module_id;
} SceneOverlayHeader;

ASSERT_SIZE(SceneOverlayHeader, 4);
ASSERT_OFFSET(SceneOverlayHeader, module_id, 0x00);

#endif
