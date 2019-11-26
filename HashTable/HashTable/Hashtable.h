#ifndef  _HASHTABLE_H_ 
#define  _HASHTABLE_H_

#include  <iostream>
#include  <vector>
#include  <list>
#include  <algorithm>
#include  <string>
#include  <stdlib.h>

#include  "hashset.h"
#include  "hashset.cpp"

using namespace std;


//Хеш функция с возможностью ее изменения
class hash_function
{
public:

	unsigned int operator()(const string& s)  const {

		unsigned int hash = 0;

		for (unsigned int i = 0; i < s.size(); ++i) {
			hash ^= ((i & 1) == 0) ?
				((hash << 7) ^ (unsigned char)(s[i]) ^ (hash >> 3)) :
				(~((hash << 11) ^ (unsigned char)(s[i]) ^ (hash >> 5)));
		}
		return hash;

	}
};


//Сравнение с возможностью изменения
class equality
{
public:
	equality() {}
	bool  operator()(const string& A, const string& B)  const
	{
		return  (A == B);
	}
};


//Для удобства будем читать все из файла
class HashTable : public HashSet<string, hash_function, equality> {

public:
	HashTable(string filename);

};
#endif // _HASHTABLE_H_
