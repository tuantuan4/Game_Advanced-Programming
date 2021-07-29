#pragma once

#include "BaseProperties.h"
#include "BaseObject.h"

#define WIDTH_THREAT 50 //chieu rong cua vat can
#define HEIGHT_THREAT 100 // chieu dai cua vat can

class ThreatObject : public BaseObject {
	int x_val;
	int y_val;
public:
	ThreatObject();
	~ThreatObject();
	void HandleMove();
};
