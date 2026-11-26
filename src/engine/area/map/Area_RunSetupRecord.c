#include "engine/game/00/game_00.h"

/* The high nibble of a setup stream record selects its handler; 0xF0 and above are control records. */
typedef enum AreaSetupType {
    AREA_SETUP_TYPE_ENTITY                 = 0x0, /* map entity: scene record, cell position, mode, step */
    AREA_SETUP_TYPE_ENTITY_1               = 0x1, /* map entity with the extra fields of type 0 */
    AREA_SETUP_TYPE_ENTITY_2               = 0x2, /* map entity with two extra bytes */
    AREA_SETUP_TYPE_ENTITY_VOICED          = 0x3, /* map entity with voice flags */
    AREA_SETUP_TYPE_ENTITY_4               = 0x4, /* map entity with a byte for the shadow table */
    AREA_SETUP_TYPE_ENTITY_5               = 0x5, /* map entity with two extra bytes */
    AREA_SETUP_TYPE_ENTITY_NO_SCENE_RECORD = 0x6, /* entity without a scene record id */
    AREA_SETUP_TYPE_ENTITY_7               = 0x7, /* map entity, record id and position one byte earlier */
    AREA_SETUP_TYPE_ENTITY_SHORT           = 0x8, /* short map entity record, no callback */
    AREA_SETUP_TYPE_ENTITY_FLAGGED         = 0x9, /* map entity whose bit in the scene flags picks its first script */
    AREA_SETUP_TYPE_ENTITY_AT_AREA_CELL    = 0xA, /* entity placed by the area cell table */
    AREA_SETUP_TYPE_PARTY_ENTITY           = 0xB, /* party work row placed by the area cell table */
    AREA_SETUP_TYPE_SCROLL_ROUTE           = 0xC, /* start a scroll route */
    AREA_SETUP_TYPE_ENTITY_CALLBACK        = 0xD, /* set the current entity callback */
    AREA_SETUP_TYPE_ACTOR                  = 0xE, /* Actor_Create: a staged scene object */
} AreaSetupType;

/* func_801A4BF8 */
/* Runs one setup record of type 0x0 to 0xE; returns the next record. */
MATCH u8* Area_RunSetupRecord(u8* script) {
    switch (script[0] >> 4) {
        case AREA_SETUP_TYPE_ACTOR:
            Actor_Create(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_CALLBACK:
            Area_SetEntityCallback(script);
            break;
        case AREA_SETUP_TYPE_SCROLL_ROUTE:
            Area_ScrollInitRoute(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_5:
            func_801A6F58(script);
            break;
        case AREA_SETUP_TYPE_PARTY_ENTITY:
            func_801A6C98(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_AT_AREA_CELL:
            func_801A68C0(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_NO_SCENE_RECORD:
            Actor_SpawnPartyFromRecord(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_7:
            Actor_SpawnBattleEntry(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_FLAGGED:
            Actor_SpawnSearchSpot(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_4:
            func_801A5EFC(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_VOICED:
            func_801A5B78(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_2:
            func_801A57F0(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_SHORT:
            func_801A5400(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_1:
            func_801A50C0(script);
            break;
        case AREA_SETUP_TYPE_ENTITY:
        default:
            Actor_SpawnFromRecord(script);
            break;
    }
    return script + s_ScriptOpcodeLengths[script[0] >> 4];
}
