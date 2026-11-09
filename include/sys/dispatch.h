#ifndef SYS_DISPATCH_H
#define SYS_DISPATCH_H

#define SYS_DISPATCH_TASK(handlers, index, work) ((void (**)(void))(handlers))[((u8*)(work))[(index)]]()

/* Run the handler a byte value selects out of a callback table. The index keeps
 * its own type: a signed scenario mode byte loads with lb, an unsigned step
 * byte with lbu. */
#define SYS_DISPATCH_BYTE(handlers, byte)        ((Callback*)(handlers))[(byte)]()

#endif
