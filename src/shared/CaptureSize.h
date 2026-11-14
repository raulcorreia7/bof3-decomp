#ifndef SHARED_CAPTURE_SIZE_H
#define SHARED_CAPTURE_SIZE_H

/* The screen-capture size for one row of an overlay's capture table. */
typedef struct CaptureSize {
    s16 w;
    s16 h;
    s16 unk_04[2];
} CaptureSize;

ASSERT_SIZE(CaptureSize, 8);

#endif
