#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "raylib.h"

typedef struct {
    float *data;
    size_t length;
    uint16_t n; // number of terms for approximations
    uint8_t type;
    char *label;
    float time;

    Vector2 pos;
    float k; // number of multiples of pi
    float radius;
} wave_t;

void wave_init(wave_t *wave, size_t length);
void wave_key_pressed_events(wave_t *wave);
void wave_update(wave_t *wave);
void wave_free(wave_t *wave);
