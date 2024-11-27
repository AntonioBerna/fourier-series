#include "wave.h"

float square_wave_k(const uint16_t term) {
    return 2 * term + 1;
}

float square_wave_radius(const uint16_t term) {
    float k = square_wave_k(term);
    return 75.0f * (4.0f / (k * PI));
}

float sawtooth_wave_k(const uint16_t term) {
    return (term % 2 == 0) ? (term + 1) : -(term + 1);
}

float sawtooth_wave_radius(const uint16_t term) {
    float k = sawtooth_wave_k(term);
    return 75.0f * (2.0f / (k * PI));
}

static const wave_properties_t WAVE_PROPERTIES[WAVE_COUNT] = {
    [WAVE_SQUARE] = {
        .name = "Square Wave",
        .radius_fn = square_wave_radius,
        .k_fn = square_wave_k
    },
    [WAVE_SAWTOOTH] = {
        .name = "Sawtooth Wave",
        .radius_fn = sawtooth_wave_radius,
        .k_fn = sawtooth_wave_k
    }
};

wave_t *wave_create(const wave_config_t *config) {
    wave_t *wave = malloc(sizeof(*wave));
    assert(wave != NULL);
    
    wave->data = calloc(config->length, sizeof(*wave->data));
    assert(wave->data != NULL);
    
    wave->length = config->length;
    wave->terms = 1;
    wave->type = WAVE_SQUARE;
    wave->time = 0.0f;
    wave->pos = (Vector2){ 0 };
    wave->config = config;
    
    return wave;
}

void wave_handle_input(wave_t *wave) {
    if (IsKeyPressed(KEY_UP)) {
        wave->terms = wave->terms > MAX_TERMS - 1 ? MAX_TERMS : wave->terms + 1;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        wave->terms = wave->terms < 2 ? 1 : wave->terms - 1;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        wave->type = (wave->type + 1) % WAVE_COUNT;
    }
    if (IsKeyPressed(KEY_LEFT)) {
        wave->type = (wave->type - 1 + WAVE_COUNT) % WAVE_COUNT;
    }
}

void wave_draw_epicycles(wave_t *wave) {
    const wave_properties_t *props = &WAVE_PROPERTIES[wave->type];
    wave->pos = (Vector2){ 0 };
    
    for (uint16_t i = 0; i < wave->terms; ++i) {
        Vector2 prev_pos = wave->pos;
        float k = props->k_fn(i);
        float radius = props->radius_fn(i);
        
        wave->pos.x += radius * cosf(fabsf(k) * wave->time);
        wave->pos.y += radius * sinf(fabsf(k) * wave->time);
        
        // ? Draw circle and radius
        DrawCircleLines(
            prev_pos.x + wave->config->offset,
            GetScreenHeight() / 2 - prev_pos.y,
            radius,
            WHITE
        );
        DrawLine(
            prev_pos.x + wave->config->offset,
            GetScreenHeight() / 2 - prev_pos.y,
            wave->pos.x + wave->config->offset,
            GetScreenHeight() / 2 - wave->pos.y,
            BLUE
        );
    }
}

void wave_draw_trace(wave_t *wave) {
    int32_t screen_center_y = GetScreenHeight() / 2;
    int32_t trace_start_x = GetScreenWidth() / 2 + wave->config->offset;
    
    // ? Connect last epicycle to trace
    DrawLine(
        wave->pos.x + wave->config->offset,
        screen_center_y - wave->pos.y,
        trace_start_x,
        screen_center_y - wave->pos.y,
        BLUE
    );
    
    // ? Update and draw trace
    wave->data[0] = wave->pos.y;
    for (size_t i = wave->length - 1; i > 0; --i) {
        wave->data[i] = wave->data[i - 1];
        
        int current_x = trace_start_x + (int32_t)i;
        if (current_x + 1 < GetScreenWidth()) {
            DrawLine(
                current_x,
                screen_center_y - wave->data[i],
                current_x + 1,
                screen_center_y - wave->data[i + 1],
                BLUE
            );
        }
    }
}

void wave_draw_ui(const wave_t *wave) {
    const char *wave_name = WAVE_PROPERTIES[wave->type].name;
    const int title_size = 40;
    const int info_size = 30;
    
    // ? Draw title
    DrawText(
        wave_name,
        (GetScreenWidth() - MeasureText(wave_name, title_size)) / 2,
        10,
        title_size,
        WHITE
    );
    
    // ? Draw terms counter
    DrawText(
        TextFormat("n = %d", wave->terms),
        10,
        GetScreenHeight() - info_size - 10,
        info_size,
        WHITE
    );
    
    // ? Draw reference lines
    DrawLine(wave->config->offset, 0, wave->config->offset, GetScreenHeight(), GRAY);
    DrawLine(wave->config->offset, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, GRAY);
}

void wave_update(wave_t *wave) {
    wave_draw_epicycles(wave);
    wave_draw_trace(wave);
    wave_draw_ui(wave);
    wave->time -= wave->config->time_step;
}

void wave_destroy(wave_t *wave) {
    if (wave->data != NULL) {
        free(wave->data);
    }
    if (wave != NULL) {
        free(wave);
    }
}