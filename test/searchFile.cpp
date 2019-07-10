#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <thread>
#include <windows.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include "searchFile.h"

using namespace std;
namespace fs = std::experimental::filesystem;


void findFile(const string& name)
{

	vector<char> disks = diskParser();
	std::string path;
	vector<thread> threads;
	try {
		for (int i = 0; i < disks.size(); i++)
		{
			path = "";
			path += disks[i];
			path += ":/";

			threads.push_back(thread(diskSearch, path, name));
		}
		for (int i = 0; i < threads.size(); i++)
		{
			if (threads[i].joinable()) { threads[i].join(); }
		}
		cout << "Done!" << endl;
	}
	catch (exception e) {
		cout << "Error: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unhandled exeption!" << endl;
	}
}

void diskSearch(const string& path, const string& name)
{
	std::fstream file;
	file.open("file.txt", fstream::out);
	if (fs::exists(path)) {
		for (const auto & entry : fs::recursive_directory_iterator(path))
		{
			if (entry.path().filename() == name)
			{
				file << entry.path() << std::endl;
				file.close();
				break;
			}
		}
	}
	/*else {

		throw new exception("Path doen't exist!");
	}*/
}

vector<char> diskParser()
{
	DWORD mydrives = 100;
	char lpBuffer[100];
	DWORD test = GetLogicalDriveStrings(mydrives, lpBuffer);

	vector<char> disks;
	int i = 0;
	while (i < 100 || lpBuffer[i] == lpBuffer[i + 1])
	{
		if (isalpha(lpBuffer[i])) {
			disks.push_back(lpBuffer[i]);
			i += 4;
		}
		else {
			break;
		}
	}
	return disks;
}
