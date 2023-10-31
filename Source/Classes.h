#pragma once
#include "raylib.h"
#include <vector>

class Particle
{
	public:
		Particle(Vector2 position, Vector2 direction, int speed, int size, Color color);
		virtual ~Particle() = default;

		Vector2 position;
		Vector2 direction;
		Color color;
		int speed;
		int size;

		virtual void update();
		virtual void render(float x_camera_shake, float y_camera_shake);
};

class BackgroundParticles
{
	public:
		std::vector<Particle> particles;
		int particle_count = 50;

	virtual void initialize();
	virtual void update();
	virtual void render();
};

class ExplosionParticleSystem
{
	public:
		std::vector<Particle> particles;
		int particle_count = 20;

		virtual void initialize(Vector2 explosion_source);
		virtual void update();
		virtual void render(float x_camera_shake, float y_camera_shake);
};

class Debris
{
	public:
		Debris(Vector2 position, float speed, float size);
		virtual ~Debris() = default;

		Vector2 position;
		float speed;
		float size;

		virtual void update();
		virtual void render(float x_camera_shake, float y_camera_shake, Texture2D jewel_texture);
};

class Rock
{
	public:	
		Rock(Vector2 position, Vector2 direction, float speed, float size);
		virtual ~Rock() = default;

		Vector2 position;
		Vector2 direction;
		float speed;
		float size;
		float rotation = 0;

		virtual void update();
		virtual void render(float x_camera_shake, float y_camera_shake, Texture2D rock_texture);
};

class Bullet
{
	public:
		Bullet(Vector2 position, float speed, float radius);
		virtual ~Bullet() = default;
		Vector2 position;
		float speed;
		float radius;

		virtual void update();
		virtual void render(float x_camera_shake, float y_camera_shake, Texture2D bullet_texture);
};

class Player
{
	public:
		float y_offset = 0;
		float x_position = 0;
		float movespeed = 5.0f;

		int score = 0;
		int score_cooldown_timer = 0;
		int score_cooldown_timer_max = 120;
		int score_modifier = 0;
		int player_size = 64;

		int charge_time = 0;
		std::vector<Bullet> bullets;

		virtual ~Player() = default;

		virtual void initialize();
		virtual void update(Sound shoot_sound);
		virtual void render(float x_camera_shake, float y_camera_shake, Texture2D player_texture, Texture2D bullet_texture);
};

enum class GameState
{
	start_screen,
	in_game
};

class Level
{
	public:
		Player player = {};

		std::vector<Rock> rocks;
		std::vector<Debris> debris;
		std::vector<ExplosionParticleSystem> explosions;

		int score = 0;

		int rock_spawn_timer = 0;

		GameState game_state = GameState::start_screen;

		int time = 0;

		float camera_shake_sin_multiplier = 0;
		float sin_multiplier_damping = .05f;
		float camera_shake_intensity = 25;
		Vector2 camera_shake_offset = Vector2(0, 0);

		float rock_spawn_interval = 120;
		float min_rock_spawn_interval = 20;

		virtual ~Level() = default;

		void reset();
		void update(Sound sounds[3]);
		void render(Texture2D textures[4]);
};