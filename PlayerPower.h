# pragma once
// hien thi so mang choi 3 lan
#include "BaseProperties.h"
#include "BaseObject.h"

class PlayerPower : public BaseObject {
	int number;
	vector<int> pos_list; // danh sach cac toa do de in cai trai tim
public:
	PlayerPower();
	~PlayerPower();

	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);
	void SetNum ( int _x ) {
	    number = _x;
	    }
	int GetNum() { return number; }
	void Decrease();
};
