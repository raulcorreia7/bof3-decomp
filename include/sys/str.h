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

#endif
