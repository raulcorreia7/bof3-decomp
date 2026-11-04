#ifndef GAME_00_DATA_H
#define GAME_00_DATA_H

/* The game overlay's data tables: sprite rectangles, map hooks, world routes and
 * the handler rows its frontend walks. Only this image includes the file. */

#define GAME_AREA_HANDLER_COUNT  11

/* A two-field row: a work step, a delta or a position offset. */
#define GAME_PAIR(a, b)          {(a), (b)}
#define GAME_WORK_STEP(dx, dy)   GAME_PAIR(dx, dy)
#define GAME_DELTA(dx, dy)       GAME_PAIR(dx, dy)
#define MAP_HOOK(map, handler)   {(map), {0, 0, 0}, (handler)}
#define UV_RECT(u, v, w, h)      {(u), (v), (w), (h)}
#define POS_OFF(x, y)            GAME_PAIR(x, y)
#define GAME_MAP(world, context) {(world), (context)}
#define PARTY_SLOT(active, key)  {(active), (key), 0, 0}
/* Data-table row initializer: no function body, so not a fragment. */
#define GAME_INDEX_HANDLER(h00, h04, h08, h0C, h10, selector, key)    \
    {(h00), (h04), (h08), (h0C), (h10), (selector), (key), {0, 0, 0}}

/* Four-byte sprite rectangle: u, v, width, height. UI_DrawSprite copies it
 * into a SPRT. */
typedef struct UvRect {
    u8 u;
    u8 v;
    u8 w;
    u8 h;
} UvRect;

/* D_801CCE84[62] spans 0xF8 bytes up to D_801CCF7C. */
ASSERT_SIZE(UvRect, 0x4);

/* Eight-byte area entry: the area id it applies to, then the map id and the
 * x and y that func_801B6470 stages for the transition. */
typedef struct WorldMapDestination {
    u16 area_id;
    u16 map_id;
    u16 x;
    u16 y;
} WorldMapDestination;

/* One of five source slots; func_801C0F9C reads the four bytes. */
typedef struct SlotSource {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} SlotSource;

/* Eight-byte map hook: the map id byte and the handler at +4. func_801A8CB4
 * scans the rows by byte offset, because the retail loop keeps a running
 * offset instead of an index. */
typedef struct AreaHook {
    u8       map;
    u8       unk_01[3];
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

/* Two signed coordinate deltas, one row per direction. func_80197AA4 adds the
 * pair to the world coordinates. */
typedef struct GameDelta {
    s8 dx;
    s8 dy;
} GameDelta;

/* Eight-byte signed position offset. func_801C63B0 adds the pair to the
 * party position when the slots move. */
typedef Vec2i PositionOffset;

/* Four-byte battle party slot. func_801C63B0 marks it active, stores its sort
 * key and orders the slots by that key. */
typedef struct PartySlot {
    u8 active;
    u8 key;
    u8 unk_02;
    u8 unk_03;
} PartySlot;

/* 0x1C-byte front-end handler row. Game_FindAreaHandler returns the row whose key
 * byte at +0x18 matches the current world state; the handlers sit at +0, +4,
 * +8, +0x0C and +0x10, and +0x14 points to the area's map points, four-byte rows (x, y,
 * context seed, context kind) that func_801B690C searches for the actor cell; Fish_LocationMessage walks the same
 * rows. The only reader of the member is func_8019A1D4; the rows are written by the data initialiser only. */
typedef struct AreaHandler {
    Callback handler_00;
    Callback handler_04;
    Callback handler_08;
    Callback handler_0C;
    Callback handler_10;
    u8*      map_points_14;
    u8       area_id;
    u8       unk_19[3];
} AreaHandler;

/* D_801C7F5C[11] spans 0x134 bytes up to D_801C8090. */
ASSERT_SIZE(AreaHandler, 0x1C);

typedef u8 (*ActorActionFunc)(void* entity, u8 param, s32 phase);
typedef void (*ActorWorkFunc)(s32 fallback_index, s32 index);

extern GameDelta            D_801C7B74[4];
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
extern WorldMapDestination  D_801CD24C[10];
extern SlotSource           D_801CD4AC[5];
extern PositionOffset       D_801CD620[36];
extern PositionOffset       D_801CD740[6];
extern CameraAngleOffset    D_801CD778[5];
extern PartySlot            D_801CD944[3];

#endif
