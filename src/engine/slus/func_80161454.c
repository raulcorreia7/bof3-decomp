#include "engine/slus/slus.h"

/* lifted draft, best score 48.50%; semantics unverified
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; register pins dropped, score is the pinned
 * draft; best score 48.50%. resume: a lever or header fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_80161454(u32 index) {
    struct {
        s32 mask;
        s32 attr;
        s16 volume;
        s16 pan;
        u8  pad[0x34];
    } voice;

    s16    tmp0;
    s16    tmp1;
    s16    val0;
    s16    val1;
    s32    a1;
    s32    val2;
    s32    val3;
    s32    q;
    s32    tmp2;
    s32    tmp3;
    s32    tmp4;
    s32    val4;
    s32    val5;
    s32    val6;
    u32    tmp5;
    u32    val7;
    u32    val8;
    Actor* work;

    val3 = 0;
    if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        work = g_Task;
        tmp0 = (s16)work->screen_y;
        val0 = (tmp0 + 0x40) * 0x2C;
        if (tmp0 < -0x40) {
            val0 = 0;
        }
        if (tmp0 >= 0x131) {
            val0 = 0x3FFF;
        }
        val1 = val0;
        if (g_SndMono == 0) {
            tmp1 = (s16)work->screen_x;
            q    = tmp1 + 0x28;
            val7 = (u32)q >> 2;
            if (q < 0) {
                val7 = (u32)(tmp1 + 0x2B) >> 2;
            }
            if (tmp1 < -0x28) {
                val7 = 0;
            }
            if (tmp1 >= 0x169) {
                val7 = 0x64;
            }
            val7 &= BYTE_MASK;
            val1 = (val1 * val7) / 100;
            val0 = (val0 * (0x64 - val7)) / 100;
        }
    } else {
        work = g_Task;
        tmp2 = (s32)(work->pos.x.fixed - g_AreaScrollTargetX) >> 0xC;
        tmp3 = (s32)(work->pos.y.fixed - g_AreaScrollTargetY) >> 0xC;
        tmp5 = (csqrt((tmp2 * tmp2) + (tmp3 * tmp3)) >> 4) * 0xA;
        if (tmp5 >= 0x37FFU) {
            val1 = 0;
            val0 = 0;
        } else {
            val1 = 0x37FF - tmp5;
            val0 = val1;
        }
        if (g_SndMono == 0) {
            work = g_Task;
            a1   = (s16)work->screen_x - 0xA0;
            if (a1 < 0) {
                q = (a1 * (s16)val1) / 480;
                q = ABS(q);
                if (q < (s16)val1) {
                    a1   = ABS(a1);
                    val1 = val1 - (a1 * (s16)val1) / 480;
                } else {
                    val1 = 0;
                }
            } else {
                q = (a1 * (s16)val0) / 480;
                if (q < (s16)val0) {
                    val0 = val0 - q;
                } else {
                    val0 = 0;
                }
            }
        }
    }
    work = g_Task;
    val4 = 8;
    if (((s32)work->state_70.word & 0x0FFFFF00) == 0x0FFFFF00) {
        work->header.flags = work->header.flags & 0xF7;
        work               = g_Task;
        work->state_70.word &= 0xF00000FF;
        return;
    }
    val2 = 0x1F;
    do {
        val5 = val4 & BYTE_MASK;
        tmp4 = ((s32)g_Task->state_70.word >> val5) & 0x1F;
        if (tmp4 != 0x1F) {
            val8 = 1 << tmp4;
            if (SpuGetKeyStatus(val8) == SPU_OFF) {
                work = g_Task;
                work->state_70.word |= 0x1F << val5;
            } else {
                val3 |= val8;
            }
        }
        val4 += 5;
    } while ((u32)(val4 & BYTE_MASK) < 0x18U);
    voice.mask   = val3;
    voice.attr   = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    voice.volume = val0;
    voice.pan    = val1;
    SpuSetVoiceAttr((SpuVoiceAttr*)&voice);
}
#else
INCLUDE_ASM(func_80161454);
#endif
