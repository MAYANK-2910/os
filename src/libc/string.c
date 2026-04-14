#include "string.h"

int strcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return *(unsigned char *)a - *(unsigned char *)b;
}

int strncmp(const char *a, const char *b, uint32_t n) {
    while (n && *a && *a == *b) { a++; b++; n--; }
    if (!n) return 0;
    return *(unsigned char *)a - *(unsigned char *)b;
}

void int_to_str(int value, char *buf) {
    if (value < 0) { *buf++ = '-'; value = -value; }
    char tmp[12];
    int i = 0;
    if (value == 0) { tmp[i++] = '0'; }
    while (value > 0) { tmp[i++] = '0' + (value % 10); value /= 10; }
    while (i--) *buf++ = tmp[i];
    *buf = '\0';
}

void *memset(void *dst, int c, uint32_t n) {
    uint8_t *d = (uint8_t *)dst;
    while (n--) *d++ = (uint8_t)c;
    return dst;
}

void *memcpy(void *dst, const void *src, uint32_t n) {
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (n--) *d++ = *s++;
    return dst;
}
