#include "scena04_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F6D44(void) {
    Actor* work;

    work                   = g_Task;
    work->vz               = 0x1000000;
    FIELD(s32, work, 0x2C) = 0x1000000;
    work->vx               = 0x568000;
    work->vy               = 0x128000;
    work->unk_1C           = 0;
    work->gravity          = 0x2200000;
    FIELD(s32, work, 0x24) = 0x568000;
    FIELD(s32, work, 0x28) = 0x128000;
    work->pos.x.fixed      = 0x4000;
    work->pos.y.fixed      = 0x2200000;
    func_801F747C();
    g_Task->timer = 8;
    g_Task->header.mode += 1;
}

INCLUDE_ASM(func_801F6DD4);

MATCH void func_801F6EA4(void) {
    Actor* work;
    Actor* actor;
    u8     mode;

    work = g_Task;
    func_801F7084(&work->vx);
    func_801F75BC(0x10, 0xFF);
    actor        = g_Task;
    mode         = actor->timer - 1;
    actor->timer = mode;
    if (mode == 0) {
        g_Task->timer = 4;
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801F6F2C);

MATCH void func_801F6FF8(void) {
    Actor* work;

    func_801F7084(&g_Task->vx);
    work = g_Task;
    work->timer--;
    if (work->timer == 0) {
        g_Task->header.mode++;
    }
}

MATCH void func_801F7064(void) {
    Actor_Clear();
}

INCLUDE_ASM(func_801F7084);

INCLUDE_ASM(func_801F732C);

INCLUDE_ASM(func_801F747C);

INCLUDE_ASM(func_801F75BC);

MATCH void func_801F77A8(void) {
    SYS_DISPATCH_TASK(D_801FA198, 1, g_Task);
}

MATCH void func_801F77EC(void) {
    ScenePathWork* work;
    u8             i;

    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);

    work    = MEM_PTR(ScenePathWork, 0x800E5C00u);
    work->x = D_80147A8C;
    work->y = g_AreaFocusY;
    work->z = D_80147A94 >> 8;
    i       = 0;
    do {
        work->points[i].x = work->x + D_801FA1A4[i];
        work->points[i].y = work->y + D_801FA1C4[i];
        work->points[i].z = (s16)Area_SampleHeight(work->points[i].x, work->points[i].y) << 8;
        i++;
    } while (i < 8);
    func_801F7FCC();
    g_Task->vx = 0x200;
    g_Task->header.mode++;
}

INCLUDE_ASM(func_801F78F4);

MATCH void func_801F7A64(void) {
    Actor_Clear();
}

MATCH void func_801F7A84(void) {
    SYS_DISPATCH_TASK(D_801FA1E4, 1, g_Task);
}

MATCH void func_801F7AC8(void) {
    Actor* work;

    func_801F7FCC();
    work = g_Task;
    work->header.mode += 1;
}

MATCH void func_801F7B00(void) {
    /* FAKE: unused frame, 16 bytes; `row` and `shade` also stay uninitialized
       when the frame count skips the spawn, as in retail. */
    FAKE_STACK_PADS(u8, 16);
    u8* row;
    s32 shade;
    s32 height;

    if ((g_FrameCount & 7) == 0) {
        row   = func_801F7FF8();
        shade = 0x80;
        if (row != NULL) {
            FIELD(s32, row, 0x00) = D_80146954;
            FIELD(s32, row, 0x04) = D_80146958;
            height                = D_8014695C;
            FIELD(s32, row, 0x10) = 0;
            FIELD(s32, row, 0x14) = 0;
            FIELD(s32, row, 0x18) = 0;
            FIELD(s8, row, 0x24)  = shade;
            FIELD(s32, row, 0x20) = 0x800;
            FIELD(s8, row, 0x25)  = shade;
            FIELD(s32, row, 0x08) = height >> 8;
        }
    }
    func_801F7EC0(shade, row);
    if (g_ScriptVarsReq.byte == 3) {
        Scene_AdvanceActorStep();
    }
}

MATCH void func_801F7BC0(void) {
    u8*  row;
    u8   i;
    s32  angle;
    s32* spot;

    i    = 0;
    spot = &D_80146954;
    for (; i < 16; i++) {
        row = func_801F7FF8();
        if (row != NULL) {
            FIELD(s32, row, 0x00) = spot[0];
            angle                 = i << 8;
            FIELD(s32, row, 0x04) = spot[1];
            FIELD(s32, row, 0x08) = spot[2] >> 8;
            FIELD(s32, row, 0x10) = rsin(angle) >> 2;
            FIELD(s32, row, 0x14) = rcos(angle) >> 2;
            FIELD(s32, row, 0x18) = 0;
            FIELD(s8, row, 0x24)  = 0x40;
            FIELD(s32, row, 0x20) = 0x800;
            FIELD(s8, row, 0x25)  = 0x40;
        }
    }
    func_801F7EC0();
    FIELD(s32, g_Task, 0x0C) = 0x40;
}

