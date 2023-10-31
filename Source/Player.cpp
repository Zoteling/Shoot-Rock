#include "Classes.h"

void Player::initialize()
{
    bullets.clear();
    y_offset = (float)GetScreenHeight() - 100.0f;
    x_position = (float)GetScreenWidth() / 2.0f;
}

void Player::update(Sound shoot_sound)
{
    if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
        if (x_position > 0) x_position -= movespeed;
    }
    else if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
    {
        if (x_position < GetScreenWidth() - 40) x_position += movespeed;
    }

    if (IsKeyDown(KEY_Z))
    {
        charge_time += 1;
    }

    if (IsKeyReleased(KEY_Z))
    {
        PlaySoundMulti(shoot_sound);

        if (charge_time > 32)
        {
            Bullet new_bullet = Bullet(Vector2(x_position + 20, y_offset - 10), 15, 10);
            bullets.push_back(new_bullet);
        }
        charge_time = 0;
    }
}

void Player::render(float x_camera_shake, float y_camera_shake, Texture2D player_texture, Texture2D bullet_texture)
{
    Vector2 player_position = Vector2(0, 0);
    Rectangle player_source = Rectangle(0, 0, 24, 17);
    Rectangle player_dest = Rectangle(x_position + x_camera_shake, y_offset + y_camera_shake, (float)player_size, (float)player_size * .7f);
    DrawTexturePro(player_texture, player_source, player_dest, player_position, 0, WHITE);

    if (charge_time > 0)
    {
        float charge_radius = 64.0f - (float)charge_time;
        if (charge_radius <= 32) charge_radius = 32;

        float charge_shake = 5;
        float charge_offset_1 = (float)sin(charge_time * 2) * charge_shake;
        float charge_offset_2 = (float)sin(charge_time * 3) * charge_shake;

        Vector2 bullet_position = Vector2(4, 4);
        Rectangle bullet_source = Rectangle(0, 0, 8, 8);

        Rectangle bullet_1_dest = Rectangle(x_position + 40 - (charge_radius * .8f) + x_camera_shake + charge_offset_2, y_offset - charge_radius + y_camera_shake + charge_offset_1, charge_radius, charge_radius);
        Rectangle bullet_2_dest = Rectangle(x_position + (charge_radius * .8f) + x_camera_shake + charge_offset_1, y_offset - charge_radius + y_camera_shake + charge_offset_2, charge_radius, charge_radius);

        DrawTexturePro(bullet_texture, bullet_source, bullet_1_dest, bullet_position, 0, SKYBLUE);
        DrawTexturePro(bullet_texture, bullet_source, bullet_2_dest, bullet_position, 0, WHITE);
    }
}