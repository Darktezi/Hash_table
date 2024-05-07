#include <gtest/gtest.h>
#include "Hash_Table/Hash_Table.h"

TEST(HashTableTest, InsertAndSearch) {
    HashTable<int, std::string> hashTable(10);
    hashTable.insert(5, "value");
    EXPECT_TRUE(*hashTable.search(5) == "value");
}

TEST(HashTableTest, InsertAndErase) {
    HashTable<int, std::string> hashTable(10);
    hashTable.insert(5, "value");
    EXPECT_TRUE(hashTable.erase(5));
    EXPECT_FALSE(hashTable.search(5));
}

TEST(HashTableTest, CollisionResolution) {
    HashTable<int, std::string> hashTable(5);
    hashTable.insert(1, "value1");
    hashTable.insert(6, "value2");

    EXPECT_EQ(hashTable.count(1), 1);
    EXPECT_EQ(hashTable.count(6), 1);
}

TEST(HashTableTest, InsertOrAssign) {
    HashTable<int, std::string> hashTable(10);
    hashTable.insert_or_assign(5, "value");
    EXPECT_TRUE(*hashTable.search(5) == "value");
    hashTable.insert_or_assign(5, "new_value");
    EXPECT_TRUE(*hashTable.search(5) == "new_value");
}

TEST(HashTableTest, Contains) {
    HashTable<int, std::string> hashTable(10);
    hashTable.insert(5, "value");
    EXPECT_TRUE(hashTable.contains("value"));
    EXPECT_FALSE(hashTable.contains("nonexistent_value"));
}

TEST(HashTableTest, Size) {
    HashTable<int, std::string> hashTable(10);
    EXPECT_EQ(hashTable.getSize(), 10);
}

TEST(HashTableTest, countDuplicatesTest) {
    std::vector<int> testArray = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 };

    HashTable<int, int> counts = countDuplicates(testArray);

    /*std::cout << "Contents of HashTable:\n";
    for (int i = 1; i <= 4; ++i) {
        if (counts.search(i) != nullptr) {
            std::cout << i << ": " << *counts.search(i) << std::endl;
        }
    }*/

    EXPECT_TRUE(*(counts.search(1)) == 1);
    EXPECT_TRUE(*(counts.search(2)) == 2);
    EXPECT_TRUE(*(counts.search(3)) == 3);
    EXPECT_TRUE(*(counts.search(4)) == 4);
}
