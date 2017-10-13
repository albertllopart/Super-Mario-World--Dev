#ifndef _j1PLAYER_H_
#define _j1PLAYER_H_

#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"j1Animation.h"

#define		SPEED_X 0.5f
#define		SPEED_Y 0.75f
#define		GRAVITY -2.0f
#define		MARIO_HIGHT 28
#define		MARIO_WIDTH 12

struct SDL_texture;
struct SDL_Rect;

enum PLAYER_STATE
{
	IDLE,
	JUMP,
	WALK,
	FALL
};

enum PLAYER_SUBSTATE
{
	GROUNDED,
	AIRBORN
};

enum Direction
{
	NM, //Not moving
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();
	bool Start();
	bool CleanUp();
	bool Awake(pugi::xml_node& config);
	bool Update();
	bool PostUpdate();
	bool Load(pugi::xml_node&);
	void Input();
	void Draw();
	
	bool Falling();
	void Jumping();

	fPoint				position;
	Direction			dir;

private:
	p2SString			name = nullptr;
	unsigned int		width = 0;
	unsigned int		height = 0;
	SDL_Texture*		graphic = nullptr;
	SDL_Rect*			test;
	
	PLAYER_STATE		state;
	PLAYER_SUBSTATE		substate;
	fPoint				velocity;
	float				p_time = 0;
	float				c_time;
	float				gravity = 9.8;

	//Animations
	Animation			idle_left;
	Animation			idle_right;
	Animation			walk_left;
	Animation			walk_right;
	Animation			short_hop_left;
	Animation			short_hop_right;
	Animation			falling_left;
	Animation			falling_right;
	Animation			victory;
	Animation*			current_animation;

	//jump albert
	uint jump_count = 0;
};

#endif