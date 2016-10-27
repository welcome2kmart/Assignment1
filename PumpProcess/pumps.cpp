#include "../Assignment1/CustomerClass.h"
#include "../Assignment1/PumpDataPoolStruct.h"
#include "../Assignment1/PumpClass.h"
#include "../GSCChild/variables.h"

UINT __stdcall pumpIO(void *args) {
	// implement io for pumps here - consumer for producer that is the pumps customer data

	return 0;
}


int main(void){
	// create rendevous to wait for all processes
	CRendezvous r1("MyRendezvous", NUM_PROCESSES);
	
	// create pump active objects
	Pump *pumps[NUM_PUMPS];
	for (int i = 0; i < NUM_PUMPS; i++)
	{
		pumps[i] = new Pump(i);
		pumps[i]->Resume();
	}

	// signal main processes rendezvous that the processs is initialized
	r1.Wait();
	printf("Pumps passed main process rendezvous\n");

	// wait for pumps to complete
	for (int i = 0; i < NUM_PUMPS; i++)
	{

		printf("Waiting for %d\n", i);
		pumps[i]->WaitForThread();
	}

	system("Pause");
	return 0;
}