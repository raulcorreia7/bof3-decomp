#ifndef OVERLAY_ETC_START_09_H
#define OVERLAY_ETC_START_09_H

/* The etc/start/09 save overlay's local declarations: the save directory, the card
 * name and prefix tables, the TIM image records and the card file header. Only this
 * image includes the file. */

#include "shared/etc.h"
#include <string.h>

/* Save-directory entries and the address of the save file buffer (g_SaveHeader, then the save data). */
#define SAVE_DIR_NAME_MAX     20
#define SAVE_DIR_SIZE         0x18
#define SAVE_FILE_ADDR        0x800C1800u

/* Card-name table dimensions. */
#define CARD_NAME_MAX         8
#define CARD_NAME_SIZE        0x30
#define CARD_WILDCARD_MAX     4
#define CARD_PORT_PREFIX_LEN  6
#define CARD_GAME_ID_LEN      6
#define CARD_PORT_PATTERN_LEN 7

/* PSX TIM constants and record dimensions. */
#define TIM_MAGIC             0x10

#define TIM_HEADER_SIZE       0x08
#define TIM_CLUT_BLOCK_SIZE   0x2C
#define TIM_IMAGE_BLOCK_SIZE  0x8C
#define TIM_ICON_SIZE         0xC0
#define TIM_CLUT_COLORS       16
#define TIM_IMAGE_WORDS       64
#define TIM_ICON_COUNT        3
#define TIM_ICON_PIXEL_SIZE   16

/* Memory card file header layout (the PsyQ sample's _CARD). */
#define SAVE_MAGIC_SIZE       2
#define SAVE_TITLE_SIZE       64
#define SAVE_RESERVE_SIZE     28
#define SAVE_ICON_CLUT_SIZE   0x20
#define SAVE_ICON_SIZE        0x80
#define SAVE_ICON_COUNT       3
#define SAVE_HEADER_SIZE      0x200

typedef enum TimFlags {
    TIM_FLAG_CLUT = 1 << 3,
} TimFlags;

typedef struct SaveFile {
    char name[SAVE_DIR_NAME_MAX];
    s32  size;
} SaveFile;

ASSERT_OFFSET(SaveFile, name, 0x00);
ASSERT_OFFSET(SaveFile, size, 0x14);
ASSERT_SIZE(SaveFile, SAVE_DIR_SIZE);

typedef struct {
    u32  unk_00;                       /* 0x00 0x141; no reader */
    char port0_prefix[CARD_NAME_MAX];  /* 0x04 "bu00:" */
    char port1_prefix[CARD_NAME_MAX];  /* 0x0C "bu10:" */
    char game_id[CARD_NAME_MAX];       /* 0x14 "BASLUS" */
    char port0_pattern[CARD_NAME_MAX]; /* 0x1C "bu00:*" */
    char port1_pattern[CARD_NAME_MAX]; /* 0x24 "bu10:*" */
    char wildcard[CARD_WILDCARD_MAX];  /* 0x2C "*" */
} CardNames;

ASSERT_OFFSET(CardNames, unk_00, 0x00);
ASSERT_OFFSET(CardNames, port0_prefix, 0x04);
ASSERT_OFFSET(CardNames, port1_prefix, 0x0C);
ASSERT_OFFSET(CardNames, game_id, 0x14);
ASSERT_OFFSET(CardNames, port0_pattern, 0x1C);
ASSERT_OFFSET(CardNames, port1_pattern, 0x24);
ASSERT_OFFSET(CardNames, wildcard, 0x2C);
ASSERT_SIZE(CardNames, CARD_NAME_SIZE);

/* The 16 colours of the save icon, copied as bytes. */
typedef struct {
    u8 bytes[SAVE_ICON_CLUT_SIZE];
} SaveIconClut;

ASSERT_OFFSET(SaveIconClut, bytes, 0x00);
ASSERT_SIZE(SaveIconClut, SAVE_ICON_CLUT_SIZE);

/* One 16x16 4-bit frame of the save icon, copied as bytes. */
typedef struct {
    u8 bytes[SAVE_ICON_SIZE];
} SaveIcon;

ASSERT_OFFSET(SaveIcon, bytes, 0x00);
ASSERT_SIZE(SaveIcon, SAVE_ICON_SIZE);

typedef struct {
    u32 magic; /* 0x00 0x10 = TIM magic */
    u32 flags; /* 0x04 TimFlags; bits 0-2 0 = 4bpp */
} TimHeader;

ASSERT_OFFSET(TimHeader, magic, 0x00);
ASSERT_OFFSET(TimHeader, flags, 0x04);
ASSERT_SIZE(TimHeader, TIM_HEADER_SIZE);

typedef struct {
    u32 length; /* 0x00 block bytes incl. header: 0x2C */
    u16 x;      /* 0x04 VRAM x */
    u16 y;      /* 0x06 VRAM y */
    u16 width;  /* 0x08 16-bit words: 16 */
    u16 height; /* 0x0A rows: 1 */

    union {
        u16          color[TIM_CLUT_COLORS];
        SaveIconClut save_clut;
    } data; /* 0x0C CLUT words */
} TimClutBlock;

