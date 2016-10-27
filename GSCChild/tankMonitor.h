#pragma once
#include "../../rt.h"
#include "../Assignment1/TankDataPoolStruct.h"
#include "../GSCChild/variables.h"


class tankMonitor {
private:
	CDataPool	*theDataPool;   
	CMutex	    *theMutex;
	TankDataPool *poolPtr;	

public:
	tankMonitor();
	~tankMonitor();
	double ReadCapacity(int grade);
	void SetCapacity(int grade, double capacity);
	void Reduce(int grade, double amount);
};

