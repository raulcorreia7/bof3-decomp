#include "slus.h"

const u32 g_EmiCDSteps[9] = {
    (u32)EMI_LoaderIdle,
    (u32)EMI_LoaderSetCDSpeed,
    (u32)EMI_LoaderSeekCD,
    (u32)EMI_LoaderFinishSeek,
    (u32)EMI_LoaderStartRead,
    (u32)EMI_LoaderFinishRead,
    (u32)EMI_LoaderPauseCD,
    (u32)EMI_LoaderFinishPause,
    (u32)EMI_LoaderIdle,
};

const SystemDispatchFuncs g_EmiSlotDrainFuncs = {{
    (u32)func_80163230,
    (u32)EMI_LoaderStageSector,
    (u32)EMI_LoaderReadSector,
    (u32)EMI_LoaderUploadSector,
    (u32)EMI_LoaderTransferVabBody,
    (u32)func_80163698,
}};
