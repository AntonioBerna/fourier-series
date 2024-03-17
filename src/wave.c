#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "settings.h"
#include "wave.h"

void wave_init(wave_t *wave, size_t length) {
    wave->data = calloc(length, sizeof(*wave->data));
    assert(wave->data != NULL && "Buy More RAM lol");
    wave->length = length;
    wave->n = 1;
    wave->type = SQUARE_WAVE_TYPE;
    wave->label = SQUARE_WAVE_LABEL;
    wave->time = 0.0f;
}

void wave_key_pressed_events(wave_t *wave) {
    if (IsKeyPressed(KEY_UP)) {
        wave->n = wave->n > 99 ? 100 : wave->n + 1;
    } else if (IsKeyPressed(KEY_DOWN)) {
        wave->n = wave->n < 2 ? 1 : wave->n - 1;
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        wave->type = SAWTOOTH_WAVE_TYPE;
        wave->label = SAWTOOTH_WAVE_LABEL;
    } else if (IsKeyPressed(KEY_LEFT)) {
        wave->type = SQUARE_WAVE_TYPE;
        wave->label = SQUARE_WAVE_LABEL;
    }
}

void wave_update(wave_t *wave) {
    wave->pos.x = 0.0f;
    wave->pos.y = 0.0f;

    for (uint16_t i = 0; i < wave->n; ++i) {
        float prev_x = wave->pos.x;
        float prev_y = wave->pos.y;

        switch (wave->type) {
        case SQUARE_WAVE_TYPE:
            wave->k = 2 * i + 1;
            wave->radius = 75 * (4 / (wave->k * PI));
            break;
        
        case SAWTOOTH_WAVE_TYPE:
            wave->k = (i % 2 == 0) ? i + 1 : -(i + 1);
            wave->radius = 75 * (2 / (wave->k * PI));
            break;

        default:
            break;
        }

        wave->pos.x += wave->radius * cosf(fabsf(wave->k) * wave->time);
        wave->pos.y += wave->radius * sinf(fabsf(wave->k) * wave->time);

        // circle
        DrawCircleLines(prev_x + OFFSET, SCREEN_HEIGHT / 2 - prev_y, wave->radius, WHITE);
        
        // radius
        DrawLine(prev_x + OFFSET, SCREEN_HEIGHT / 2 - prev_y, wave->pos.x + OFFSET, SCREEN_HEIGHT / 2 - wave->pos.y, BLUE);
    }

    wave->data[0] = wave->pos.y;
    DrawLine(wave->pos.x + OFFSET, SCREEN_HEIGHT / 2 - wave->pos.y, SCREEN_WIDTH / 2 + OFFSET, SCREEN_HEIGHT / 2 - wave->data[0], BLUE);

    for (size_t i = 0; i < wave->length; ++i) {
        if (i < wave->length - 1) wave->data[wave->length - 1 - i] = wave->data[wave->length - 2 - i]; else wave->data[0] = wave->pos.y;
        if (SCREEN_WIDTH / 2 + i + 1 + OFFSET < SCREEN_WIDTH) DrawLine(SCREEN_WIDTH / 2 + i + OFFSET, SCREEN_HEIGHT / 2 - wave->data[i], SCREEN_WIDTH / 2 + i + 1 + OFFSET, SCREEN_HEIGHT / 2 - wave->data[i + 1], BLUE);
    }

    wave->time -= 0.05f;
}

void wave_free(wave_t *wave) {
    if (wave != NULL && wave->data != NULL) {
        free(wave->data);
        wave->data = NULL;
#ifdef DEBUG
        puts("\nI freed up all the memory. Bye.");
#endif
    }
}