#include "p2Defs.h"
#include "p2Log.h"
#include "j1Player.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"

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
	position.y = 197;
	velocity.x = 0;
	velocity.y = 0;

	return ret;
}

bool j1Player::Start()
{
	LOG("starting player");
	bool ret = true;
	graphic = App->tex->Load("maps/Mario.png");
	state = IDLE_R;
	dir = RIGHT;

	return ret;
}

bool j1Player::Update()
{
	
	return true;
}

bool j1Player::PostUpdate()
{
	Input();
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
	switch (state)
	{
		case IDLE_R:
			current_animation = &idle_right;
			break;

		case IDLE_L:
			current_animation = &idle_left;
			break;
	
		case SHORT_HOP_L:
			current_animation = &short_hop_left;
			break;
	
		case SHORT_HOP_R:
			current_animation = &short_hop_right;
			break;
		
		case WALK_L:
			current_animation = &walk_left;
			break;
		
		case WALK_R:
			current_animation = &walk_right;
			break;
	

	}
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphic, position.x, position.y, &r);
}

void j1Player::Input()
{
	//Right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		dir = RIGHT;
		position.x += SPEED_X;
		state = WALK_R;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		dir = RIGHT;
		position.x += SPEED_X;
		state = IDLE_R;
	}


	//Left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		dir = LEFT;
		position.x -= SPEED_X;
		state = WALK_L;	
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		dir = LEFT;
		position.x -= SPEED_X;
		state = IDLE_L;	
	}

	//Jump
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (dir == LEFT)
		{
			state = SHORT_HOP_L;
			c_time = GetCurrentTime();
			
			while (velocity.y >= 0)				//en algun moment hauria de ser negativa no?
			{
				p_time = c_time;				//previous time = current time
				c_time = GetCurrentTime();		//current time = el temps actual
				float dt = c_time - p_time;		//la diferencia de temps es el actual- el previ
				Jump(dt);		
			}
			               
	
		}
		/*if (dir == RIGHT)
		{
			//position.y += velocity.y*dt;
			velocity.y -= GRAVITY;
			//position.y -= SPEED_Y;
			state = SHORT_HOP_R;
		}*/
		
	}
	

}

void j1Player::Jump(float dt)
{
	position.y -= velocity.y*dt;	
	velocity.y += gravity*dt;
}