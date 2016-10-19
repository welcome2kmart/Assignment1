#include "../../rt.h"
#include <stdio.h>
#include "../Assignment1/PumpDataPoolStruct.h"
#include "../Assignment1/TankDataPoolStruct.h"

UINT __stdcall PumpStatusThread(void *args) {


	return 0;
}

int main(void) {
	// create rendevous to wait for all processes
	CRendezvous r1("MyRendezvous", 3);



	r1.Wait();
	printf("GCS passed rendezvous\n");

	//// create datapool for status communication between pump and GSC
	//CDataPool pumpPool("PumpPool1", sizeof(struct PumpDataPool));
	//struct PumpDataPool *myPumpDataPool = (struct PumpDataPool *)(pumpPool.LinkDataPool());

	//// create datapool for tank level communication to pump
	//CDataPool tankPool("TankPool1", sizeof(struct TankDataPool));
	//struct PumpDataPool *myTankDataPool = (struct PumpDataPool *)(tankPool.LinkDataPool());

	//Sleep(5000);
	//printf("Pump data pool reports status: %d\n", myPumpDataPool->status);


	system("Pause");
	return 0;
}