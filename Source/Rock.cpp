#include "Classes.h"

Rock::Rock(Vector2 position, Vector2 direction, float speed, float size)
{
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	this->size = size;
}

void Rock::update()
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;
	rotation += 5;
}

void Rock::render(float x_camera_shake, float y_camera_shake, Texture2D rock_texture)
{
	Vector2 rock_position = Vector2(size/2, size/2);
	Rectangle rock_source = Rectangle(0, 0, 12, 12);
	Rectangle rock_dest = Rectangle(position.x + x_camera_shake, position.y + y_camera_shake, size, size);
	DrawTexturePro(rock_texture, rock_source, rock_dest, rock_position, rotation, WHITE);
}

