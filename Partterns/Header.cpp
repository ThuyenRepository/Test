#include "stdafx.h"
#include "Header.h"
int variable = 0;
TestExtern::TestExtern()
{
}

TestExtern::~TestExtern()
{
}

void TestExtern::update(int i)
{
	variable = i;
}
void updateExtern(TestExtern & x, int val)
{
	x.update(val);
}