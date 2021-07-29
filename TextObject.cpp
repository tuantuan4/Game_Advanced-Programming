//hien thi thoi gian
#include "TextObject.h"

TextObject::TextObject() {
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
	width = 0;
	height = 0;
	str_val = "";
}

TextObject::~TextObject() {

}

void TextObject::LoadFromRenderText( TTF_Font* font, SDL_Renderer* screen ) {
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	texture = SDL_CreateTextureFromSurface(screen, text_surface);
	width = text_surface->w;
	height = text_surface->h;
	SDL_FreeSurface(text_surface);
}

void TextObject::Free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void TextObject::SetColor (Uint8 red, Uint8 green, Uint8 blue) {
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::SetColor(int type) {
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
	else if (type == BlACK_TEXT)
	{
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
}

void TextObject::RenderText( SDL_Renderer* screen,
							int x_pos, int y_pos,
							SDL_Rect* clip,
							double angle,
							SDL_Point* center,
							SDL_RendererFlip flip )
{
	SDL_Rect render_quad = { x_pos, y_pos, width, height };
	if ( clip != NULL ) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture, clip, &render_quad, angle, center, flip);
}
