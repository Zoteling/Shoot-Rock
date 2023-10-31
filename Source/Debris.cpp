#include "Classes.h"

Debris::Debris(Vector2 position, float speed, float size)
{
	this->position = position;
	this->speed = speed;
	this->size = size;
}

void Debris::update()
{
	position.y += speed;
}

void Debris::render(float x_camera_shake, float y_camera_shake, Texture2D jewel_texture)
{
	Vector2 debris_position = Vector2(size / 2, size / 2);
	Rectangle debris_source = Rectangle(0, 0, 6, 6);
	Rectangle debris_dest = Rectangle(position.x + x_camera_shake, position.y + y_camera_shake, size, size);
	DrawTexturePro(jewel_texture, debris_source, debris_dest, debris_position, 0, WHITE);
}