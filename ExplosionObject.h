#pragma once // tranh viec goi lai nhieu thu vien trong 1 file

#include "BaseProperties.h"
#include "BaseObject.h"


#define NUM_FRAME_EXP 8 // laod lan luot 8 hinh anh no

const int EXP_WIDTH = 150; //chieu rong vu no
const int EXP_HEIGHT = 165; // chieu dai vu no

class ExplosionObject : public BaseObject {
	int frame;
	SDL_Rect frame_clip[NUM_FRAME_EXP]; // mang 1 chieu co 8 phan tu
public:
	ExplosionObject();
	~ExplosionObject();
	void set_clip();
	void set_frame(const int& _frame) { frame = _frame; }
	void Show(SDL_Renderer* screen);
};
