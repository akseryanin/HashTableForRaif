#include  "hashset.h"

using namespace std;

template<class key_type, class hash_func, class key_equal>
const int HashSet<key_type, hash_func, key_equal>::num_primes = 25;


template<class key_type, class hash_func, class key_equal>
const unsigned long HashSet<key_type, hash_func, key_equal>::prime_list[] =
{ 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
 50331653, 100663319, 201326611, 402653189, 805306457 };


template<class key_type, class hash_func, class key_equal>
bool HashSet<key_type, hash_func, key_equal>::search(const key_type& k)
{
	int p = hf(k) % table_size();

	while ((*ht)[p].used)
	{
		if (eq((*ht)[p].key, k) && !(*ht)[p].deleted)      // equality predicate for key_type
			return true;

		p++;
		if (p == table_size())
		{
			p = 0;  // wrap around to beginning
		}
	}

	return false;
}

template<class key_type, class hash_func, class key_equal>
void HashSet<key_type, hash_func, key_equal>::remove(const key_type& k)
{
	int p = hf(k) % table_size();

	while ((*ht)[p].used)
	{
		if (eq((*ht)[p].key, k) && !(*ht)[p].deleted)
		{
			(*ht)[p].deleted = true;
			return;
		}

		p++;
		if (p == table_size())
		{
			p = 0;
		}
	}
	throw std::invalid_argument("Key not in hash table.");
}


template<class key_type, class hash_func, class key_equal>
void HashSet<key_type, hash_func, key_equal>::insert(const key_type& k)
{

	if (load_factor() > .7) {
		resize();
	}


	int p = hf(k) % table_size();

	while ((*ht)[p].used)
	{
		if ((*ht)[p].deleted)
		{
			(*ht)[p].used = true;
			(*ht)[p].key = k;
			entries++;
			return;
		}

		p++;
		if (p == table_size())
		{
			p = 0;
		}
	}
	(*ht)[p].used = true;
	(*ht)[p].key = k;
	entries++;
}

template<class key_type, class hash_func, class key_equal>
int HashSet<key_type, hash_func, key_equal>::resize() {

	if (prime == num_primes - 1) {
		cerr << "maximal table size reached, aborting ... " << endl;
		exit(2);
	}

	unsigned int mm = prime_list[prime];
	prime++;
	unsigned int m = prime_list[prime];
	vector<Entry>* ptr = new vector<Entry>(m);
	entries = 0;
	std::swap(ptr, ht);
	for (int i = 0; i < ptr->size(); ++i)
	{
		if (!(*ptr)[i].deleted && (*ptr)[i].used)
			insert((*ptr)[i].key);
	}
	delete ptr;
}
