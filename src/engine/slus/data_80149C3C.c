#include "slus.h"

const u32 g_CdSteps[9] = {
    (u32)CD_Idle,
    (u32)CD_SetSpeed,
    (u32)CD_Seek,
    (u32)CD_OnSeek,
    (u32)CD_Read,
    (u32)CD_OnRead,
    (u32)CD_Pause,
    (u32)CD_OnPause,
    (u32)CD_Idle,
};

const EmiRingSteps g_EmiRingSteps = {{
    (u32)func_80163230,
    (u32)EMI_SectorCopyToScratchpad,
    (u32)EMI_SectorDecompress,
    (u32)EMI_SectorUploadImage,
    (u32)EMI_VabUploadBody,
    (u32)func_80163698,
}};
