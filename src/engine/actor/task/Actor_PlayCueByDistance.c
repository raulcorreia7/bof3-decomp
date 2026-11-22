#include "engine/slus/slus.h"

/* func_8015D820 */
/* Plays a cue when the point is within a range band of the actor. */
MATCH void Actor_PlayCueByDistance(u16 cue_id, u16 index) {
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 22 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 22 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 22 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 22) {
        g_SndSeVolumeL = g_SndVolumeLevels[64];
        g_SndSeVolumeR = g_SndVolumeLevels[64];
        SND_SEPlay(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 18 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 18 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 18 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 18) {
        g_SndSeVolumeL = g_SndVolumeLevels[64];
        g_SndSeVolumeR = g_SndVolumeLevels[64];
        SND_SEPlay(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 12 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 12 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 12 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 12) {
        g_SndSeVolumeL = g_SndVolumeLevels[49];
        g_SndSeVolumeR = g_SndVolumeLevels[49];
        SND_SEPlay(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 8 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 8 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 8 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 8) {
        g_SndSeVolumeL = g_SndVolumeLevels[33];
        g_SndSeVolumeR = g_SndVolumeLevels[33];
        SND_SEPlay(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 6 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 6 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 6 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 6) {
        g_SndSeVolumeL = g_SndVolumeLevels[17];
        g_SndSeVolumeR = g_SndVolumeLevels[17];
        SND_SEPlay(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 2 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 2 && D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 2 &&
        D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 2) {
        g_SndSeVolumeL = g_SndVolumeLevels[4];
        g_SndSeVolumeR = g_SndVolumeLevels[4];
        SND_SEPlay(cue_id);
    }
}
