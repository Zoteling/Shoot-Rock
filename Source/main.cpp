/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*b
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "Classes.h"

void update(Level* level, Sound sounds[4])
{
    level->update(sounds);
}

void render(Level* level, Texture2D textures[4])
{
    level->render(textures);
}

void process_game(Level* level, Texture2D textures[4], Sound sounds[4])
{
    update(level, sounds);
    render(level, textures);
}

void handle_start_screen_camera_shake(Level* level)
{
    if (level->camera_shake_sin_multiplier > 0)
    {
        level->time++;
        level->camera_shake_sin_multiplier -= level->sin_multiplier_damping;
        level->camera_shake_offset = Vector2((float)sin(level->time / 2) * level->camera_shake_intensity * level->camera_shake_sin_multiplier, (float)sin(level->time / 3) * level->camera_shake_intensity * level->camera_shake_sin_multiplier);
    }
    else level->camera_shake_sin_multiplier = 0;

    if (!level->explosions.empty())
    {
        level->explosions[0].update();
        level->explosions[0].render(level->camera_shake_offset.x, level->camera_shake_offset.y);
    }
}

void process_start_screen(Level* level, Sound start_game_sound)
{
    int x_pos = (GetScreenWidth() - (MeasureText("Shoot Rock", 60))) / 2;
    int y_pos = (GetScreenHeight() / 2) - 30;

    DrawText("Shoot Rock", x_pos, y_pos, 60, PINK);

    int start_x_pos = (GetScreenWidth() - (MeasureText("Press X To Start", 20))) / 2;
    int start_y_pos = (GetScreenHeight() / 2) + 30;
    DrawText("Press X To Start", start_x_pos, start_y_pos, 20, SKYBLUE);

    handle_start_screen_camera_shake(level);

    if (IsKeyPressed(KEY_X))
    {
        PlaySoundMulti(start_game_sound);
        level->reset();
        level->game_state = GameState::in_game;
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Level level{};
    level.reset();
    level.game_state = GameState::start_screen;

    BackgroundParticles background_particles;
    background_particles.initialize();

    Texture2D ship_texture = LoadTexture("Assets/Ship.png");
    Texture2D bullet_texture = LoadTexture("Assets/Bullet.png");
    Texture2D rock_texture = LoadTexture("Assets/Rock.png");
    Texture2D jewel_texture = LoadTexture("Assets/Jewel.png");

    Texture2D textures[4] = { ship_texture, bullet_texture, rock_texture, jewel_texture };

    Sound shoot_sound = LoadSound("Assets/Shooting.ogg");
    Sound explosion_sound = LoadSound("Assets/Explosion.ogg");
    Sound death_sound = LoadSound("Assets/Death.ogg");
    Sound start_game_sound = LoadSound("Assets/StartGame.ogg");
    Sound pick_up_sound = LoadSound("Assets/PickUp.ogg");

    Sound sounds[4] = { shoot_sound, explosion_sound, death_sound, pick_up_sound };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        //Background and particles
        ClearBackground(BLACK);

        background_particles.render();
        background_particles.update();

        switch (level.game_state)
        {
            case GameState::start_screen:
                process_start_screen(&level, start_game_sound);
                break;
            case GameState::in_game:
                process_game(&level, textures, sounds);
                break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadTexture(ship_texture);
    UnloadTexture(bullet_texture);
    UnloadTexture(rock_texture);
    UnloadTexture(jewel_texture);

    UnloadSound(shoot_sound);
    UnloadSound(explosion_sound);
    UnloadSound(death_sound);
    UnloadSound(start_game_sound);
    UnloadSound(pick_up_sound);
    
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}