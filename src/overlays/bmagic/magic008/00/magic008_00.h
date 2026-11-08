#ifndef OVERLAY_BMAGIC_MAGIC008_00_H
#define OVERLAY_BMAGIC_MAGIC008_00_H

/* The bmagic/magic008/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

typedef struct Magic008Steps801EEC04 {
    Callback steps[4];
} Magic008Steps801EEC04;

typedef struct Magic008Steps801EEC14 {
    Callback steps[3];
} Magic008Steps801EEC14;

extern Magic008Steps801EEC04 D_801EEC04;
extern BMagicEffectFuncs     D_801EEC58;

extern Magic008Steps801EEC14 D_801EEC14;
extern Magic008Steps801EEC04 D_801EEC20;
extern Magic008Steps801EEC04 D_801EEC30;
extern Magic008Steps801EEC14 D_801EEC40;
extern Magic008Steps801EEC14 D_801EEC4C;
extern Magic008Steps801EEC04 D_801EEC84;
extern BMagicEffectFuncs     D_801EEC94;

#endif
