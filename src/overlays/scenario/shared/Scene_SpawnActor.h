/* Claims a free actor slot, keeps it in the image's slot byte and seeds its type, camera angles, scene step and layer;
 * returns whether a slot was free. A statement macro: the slot byte differs per image. Every change must verify every
 * member. */
/* Scene_SpawnActor (scena14, scena15) */
#define SCENE_SPAWN_ACTOR(slot_byte)                                \
    {                                                               \
        u8 slot;                                                    \
                                                                    \
        slot      = Actor_FindFreeSpawned();                        \
        slot_byte = slot;                                           \
        if (slot != GAME_NONE) {                                    \
            g_SpawnedActors[slot].header.flags        = 1;          \
            g_SpawnedActors[slot_byte].type           = type;       \
            g_SpawnedActors[slot_byte].camera_angle.x = angle_x;    \
            g_SpawnedActors[slot_byte].camera_angle.y = angle_y;    \
            g_SpawnedActors[slot_byte].camera_angle.z = angle_z;    \
            g_SpawnedActors[slot_byte].scene_step     = scene_step; \
            g_SpawnedActors[slot_byte].layer          = layer;      \
        } else {                                                    \
            return false;                                           \
        }                                                           \
        return true;                                                \
    }
