#include "engine/slus/slus.h"

/* TODO. */
MATCH void func_8015D820(u16 cue_id, u16 index) {
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 22 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 22 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 22 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 22) {
        D_8018B3D8 = D_80182308[0];
        D_8018B3DC = D_80182308[0];
        SND_PlayCue(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 18 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 18 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 18 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 18) {
        D_8018B3D8 = D_80182308[0];
        D_8018B3DC = D_80182308[0];
        SND_PlayCue(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 12 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 12 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 12 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 12) {
        D_8018B3D8 = D_801822EA;
        D_8018B3DC = D_801822EA;
        SND_PlayCue(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 8 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 8 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 8 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 8) {
        D_8018B3D8 = D_801822CA;
        D_8018B3DC = D_801822CA;
        SND_PlayCue(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 6 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 6 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 6 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 6) {
        D_8018B3D8 = D_801822AA;
        D_8018B3DC = D_801822AA;
        SND_PlayCue(cue_id);
    }
    if (D_80145EC6 <= COORD_INT(g_Actors[index].pos.x) + 2 && D_80145EC6 >= COORD_INT(g_Actors[index].pos.x) - 2 &&
        D_80145ECA <= COORD_INT(g_Actors[index].pos.y) + 2 && D_80145ECA >= COORD_INT(g_Actors[index].pos.y) - 2) {
        D_8018B3D8 = D_80182290[0];
        D_8018B3DC = D_80182290[0];
        SND_PlayCue(cue_id);
    }
}
