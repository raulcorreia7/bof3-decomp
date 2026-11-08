/* Host driver for the C equivalents of LZ77_DecodeBegin, LZ77_DecodeStep and func_801642F4.
 *
 *   lz77_host decode PAYLOAD OUT   decode a type-1 payload the way the sector loader feeds it and
 *                                  print the resume states the window ends left behind
 *   lz77_host copy                 check the copy kernel against memcpy and a forward byte copy
 *
 * The decoder reads a HOST_WINDOW-byte window; the loader refills it one window at a time and
 * calls LZ77_DecodeStep again, as EMI_CopySectorToScratchpad does with its two 0x400-byte halves.
 */
#include "engine/slus/slus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u8               g_host_scratchpad[HOST_WINDOW];
EMIDecodeContext D_800327A0[1];

static int decode(const char* in_path, const char* out_path) {
    FILE*  in = fopen(in_path, "rb");
    long   size;
    u8*    payload;
    u8*    out;
    u32    declared;
    size_t pos = 0;
    s32    status = 0;
    int    seen[5] = {0, 0, 0, 0, 0};
    int    k;
    FILE*  out_file;

    if (!in) {
        return 2;
    }
    fseek(in, 0, SEEK_END);
    size = ftell(in);
    fseek(in, 0, SEEK_SET);
    payload = malloc((size_t)size);
    if (fread(payload, 1, (size_t)size, in) != (size_t)size || size < LZ77_HEADER_SIZE) {
        return 2;
    }
    fclose(in);
    declared = payload[0] | payload[1] << 8 | payload[2] << 16 | (u32)payload[3] << 24;
    out      = calloc(declared + 0x1000, 1);

    LZ77_DecodeBegin(out);
    while (pos < (size_t)size) {
        size_t n = (size_t)size - pos < HOST_WINDOW ? (size_t)size - pos : HOST_WINDOW;

        memset(g_host_scratchpad, 0, HOST_WINDOW);
        memcpy(g_host_scratchpad, payload + pos, n);
        pos += n;
        status = LZ77_DecodeStep();
        seen[D_800327A0[0].state / 4] = 1;
        if (status == 15) {
            break;
        }
    }
    if (status != 15) {
        fprintf(stderr, "the stream ended without the 0xFF marker\n");
        return 1;
    }
    for (k = 0; k < 5; k++) {
        if (seen[k]) {
            printf("%d ", k * 4);
        }
    }
    printf("\n");
    out_file = fopen(out_path, "wb");
    fwrite(out, 1, declared, out_file);
    fclose(out_file);
    return 0;
}

static int copy(void) {
    u8     src[512];
    u8     want[1024];
    u8     got[1024];
    u32    count;
    u32    gap;
    size_t i;

    for (i = 0; i < sizeof(src); i++) {
        src[i] = (u8)(i * 7 + 1);
    }
    for (count = 0; count < 200; count++) {
        memset(got, 0xEE, sizeof(got));
        memset(want, 0xEE, sizeof(want));
        memcpy(want, src, count);
        if (func_801642F4(got, src, count) != got + count || memcmp(got, want, sizeof(got)) != 0) {
            fprintf(stderr, "copy of %u bytes differs from memcpy\n", count);
            return 1;
        }
    }
    /* A source behind the destination repeats its pattern, which memcpy does not promise. */
    for (gap = 1; gap < 40; gap++) {
        for (count = 0; count < 120; count++) {
            for (i = 0; i < gap; i++) {
                got[i] = want[i] = (u8)(i + 1);
            }
            for (i = 0; i < count; i++) {
                want[gap + i] = want[i];
            }
            if (func_801642F4(got + gap, got, count) != got + gap + count ||
                memcmp(got, want, gap + count) != 0) {
                fprintf(stderr, "overlapping copy gap %u count %u differs\n", gap, count);
                return 1;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc == 4 && strcmp(argv[1], "decode") == 0) {
        return decode(argv[2], argv[3]);
    }
    if (argc == 2 && strcmp(argv[1], "copy") == 0) {
        return copy();
    }
    fprintf(stderr, "usage: lz77_host decode PAYLOAD OUT | copy\n");
    return 2;
}
