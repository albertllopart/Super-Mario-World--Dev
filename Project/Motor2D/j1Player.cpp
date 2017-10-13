#include "p2Defs.h"
#include "p2Log.h"
#include "j1Player.h"
#include "p2List.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Map.h"
#include "j1Audio.h"

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
	position.x = 150;
	position.y = 197;
	velocity.x = 2;
	velocity.y = 3;

	return ret;
}

bool j1Player::Start()
{
	LOG("starting player");
	bool ret = true;
	graphic = App->tex->Load("maps/Mario.png");
	state = IDLE_R;
	substate = GROUNDED;
	dir = RIGHT;
	App->audio->LoadFx("/audio/jump.wav");

	return ret;
}

bool j1Player::Update()
{
	
	return true;
}

bool j1Player::PostUpdate()
{
	Input();
	if (Falling())
	{
		position.y += 1.0f;
	}
	else substate = GROUNDED;
	if (state == SHORT_HOP_R)
	{
		Jumping();
	}
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
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && substate == GROUNDED)
	{
		dir = RIGHT;
		if (App->map->IsWalkable())
		{
			position.x += SPEED_X;
		}
		state = WALK_R;
		
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP && substate == GROUNDED)
	{
		dir = RIGHT;
		if (App->map->IsWalkable())
		{
			position.x += SPEED_X;
		}
		state = IDLE_R;
	}


	//Left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && substate == GROUNDED)
	{
		dir = LEFT;
		if (App->map->IsWalkable())
		{
			position.x -= SPEED_X;
		}
		state = WALK_L;	
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP && substate == GROUNDED)
	{
		dir = LEFT;
		if (App->map->IsWalkable())
		{
			position.x -= SPEED_X;
		}
		state = IDLE_L;
	}

	//jump albert
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && substate == GROUNDED)
	{
		state = SHORT_HOP_R;
		substate = AIRBORN;
	}

	//Jump
	/*if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->audio->PlayFx(1);
		if (dir == LEFT)
		{
			state = SHORT_HOP_L;
			c_time = GetCurrentTime();
			App->audio->PlayFx(1);
			while (velocity.y >= 0)				
			{
				p_time = c_time;				
				c_time = GetCurrentTime();		
				float dt = c_time - p_time;		
				Jump(dt);		
			}
			state = IDLE_L;

		}
		if (dir == RIGHT)
		{
			state = SHORT_HOP_R;
			c_time = GetCurrentTime();
			
			while (velocity.y >= 0)
			{
				p_time = c_time;
				c_time = GetCurrentTime();
				float dt = c_time - p_time;
				Jump(dt);
			}
			state = IDLE_R;
		}
		
		velocity.y = 3;;
		
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		state = SHORT_HOP_L;
		c_time = GetCurrentTime();

		while (velocity.y >= 0)
		{
			p_time = c_time;
			c_time = GetCurrentTime();
			float dt = c_time - p_time;
			Jump(dt);
			Jump_l(dt);	
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		state = SHORT_HOP_R;
		c_time = GetCurrentTime();

		while (velocity.y >= 0)
		{
			p_time = c_time;
			c_time = GetCurrentTime();
			float dt = c_time - p_time;
			Jump(dt);
			Jump_r(dt);
		}
	}*/

}

void j1Player::Jump(float dt)
{
	position.y -= velocity.y*dt;	
	velocity.y += GRAVITY*dt;
}

void j1Player::Jump_l(float dt)
{
	position.x -= velocity.x*dt;
}

void j1Player::Jump_r(float dt)
{
	position.x += velocity.x*dt;
}

bool j1Player::Falling()
{
	bool ret = false;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;

	for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}

	//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
	uint* nextGid = &fakeLayer->data->gid[(int)position.x / 16 + (((int)position.y + MARIO_HIGHT) / 16) * fakeLayer->data->width];

	if (state != SHORT_HOP_L && state != SHORT_HOP_R && dir == RIGHT)
	{
		if (*nextGid != 19)
		{
			ret = true;
		}
		else
		{
			ret = false;
		}
	}
	else if (state != SHORT_HOP_L && state != SHORT_HOP_R && dir == LEFT)
	{
		nextGid++;
		if (*nextGid != 19)
		{
			ret = true;
		}
		else
		{
			ret = false;
		}
	}

	if (ret == true)
	{
		substate = AIRBORN;
	}
		
	return ret;
}

void j1Player::Jumping()
{
	if (jump_count > 30)
	{
		jump_count = 0;
		state = IDLE_R;
	}
	if (jump_count <= 30)
	{
		position.y -= SPEED_Y;
		jump_count++;
	}	
}