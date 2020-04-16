#include <iostream>

using namespace std;

template <class T> // T must can compare with int and can cast from int
class Queue {
public:
	Queue(int len=20);
	~Queue();
	T take();
	bool put(T value);
	// Deep copy
	Queue(const Queue & queue1);
	Queue & operator= (const Queue & queue1);
protected:
	int size{}; // Maximum Size
	int length{};
	T * queue{};
	int begin{};
	int end{};
};

template <class T> Queue<T>::Queue(int len) {
	begin = end = length = 0;
	size = len;
	if(len < 1) {
		throw "Error size";
	}
	queue = new int[len];
	for (int i = 0; i < len; ++i) {
		queue[i] = -1;
	}
}

template <class T> Queue<T>::~Queue() {
	delete [] queue;
}

template <class T> T Queue<T>::take() {
	if(length == 0) {
		return -1;
	}
	int index = (size + begin) % size;
	begin = (begin + 1) % size;
	length--;
	return queue[index];
}

template <class T> bool Queue<T>::put(T value) {
	if(value <= 0) {
		throw "Error put value size";
	}
	if(length == size) {
		return false;
	}
	length++;
	queue[end] = value;
	end = (end + 1) % size;
	return true;
}

template <class T> Queue<T>::Queue(const Queue<T> &queue1) {
	this->operator=(queue1); // Use the Queue::operator= explicitly
}

template <class T> Queue<T> & Queue<T>::operator=(const Queue<T> & queue1) {
	if(this == &queue1){
		return *this;
	}
	this->size = queue1.size;
	this->length = queue1.length;
	this->begin = queue1.size;
	this->end = queue1.size;
	// cout << "Copy " << size << endl;
	queue = new int[size];
	for (int i = 0; i < size; ++i) {
		queue[i] = queue1.queue[i];
	}
	return *this;
}


#include <unordered_map>
template <class K, class V> // K must can compare with int and can cast from int
class LRUCache {
public:
	LRUCache(int len=20): queue(len){};
	V get(K key);
	void put(K key, V value);
protected:
	Queue<K> queue;
	std::unordered_map<K, V> table;
};

template<class K, class V>
V LRUCache<K, V>::get(K key) {
	auto it = table.find(key);
	if(it != it.end()) {
		return it->second;
	}
	return -1;
}

template<class K, class V>
void LRUCache<K, V>::put(K key, V value) {
	auto it = table.find(key);
	if(it == it.end()) { // Not find. Then it is a new key
		int check = queue.put(key);
		if(!check) { // Queue is full
			K pop = queue.take();
			table.erase(pop); // Remove the oldest one
		}
		check = queue.put(key);
	}
	table[key] = value;
}


int main(){
	Queue<int> a(5);
	for (int i = 1; i < 7; ++i) {
		cout << i << " : " << a.put(i) << endl;
	}
	Queue<int> b = a;
	Queue<int> c;
	c = a;
	cout << c.take() << endl;
	cout << b.take() << endl;
	cout << a.take() << endl;
}
