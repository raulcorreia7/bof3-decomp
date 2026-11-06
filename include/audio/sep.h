#ifndef AUDIO_SEP_H
#define AUDIO_SEP_H

#include "types.h"

/* A SEP sequence package (EMI entry type 10): a file header, then per sequence
 * a header and its event data. libsnd's SsSepOpen reads the package through
 * the table g_SelectionFxVoices; the fields are measured over all 119 retail packages
 * (@source: wiki:formats/audio#sep-package). Multi-byte
 * fields are big-endian and unaligned, so the headers are byte arrays. */
#define SEP_MAGIC_SIZE           4
#define SEP_SEQUENCE_COUNT       4 /* sequences in every retail package */
#define SEP_FILE_HEADER_SIZE     6
#define SEP_SEQUENCE_HEADER_SIZE 13

#endif
