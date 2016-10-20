#include "PumpClass.h"

// Pump standard constructor
Pump::Pump(int i) {
	instance = i;
	pumpName = "Pump" + to_string(instance);
	pipeName = "Pipe" + to_string(instance);
	poolName = "PumpPool" + to_string(instance);
}

// Pump destructor
Pump::~Pump() { }

// Pump main
int Pump::main(void) {
	// create pipe for communication between customer and pump
	CPipe myPipe(pipeName, 1024);
	printf("Pipe\n");

	// create datapool for status communication between pump and GSC
	CDataPool pumpPool("Datapool" + to_string(instance), sizeof(struct PumpDataPool));
	struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());
	// create semaphores to implement producer/consumer with GSC
	CSemaphore ps("ps" + to_string(instance), 0, 1);
	CSemaphore cs("cs" + to_string(instance), 1, 1);
	printf("Semaphores\n");


	// send data to pump data pool
	for (int j = 0; j < 10; j++)
	{
		cs.Wait();
		myPumpDataPool->status = j;
		printf("sent %d\n", j);
		ps.Signal();
	}


	//
	//Sleep(1000);
	//// test reading data sent from customer
	//myPipe.Read(&pumpPipeData, sizeof(pumpPipeData));
	//printf("%s read the following values from %s:\n", pumpName, pumpPipeData.pipeName);
	//printf("cust name: %s\n", pumpPipeData.custName);
	//printf("credit card: %d\n", pumpPipeData.creditcard);
	//printf("pipe name: %s\n", pumpPipeData.pipeName);
	//printf("fuel request: %f\n", pumpPipeData.fuelReq);



	return 0;
}