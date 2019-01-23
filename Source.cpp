/*
 * In your group, propose one hash function for the numbers in the data on page 577 
 * (the number is the key – index in the hash table array – and the name and number are the data). 
 * Define a hash table with 11 entries, and describe a linear method for handling collisions between 
 * indexes when inserting data in the table. Demonstrate that the hashing function works and collisions are handled, 
 * by storing and retrieving data from the hash table using the key as the position of a data item in the table.
 */

/*
 Adam 123-4567 
 Brenda 345-5352 
 Brendon 983-7373 
 Charles 987-1122 
 Jeremiah 789-4563 
 Katherine 823-1573 
 Patrick 757-4532 
 Raymond 090-9383 
 Thorsten 929-6632 
 */


// template copied from: https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250
// similar template: https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
#include <cstddef> 
template <typename K, typename V>
class HashNode
{
public:
	HashNode(const k &key, const V &value) :
	key(key), value(value), next(NULL) {}
	K getKey() const { return key; }
	V getValue() const { return value; }
	void setValue(V value) { HashNode::value = value; }
	HashNode *getNext() const { return next; }
	void setNext(HashNode *next) { HashNode::next = next; }
private:
	// key-value pair
	K key;
	V value;
	// next bucket with the same key
	HashNode *next;
};
