
#include <windows.h>
#include <iostream>
#include "../DLLTest/DLLInterface.h"



int main(int args, char **argc) {
	HINSTANCE  dll = LoadLibrary("DLLTest.dll");
	if (dll) {
		THE_INTERFACE a = (THE_INTERFACE)GetProcAddress(dll, "newObject");
		DLL_I *b = a();
		if (!a) {
			printf("Function not found\n");
		}
		else {
			if (b) {
				int a = b->func1();
			}
		}
		delete b;
		FreeLibrary(dll);
	}
	else {
		printf("Problem loading the DLL\n");
	}
	system("pause");
}