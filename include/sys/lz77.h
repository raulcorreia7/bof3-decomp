#ifndef SYS_LZ77_H
#define SYS_LZ77_H

/* The prefix of a packed EMI payload (entry type 1). LZ77_DecodeBegin points the
 * decoder's input cursor LZ77_HEADER_SIZE bytes into the first scratchpad
 * sector, so the control stream starts after the prefix (@source: wiki:formats/lz77).
 * The prefix is a little-endian u32 decoded size at LZ77_SIZE_OFFSET and the
 * u16 LZ77_MARKER at LZ77_MARKER_OFFSET (0xFFFF in all 65 retail samples), then
 * the control stream, which ends with 0xFF. */
#define LZ77_SIZE_OFFSET                 0x00
#define LZ77_MARKER_OFFSET               0x04
#define LZ77_HEADER_SIZE                 0x06
#define LZ77_MARKER                      0xFFFF

#define LZ77_CONTROL_LITERAL_LENGTH_MASK 0x1F
#define LZ77_CONTROL_MATCH_DISTANCE_MASK 0xE0
#define LZ77_CONTROL_MATCH_LENGTH_MASK   0x0F
#define LZ77_CONTROL_END                 0xFF

/* Decoder control stream (`exe/slus_004_22@0x801640E4`). */
typedef enum Lz77ControlFlags {
    LZ77_CONTROL_LITERAL_FLAG = 1 << 4,
} Lz77ControlFlags;

#endif
