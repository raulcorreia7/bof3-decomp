#ifndef MSG_MESSAGE_IDS_H
#define MSG_MESSAGE_IDS_H

/* Every named message id, MSG_<ARCHIVE>_<TAG>, from messages.def. */
#define DEFINE_MESSAGE(archive, id, tag) MSG_##archive##_##tag = id,

enum {
#include "msg/messages.def"
    MESSAGE_ID_LAST = 0xFFFF
};

#undef DEFINE_MESSAGE

#endif
