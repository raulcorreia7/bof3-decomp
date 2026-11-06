#ifndef SYS_SCENE_H
#define SYS_SCENE_H

#include "types.h"
#include "psx/psyq.h"

/* The per-frame camera turn step, in the 4096-unit scene rotation. */
#define AREA_CAMERA_STEP 22

/* The scene camera rotation: x, y and z halfwords in the 4096-unit turn, as RotMatrix takes them. */
typedef SVECTOR CameraAngle;

/* D_801492D8 */
extern CameraAngle g_AreaCameraAngle; /* x, y, z scene rotation halfwords */

#endif
