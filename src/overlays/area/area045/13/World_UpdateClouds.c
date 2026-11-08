#include "area045_13.h"

#include "overlays/area/World_UpdateCloudLayer.h"

extern WorldCloudTexture g_WorldCloudTexture;

MATCH void World_UpdateClouds(void) {
    WORLD_UPDATE_CLOUD_LAYER(g_WorldCloudTexture);
}
