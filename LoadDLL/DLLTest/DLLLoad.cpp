#include "DLLLoad.h"
#include <limits>

EXPORT DLL_I* newObject() {
	return new DLL();
}

DLL::DLL() {
	printf("Contructor\n");
	v =  std::vector<int>(300000000);
}

DLL::~DLL() {
	printf("Destructor\n");
}

int DLL::func1() {
	printf("func1\n");
	func2();
	return 132;
}
void DLL::func2() {
	printf("func2\n"); func3();
}
void DLL::func3() {
	printf("func3\n");
	printf(a);
}

