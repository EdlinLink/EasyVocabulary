#include <iostream>
#include <stdio.h>
#include "WORD.h"
#include <fstream>
#include <algorithm>                                                                                                                   
#include <ctime>

#define SIZE 500
using namespace std;

void showMenu();
void addWord();
void takeTest();
void takeTest2();

WORD Dict[SIZE];

int main(){
	srand((unsigned)time(NULL));

	char command;

	bool exitFlag = false;
	while(!exitFlag){
		showMenu();	
		cin >> command;
		switch (command){
			case '1':
			case 'A':
				addWord();
				break;
			case '2':
			case 'R':
				takeTest();
				break;
			case '3':
			case 'S':
				takeTest2();
				break;
			case '4':
			case 'X':
				exitFlag = true;
				break;
			default:
				break;
		}
	}

	return 0;
}



void showMenu(){
	cout<<" ----------------------------------------"<<endl;
	cout<<"| 1.Add new words.                   [A] |"<<endl;
	cout<<"| 2.Take a test - Remember Mode.     [R] |"<<endl;
	cout<<"| 3.Take a test - Spell Mode.        [S] |"<<endl;
	cout<<"| 4.Exit.                            [X] |"<<endl;
	cout<<" ----------------------------------------"<<endl;
}



void addWord(){
	//Load the current size of vocabulary.
	long total = 0;
	ifstream fin;
	fin.open("COUNT.txt", ios::in);
	fin >> total;
	fin.close();



	int count = 0;
	ofstream fout;
	fout.open("VocabularyBase1.txt", ios::app);
	while(1){
		WORD newWord;
		cin >> newWord.spell >> newWord.attribute >> newWord.chinese;
		newWord.No = total+count;

		if(newWord.spell==":q" || newWord.attribute==":q" || newWord.chinese==":q")
			break;

		fout << newWord.No <<" "<< newWord.spell <<" "<< newWord.attribute <<" "<< newWord.chinese <<" 0 0"<<endl;
		cout << newWord.spell <<" "<< newWord.attribute <<" "<< newWord.chinese << endl;
		count++;
	}
	fout.close();



	fout.open("COUNT.txt", ios::out);
	fout << total+count;
	fout.close();
}



void takeTest(){
	long total = 0;
	ifstream fin;
	fin.open("COUNT.txt", ios::in);
	fin >> total;
	fin.close();

	int MIN = total; 
	if(MIN>SIZE)
		MIN = SIZE;

	fin.open("VocabularyBase1.txt", ios::in);
	for(int i=0; i<MIN; i++){
		fin >> Dict[i].No >> Dict[i].spell >>Dict[i].attribute >> Dict[i].chinese >> Dict[i].correct >> Dict[i].wrong;
	}

	bool remember[SIZE];
	memset(remember, 0, sizeof(remember));

	int r;
	string command;
	for(long sum=0; sum<MIN; ){
		r = rand()%MIN;
		cout << "---------------------------" << endl;
		cout << " "<<Dict[r].spell<<" "<<Dict[r].attribute<<"\t\t";
		
		cin >> command;
		if(command=="y" || command=="Y"){
			cout<<"  "<<Dict[r].chinese<<endl;
		}
		else{
			cout<<"  "<<Dict[r].chinese<<endl;
		}

		sum++;
	}
	fin.close();
}



void takeTest2(){
	long total = 0;
	ifstream fin("COUNT.txt", ios::in);
	fin >> total;
	fin.close();

	int MIN = total; 
	if(MIN>SIZE)
		MIN = SIZE;

	fin.open("VocabularyBase1.txt", ios::in);
	for(int i=0; i<MIN; i++){
		fin >> Dict[i].No >> Dict[i].spell >>Dict[i].attribute >> Dict[i].chinese >> Dict[i].correct >> Dict[i].wrong;
	}
	bool remember[SIZE];
	memset(remember, 0, sizeof(remember));



	int r;
	string mySpell;
	int sum = 0;
	bool exitFlag = false;
	while(sum<MIN && !exitFlag){
		do{
			r = rand()%MIN;
		}while(remember[r]==true);

		cout << "---------------------------" << endl;
		cout << " " << Dict[r].chinese << " " << Dict[r].attribute << endl;
		cout << "-> " ;
		cin >> mySpell;

		bool validCorrect = true;
		while(1){
			if(mySpell==":s"){
				cout <<" - [" << Dict[r].spell << "]"<<endl;	
				validCorrect = false;
			}
			else if(mySpell==":q"){
				ofstream fout;
				fout.open("VocabularyBase1.txt", ios::out);
				for(int i=0; i<MIN; i++){
					fout<< Dict[i].No <<" "<< Dict[i].spell <<" "<< Dict[i].attribute <<" "
						<< Dict[i].chinese <<" "<< Dict[i].correct <<" "<< Dict[i].wrong<<endl;
					
				}
				exitFlag = true;
				break;
			}
			else if(mySpell==Dict[r].spell){
				cout <<" O [CORRECT] "<<endl;
				if(validCorrect)
					Dict[r].correct+=1;
				if(Dict[r].correct>10 && Dict[r].correct/(Dict[r].wrong+1)>1){
					remember[r] = true;
					sum++;
					cout <<" * [Remember:"<<sum<<", Left:"<<MIN-sum<<"]"<<endl;
					cout << "---------------------------" << endl;
				}
				break;
			}
			else{
				cout <<" X [WRONG] "<<endl;
				Dict[r].wrong+=1;
			}
			cout << "-> " ;
			cin >> mySpell;
		}



	}
	fin.close();
}
