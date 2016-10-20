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

	// create datapool for status communication between pump and GSC
	CDataPool pumpPool("Datapool" + to_string(instance), sizeof(struct PumpDataPool));
	struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());
	// create semaphores to implement producer/consumer with GSC
	CSemaphore ps("ps" + to_string(instance), 0, 1);
	CSemaphore cs("cs" + to_string(instance), 1, 1);

	// create a monitor to communicate with tanks
	tankMonitor *pumpMonitor = new tankMonitor();

	// wait for tank status threads
	//CRendezvous rTankThread("TankThreadRendezvous", NUM_PUMPS + 1); 

	// send data to pump data pool
	for (int j = 0; j < 10; j++)
	{
		cs.Wait();
		myPumpDataPool->status = j;
		printf("Pump %d sent %d\n", instance, j);
		ps.Signal();
	}


	printf("Pump %d the value of the tanks...\n", instance);
	//rTankThread.Wait();
	for (int j = 0; j < 50; j++)
	{
		for (int k = 0; k < NUM_FUELGRADES; k++)
		{
			pumpMonitor->Reduce(k, 10);
			Sleep(50);
		}

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