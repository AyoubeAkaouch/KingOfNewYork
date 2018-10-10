#include "TestClass.h"



TestClass::TestClass(string name)
{
	this->name = name;
	cout << this << endl;
}

TestClass::~TestClass()
{
}

bool TestClass::operator==(const TestClass & object2) const
{
	if (name == object2.name)
		return true;
	else
		return false;
}

ostream & operator<<(ostream & os, const TestClass & txt)
{
	os << txt.name;
	return os;
}
