// Reference: https://en.wikipedia.org/wiki/Fourier_series#Convergence

#include "settings.h"
#include "wave.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);
    
    wave_t wave;
    wave_init(&wave, WAVE_LENGTH);

    while (!WindowShouldClose()) {
        wave_key_pressed_events(&wave);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText(wave.label, (SCREEN_WIDTH - MeasureText(wave.label, 40)) / 2, 10, 40, WHITE);
        DrawText(TextFormat("n = %d", wave.n), 10, SCREEN_HEIGHT - 30, 30, WHITE);

        DrawLine(OFFSET, 0, OFFSET, SCREEN_HEIGHT, GRAY);
        DrawLine(OFFSET, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, GRAY);
        
        wave_update(&wave);

        EndDrawing();
    }

    CloseWindow();
    
    wave_free(&wave);

    return 0;
}
