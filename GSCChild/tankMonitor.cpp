#include "tankMonitor.h"

// constructor and destructor
tankMonitor::tankMonitor() {
	// create mutex to protect datapool and the datapool w/ pointer
	theMutex = new CMutex("TankMutex");
	theDataPool = new CDataPool("TankDataPool", sizeof(struct TankDataPool));
	poolPtr = (struct TankDataPool *)(theDataPool->LinkDataPool());

	for (int i = 0; i < NUM_FUELGRADES; i++)
	{
		theMutex->Wait();
		poolPtr->capacity[i] = TANKSIZE;
		theMutex->Signal();
	}
}

tankMonitor::~tankMonitor() { 
	// delete pointers
	delete theDataPool;
	delete theMutex;
	delete poolPtr;
}

double tankMonitor::ReadCapacity(int grade) {
	double capacity;
	theMutex->Wait();
	capacity = poolPtr->capacity[grade];
	theMutex->Signal();
	return capacity;
}

void tankMonitor::SetCapacity(int grade, double newcapacity) {
	theMutex->Wait();
	poolPtr->capacity[grade] = newcapacity;
	theMutex->Signal();
	return;
}

void tankMonitor::Reduce(int grade, double amount) {
	theMutex->Wait();
	poolPtr->capacity[grade] -= amount;
	theMutex->Signal();
	return;
}