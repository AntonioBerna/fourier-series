#pragma once

#include "settings.h"

float square_wave_k(const uint16_t term);
float square_wave_radius(const uint16_t term);
float sawtooth_wave_k(const uint16_t term);
float sawtooth_wave_radius(const uint16_t term);

wave_t *wave_create(const wave_config_t *config);
void wave_handle_input(wave_t *wave);
void wave_draw_epicycles(wave_t *wave);
void wave_draw_trace(wave_t *wave);
void wave_draw_ui(const wave_t *wave);
void wave_update(wave_t *wave);
void wave_destroy(wave_t *wave);
