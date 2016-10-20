#include "../../rt.h"
#include <stdio.h>
#include "../Assignment1/PumpDataPoolStruct.h"
#include "../Assignment1/TankDataPoolStruct.h"
#include "variables.h"

// create rendezvous
CRendezvous rPumpThread("PumpThreadRendezvous", NUM_PUMPS+1); // wait for pump status threads
CRendezvous rProcess("MyRendezvous", NUM_PROCESSES); // wait for all processes
int ThreadNum[8];

UINT __stdcall PumpStatusThread(void *args) {
	int instance = *((int *)(args)+1); // thread instance for corresponding pump active object
	string pumpName = "Pump" + to_string(instance);
	
	// create datapool for status communication between pump and GSC
	CDataPool pumpPool("Datapool"+to_string(instance), sizeof(struct PumpDataPool));
	struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());
	// create semaphores to implement producer/consumer with GS
	CSemaphore ps("ps" + to_string(instance), 0, 1);
	CSemaphore cs("cs" + to_string(instance), 1, 1);
	printf("Semaphores\n");
	// signal pump thread rendezvous that the thread is initialized
	rPumpThread.Wait();
	printf("Thread rendezvous\n");
	
	// read data from pump datapool
	for (int j = 0; j < 10; j++)
	{
		printf("Thread waiting for producer\n");
		ps.Wait();
		printf("Pump data pool reports status: %d\n", myPumpDataPool->status);
		cs.Signal();
	}

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

	system("Pause");
	return 0;
}