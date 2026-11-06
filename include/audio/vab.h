#ifndef AUDIO_VAB_H
#define AUDIO_VAB_H

/* A VAB bank: one instrument bank loaded from an EMI type-6 header and type-7
 * body. It is the sample side of the audio path: the type-8 cue table
 * (audio/cue.h) names tones in it, and the SEP packages drive the music. The
 * bank holds up to 128 program records, each with 16 tone slots, and a live
 * slot names a sample in the body. The records themselves are the PsyQ SDK's:
 * `VabHdr` (32 bytes), `ProgAtr` (16 bytes) and `VagAtr` (32 bytes) from the
 * staged PsyQ 3.7 `libsnd.h`. This header owns the bank's layout around them and
 * the name mapping the specs use (@source: wiki:formats/audio#vab-bank). The main executable's
 * SsVabOpenHeadWithMode (0x80173CB0) reads the bank, and the seven cue readers
 * index its tone table. */

#include "types.h"

/* The tone slot's fields, with the names the C record and the specs use
 * (@source: wiki:formats/audio#vagatr). The C record is the SDK's
 * `VagAtr`, whose members carry the PsyQ spelling.
 *
 * | Offset | C (`VagAtr`) | Spec |
 * | --- | --- | --- |
 * | 0x00 | prior | priority |
 * | 0x01 | mode | mode |
 * | 0x02 | vol | vol |
 * | 0x03 | pan | pan |
 * | 0x04 | center | center note |
 * | 0x05 | shift | pitch tune |
 * | 0x06 | min | min note |
 * | 0x07 | max | max note |
 * | 0x08 | vibW | vibrato width |
 * | 0x09 | vibT | vibrato time |
 * | 0x0A | porW | portamento width |
 * | 0x0B | porT | portamento time |
 * | 0x0C | pbmin | bend range down |
 * | 0x0D | pbmax | bend range up |
 * | 0x10 | adsr1 | ADSR1 |
 * | 0x12 | adsr2 | ADSR2 |
 * | 0x14 | prog | parent program |
 * | 0x16 | vag | VAG index |
 */

/* Bank geometry: a header (VH) followed by the program table, the tone table
 * and the VAG size table. The tone table sits at 0x820 because the program
 * table holds 128 fixed 16-byte records. */
#define VAB_PROGRAM_SIZE      0x10
#define VAB_TONES_PER_PROGRAM 16
#define VAB_HEADER_SIZE       0x20
#define VAB_TONE_SIZE         0x20
#define VAB_PROGRAM_TABLE     0x20
#define VAB_PROGRAM_MAX       128
#define VAB_SIZE_TABLE_MAX    256
#define VAB_TONE_TABLE        0x820

#endif
