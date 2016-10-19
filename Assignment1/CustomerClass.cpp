#include "CustomerClass.h"

// Customer standard constructor
Customer::Customer(char newName[256], int newCreditcard, char newPipeName[], double newFuelReq) {
	strcpy_s(custPipeData.custName, newName);
	custPipeData.creditcard = newCreditcard;
	strcpy_s(custPipeData.pipeName, newPipeName);
	custPipeData.fuelReq = newFuelReq;
}

// Customer default constructor 
Customer::Customer() {
	
}

// Customer destructor
Customer::~Customer() {
	
}

// Customer main
int Customer::main(void) {
	// create pipe for communication between customer and pump
	CPipe myPipe(custPipeData.pipeName, 1024);
	Sleep(500);
	// test sending information via struct to pump
	myPipe.Write(&custPipeData, sizeof(custPipeData));
	printf("%s wrote the following values to %s:\n", custPipeData.custName, custPipeData.pipeName);
	printf("cust name: %s\n", custPipeData.custName);
	printf("credit card: %d\n", custPipeData.creditcard);
	printf("pipe name: %s\n", custPipeData.pipeName);
	printf("fuel request: %f\n", custPipeData.fuelReq);

	return 0;
}