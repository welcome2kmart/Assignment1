#pragma once
#include "../../rt.h"
#include "CustomerPumpPipeStruct.h"

class Pump : public ActiveClass {
private:
	struct CPpipe pumpPipeData;
	char pumpName[25];
	char pipeName[25];
	int main(void);

public:
	// constructors
	Pump(char newName[], char newPipeName[]);
	Pump();

	// destructor
	~Pump();

};