#include "../Assignment1/CustomerClass.h"
#include "../Assignment1/PumpDataPoolStruct.h"
#include "../Assignment1/PumpClass.h"

UINT __stdcall pumpIO(void *args) {
	// implement io for pumps here - consumer for producer that is the pumps

	return 0;
}


int main(void){
	// create rendevous to wait for all processes
	CRendezvous r1("MyRendezvous", 3);
	r1.Wait();
	printf("Pumps passed rendezvous\n");

	// create pump active objects
	Pump pump1("Pump1", "pipe1");
	Pump pump2("Pump2", "pipe2");
	Pump pump3("Pump3", "pipe3");
	Pump pump4("Pump4", "pipe4");

	pump1.Resume();
	pump2.Resume();
	pump3.Resume();
	pump4.Resume();


	pump1.WaitForThread();
	pump2.WaitForThread();
	pump3.WaitForThread();
	pump4.WaitForThread();

	system("Pause");
	return 0;
}