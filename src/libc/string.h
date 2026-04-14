#ifndef STRING_H
#define STRING_H

#include <stdint.h>

int  strcmp(const char *a, const char *b);
int  strncmp(const char *a, const char *b, uint32_t n);
void int_to_str(int value, char *buf);
void *memset(void *dst, int c, uint32_t n);
void *memcpy(void *dst, const void *src, uint32_t n);

#endif