MATCH void func_801F7CA8(void) {
    func_801F7EC0();
    g_Task->vx = g_Task->vx - 1;
    if (g_Task->vx == 0) {
        func_80196070();
    }
}

INCLUDE_ASM(func_801F7CF0);

INCLUDE_ASM(func_801F7EC0);

MATCH void func_801F7FCC(void) {
    s32   index;
    void* cell;

    cell  = (void*)AREA_WORK;
    index = 0;
    do {
        FIELD(s8, cell, 0x25u) = 0;
        index += 1;
        cell += 0x28;
    } while ((index & BYTE_MASK) < 0x80U);
}

MATCH u8* func_801F7FF8(void) {
    u8* p;
    u8  i;

    p = MEM_PTR(u8, AREA_WORK);
    for (i = 0; i < 128; i++) {
        if (p[SCRATCH_ROW_OFFSET] == 0) {
            return p;
        }
        p += SCRATCH_ROW_STRIDE;
    }
    return NULL;
}

/* Area_AddCellPrim with the caller's tag stored in the slot and an unmasked size. */
MATCH void func_801F8034(s32 x, s32 y, s32 depth, s32 size, u32 tag) {
    u8*  cursor;
    u8*  next;
    u8*  packet;
    u32* slot;
    u32  offset;
    u32  limit;
    s32  index;
    s32  value;
    s32  cell;
    s32  seed;
    s32  count;
    s32  addend;

    index = (x >> 16) - g_AreaTileOriginX;
    value = (y >> 16) - g_AreaTileOriginY;
    if (x & HALF_MASK) {
        value += 1;
    }
    /* FAKE: keeps index in its own pseudo so the sum lands in a fresh register, as in Area_AddCellPrim. */
    index++;
    index--;
    cell = index;
    cell += value;
    seed = (s8)depth;
    if (y & HALF_MASK) {
        addend = seed + 1;
        count  = cell + addend;
    } else {
        count = cell + seed;
    }
    if ((u32)count < 56) {
        cursor = g_GfxPrimCursor;
        limit  = g_FrameBufferIndex * 0x9000 + PRIM_ARENA_BASE;
        next   = cursor + size;
        if (next < limit) {
            offset = (g_FrameBufferIndex + 4) * 8 + count * 0x30;
            packet = *(u8**)(D_80142CC4 + offset);
            setaddr(packet, cursor);
            g_GfxPrimCursor = next;
            slot            = (u32*)(D_80142CC4 + offset);
            *slot           = tag;
        }
    }
}

MATCH void func_801F8124(void) {
    SYS_DISPATCH_BYTE(D_801FA204, D_80146872);
}

MATCH void func_801F8160(void) {
    D_80146872 = 1;
    D_80144EA8 = 0;
}

INCLUDE_ASM(func_801F817C);

MATCH void func_801F863C(void) {
    SYS_DISPATCH_BYTE(D_801FA210, g_SceneState.state_04);
}

MATCH void func_801F8678(void) {
}

INCLUDE_ASM(func_801F8680);

INCLUDE_ASM(func_801F8F98);

MATCH void func_801F9CFC(void) {
    s32 offset = D_801FA220[(g_FrameCount >> 1) & 3];

    g_AreaCameraRefreshCount = 2;
    g_AreaCameraHeight += offset * 4;
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH s32 func_801F9D88(void* entity, void* flags) {
    SYS_SetFlag(flags, 0);
    return 0;
}

MATCH s32 func_801F9DAC(void) {
    return 0;
}

MATCH s32 func_801F9DB4(void) {
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_FIRST_FLOOR) {
        return func_801F9DF4();
    }
    return 0;
}

INCLUDE_ASM(func_801F9DF4);

#include "overlays/scenario/Scene_ShowMessage.h"

#include "overlays/scenario/Scene_DispatchByPosition.h"

MATCH void func_801FA074(void) {
    Game_SetScriptActive();
    g_SceneState.timer_06 = 0xA;
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FA0B4(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0);
    g_PartyFieldOrder     = 255;
    D_80144F5B            = 255;
    D_80144F5C            = 255;
    g_PartyBattleOrder[0] = 255;
    D_80144F5E            = 255;
    D_80144F5F            = 255;
    g_Game.party_size     = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

#include "overlays/scenario/Scene_SetPartyRyuYoungNinaYoungMomo.h"

MATCH void func_801FA178(void) {
}
