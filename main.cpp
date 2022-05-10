#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <random>
#include <time.h>

#define MAX_SIZE 150000001ll

using namespace std;

void generateRandomIntArray(int arr[], int N) {

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(10000000, 20000000);
	for (int i = 0; i < N; i++) {
		arr[i] = dist6(rng);
	}
}

template <typename K, typename V>

class HashNode {
public:
	V value;
	K key;

	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
	}
};

template <typename V>
class HashMapInt {

	HashNode<int, V>** arr;
	int counter;
	int capacity;
	int size;
	int lastPrime;
	bitset<MAX_SIZE> isPrime;

	/* Function to set sieve of Eratosthenes. */
	void __setSieve() {
		isPrime[0] = isPrime[1] = 1;
		for (long long i = 2; i * i <= MAX_SIZE; i++)
			if (isPrime[i] == 0)
				for (long long j = i * i; j <= MAX_SIZE; j += i)
					isPrime[j] = 1;

	}

public:
	HashMapInt()
	{
		capacity = 1000000;
		size = 0;
		counter = 0;
		arr = new HashNode<int, V>*[capacity];

		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		lastPrime = capacity - 1;
		while (isPrime[lastPrime] == 1)
			lastPrime--;
	}

	int hashFunctionInt(int key)
	{
		return key % capacity;
	}

	int secondHashInt(int key) {
		return lastPrime - (key % lastPrime);
	}

	void linearProbing(int key, V value, int hashIndex) {

		HashNode<int, V>* temp = new HashNode<int, V>(key, value);

		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key) {
			hashIndex++;
			hashIndex %= capacity;
		}

		if (arr[hashIndex] == NULL)
			size++;
		arr[hashIndex] = temp;
	}

	void doubleHashing(int key, V value, int hashIndex) {

		HashNode<int, V>* temp = new HashNode<int, V>(key, value);

		int offset = secondHashInt(key);

		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key) {
			hashIndex = (hashIndex + offset) % capacity;
		}

		if (arr[hashIndex] == NULL)
			size++;
		arr[hashIndex] = temp;
	}

	void insertNode(int key, V value)
	{
		int hashIndex = hashFunctionInt(key);

		//linearProbing(key, value, hashIndex);

		doubleHashing(key, value, hashIndex);

	}

	V search(int key)
	{
		int hashIndex = hashFunctionInt(key);
		int offset = secondHashInt(key);
		counter = 0;

		while (arr[hashIndex] != NULL) {

			if (++counter > capacity)
				return NULL;

			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;

			//hashIndex++;
			//hashIndex %= capacity;
			hashIndex = (hashIndex + offset) % capacity;
		}

		return NULL;
	}

	int sizeofMap()
	{
		return size;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	int numberOfOperations() {
		return counter;
	}

	void display()
	{
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL)
				cout << "key = " << arr[i]->key << " value = " << arr[i]->value << endl;
			else
				cout << "key = null value = null" << endl;
		}
	}
};

template <typename V>
class HashMapString {

	HashNode<string, V>** arr;
	int capacity;
	int size;
	int counter;

public:
	HashMapString()
	{
		capacity = 100000;
		size = 0;
		counter = 0;
		arr = new HashNode<string, V>*[capacity];

		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

	}

	int hashFunctionString(string key)
	{
		//return key % capacity;
		int sum = 0;
		for (int i = 0; i < key.size(); i++) {
			sum += int(key[i]);
		}
		return sum % capacity;
	}

	int secondHashString(string key) {
		int h = 0, c = 29;
		for (int i = 0; i < key.size(); i++) {
			h = (c * h + key[i]) % capacity;
		}
		return h;
	}

	void linearProbingString(string key, V value, int hashIndex) {

		HashNode<string, V>* temp = new HashNode<string, V>(key, value);

		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key) {
			hashIndex++;
			hashIndex %= capacity;
		}

		if (arr[hashIndex] == NULL)
			size++;
		arr[hashIndex] = temp;
	}

	void doubleHashingString(string key, V value, int hashIndex) {

		HashNode<string, V>* temp = new HashNode<string, V>(key, value);

		int offset = secondHashString(key);

		while (arr[hashIndex] != NULL && arr[hashIndex]->key != key) {
			hashIndex = (hashIndex + offset) % capacity;
		}

		if (arr[hashIndex] == NULL)
			size++;
		arr[hashIndex] = temp;
	}

	void insertNode(string key, V value)
	{
		int hashIndex = hashFunctionString(key);

		//linearProbingString(key, value, hashIndex);

		doubleHashingString(key, value, hashIndex);

	}

	V search(string key)
	{
		int hashIndex = hashFunctionString(key);
		int offset = secondHashString(key);
		int counter = 0;

		while (arr[hashIndex] != NULL) {

			if (++counter > capacity)
				return NULL;

			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;

			//hashIndex++;
			//hashIndex %= capacity;
			hashIndex = (hashIndex + offset) % capacity;
		}

		return NULL;
	}

	int sizeofMap()
	{
		return size;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void display()
	{
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL)
				cout << "key = " << arr[i]->key << " value = " << arr[i]->value << endl;
			else
				cout << "key = null value = null" << endl;
		}
	}
};

int main()
{
	HashMapInt<int>* h = new HashMapInt<int>;

	HashMapString<int>* h2 = new HashMapString<int>;

	int load = 6000000;
	/*
	int* randoms = new int[load];
	generateRandomIntArray(randoms, load);
	for (int i = 0; i < load; i++) {
		h->insertNode(randoms[i], i);
	}*/

	srand(time(0));
	for (int i = 0; i < load; i++) {
		int key = rand() % 20000000 + 10000000;
		h->insertNode(key, i);
	}
	/*
	int counter = 0;
	ifstream stringsFile("english.txt");
	if (stringsFile) {
		string line;
		while (getline(stringsFile, line) && counter < 500000) {
			h2->insertNode(line, counter);
			counter++;
		}
	}
	stringsFile.close();

	ifstream file("randoms.txt");
	int counter = 0;
	string line;
	if (file) {
		istringstream iss(line);
		int key;
		while (iss >> key) {
			h->insertNode(key, counter);
		}
	}

	file.close();
	/*
	int insertions[] = { 1, 21, 41, 5, 6, 7 };
	int capacity = sizeof(insertions) / sizeof(insertions[0]);

	for (int i = 0; i < 500000; i++)
		h->insertNode(i, i);

	// h->display();
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(10000000, 20000000);
	int randomNum = dist6(rng);
	*/
	int randomNum = rand() % 20000000 + 10000000;
	int value = h->search(randomNum);
	if (value != NULL) {
		cout << "Value for key = " << randomNum << ": " << value << endl;
	}
	else {
		cout << "Key not found" << endl;
	}

	cout << "Number of operations performed: " << h->numberOfOperations() << endl;

	delete h;
	delete h2;
	//delete[] randoms;

	return 0;
}
