#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string> // For string hashing
#include <functional> // For std::hash
#include <iostream>   // For debugging/error

// A simple Hash Table implementation using chaining
// K: Key type (e.g., std::string for IDs)
// V: Value type (e.g., Voter, Candidate)
template <typename K, typename V>
class HashTable {
private:
    static const int DEFAULT_TABLE_SIZE = 100; // A reasonable default size
    std::vector<std::list<std::pair<K, V>>> table;
    int currentSize;

    // A generic hash function using std::hash
    unsigned int hash(const K& key) const {
        return std::hash<K>{}(key) % table.size();
    }

public:
    HashTable(int size = DEFAULT_TABLE_SIZE) : currentSize(0) {
        if (size <= 0) size = DEFAULT_TABLE_SIZE; // Ensure valid size
        table.resize(size);
    }

    // Insert a key-value pair
    // If key exists, update the value.
    void insert(const K& key, const V& value) {
        unsigned int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Update existing value
                return;
            }
        }
        table[index].push_back({key, value}); // Add new pair
        currentSize++;
    }

    // Retrieve a pointer to the value associated with the key
    // Returns nullptr if key not found.
    V* get(const K& key) {
        unsigned int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return &pair.second; // Return pointer to the stored value
            }
        }
        return nullptr; // Key not found
    }

    // Check if a key exists
    bool contains(const K& key) const {
        unsigned int index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    // Remove a key-value pair
    void remove(const K& key) {
        unsigned int index = hash(key);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                currentSize--;
                return;
            }
        }
    }

    int size() const {
        return currentSize;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    // Function to get all values (useful for populating BST)
    std::vector<V> getAllValues() const {
        std::vector<V> allValues;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                allValues.push_back(pair.second);
            }
        }
        return allValues;
    }
};

#endif // HASHTABLE_H