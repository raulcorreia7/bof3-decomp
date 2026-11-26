#ifndef GAME_00_DATA_H
#define GAME_00_DATA_H

/* The game overlay's data tables: sprite rectangles, map hooks, world routes and
 * the handler rows its frontend walks. Only this image includes the file. */

#define WORLD_MAP_REGION_COUNT       11

/* Cells in the square-spiral search order around a formation: the centre, then rings one to three, and a closing centre. */
/* Camera directions and the scroll step of one cell quarter. */
#define CAMERA_DIR_COUNT             4
#define CAMERA_SCROLL_STEP           4

#define ENCOUNTER_SPAWN_OFFSET_COUNT 50
#define ENTITY_SPAWN_SEARCH_COUNT    (ENCOUNTER_SPAWN_OFFSET_COUNT - 1)

/* Eight-byte area entry: the area id it applies to, then the map id and the
 * x and y that func_801B6470 stages for the transition. */
typedef struct WorldMapDestination {
    u16 area_id;
    u16 map_id;

    Pos2u pos;
} WorldMapDestination;

/* One of five source slots; func_801C0F9C reads the four bytes. */
typedef struct SlotSource {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} SlotSource;

/* Eight-byte map hook: the map id byte and the handler at +4. Game_CallArea
 * scans the rows by byte offset, because the retail loop keeps a running
 * offset instead of an index. */
typedef struct AreaHook {
    u8       map;
    u8       pad_01[3];
    Callback handler;
} AreaHook;

/* Four-byte world routing row: a world id and the context seed it selects. */
typedef struct WorldMapBattlefield {
    u16 world;
    u16 context;
} WorldMapBattlefield;

/* The ten rows fill the 40 bytes of D_801CD224. */
ASSERT_SIZE(WorldMapBattlefield, 0x4);

/* Byte views of two typed tables. The retail readers walk the bytes by offset,
 * so the union keeps both the record rows and the byte view. */
typedef union AreaHooks {
    AreaHook rows[28];
    u8       bytes[224];
} AreaHooks;

typedef union WorldMapBattlefields {
    WorldMapBattlefield rows[10];
    u8                  bytes[40];
} WorldMapBattlefields;

/* The handlers of one scenario, behind g_ScenarioHandlers: update (+0x00), record, step_test, cell_test and call (+0x10). */
typedef struct ScenarioHandlers {
    Callback update;
    void (*record)(void*);
    s8 (*step_test)(s32, s32);
    s8 (*cell_test)(s32, s32);
    s8 (*call)(s32, s32);
} ScenarioHandlers;

ASSERT_SIZE(ScenarioHandlers, 0x14);

/* Four-byte battle party slot. Area_EncounterPlaceParty marks it active, stores its sort
 * key and orders the slots by that key. */
typedef struct PartySlot {
    u8 active;
    u8 key;
    u8 unk_02;
    u8 unk_03;
} PartySlot;

ASSERT_OFFSET(PartySlot, active, 0x0);
ASSERT_OFFSET(PartySlot, key, 0x1);
ASSERT_SIZE(PartySlot, 0x4);

/* One 0x1C-byte world map region row. WorldMap_FindRegion returns the row whose
 * area id at +0x18 matches the current world state. Each row carries the five
 * actor steps the region runs (the party's cell walk, the exit-cell entry, the
 * bird flock, the region script and the cloud draw) and +0x14 points to the
 * region's map points, four-byte rows (x, y, area id, type) that func_801B690C
 * searches for the actor cell; Fishing_ShowLocation walks the same rows. The
 * only reader of the member is WorldMap_GetPoints; the rows are written by the
 * data initialiser only. */
typedef struct WorldMapRegion {
    Callback       walk;
    Callback       entry;
    Callback       flock;
    Callback       script;
    Callback       clouds;
    WorldMapPoint* map_points;
    u8             area_id;
    u8             pad_19[3];
} WorldMapRegion;

/* g_WorldMapRegions[11] spans 0x134 bytes up to D_801C8090. */
ASSERT_SIZE(WorldMapRegion, 0x1C);

typedef u8 (*ActorStepCallback)(void* entity, u8 param, s32 phase);
typedef void (*AreaActionCallback)(s32 character_id, s32 index);

/* D_801C7B74 */
extern Step2                s_BattleScrollCellSteps[4];
extern WorldMapRegion       g_WorldMapRegions[WORLD_MAP_REGION_COUNT];
/* D_801C83BC */
extern ActorStepCallback    g_ActorPaceSteps[ACTOR_PACE_COUNT];
/* D_801C83D8 */
extern ActorModeCallback    g_ActorModes[ACTOR_MODE_COUNT];
extern ScenarioHandlers*    g_ScenarioHandlers[20];
extern AreaHooks            g_AreaHooks;
/* D_801C890C */
extern AreaActionCallback   g_AreaActions[11];
extern u8*                  g_ItemCategoryIds[5];
extern u8*                  g_ItemCategoryCounts[5];
extern ShopStock            g_GameShopStock[SHOP_COUNT];
extern UvRect               D_801CCE84[62];
extern UvRect               D_801CCF7C[53];
extern WorldMapBattlefields D_801CD224;
#define WORLD_MAP_DESTINATION_COUNT 10
extern WorldMapDestination D_801CD24C[WORLD_MAP_DESTINATION_COUNT];
extern SlotSource          D_801CD4AC[5];
extern Step2               s_CameraScrollDeltas[CAMERA_DIR_COUNT];
extern Step2               s_EncounterSpawnOffsets[ENCOUNTER_SPAWN_OFFSET_COUNT];
/* D_801CD620 */
extern Offset2             s_EncounterEnemyOffsets[36];
/* D_801CD740 */
extern Offset2             s_EncounterOriginNudges[6];
extern Pos2                D_801CD778[5];
extern PartySlot           D_801CD944[3];

#endif
