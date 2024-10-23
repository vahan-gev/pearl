#pragma once
#include <iostream>
#include <cstdlib>
#include <unordered_set>

class IDGenerator {
public:
 
    unsigned int generateID(int max_id) {
        unsigned int id;
        do {
            id = rand() % max_id;
        } while (used_ids.count(id) != 0);
        used_ids.insert(id);
        return id;
    }

private:
    std::unordered_set<unsigned int> used_ids;
};