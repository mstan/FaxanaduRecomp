#pragma once
#include <stdbool.h>
#include <stdint.h>
void fax_world_reset(void);
void fax_world_loaded(void);
void fax_world_step(void);
bool fax_world_option(const char *name,const char *value);
void fax_world_event(const void *event);
const uint32_t *fax_world_present(int *w,int *h,const uint32_t *native);
void fax_world_tcp_setup(void);
