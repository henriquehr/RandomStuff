#pragma once

#include "DLLInterface.h"
#include <stdio.h>
#include <vector>


class DLL :public DLL_I {
public:
	DLL::DLL();
	DLL::~DLL() override;
	int func1() override;
private:
	void func2() override;
	void func3();
	char* a = "variable a\n";
};
