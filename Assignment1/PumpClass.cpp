#include "PumpClass.h"
#include "PumpDataPoolStruct.h"
#include "TankDataPoolStruct.h"

// Pump standard constructor
Pump::Pump(char newName[25], char newPipeName[25]) {
	strcpy_s(pumpName, newName);
	strcpy_s(pipeName, newPipeName);
}

// Pump default constructor 
Pump::Pump() {

}

// Pump destructor
Pump::~Pump() {

}

// Pump main
int Pump::main(void) {
	// create pipe for communication between customer and pump
	CPipe myPipe(pipeName, 1024);

	// create datapool for status communication between pump and GSC
	CDataPool pumpPool("PumpPool1", sizeof(struct PumpDataPool));
	struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());
	// create datapool for tank level communication to GSC
	CDataPool tankPool("TankPool1", sizeof(struct TankDataPool));
	struct PumpDataPool *myTankDataPool = (struct PumpDataPool *)(tankPool.LinkDataPool());
	
	Sleep(1000);
	// test reading data sent from customer
	myPipe.Read(&pumpPipeData, sizeof(pumpPipeData));
	printf("%s read the following values from %s:\n", pumpName, pumpPipeData.pipeName);
	printf("cust name: %s\n", pumpPipeData.custName);
	printf("credit card: %d\n", pumpPipeData.creditcard);
	printf("pipe name: %s\n", pumpPipeData.pipeName);
	printf("fuel request: %f\n", pumpPipeData.fuelReq);

	// test sending status to  pump datapool
	myPumpDataPool->status = 1;

	return 0;
}