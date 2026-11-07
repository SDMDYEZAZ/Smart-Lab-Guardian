#include "types.h"

static u8 CHECK_EDGE(u32 level, u32 time_out);
static void CHECK_IDLE(void);
u8 IR_READ(u32 *address, u32 *command, u32 *toggle);