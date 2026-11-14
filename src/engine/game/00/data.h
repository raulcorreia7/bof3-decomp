#ifndef GAME_00_DATA_H
#define GAME_00_DATA_H

/* The game overlay's data tables: sprite rectangles, map hooks, world routes and
 * the handler rows its frontend walks. Only this image includes the file. */

#define GAME_AREA_HANDLER_COUNT   11

/* Cells in the square-spiral search order around a formation: the centre, then rings one to three, and a closing centre. */
/* Camera directions and the scroll step of one cell quarter. */
#define CAMERA_DIR_COUNT          4
#define CAMERA_SCROLL_STEP        4

#define ENTITY_SPAWN_OFFSET_COUNT 50
#define ENTITY_SPAWN_SEARCH_COUNT (ENTITY_SPAWN_OFFSET_COUNT - 1)

/* Eight-byte area entry: the area id it applies to, then the map id and the
 * x and y that func_801B6470 stages for the transition. */
typedef struct WorldMapDestination {
    u16 area_id;
    u16 map_id;

    Point2u pos;
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

/* Scene handler block behind g_SceneScenes: one entry per dispatch slot. */
typedef struct SceneSlots {
    Callback entry_00;
    void (*entry_04)(void*);
    s8 (*entry_08)(s32, s32);
    s8 (*entry_0C)(s32, s32);
    s8 (*entry_10)(s32, s32);
} SceneSlots;

/* Four-byte battle party slot. Area_PlaceEncounterParty marks it active, stores its sort
 * key and orders the slots by that key. */
typedef struct PartySlot {
    u8 active;
    u8 key;
    u8 unk_02;
    u8 unk_03;
} PartySlot;

ASSERT_SIZE(PartySlot, 0x4);
ASSERT_OFFSET(PartySlot, active, 0x0);
ASSERT_OFFSET(PartySlot, key, 0x1);

/* 0x1C-byte front-end handler row. Game_FindArea returns the row whose key
 * byte at +0x18 matches the current world state; the handlers sit at +0, +4,
 * +8, +0x0C and +0x10, and +0x14 points to the area's map points, four-byte rows (x, y,
 * context seed, context kind) that func_801B690C searches for the actor cell; Fishing_ShowLocation walks the same
 * rows. The only reader of the member is Game_GetAreaMapPoints; the rows are written by the data initialiser only. */
typedef struct AreaHandler {
    Callback handler_00;
    Callback handler_04;
    Callback handler_08;
    Callback handler_0C;
    Callback handler_10;
    u8*      map_points_14;
    u8       area_id;
    u8       pad_19[3];
} AreaHandler;

/* D_801C7F5C[11] spans 0x134 bytes up to D_801C8090. */
ASSERT_SIZE(AreaHandler, 0x1C);

typedef u8 (*ActorActionFunc)(void* entity, u8 param, s32 phase);
typedef void (*ActorWorkFunc)(s32 fallback_index, s32 index);

/* D_801C7B74 */
extern Offset2b            s_BattleScrollCellSteps[4];
extern AreaHandler          D_801C7F5C[11];
extern ActorActionFunc      D_801C83BC[7];
extern ObjectFunc           D_801C83D8[11];
extern SceneSlots*          g_SceneScenes[20];
extern AreaHooks            D_801C86F8;
extern ActorWorkFunc        D_801C890C[11];
extern u8*                  D_801C893C[5];
extern u8*                  D_801C8950[5];
extern ShopStock            g_GameShopStock[SHOP_COUNT];
extern UvRect               D_801CCE84[62];
extern UvRect               D_801CCF7C[53];
extern WorldMapBattlefields D_801CD224;
#define WORLD_MAP_DESTINATION_COUNT 10
extern WorldMapDestination D_801CD24C[WORLD_MAP_DESTINATION_COUNT];
extern SlotSource          D_801CD4AC[5];
extern Offset2b           s_CameraScrollDeltas[CAMERA_DIR_COUNT];
extern Offset2b           s_EntitySpawnOffsets[ENTITY_SPAWN_OFFSET_COUNT];
/* D_801CD620 */
extern Point2l            s_EncounterEnemyOffsets[36];
/* D_801CD740 */
extern Point2l            s_EncounterOriginNudges[6];
extern Point2s             D_801CD778[5];
extern PartySlot           D_801CD944[3];

#endif
