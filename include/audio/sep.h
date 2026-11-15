#ifndef AUDIO_SEP_H
#define AUDIO_SEP_H

#include "types.h"

/* A SEP sequence package (EMI entry type 10): a file header, then per sequence
 * a header and its event data. libsnd's SsSepOpen reads the package through
 * the table g_SelectionEffectVoices; the fields are measured over all 119 retail packages
 * (@source: wiki:formats/audio#sep-package). Multi-byte
 * fields are big-endian and unaligned, so the headers are byte arrays. */
#define SEP_MAGIC_SIZE           4
#define SEP_SEQUENCE_COUNT       4 /* sequences in every retail package */
#define SEP_FILE_HEADER_SIZE     6
#define SEP_SEQUENCE_HEADER_SIZE 13

typedef struct SepFileHeader {
    u8 magic[SEP_MAGIC_SIZE]; /* 0x00 bytes 70 51 45 53 */
    u8 version[2];            /* 0x04 u16 big-endian, 0 in every retail package */
} SepFileHeader;

ASSERT_SIZE(SepFileHeader, SEP_FILE_HEADER_SIZE);

typedef struct SepSequenceHeader {
    u8 sequence_id[2];    /* 0x00 u16 big-endian, 0..3 */
    u8 resolution[2];     /* 0x02 u16 big-endian, ticks per quarter note, 48 in every retail sequence */
    u8 tempo[3];          /* 0x04 big-endian microseconds per quarter note */
    u8 time_signature[2]; /* 0x07 */
    u8 data_size[4];      /* 0x09 u32 big-endian, bytes of event data that follow */
} SepSequenceHeader;

ASSERT_SIZE(SepSequenceHeader, SEP_SEQUENCE_HEADER_SIZE);

#endif
