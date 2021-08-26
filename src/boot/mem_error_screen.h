#ifndef MEM_ERROR_SCREEN_H
#define MEM_ERROR_SCREEN_H
extern Bool8 gNotEnoughMemory;
void thread5_mem_error_message_loop(UNUSED void *arg);
Bool32 does_pool_end_lie_out_of_bounds(void *end);
#endif
