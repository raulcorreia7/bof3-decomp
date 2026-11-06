#ifndef SYSTEM_STR_H
#define SYSTEM_STR_H

#include "types.h"

/* STR streaming sector geometry: an XA subheader, the payload and its EDC,
 * plus the outer header of a raw 2352-byte CD sector. The logo player's STR
 * reader decodes CAPCOM30.STR with this geometry (@source: wiki:formats/str). */
/* [XA subheader 8][payload 2324][EDC 4] = 2336 bytes.
 * Raw CD sectors add a 16-byte outer header for 2352 bytes. */
#define STR_RAW_HEADER_SIZE   16
#define STR_XA_SUBHEADER_SIZE 4
#define STR_XA_SUB_SIZE       8 /* two XA subheaders */
#define STR_PAYLOAD_SIZE      2324
#define STR_EDC_SIZE          4
#define STR_SECTOR_SIZE       2336
#define STR_RAW_SECTOR_SIZE   2352

/* An XA subheader: the 4-byte frame header of an XA sector; the sector's
 * 8-byte subheader holds two (psx-spx: "CDROM XA Subheader, File, Channel,
 * Interleave"). */
typedef struct XaSubheader {
    u8 file;    /* 0x00 stream file number */
    u8 channel; /* 0x01 interleaved channel number */
    u8 submode; /* 0x02 bit 2: audio sector; bit 7: end of file */
    u8 coding;  /* 0x03 bit 0: stereo; bit 2: 18.9 kHz rate */
} XaSubheader;

ASSERT_SIZE(XaSubheader, STR_XA_SUBHEADER_SIZE);

#endif
