// template hash set class

#ifndef  _HASHSET_H_ 
#define  _HASHSET_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;


//Заголовок для хешсета
template<class key_type, class hash_func, class key_equal>
class  HashSet {

protected:
	class Entry {
	public:
		key_type key; 
		bool used; //использован ли элемент
		bool deleted; //удален ли элемент
		Entry() : used(false), deleted(false) {}
	};

	int entries;      //число добавленных
	int prime;        //индекс простого числа

	vector<Entry>* ht;
	hash_func hf;        //класс обертка для изменения хеш функции
	key_equal eq;        //класс оберетка для изменения компаратора

	int table_size()  const { return prime_list[prime]; } //память выделена под такое число элементов
	float load_factor() const { return float(size()) / table_size(); } //загруженность таблицы
	int resize(); //увеличиваем размер, чтобы таблица "не тормозила"
	//обоснование этого в readme

public:
	// предподсчитанный массив простых чисел
	static const int num_primes;
	static const unsigned long prime_list[];

	HashSet() : entries(0), prime(0), ht(new vector<Entry>(prime_list[0])) {};


	virtual ~HashSet() {
		delete ht;
	}

	virtual int size() const { return entries; }
	virtual bool search(const key_type& k);
	virtual void insert(const key_type& k);
	virtual void remove(const key_type& k);
};

#endif
