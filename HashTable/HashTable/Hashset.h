// template hash set class

#ifndef  _HASHSET_H_ 
#define  _HASHSET_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;


//��������� ��� �������
template<class key_type, class hash_func, class key_equal>
class  HashSet {

protected:
	class Entry {
	public:
		key_type key; 
		bool used; //����������� �� �������
		bool deleted; //������ �� �������
		Entry() : used(false), deleted(false) {}
	};

	int entries;      //����� �����������
	int prime;        //������ �������� �����

	vector<Entry>* ht;
	hash_func hf;        //����� ������� ��� ��������� ��� �������
	key_equal eq;        //����� �������� ��� ��������� �����������

	int table_size()  const { return prime_list[prime]; } //������ �������� ��� ����� ����� ���������
	float load_factor() const { return float(size()) / table_size(); } //������������� �������
	int resize(); //����������� ������, ����� ������� "�� ���������"
	//����������� ����� � readme

public:
	// ���������������� ������ ������� �����
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
