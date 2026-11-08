#include "slus.h"

const u32 g_EmiCDSteps[9] = {
    (u32)EMI_CdIdle,
    (u32)EMI_CdSetSpeed,
    (u32)EMI_CdSeek,
    (u32)EMI_CdOnSeek,
    (u32)EMI_CdRead,
    (u32)EMI_CdOnRead,
    (u32)EMI_CdPause,
    (u32)EMI_CdOnPause,
    (u32)EMI_CdIdle,
};

const SystemDispatchFuncs g_EmiRingSlotHandlers = {{
    (u32)func_80163230,
    (u32)EMI_CopySectorToScratchpad,
    (u32)EMI_DecompressSector,
    (u32)EMI_UploadSectorImage,
    (u32)EMI_UploadVabBody,
    (u32)func_80163698,
}};
