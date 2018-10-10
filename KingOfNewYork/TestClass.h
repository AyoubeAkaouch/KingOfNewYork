#pragma once
#include<iostream>
#include<string>
using namespace std;


class TestClass
{
public:
	TestClass(string name);
	~TestClass();
	const TestClass* pointer=this;
	string name;
	friend ostream& operator<<(ostream& os, const TestClass& txt);
	bool operator ==(const TestClass& object2) const;

};

