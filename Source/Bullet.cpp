#include "Classes.h"

Bullet::Bullet(Vector2 position, float speed, float radius)
{
	this->position = position;
	this->speed = speed;
	this->radius = radius;
}

void Bullet::update() 
{
	position.y -= speed; 
}

void Bullet::render(float x_camera_shake, float y_camera_shake, Texture2D bullet_texture)
{
	Vector2 bullet_position = Vector2(4, 4);
	Rectangle bullet_source = Rectangle(0, 0, 8, 8);

	Rectangle bullet_1_dest = Rectangle(position.x + x_camera_shake, position.y + 10 + y_camera_shake, 32, 32);
	Rectangle bullet_2_dest = Rectangle(position.x + x_camera_shake, position.y + y_camera_shake, 32, 32);

	DrawTexturePro(bullet_texture, bullet_source, bullet_1_dest, bullet_position, 0, SKYBLUE);
	DrawTexturePro(bullet_texture, bullet_source, bullet_2_dest, bullet_position, 0, WHITE);
}