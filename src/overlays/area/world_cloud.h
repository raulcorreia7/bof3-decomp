#ifndef OVERLAY_AREA_WORLD_CLOUD_H
#define OVERLAY_AREA_WORLD_CLOUD_H

/* The world map cloud layer shared by the world area overlays. */

/* The texture window of an image's cloud layer, indexed by layer width (0 or 1). */
typedef struct WorldCloudTexture {
    u8 u_origin[4];
    u8 v_origin[4];
    u8 cell_size[4];
} WorldCloudTexture;

/* The layer is skipped when the target cell is this many cells or more away on both axes. */
#define WORLD_CLOUD_DRAW_RANGE 26

extern WorldCloudTexture g_WorldCloudTexture;

#endif
