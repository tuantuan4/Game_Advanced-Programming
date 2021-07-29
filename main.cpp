#include "BaseProperties.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"

BaseObject g_background;
BaseObject g_background1;
MainObject Car;
ThreatObject p_threat1;
ThreatObject p_threat2;
ThreatObject p_threat3;
ExplosionObject exp_Car;
TTF_Font* font_time;
TextObject time_game;
PlayerPower player_power;

void InitData()
{ // truyen du lieu
	SDL_Init( SDL_INIT_VIDEO );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	g_window = SDL_CreateWindow(" Games Racing Car", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

	TTF_Init();
	font_time = TTF_OpenFont("dlxfont_.ttf", 12); // font chu

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	g_sound_exp = Mix_LoadWAV("Explosion.wav"); //load am thanh vu no
	g_sound = Mix_LoadWAV("mission.wav"); // load nhac nen
}

void Load_Background() {
	g_background.LoadImg("Image//racingRoad_Light.png", g_screen); // load duong di
	g_background1.LoadImg("Image//racingRoad_Light.png", g_screen);
	g_background1.SetRect(0, -SCREEN_HEIGHT );
	// 2 anh nen chay noi tiep nhau
}

void Load_Objects() {
	// MainObject
	Car.LoadImg( "Image//Car_4.png", g_screen ); // load anh nhan vat chinh
	Car.SetRect( POS_X_START_MAIN_OBJECT, POS_Y_START_MAIN_OBJECT ); //

	// ThreastObject
	p_threat1.LoadImg("Image//Car_1.png", g_screen); // chuong ngai vat 1
	p_threat2.LoadImg("Image//Car_2.png", g_screen); // chuong ngai vat 2
	p_threat3.LoadImg("Image//Car_3.png", g_screen); // chuong ngai vat 3

	p_threat1.SetRect(LANE_1, 0);
	p_threat2.SetRect(LANE_2, p_threat1.GetRect().y - SCREEN_HEIGHT / 3);
	p_threat3.SetRect(LANE_3, p_threat2.GetRect().y - SCREEN_HEIGHT / 3);

	// ExplosionObject
	exp_Car.LoadImg("Image//exp.png", g_screen); // hieu ung vu no
	exp_Car.set_clip();

	//TextObject (time)
	time_game.SetColor(TextObject::RED_TEXT); // hien thi thoi gian bang chu mau do

	// PlayerObject
	player_power.Init( g_screen ); //hien thi trai tim
}

void close() {
	g_background.Free();
	Car.Free();
	p_threat1.Free();
	p_threat2.Free();
	p_threat3.Free();
	exp_Car.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int agrc, char* agrv[])
{
	InitData();
	Load_Background();
	Load_Objects();

	Mix_PlayChannel( -1, g_sound, 0 );
	bool stop = false;
	int delay_speed = 3;
	while ( !stop )
	{
		while ( SDL_PollEvent ( &g_event ) != 0 ) {
			if (g_event.type == SDL_QUIT) {
				stop = true;
				break;
			}
			Car.HandleInputAction(g_event);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); // set lại màu screen
		SDL_RenderClear(g_screen); // xóa màn hình

		// chạy background
		g_background.SetRect(0, g_background.GetRect().y + 1);
		g_background1.SetRect(0, g_background1.GetRect().y + 1);

		if ( g_background.GetRect().y > SCREEN_HEIGHT ) {
			g_background.SetRect(0, -SCREEN_HEIGHT);
		}
		if ( g_background1.GetRect().y > SCREEN_HEIGHT ) {
			g_background1.SetRect( 0, -SCREEN_HEIGHT );
		}

		// Show
		g_background.Render(g_screen);
		g_background1.Render(g_screen);

		Car.Render(g_screen);

		p_threat1.Render(g_screen); p_threat2.Render(g_screen); p_threat3.Render(g_screen);
		p_threat1.HandleMove();	/*while (p_threat1.GetRect().y == p_threat2.GetRect().y || p_threat1.GetRect().y == p_threat3.GetRect().y) p_threat1.HandleMove();*/
		p_threat2.HandleMove(); /*while (p_threat2.GetRect().y == p_threat1.GetRect().y || p_threat2.GetRect().y == p_threat3.GetRect().y) p_threat2.HandleMove();*/
		p_threat3.HandleMove(); /*while (p_threat3.GetRect().y == p_threat2.GetRect().y || p_threat3.GetRect().y == p_threat1.GetRect().y) p_threat3.HandleMove();*/

		player_power.Show(g_screen);

		// Handle Collision
		bool ret1 = Car.CheckCollision(p_threat1.GetRect());
		bool ret2 = Car.CheckCollision(p_threat2.GetRect());
		bool ret3 = Car.CheckCollision(p_threat3.GetRect());
		if (ret1 || ret2 || ret3) {
			// explosion + sound
			for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
				int x_pos = (Car.GetRect().x + Car.GetRect().w * 0.5 - 0.5 * EXP_WIDTH);
				int y_pos = (Car.GetRect().y + Car.GetRect().h * 0.5 - 0.5 * EXP_HEIGHT);

				if (ex == 0) Mix_PlayChannel(-1, g_sound_exp, 0);

				exp_Car.set_frame(ex);
				exp_Car.SetRect(x_pos, y_pos);
				exp_Car.Show(g_screen);
				SDL_Delay(100);
				SDL_RenderPresent(g_screen);
			}

			//
			player_power.SetNum(player_power.GetNum() - 1);
			if ( player_power.GetNum() >= 0 ) {
				Car.SetRect(POS_X_START_MAIN_OBJECT, POS_Y_START_MAIN_OBJECT);
				SDL_Delay( 1000 );
				player_power.Decrease();
				player_power.Show(g_screen);
			}
            //else if ( Message Box(NULL, L"Game Over", L"Info", MB_OK | MB_ICONSTOP) == IDOK) stop = true;
			else close();
		}

		// show game time
		Uint32 time_val = SDL_GetTicks() / 1000;
		string str_time = "Time: " + to_string(time_val);
		time_game.SetText(str_time);
		time_game.LoadFromRenderText(font_time, g_screen);
		time_game.RenderText(g_screen, SCREEN_WIDTH - 150, 15);

		// update màn hình
		SDL_RenderPresent(g_screen);
		SDL_Delay(delay_speed);

	}

	close();

	return 0;
}
