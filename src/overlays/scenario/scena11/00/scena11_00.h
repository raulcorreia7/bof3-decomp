#ifndef OVERLAY_SCENARIO_SCENA11_00_H
#define OVERLAY_SCENARIO_SCENA11_00_H

/* The scenario/scena11/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

#define g_Task ((Actor*)g_Task)

extern u32       D_801F6C00;
extern Callback  D_801FAEC0[];
extern Callback  D_801FAEF0[];
extern Callback  D_801FAEFC[];
/* D_801FAF24 */
extern SceneFunc g_SceneActorDispatch[];

extern Point3l D_801481E8;
extern Point3l D_801481F8;

#endif
