#ifndef OVERLAY_ETC_START_09_H
#define OVERLAY_ETC_START_09_H

/* The etc/start/09 save overlay's local declarations: the save directory, the card
 * name and prefix tables, the TIM image records and the save frame. Only this
 * image includes the file. */

#include "shared/etc.h"
#include <string.h>

/* Save-directory entries and the address of the save-frame buffer. */
#define SAVE_DIR_NAME_MAX      20
#define SAVE_DIR_SIZE          0x18
#define SAVE_FRAME_ADDR        0x800C1800u

/* Card-name table dimensions. */
#define CARD_NAME_MAX          8
#define CARD_NAME_SIZE         0x30
#define CARD_WILDCARD_MAX      4
#define CARD_PORT_PREFIX_LEN   6
#define CARD_GAME_ID_LEN       6
#define CARD_PORT_PATTERN_LEN  7

/* PSX TIM constants and record dimensions. */
#define TIM_MAGIC              0x10

#define TIM_HEADER_SIZE        0x08
#define TIM_CLUT_BLOCK_SIZE    0x2C
#define TIM_IMAGE_BLOCK_SIZE   0x8C
#define TIM_ICON_SIZE          0xC0
#define TIM_CLUT_COLORS        16
#define TIM_IMAGE_WORDS        64
#define TIM_ICON_COUNT         3
#define TIM_ICON_PIXEL_SIZE    16

/* Save-frame layout. */
#define CARD_HEADER_MAGIC_SIZE 4
#define CARD_HEADER_NAME_SIZE  28
#define CARD_ICON_PALETTE_SIZE 0x20
#define CARD_ICON_FRAME_SIZE   0x80
#define CARD_ICON_FRAME_COUNT  3
#define CARD_FILE_HEADER_SIZE  0x200

/* Card event result codes, in event order: the software events
 * (EvSpIOE, EvSpTIMOUT, EvSpNEW, EvSpERROR) and the hardware events that
 * follow them. A poll starts at CARD_EVENT_PENDING, and a directory that would
 * outgrow the card returns CARD_EVENT_CAPACITY. */
typedef enum CardEvent {
    CARD_EVENT_PENDING  = -1,
    CARD_EVENT_OK       = 0,
    CARD_EVENT_TIMEOUT  = 1,
    CARD_EVENT_NEW      = 2,
    CARD_EVENT_ERROR    = 3,
    CARD_EVENT_CAPACITY = 4,
} CardEvent;

typedef enum TimFlags {
    TIM_FLAG_CLUT = 1 << 3,
} TimFlags;

typedef struct SaveFile {
    char name[SAVE_DIR_NAME_MAX];
    s32  size;
} SaveFile;

ASSERT_SIZE(SaveFile, SAVE_DIR_SIZE);
ASSERT_OFFSET(SaveFile, name, 0x00);
ASSERT_OFFSET(SaveFile, size, 0x14);

typedef struct {
    u32  unk_00;                       /* 0x00 0x141; no reader */
    char port0_prefix[CARD_NAME_MAX];  /* 0x04 "bu00:" */
    char port1_prefix[CARD_NAME_MAX];  /* 0x0C "bu10:" */
    char game_id[CARD_NAME_MAX];       /* 0x14 "BASLUS" */
    char port0_pattern[CARD_NAME_MAX]; /* 0x1C "bu00:*" */
    char port1_pattern[CARD_NAME_MAX]; /* 0x24 "bu10:*" */
    char wildcard[CARD_WILDCARD_MAX];  /* 0x2C "*" */
} CardNames;

ASSERT_SIZE(CardNames, CARD_NAME_SIZE);
ASSERT_OFFSET(CardNames, unk_00, 0x00);
ASSERT_OFFSET(CardNames, port0_prefix, 0x04);
ASSERT_OFFSET(CardNames, port1_prefix, 0x0C);
ASSERT_OFFSET(CardNames, game_id, 0x14);
ASSERT_OFFSET(CardNames, port0_pattern, 0x1C);
ASSERT_OFFSET(CardNames, port1_pattern, 0x24);
ASSERT_OFFSET(CardNames, wildcard, 0x2C);

typedef struct {
    u8 data[CARD_ICON_PALETTE_SIZE];
} SaveIconPalette;

ASSERT_SIZE(SaveIconPalette, CARD_ICON_PALETTE_SIZE);
ASSERT_OFFSET(SaveIconPalette, data, 0x00);

typedef struct {
    u8 data[CARD_ICON_FRAME_SIZE];
} SaveIconFrame;

ASSERT_SIZE(SaveIconFrame, CARD_ICON_FRAME_SIZE);
ASSERT_OFFSET(SaveIconFrame, data, 0x00);

typedef struct {
    u32 magic; /* 0x00 0x10 = TIM magic */
    u32 flags; /* 0x04 TimFlags; bits 0-2 0 = 4bpp */
} TimHeader;

ASSERT_SIZE(TimHeader, TIM_HEADER_SIZE);
ASSERT_OFFSET(TimHeader, magic, 0x00);
ASSERT_OFFSET(TimHeader, flags, 0x04);

