#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template<typename KeyType, typename ValueType>
class HashTable {
private:
    struct HashNode {
        KeyType key;
        ValueType value;
        HashNode(KeyType k, ValueType v) : key(k), value(v) {}
    };

    size_t size;
    std::vector<std::list<HashNode>> table;

    size_t hash(const KeyType& key) const {
        size_t hashValue = 0;
        for (const auto& ch : key) {
            hashValue += ch;
        }
        return hashValue % size;
    }

public:
    HashTable(size_t tableSize) : size(tableSize), table(tableSize) {}
    HashTable(const HashTable& other) : size(other.size), table(other.table) {}
    ~HashTable() = default;

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            size = other.size;
            table = other.table;
        }
        return *this;
    }
};
