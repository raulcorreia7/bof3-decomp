#include "engine/slus/slus.h"

/* lifted draft, best score 48.50%; semantics unverified
 */
#ifdef NON_MATCHING
NON_MATCHING void func_80161454(u32 index) {
    struct {
        s32 mask;
        s32 attr;
        s16 volume;
        s16 pan;
        u8  pad[0x44];
    } voice;

    s16    tmp0;
    s16    tmp1;
    s16    val0;
    s16    val1;
    s32    a1;
    s32    val3;
    s32    q;
    s32    tmp2;
    s32    tmp3;
    u8     tmp4;
    u8     val4;
    s32    val5;
    s32    val6;
    u32    tmp5;
    u8     pan;
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
            pan  = (tmp1 + 40) / 4;
            if (tmp1 < -40) {
                pan = 0;
            }
            if (tmp1 >= 361) {
                pan = 100;
            }
            val1 = (val1 * pan) / 100;
            val0 = (val0 * (100 - pan)) / 100;
        }
    } else {
        tmp2 = (s32)(g_Task->pos.x.fixed - g_AreaScrollTargetX) >> 0xC;
        tmp3 = (s32)(g_Task->pos.y.fixed - g_AreaScrollTargetY) >> 0xC;
        tmp5 = ((u32)csqrt((tmp2 * tmp2) + (tmp3 * tmp3)) >> 4) * 0xA;
        if (tmp5 >= 0x37FFU) {
            val1 = 0;
            val0 = 0;
        } else {
            val1 = 0x37FF - tmp5;
            val0 = val1;
        }
        if (g_SndMono == 0) {
            a1 = (s16)g_Task->screen_x - 0xA0;
            if (a1 < 0) {
                q = (a1 * (s16)val1) / 480;
                q = ABS(q);
                if (q < (s16)val1) {
                    val1 = val1 - (ABS(a1) * (s16)val1) / 480;
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
    val4 = 8;
    if (((s32)g_Task->state_70.word & 0x0FFFFF00) == 0x0FFFFF00) {
        g_Task->header.flags &= 0xF7;
        g_Task->state_70.word &= 0xF00000FF;
        return;
    }
    do {
        q    = ((s32)g_Task->state_70.word >> val4) & 0x1F;
        tmp4 = q;
        if (q != 0x1F) {
            val8 = 1 << tmp4;
            if (SpuGetKeyStatus(val8) == SPU_OFF) {
                g_Task->state_70.word |= 0x1F << val4;
            } else {
                val3 |= val8;
            }
        }
        val4 += 5;
    } while (val4 < 0x18U);
    voice.mask   = val3;
    voice.attr   = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    voice.volume = val0;
    voice.pan    = val1;
    SpuSetVoiceAttr((SpuVoiceAttr*)&voice);
}
#else
INCLUDE_ASM(func_80161454);
#endif
