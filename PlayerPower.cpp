
#include "PlayerPower.h"

PlayerPower::PlayerPower() {
	number = 0;
}

PlayerPower::~PlayerPower() {

}

void PlayerPower::Init (SDL_Renderer* screen)
{
	LoadImg ( "Image//Heart.png", screen);
	number = 3;
	if (pos_list.size() > 0) pos_list.clear();
	pos_list.push_back(50); // them vao vi tri 50
	pos_list.push_back(80);// them vao vi tri 80
	pos_list.push_back(110);// them vao vi tri 110
}

void PlayerPower::Show( SDL_Renderer* screen ) {
	for (int i = 0; i < pos_list.size(); i++)
	{
		rect.x = pos_list[i];
		rect.y = 20;
		Render( screen );
	}
}

void PlayerPower::Decrease() {
	number--;
	pos_list.pop_back();
}
