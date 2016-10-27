#include <stdio.h>
#include "../../rt.h"
#include "CustomerClass.h"
#include "PumpClass.h"
#include "PumpDataPoolStruct.h"
#include "../GSCChild/variables.h"


int main() {
	// create rendevous to wait for all processes
	CRendezvous r1("MyRendezvous", NUM_PROCESSES);
	
	// create process for GSC
	CProcess gsc("Z:\\RTExamples\\Assignment1\\Debug\\GSCChild.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);
	CProcess pumpProcess("Z:\\RTExamples\\Assignment1\\Debug\\PumpProcess.exe",
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,
		ACTIVE);

	// signal main processes rendezvous that the processs is initialized
	r1.Wait();
	printf("Parent passed main process rendezvous\n");

	// create customer active objects
	Customer cust1("Joe", 1234, "pipe1", 70);
	Customer cust2("Mary", 4321, "pipe2", 70);
	Customer cust3("Jane", 1234, "pipe3", 70);
	Customer cust4("Patrick", 1234, "pipe4", 70);
	cust1.Resume();
	cust2.Resume();
	cust3.Resume();
	cust4.Resume();

	// wait for customers to terminate
	cust1.WaitForThread();
	cust2.WaitForThread();
	cust3.WaitForThread();
	cust4.WaitForThread();

	// wait for processes to terminate
	gsc.WaitForProcess();
	pumpProcess.WaitForProcess();

	system("Pause");
	return 0;
}