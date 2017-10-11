#pragma once
#include <stdio.h>
#include <vector>

#define EXPORT __declspec (dllexport) 

class DLL_I {
public:
	virtual ~DLL_I() {
		printf("Interface Destructor\n");
	};
	virtual int func1() = 0;
protected:
	std::vector<int> v;
private:
	virtual void func2() = 0;
};
extern "C" {
	EXPORT DLL_I* newObject();
};
typedef DLL_I* (*THE_INTERFACE) ();
