#include <iostream>
#include "searchFile.h"
using namespace std;

int main()
{	
	string fileName;
	cout << "Enter file name with file format (fileToFind.txt): ";
	cin >> fileName;
	findFile(fileName);

	getchar();
	system("Pause");
	return 0;
}

