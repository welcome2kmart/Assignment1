#pragma once
#include "../../rt.h"
#include "CustomerPumpPipeStruct.h"

class Customer : public ActiveClass {
private:
	struct CPpipe custPipeData;
	int main(void);
	

public:
	// constructors
	Customer(char newname[], int newcreditcard, char pipeName[], double newFuelReq);
	Customer();

	// destructor
	~Customer();

};