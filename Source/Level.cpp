#include "Classes.h"

void spawn_rock(std::vector<Rock>* rocks_vector)
{
    float size = 64.0f;
    float speed = (float)GetRandomValue(10, 16);

    Vector2 position;

    position.x = (float)GetRandomValue(50, GetScreenWidth() - 50);
    position.y = -size;

    Vector2 direction = {};
    int at_angle = GetRandomValue(0, 1);

    if (at_angle == 0) direction = Vector2(0.0f, 1.0f);
    else if (at_angle == 1)
    {
        float random_x = (float)GetRandomValue(-20, 20);
        random_x = random_x / 100;

        direction = Vector2(random_x, 1.0f);
    }

    Rock rock = Rock(position, direction, speed, size);
    rocks_vector->push_back(rock);
}

void bullet_rock_collisions(Level* level, Sound explosion_sound)
{
    for (int b = 0; b < level->player.bullets.size(); b++)
    {
        for (int r = 0; r < level->rocks.size(); r++)
        {
            if (CheckCollisionCircles(level->player.bullets.at(b).position, level->player.bullets.at(b).radius,
                level->rocks.at(r).position, level->rocks.at(r).size))
            {
                ExplosionParticleSystem new_explosion;
                new_explosion.initialize(level->rocks.at(r).position);
                level->explosions.push_back(new_explosion);
                PlaySoundMulti(explosion_sound);

                level->camera_shake_sin_multiplier = 1;

                int amount_of_debris = GetRandomValue(5, 10);
                for (int i = 0; i < amount_of_debris; i++)
                {
                    Vector2 offset = Vector2((float)GetRandomValue(-(int)level->rocks.at(r).size - 20, (int)level->rocks.at(r).size + 20),
                                             (float)GetRandomValue(-(int)level->rocks.at(r).size - 20, (int)level->rocks.at(r).size + 20));
                    Vector2 debris_position = Vector2(level->rocks.at(r).position.x + offset.x, level->rocks.at(r).position.y + offset.y);
                    float speed = (float)GetRandomValue(8, 10);
                    float size = 24;

                    Debris new_debris = Debris(debris_position, speed, size);
                    level->debris.push_back(new_debris);
                }

                level->rocks.erase(level->rocks.begin() + r);
                return;
            }
        }
    }
}

void player_debris_collisions(Level* level, Sound pick_up_sound)
{
    for (int i = 0; i < level->debris.size(); i++)
    {
        if (CheckCollisionCircles(level->debris.at(i).position, level->debris.at(i).size,
            Vector2(level->player.x_position + (level->player.player_size / 2), level->player.y_offset + 20), 20))
        {
            PlaySoundMulti(pick_up_sound);
            level->debris.erase(level->debris.begin() + i);
            level->score += 50 + level->player.score_modifier;
            level->player.score_modifier += 10;
            level->player.score_cooldown_timer = level->player.score_cooldown_timer_max;
        }
    }

    level->player.score_cooldown_timer -= 1;
    if (level->player.score_cooldown_timer <= 0)
    { 
        level->player.score_cooldown_timer = 0;
        level->player.score_modifier = 0;
    }
}

void player_rock_collisions(Level* level, Sound death_sound)
{
    for (int i = 0; i < level->rocks.size(); i++)
        if (CheckCollisionCircles(level->rocks.at(i).position, level->rocks.at(i).size/2,
        Vector2(level->player.x_position + (level->player.player_size / 2), level->player.y_offset + 20), 20))
        { 
            PlaySoundMulti(death_sound);
            ExplosionParticleSystem new_explosion;
            new_explosion.initialize(Vector2(level->player.x_position, level->player.y_offset));
            level->explosions.clear();
            level->explosions.push_back(new_explosion);
            level->camera_shake_sin_multiplier = 1;
            level->game_state = GameState::start_screen;
        }
}

void handle_out_of_bounds_bullets(std::vector<Bullet>* bullets_vector)
{
    for (int i = 0; i < bullets_vector->size(); i++)
    {
        if (bullets_vector->at(i).position.y < -10) bullets_vector->erase(bullets_vector->begin() + i);
    }
}

void handle_out_of_bounds_rocks(std::vector<Rock>* rocks_vector)
{
    for (int i = 0; i < rocks_vector->size(); i++)
    {
        if (rocks_vector->at(i).position.y > (GetScreenHeight() + rocks_vector->at(i).size)) rocks_vector->erase(rocks_vector->begin() + i);
    }
}

void render_score(Level* level)
{
    if (level->score == 0)
    {
        int x_pos = (GetScreenWidth() - (MeasureText("00", 40))) / 2;
        DrawText("00", x_pos, 20, 40, SKYBLUE);
    }
    else
    {
        int x_pos = (GetScreenWidth() - (MeasureText(TextFormat("%i", level->score), 40))) / 2;
        DrawText(TextFormat("%i", level->score), x_pos, 20, 40, SKYBLUE);
    }
}

void render_score_text(Player* player)
{
    if (player->score_cooldown_timer > 0)
    {
        int x_pos = (int)player->x_position + (player->player_size / 2) - (MeasureText(TextFormat("+%i", 50 + player->score_modifier), 40) / 2);
        DrawText(TextFormat("+%i", 40 + player->score_modifier), x_pos, (int)player->y_offset - 60, 40, RAYWHITE);
    }
}

void Level::update(Sound sounds[3])
{
    time++;

    player.update(sounds[0]);
    for (int i = 0; i < rocks.size(); i++) rocks[i].update();
    for (int i = 0; i < debris.size(); i++) debris[i].update();
    for (int i = 0; i < explosions.size(); i++) explosions[i].update();
    for (int i = 0; i < player.bullets.size(); i++) player.bullets[i].update();

    rock_spawn_timer += 1;
    if (rock_spawn_timer >= rock_spawn_interval)
    {
        spawn_rock(&rocks);
        rock_spawn_timer = 0;
    }
    if (time % 100 == 0 && rock_spawn_interval > min_rock_spawn_interval) rock_spawn_interval -= 10;

    bullet_rock_collisions(this, sounds[1]);
    player_debris_collisions(this, sounds[3]);
    player_rock_collisions(this, sounds[2]);
    handle_out_of_bounds_rocks(&rocks);
    handle_out_of_bounds_bullets(&player.bullets);

    if (camera_shake_sin_multiplier > 0) camera_shake_sin_multiplier -= sin_multiplier_damping;
    else camera_shake_sin_multiplier = 0;
    camera_shake_offset = Vector2((float)sin(time / 2) * camera_shake_intensity * camera_shake_sin_multiplier, (float)sin(time / 3) * camera_shake_intensity * camera_shake_sin_multiplier);
}

void Level::render(Texture2D textures[4])
{
    player.render(camera_shake_offset.x, camera_shake_offset.y, textures[0], textures[1]);
    for (int i = 0; i < rocks.size(); i++) rocks[i].render(camera_shake_offset.x, camera_shake_offset.y, textures[2]);
    for (int i = 0; i < debris.size(); i++) debris[i].render(camera_shake_offset.x, camera_shake_offset.y, textures[3]);
    for (int i = 0; i < explosions.size(); i++) explosions[i].render(camera_shake_offset.x, camera_shake_offset.y);
    for (int i = 0; i < player.bullets.size(); i++) player.bullets[i].render(camera_shake_offset.x, camera_shake_offset.y, textures[1]);
    render_score_text(&player);
    render_score(this);   
}

void Level::reset()
{
    score = 0;
    time = 0;
    rock_spawn_interval = 120;
    player = {};
    player.initialize();
    rocks.clear();
    debris.clear();
    explosions.clear();
}