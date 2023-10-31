#include "Classes.h"

Particle::Particle(Vector2 position, Vector2 direction, int speed, int size, Color color)
{
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	this->size = size;
	this->color = color;
}

void Particle::update()
{
	position.x += direction.x * speed;
	position.y += direction.y * speed;
}

void Particle::render(float x_camera_shake, float y_camera_shake) 
{ 
	DrawRectangle((int)(position.x + x_camera_shake), (int)(position.y + y_camera_shake), size, size, color);
}

void BackgroundParticles::initialize()
{
	for (int i = 0; i < particle_count; i++)
	{
		int size = 5;
		int speed = GetRandomValue(10, 20);
		Vector2 direction = Vector2(0, 1);
		Vector2 particle_position = Vector2((float)GetRandomValue(0, GetScreenWidth() - size), (float)GetRandomValue(0, GetScreenHeight() - size));
		particles.push_back(Particle(particle_position, direction, speed, size, DARKGRAY));
	}
}
void BackgroundParticles::update()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].update();

		if (particles[i].position.y > GetScreenHeight())
		{
			particles[i].position.x = (float)GetRandomValue(0, GetScreenWidth() - particles[i].size);
			particles[i].position.y = -(float)particles[i].size;
		}
	}
}

void BackgroundParticles::render()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].render(0, 0);
	}
}

void ExplosionParticleSystem::initialize(Vector2 explosion_source)
{
	for (int i = 0; i < particle_count; i++)
	{
		int size = 5;
		int speed = GetRandomValue(4, 20);
		
		Vector2 particle_position = Vector2(explosion_source.x + GetRandomValue(-20, 20), explosion_source.y + GetRandomValue(-20, 20));

		Vector2 direction = Vector2(particle_position.x - explosion_source.x, particle_position.y - explosion_source.y);
		float lenth = (float)sqrt(((double)direction.x * (double)direction.x) + ((double)direction.y * (double)direction.y));
		Vector2 normalized_direction = Vector2(direction.x / lenth, (direction.y / lenth) + 1.5f);

		Color color = RED;
		int random_color_value = GetRandomValue(0, 3);
		if (random_color_value == 0) color = YELLOW;
		else if (random_color_value == 1) color = DARKBLUE;
		else if (random_color_value == 2) color = MAGENTA;
		else if (random_color_value == 3) color = DARKPURPLE;

		particles.push_back(Particle(particle_position, normalized_direction, speed, size, color));
	}
}
void ExplosionParticleSystem::update()
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].update();
		if (particles[i].position.y > GetScreenHeight()) particles.erase(particles.begin() + i);
	}
}

void ExplosionParticleSystem::render(float x_camera_shake, float y_camera_shake)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].render(x_camera_shake, y_camera_shake);
	}
}