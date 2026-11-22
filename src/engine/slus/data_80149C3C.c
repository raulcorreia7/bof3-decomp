#include "slus.h"

const Callback g_CdStateHandlers[CD_STATE_COUNT] = {
    CD_Idle,
    CD_SetSpeed,
    CD_Seek,
    CD_OnSeek,
    CD_Read,
    CD_OnRead,
    CD_Pause,
    CD_OnPause,
    CD_Idle,
};

const EmiRingSteps g_EmiRingSteps = {{
    (u32)func_80163230,
    (u32)EMI_SectorCopyToScratchpad,
    (u32)EMI_SectorDecompress,
    (u32)EMI_SectorUploadImage,
    (u32)EMI_VabUploadBody,
    (u32)func_80163698,
}};
