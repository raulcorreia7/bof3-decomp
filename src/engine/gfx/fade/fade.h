#ifndef OVERLAY_GFX_FADE_H
#define OVERLAY_GFX_FADE_H

#include "types.h"

/* func_8014EDF0 */
void GFX_FadeToBlack(void);
/* func_8014EE18 */
void GFX_FadeFromBlack(void);
/* func_8014EE40 */
void GFX_FadeToBlackFast(void);
/* func_8014EE68 */
void GFX_FadeFromBlackFast(void);
/* func_8014EE90 */
void GFX_FadeToBlackSlow(void);
/* func_8014EEB8 */
void GFX_FadeFromBlackSlow(void);
/* func_8014EEE0 */
void GFX_FadeToBlackFront(void);
/* func_8014EF08 */
void GFX_FadeFromBlackFront(void);
/* func_8014EF30 */
void GFX_FadeToWhite(void);
/* func_8014EF58 */
void GFX_FadeFromWhite(void);
/* func_8014EF80 */
void GFX_ZoomToBlackSlow(void);
/* func_8014F024 */
void GFX_ZoomFromBlackSlow(void);
void func_8014F16C(void);
/* func_8014F1AC */
void GFX_FadeToBlackSlower(void);
/* func_8014F1D4 */
void GFX_FadeFromBlackSlower(void);
/* func_8014F1FC */
void GFX_FadeToWhiteSlower(void);
/* func_8014F224 */
void GFX_FadeFromWhiteSlower(void);
/* func_8014F24C */
void GFX_ZoomToBlackSlower(void);
void func_8014F2F0(void);
/* func_8014F438 */
void GFX_FadeToBlackSlowest(void);
/* func_8014F460 */
void GFX_SpinToBlack(void);
void GFX_FadeRunBlack(s32 delta, s32 semi_trans, s32 order);
void GFX_FadeRunWhite(s32 delta, s32 semi_trans, s32 order);
/* func_8014F704 */
s32  GFX_FadeUpdateScreen(u16* level, s32 delta, char semi_trans, u32 order, u8 blend_mode);

#endif
