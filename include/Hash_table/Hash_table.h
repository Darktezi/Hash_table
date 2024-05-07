#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <random>

template<typename K, typename T>
class HashTable {
private:
    struct HashNode {
        K key;
        T value;
        HashNode(K k, T v) : key(k), value(v) {}
    };

    size_t _size;
    std::vector<std::list<HashNode>> table;

    size_t hash(const K& key) const {
        const double A = 0.6180339887;
        size_t hashValue = static_cast<size_t>(_size * (std::fmod(key * A, 1)));
        return hashValue;
    }

public:
    HashTable(size_t tableSize) : _size(tableSize), table(tableSize) {}
    HashTable(const size_t size, const K& min_k, const K& max_k, const size_t min_v, const size_t max_v) {
        if (size == 0)
            throw std::invalid_argument("Size = 0");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> key_dist(min_k, max_k);

        _size = 0;
        table.resize(size);

        for (size_t i = 0; i < size; ++i) {
            K random_key = key_dist(gen);
            size_t len = std::uniform_int_distribution<size_t>(min_v, max_v)(gen);
            T random_value;
            random_value.reserve(len);
            for (size_t j = 0; j < len; ++j) {
                random_value += 'A' + (rand() % 26);
            }
            insert(random_key, random_value);
        }
    }
    HashTable(const HashTable& other) : _size(other._size), table(other.table) {}
    ~HashTable() = default;

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            _size = other._size;
            table = other.table;
        }
        return *this;
    }

    void print() {
        for (size_t i = 0; i < _size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : table[i]) {
                std::cout << "(" << node.key << ", " << node.value << ") ";
            }
            std::cout << std::endl;
        }
    }

    void insert(const K& key, const T& value) {
        size_t index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    void insert_or_assign(const K& key, const T& value) {
        size_t index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    bool contains(const T& value) const {
        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                if (node.value == value) {
                    return true;
                }
            }
        }
        return false;
    }

    T* search(const K& key) {
        size_t index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                return &node.value;
            }
        }
        return nullptr;
    }

    bool erase(const K& key) {
        size_t index = hash(key);
        auto& bucket = table[index];
        auto it = std::find_if(bucket.begin(), bucket.end(), [&](const HashNode& node) {
            return node.key == key;
            });
        if (it != bucket.end()) {
            bucket.erase(it);
            return true;
        }
        return false;
    }

    int count(const K& key) const {
        size_t index = hash(key);
        int count = 0;
        for (const auto& node : table[index]) {
            if (node.key == key) {
                ++count;
            }
        }
        return count;
    }

    size_t getSize() const {
        return _size;
    }
};
