#pragma once

#include "BaseProperties.h"

class BaseObject {
protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetObject() const { return p_object; }
	void LoadImg(string path, SDL_Renderer* screen); 
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
};