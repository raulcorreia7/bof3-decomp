#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/shared/Scene_JoinAdultNina.h"

#include "overlays/scenario/shared/Scene_JoinMomo.h"

MATCH void Scene_JoinAdultNinaMomo3(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}

/* func_801FCF00 */
#include "overlays/scenario/shared/Scene_JoinMomoWithGarr.h"

MATCH void Scene_JoinMomo3(void) {
    SCENE_JOIN_MOMO();
}

#include "overlays/scenario/shared/Scene_JoinMomoPeco.h"

#include "overlays/scenario/shared/Scene_JoinPeco.h"

#include "overlays/scenario/shared/Scene_JoinReiGarr.h"

MATCH void func_801FD064(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_GARR, 0);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_GARR);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveRei.h"

#include "overlays/scenario/shared/Scene_RemoveGarr.h"

#include "overlays/scenario/shared/Scene_RemovePeco.h"

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

#include "overlays/scenario/shared/Scene_RemoveAdultNina.h"