typedef struct {
    u32 length; /* 0x00 block bytes incl. header: 0x2C */
    u16 x;      /* 0x04 VRAM x */
    u16 y;      /* 0x06 VRAM y */
    u16 width;  /* 0x08 16-bit words: 16 */
    u16 height; /* 0x0A rows: 1 */

    union {
        u16             color[TIM_CLUT_COLORS];
        SaveIconPalette save_header;
    } data; /* 0x0C CLUT words */
} TimClutBlock;

ASSERT_SIZE(TimClutBlock, TIM_CLUT_BLOCK_SIZE);
ASSERT_OFFSET(TimClutBlock, length, 0x00);
ASSERT_OFFSET(TimClutBlock, x, 0x04);
ASSERT_OFFSET(TimClutBlock, y, 0x06);
ASSERT_OFFSET(TimClutBlock, width, 0x08);
ASSERT_OFFSET(TimClutBlock, height, 0x0A);
ASSERT_OFFSET(TimClutBlock, data, 0x0C);

typedef struct {
    u32 length; /* 0x00 block bytes incl. header: 0x8C */
    u16 x;      /* 0x04 VRAM x */
    u16 y;      /* 0x06 VRAM y */
    u16 width;  /* 0x08 16-bit words per row: 4 */
    u16 height; /* 0x0A rows: 16 */

    union {
        u16           word[TIM_IMAGE_WORDS];
        SaveIconFrame save_block;
    } data; /* 0x0C 16x16 4bpp pixels, 64 VRAM words */
} TimImageBlock;

ASSERT_SIZE(TimImageBlock, TIM_IMAGE_BLOCK_SIZE);
ASSERT_OFFSET(TimImageBlock, length, 0x00);
ASSERT_OFFSET(TimImageBlock, x, 0x04);
ASSERT_OFFSET(TimImageBlock, y, 0x06);
ASSERT_OFFSET(TimImageBlock, width, 0x08);
ASSERT_OFFSET(TimImageBlock, height, 0x0A);
ASSERT_OFFSET(TimImageBlock, data, 0x0C);

typedef struct {
    TimHeader     header; /* 0x00 */
    TimClutBlock  clut;   /* 0x08 */
    TimImageBlock image;  /* 0x34 */
} TimIcon;

ASSERT_SIZE(TimIcon, TIM_ICON_SIZE);
ASSERT_OFFSET(TimIcon, header, 0x00);
ASSERT_OFFSET(TimIcon, clut, 0x08);
ASSERT_OFFSET(TimIcon, image, 0x34);

typedef struct {
    u8              magic[CARD_HEADER_MAGIC_SIZE]; /* 0x00 "SC" plus the save kind */
    char            name[CARD_HEADER_NAME_SIZE];   /* 0x04 */
    u8              unk_20[0x24];                  /* 0x20 */
    u8              unk_44[0x1C];                  /* 0x44 */
    SaveIconPalette header;                        /* 0x60 */
    SaveIconFrame   image[CARD_ICON_FRAME_COUNT];  /* 0x80 */
} CardFileHeader;

ASSERT_SIZE(CardFileHeader, CARD_FILE_HEADER_SIZE);
ASSERT_OFFSET(CardFileHeader, magic, 0x00);
ASSERT_OFFSET(CardFileHeader, name, 0x04);
ASSERT_OFFSET(CardFileHeader, unk_20, 0x20);
ASSERT_OFFSET(CardFileHeader, unk_44, 0x44);
ASSERT_OFFSET(CardFileHeader, header, 0x60);
ASSERT_OFFSET(CardFileHeader, image, 0x80);

typedef union {
    u8             bytes[CARD_FILE_HEADER_SIZE];
    CardFileHeader frame;
} SaveFrameBuffer;

ASSERT_SIZE(SaveFrameBuffer, CARD_FILE_HEADER_SIZE);
ASSERT_OFFSET(SaveFrameBuffer, bytes, 0x00);
ASSERT_OFFSET(SaveFrameBuffer, frame, 0x00);

/* Retail-address data symbols, in address order. */
extern u8              D_800C1800;
extern u8              D_800C1801;
extern u8              D_800C1802;
extern u8              D_800C1803;
extern SaveFile        D_8018E990[];
extern const CardNames D_801EEC00;
extern s32             D_801EEC04;
extern s32             D_801EEC0C;
extern char            D_801EEC14[];
extern s32             D_801EEC1C;
extern s32             D_801EEC24;
extern char            D_801EEC2C[];
/* The asset span asset_save_icons holds three TimIcon records at 0x801EFE54, 0x801EFF14 and
 * 0x801EFFD4. CardBuildFileHeader copies icon 0's CLUT colors and each icon's pixels into the
 * memory-card save frame; nothing reads the TIM headers or uploads them to VRAM. */
extern u8              D_801EFE68[]; /* icon 0 clut.data */
extern u8              D_801EFE94[]; /* icon 0 image.data */
extern u8              D_801EFF54[]; /* icon 1 image.data */
extern u8              D_801F0014[]; /* icon 2 image.data */

/* SDK and cross-unit functions used by this image. */
extern s32  func_801EEEC8(void);
extern s32  CardTestHardwareEvents(void);
extern void CardPollSoftwareEvents(void);
extern void CardPollHardwareEvents(void);
extern void CardPollInfo(void);
extern void CardPollLoad(void);
extern void func_801EF148(void);
extern s32  CardOpenFile(u8 port, char* name, s32 mode);
extern s32  CardTransferFile(s32 fd, s32 mode, s32 size, s32 offset);

#endif
