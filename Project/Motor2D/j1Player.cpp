#include "p2Defs.h"
#include "p2Log.h"
#include "j1Player.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"


#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

j1Player::j1Player() : j1Module()
{
	name.create("player");

	//Animations

	idle_right.PushBack({ 0, 2, 15, 28 });
	idle_left.PushBack({ 140, 2, 15, 28 });

	walk_right.PushBack({ 40, 2, 16, 28 });
	walk_right.PushBack({ 20, 3, 16, 27 });
	walk_right.PushBack({ 0, 2, 15, 28 });

	walk_left.PushBack({ 99, 2, 16, 28 });
	walk_left.PushBack({ 119, 3, 16, 27 });
	walk_left.PushBack({ 140, 2, 15, 28 });

	short_hop_right.PushBack({ 60, 0, 16, 31 });
	short_hop_left.PushBack({ 79, 0, 16, 31 });
}

j1Player::~j1Player()
{
}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");
	bool ret = true;
	position.x = 32;
	position.y = 215;
	//position.create(32, 215);

	return ret;
}

bool j1Player::Start()
{
	LOG("starting player");
	bool ret = true;
	graphic = App->tex->Load("maps/Mario.png");
	
	return ret;
}

bool j1Player::Update()
{
	
	return true;
}

bool j1Player::PostUpdate()
{
	Draw();
	return true;
}

bool j1Player::CleanUp()
{
	LOG("Destroying player");
	bool ret = true;
	return ret;
}

bool j1Player::Load(pugi::xml_node& node)
{
	bool ret = true;
	pugi::xml_node player = node.append_child("position");
	player.append_attribute("x") = position.x;
	player.append_attribute("y") = position.y;

	return ret;
}

void j1Player::Draw()
{
	SDL_Rect r = walk_left.GetCurrentFrame();
	App->render->Blit(graphic, position.x, position.y, &r);
}