ASSERT_OFFSET(TimClutBlock, length, 0x00);
ASSERT_OFFSET(TimClutBlock, x, 0x04);
ASSERT_OFFSET(TimClutBlock, y, 0x06);
ASSERT_OFFSET(TimClutBlock, width, 0x08);
ASSERT_OFFSET(TimClutBlock, height, 0x0A);
ASSERT_OFFSET(TimClutBlock, data, 0x0C);
ASSERT_SIZE(TimClutBlock, TIM_CLUT_BLOCK_SIZE);

typedef struct {
    u32 length; /* 0x00 block bytes incl. header: 0x8C */
    u16 x;      /* 0x04 VRAM x */
    u16 y;      /* 0x06 VRAM y */
    u16 width;  /* 0x08 16-bit words per row: 4 */
    u16 height; /* 0x0A rows: 16 */

    union {
        u16      word[TIM_IMAGE_WORDS];
        SaveIcon save_icon;
    } data; /* 0x0C 16x16 4bpp pixels, 64 VRAM words */
} TimImageBlock;

ASSERT_OFFSET(TimImageBlock, length, 0x00);
ASSERT_OFFSET(TimImageBlock, x, 0x04);
ASSERT_OFFSET(TimImageBlock, y, 0x06);
ASSERT_OFFSET(TimImageBlock, width, 0x08);
ASSERT_OFFSET(TimImageBlock, height, 0x0A);
ASSERT_OFFSET(TimImageBlock, data, 0x0C);
ASSERT_SIZE(TimImageBlock, TIM_IMAGE_BLOCK_SIZE);

typedef struct {
    TimHeader     header; /* 0x00 */
    TimClutBlock  clut;   /* 0x08 */
    TimImageBlock image;  /* 0x34 */
} TimIcon;

ASSERT_OFFSET(TimIcon, header, 0x00);
ASSERT_OFFSET(TimIcon, clut, 0x08);
ASSERT_OFFSET(TimIcon, image, 0x34);
ASSERT_SIZE(TimIcon, TIM_ICON_SIZE);

/* The memory card file header block: the PsyQ sample's _CARD. */
typedef struct {
    char         magic[SAVE_MAGIC_SIZE];     /* 0x00 "SC" */
    u8           type;                       /* 0x02 0x11-0x13: icon frames 1-3 */
    u8           block_entry;                /* 0x03 card blocks the file uses */
    char         title[SAVE_TITLE_SIZE];     /* 0x04 */
    u8           reserve[SAVE_RESERVE_SIZE]; /* 0x44 */
    SaveIconClut clut;                       /* 0x60 */
    SaveIcon     icons[SAVE_ICON_COUNT];     /* 0x80 */
} SaveHeader;

ASSERT_OFFSET(SaveHeader, magic, 0x00);
ASSERT_OFFSET(SaveHeader, type, 0x02);
ASSERT_OFFSET(SaveHeader, block_entry, 0x03);
ASSERT_OFFSET(SaveHeader, title, 0x04);
ASSERT_OFFSET(SaveHeader, reserve, 0x44);
ASSERT_OFFSET(SaveHeader, clut, 0x60);
ASSERT_OFFSET(SaveHeader, icons, 0x80);
ASSERT_SIZE(SaveHeader, SAVE_HEADER_SIZE);

/* The card file header at the start of the save file buffer; the code addresses it as a
 * literal (lui/ori), so it is a fixed-address view, not a linked symbol. */
#define g_SaveHeader (*MEM_PTR(SaveHeader, SAVE_FILE_ADDR))

/* Retail-address data symbols, in address order. */
/* D_8018E990 */
extern SaveFile        g_SaveCardDirectory[];
extern const CardNames D_801EEC00;
extern s32             D_801EEC04;
extern s32             D_801EEC0C;
extern char            D_801EEC14[];
extern s32             D_801EEC1C;
extern s32             D_801EEC24;
extern char            D_801EEC2C[];
/* The asset span asset_save_icons holds three TimIcon records at 0x801EFE54, 0x801EFF14 and
 * 0x801EFFD4. SAVE_BuildFileHeader copies icon 0's CLUT colors and each icon's pixels into the
 * card file header g_SaveHeader; nothing reads the TIM headers or uploads them to VRAM. */
extern u8              D_801EFE68[]; /* icon 0 clut.data */
extern u8              D_801EFE94[]; /* icon 0 image.data */
extern u8              D_801EFF54[]; /* icon 1 image.data */
extern u8              D_801F0014[]; /* icon 2 image.data */

/* SDK and cross-unit functions used by this image. */
extern s32  func_801EEEC8(void);
extern s32  SAVE_TestHardwareEvents(void);
extern void SAVE_PollSoftwareEvents(void);
extern void SAVE_PollHardwareEvents(void);
extern void SAVE_PollCard(void);
extern void SAVE_PollCardLoad(void);
extern void func_801EF148(void);
extern s32  SAVE_OpenFile(u8 port, char* name, s32 mode);
extern s32  SAVE_TransferFile(s32 fd, s32 mode, s32 size, s32 offset);

#endif
