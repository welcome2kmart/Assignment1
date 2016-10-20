#pragma once
#include "../../rt.h"
#include "CustomerPumpPipeStruct.h"
#include "../GSCChild/variables.h"
#include "PumpDataPoolStruct.h"
#include "TankDataPoolStruct.h"

class Pump : public ActiveClass {
private:
	int instance;
	struct CPpipe pumpPipeData;
	string pumpName;
	string pipeName;
	string poolName;
	int main(void);

public:
	// constructors
	Pump(int instance);

	// destructor
	~Pump();

};