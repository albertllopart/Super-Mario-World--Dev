#ifndef _j1PLAYER_H_
#define _j1PLAYER_H_

#include	"PugiXml/src/pugixml.hpp"
#include	"j1Module.h"
#include	"p2List.h"
#include	"p2Point.h"
#include	"j1Textures.h"
#include	"j1Animation.h"

#define		SPEED_X 0.15f
struct SDL_texture;
struct SDL_Rect;

enum PLAYER_STATE
{
	IDLE_R,
	IDLE_L,
	SHORT_HOP_L,
	SHORT_HOP_R,
	WALK_L,
	WALK_R,
	RUN_L,
	RUN_R

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


private:
	p2SString			name = nullptr;
	unsigned int		width = 0;
	unsigned int		height = 0;
	SDL_Texture*		graphic = nullptr;
	SDL_Rect*			test;
	fPoint				position;
	PLAYER_STATE		state;
	Direction			dir;
	bool				key_a = false;
	bool				key_d = false;

	//Animations
	Animation			idle_left;
	Animation			idle_right;
	Animation			walk_left;
	Animation			walk_right;
	Animation			short_hop_left;
	Animation			short_hop_right;
	Animation*			current_animation;
};

#endif