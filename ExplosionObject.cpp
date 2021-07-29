#pragma once

#include "ExplosionObject.h"

ExplosionObject::ExplosionObject() {
	frame = 0;
}

ExplosionObject::~ExplosionObject() {
	//
}

void ExplosionObject::set_clip()
{ // xet toa do cua anh  tu 0 den 8
    // anh thu i
	for (int i = 0; i < NUM_FRAME_EXP; i++) {
		frame_clip[i].x = i * EXP_WIDTH;
		frame_clip[i].y = 0;
		frame_clip[i].w = EXP_WIDTH;
		frame_clip[i].h = EXP_HEIGHT;
	}
}

void ExplosionObject::Show(SDL_Renderer* screen)
{ // hien vu no
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect render_quad = { rect.x, rect.y, EXP_WIDTH, EXP_HEIGHT };
	if (current_clip != NULL) {
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}
	SDL_RenderCopy(screen, p_object, current_clip, &render_quad);
}
