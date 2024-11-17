#pragma once

#include <raylib.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_TERMS 100

#define WINDOW_CONFIG \
{ \
    .width = 800, \
    .height = 450, \
    .title = "Fourier Series - Gibbs Phenomenon" \
}

#define WAVE_CONFIG \
{ \
    .length = 250, \
    .offset = 150, \
    .time_step = 0.05f \
}

typedef enum {
    WAVE_SQUARE,
    WAVE_SAWTOOTH,
    WAVE_COUNT
} wave_type_t;

typedef struct {
    const char *name;
    float (*radius_fn)(uint16_t term);
    float (*k_fn)(uint16_t term);
} wave_properties_t;

typedef struct {
    const int32_t width;
    const int32_t height;
    const char *title;
} window_config_t;

typedef struct {
    const size_t length;
    const float offset;
    const float time_step;
} wave_config_t;

typedef struct {
    float *data;
    size_t length;
    uint16_t terms; // ? Number of terms in approximation
    wave_type_t type;
    float time;
    Vector2 pos;
    const wave_config_t *config;
} wave_t;
