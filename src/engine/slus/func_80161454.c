#include "engine/slus/slus.h"

MATCH void func_80161454(u32 index) {
    struct {
        s32 mask;
        s32 attr;
        s16 volume;
        s16 pan;
        u8  pad[0x44];
    } voice;

    s16 tmp0;
    s16 tmp1;
    s16 val0;
    s16 val1;
    s32 a1;
    s32 val3;
    s32 q;
    s32 tmp2;
    s32 tmp3;
    u8  tmp4;
    /* FAKE: The counter pin keeps retail's s1 assignment. */
    FAKE_REG(u8, val4, "s1");
    s32    val5;
    s32    val6;
    u32    tmp5;
    u8     pan;
    u32    val8;
    Actor* work;

    val3 = 0;
    if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        work = SELF(Actor);
        tmp0 = work->screen_y;
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
        tmp2 = (s32)(SELF(Actor)->pos.x.fixed - g_AreaCamera.scroll_x.fixed) >> 0xC;
        tmp3 = (s32)(SELF(Actor)->pos.y.fixed - g_AreaCamera.scroll_y.fixed) >> 0xC;
        tmp5 = ((u32)csqrt((tmp2 * tmp2) + (tmp3 * tmp3)) >> 4) * 0xA;
        if (tmp5 >= 0x37FFU) {
            val1 = 0;
            val0 = 0;
        } else {
            val1 = 0x37FF - tmp5;
            val0 = val1;
        }
        if (g_SndMono == 0) {
            a1 = (s16)SELF(Actor)->screen_x - 0xA0;
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
    if (((s32)SELF(Actor)->voice_flags.raw & 0x0FFFFF00) == 0x0FFFFF00) {
        SELF(Actor)->header.flags &= 0xF7;
        SELF(Actor)->voice_flags.raw &= 0xF00000FF;
        return;
    }
    do {
        q    = ((s32)SELF(Actor)->voice_flags.raw >> val4) & 0x1F;
        tmp4 = q;
        if (q != 0x1F) {
            val8 = SPU_KEYCH(tmp4);
            if (SpuGetKeyStatus(val8) == SPU_OFF) {
                SELF(Actor)->voice_flags.raw |= 0x1F << val4;
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
