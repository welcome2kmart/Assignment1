#include "../../rt.h"
#include <stdio.h>
#include "../Assignment1/PumpDataPoolStruct.h"
#include "../Assignment1/TankDataPoolStruct.h"
#include "variables.h"
#include "tankMonitor.h"

// create rendezvous
CRendezvous rPumpThread("PumpThreadRendezvous", NUM_PUMPS + 1); // wait for pump status threads
CRendezvous rProcess("MyRendezvous", NUM_PROCESSES); // wait for all processes
// global instance variable for pump status thread
int ThreadNum[NUM_PUMPS];
// create a monitor to communicate with tanks
tankMonitor *pumpMonitor;

// threads to monitor the status of the pumps
UINT __stdcall PumpStatusThread(void *args) {
	int instance = *((int *)(args)+1); // thread instance for corresponding pump active object
	
	// create datapool for status communication between pump and GSC
	CDataPool pumpPool("Datapool"+to_string(instance), sizeof(struct PumpDataPool));
	struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());
	// create semaphores to implement producer/consumer with GS
	CSemaphore ps("ps" + to_string(instance), 0, 1);
	CSemaphore cs("cs" + to_string(instance), 1, 1);
	// signal pump thread rendezvous that the thread is initialized
	rPumpThread.Wait();
	printf("GSC Thread instance %d rendezvous passed\n", instance);
	
	// read data from pump datapool
	for (int j = 0; j < 10; j++)
	{
		ps.Wait();
		printf("GSC Thread instance %d receives %d\n", instance, myPumpDataPool->status);
		cs.Signal();
	}



	return 0;
}

// thread to check the status of the tank monitor
UINT __stdcall TankStatusThread(void *args) {
	printf("Read status of tanks\n");
	//rTankThread.Wait();
	for (int j = 0; j < 50; j++)
	{
		for (int k = 0; k < NUM_FUELGRADES; k++)
		{
			printf("Pump %d level: %.2f		", k, pumpMonitor->ReadCapacity(k));
		}
		printf("\n");
		Sleep(50);
	}

	printf("Tank status thread!!!\n");
	return 0;
}


int main(void) {
	// create threads to monitor the status of the Pumps
	CThread *pumpStatus[NUM_PUMPS];
	for (int i = 0; i < NUM_PUMPS; i++)
	{
		ThreadNum[i] = i;
		pumpStatus[i] = new CThread(PumpStatusThread, ACTIVE, &ThreadNum[i]);
	}

	// create thread to monitor the tank monitor
	pumpMonitor = new tankMonitor();
	CThread *tankStatus = new CThread(TankStatusThread, ACTIVE, NULL);

	// signal pump thread rendezvous that the thread is initialized
	rPumpThread.Wait();
	printf("GSC process passed pump thread rendezvous\n");
	// signal main processes rendezvous that the processs is initialized
	rProcess.Wait();
	printf("GSC passed main process rendezvous\n");




	// wait for threads to finish
	for (int i = 0; i < NUM_PUMPS; i++)
	{
		pumpStatus[i]->WaitForThread();
		delete pumpStatus[i];
	}
	tankStatus->WaitForThread();

	system("Pause");
	return 0;
}