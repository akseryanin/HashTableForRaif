#include <iostream>
#include <fstream>
#include <string>

#include "Hashtable.h"


HashTable::HashTable(string filename)
{
	ifstream f(filename);
	string buf;
	if (f.is_open())
	{
		while (getline(f, buf))
		{
			insert(buf);
		}
		f.close();
	}
	else
		throw std::invalid_argument("File not found.");
}
