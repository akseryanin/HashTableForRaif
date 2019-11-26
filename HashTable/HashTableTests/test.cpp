#include "pch.h"
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include "../HashTable/Hashtable.h"

using namespace std;

template <typename T, typename S>
void insertElements(S& set, vector<T> elements)
{
	for (T e : elements)
		set.insert(e);
}

template <typename T, typename S>
void removeElements(S& set, vector<T> elements)
{
	for (T e : elements)
		set.remove(e);
}

template <typename T, typename S>
void containsElements(S& set, vector<T> elements)
{
	for (T e : elements)
		ASSERT_TRUE(set.search(e));
}

using DefaultSet = HashSet<string, hash_function, equality>;

TEST(HashSetTest, simple)
{
	DefaultSet set;

	ASSERT_FALSE(set.search("a"));
	ASSERT_FALSE(set.search("b"));
	ASSERT_FALSE(set.search("c"));

	insertElements<string, DefaultSet>(set, { "a", "b", "c" });
	containsElements<string, DefaultSet>(set, { "a", "b", "c" });
	removeElements<string, DefaultSet>(set, { "a", "b", "c" });

	ASSERT_FALSE(set.search("a"));
	ASSERT_FALSE(set.search("b"));
	ASSERT_FALSE(set.search("c"));
}