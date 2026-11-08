#ifndef GAME_H
#define GAME_H

#include "common.h"

#include "audio/audio.h"
#include "scenario/state.h"
#include "area/area.h"
#include "game/game.h"
#include "battle/bmagic.h"
#include "battle/records.h"
#include "slus/data.h"
#include "slus/exports.h"
#include "game/functions.h"

/* The small base every game source reaches: the shared headers and the
 * resident systems all groups use. A group header includes this file and the
 * subsystem headers its images use; an image header includes its group header;
 * a unit includes its image header
 * ([include layers](../docs/conventions.md#include-layers)). */
#endif
