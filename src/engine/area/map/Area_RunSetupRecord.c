#include "engine/game/00/game_00.h"

/* The high nibble of a setup stream record selects its handler; 0xF0 and above are control records. */
typedef enum AreaSetupType {
    AREA_SETUP_TYPE_ENTITY                      = 0x0, /* map entity: scene record id, position, mode, move mode, step, options, label, route row */
    AREA_SETUP_TYPE_ENTITY_NO_ROUTE             = 0x1, /* type 0 without the route row byte */
    AREA_SETUP_TYPE_ENTITY_ATTACHED             = 0x2, /* type 0 plus the attach actor and offset row bytes */
    AREA_SETUP_TYPE_ENTITY_VOICED               = 0x3, /* type 0 plus a voice flags byte */
    AREA_SETUP_TYPE_ENTITY_WITH_ACTION          = 0x4, /* type 0 with the area action index in place of the route row */
    AREA_SETUP_TYPE_ENTITY_ATTACHED_FIXED_FLAGS = 0x5, /* type 2 without the tint byte */
    AREA_SETUP_TYPE_ENTITY_NO_SCENE_RECORD      = 0x6, /* entity without a scene record id */
    AREA_SETUP_TYPE_ENTITY_7                    = 0x7, /* map entity, record id and position one byte earlier */
    AREA_SETUP_TYPE_ENTITY_BLOCKER              = 0x8, /* short record that blocks the cells under the actor */
    AREA_SETUP_TYPE_ENTITY_FLAGGED              = 0x9, /* map entity whose bit in the scene flags picks its first script */
    AREA_SETUP_TYPE_ENTITY_DEF_ROW              = 0xA, /* entity whose scene record is a row index of the area's 8-byte table */
    AREA_SETUP_TYPE_PARTY_DEF_ROW               = 0xB, /* party actor row whose scene record is a row index of that table */
    AREA_SETUP_TYPE_SCROLL_ROUTE                = 0xC, /* start a scroll route */
    AREA_SETUP_TYPE_ENTITY_CALLBACK             = 0xD, /* set the current entity callback */
    AREA_SETUP_TYPE_ACTOR                       = 0xE, /* Actor_Create: a staged scene object */
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
        case AREA_SETUP_TYPE_ENTITY_ATTACHED_FIXED_FLAGS:
            Actor_SpawnAttachedFixedFlags(script);
            break;
        case AREA_SETUP_TYPE_PARTY_DEF_ROW:
            Actor_SpawnPartyFromDefRow(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_DEF_ROW:
            Actor_SpawnFromDefRow(script);
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
        case AREA_SETUP_TYPE_ENTITY_WITH_ACTION:
            Actor_SpawnWithAction(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_VOICED:
            Actor_SpawnVoiced(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_ATTACHED:
            Actor_SpawnAttached(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_BLOCKER:
            Actor_SpawnBlocker(script);
            break;
        case AREA_SETUP_TYPE_ENTITY_NO_ROUTE:
            Actor_SpawnNoRoute(script);
            break;
        case AREA_SETUP_TYPE_ENTITY:
        default:
            Actor_SpawnFromRecord(script);
            break;
    }
    return script + s_ScriptOpcodeLengths[script[0] >> 4];
}
