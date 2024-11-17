#include "settings.h"
#include "wave.h"

int32_t main(void) {
    const window_config_t window_config = WINDOW_CONFIG;
    const wave_config_t wave_config = WAVE_CONFIG;
    
    InitWindow(window_config.width, window_config.height, window_config.title);
    SetTargetFPS(60);
    
    wave_t *wave = wave_create(&wave_config);
    
    while (!WindowShouldClose()) {
        wave_handle_input(wave);
        
        BeginDrawing();
        ClearBackground(BLACK);
        wave_update(wave);
        EndDrawing();
    }
    
    wave_destroy(wave);
    CloseWindow();
    
    return 0;
}
