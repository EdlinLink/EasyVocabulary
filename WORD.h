#pragma once
#include <string>
#include <cstring>
using namespace std;

class WORD{
public:
	long No;
	string spell;
	string attribute;
	string chinese;
	float correct;
	float wrong;

	WORD(){
		spell = "";
		attribute = "";
		chinese = "";
		correct = 0;
		wrong = 0;
	}
};
