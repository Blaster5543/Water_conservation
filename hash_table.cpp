#include "hash_table.h"
#include "city.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

//hash_code, HashTable constructor, and insert method from ZyBooks, modified to fit code
int HashTable::hash_code(std::string name) {
    int h = 0;
    for (int i = 0; i < name.length(); i++) {
        h = 31 * h + name[i];
    }

    if (h < 0) {
        h = -h;
    }

    return h % buckets.size();
}

HashTable::HashTable(int nbuckets) {  
    for (int i = 0; i < nbuckets; i++) {
        buckets.push_back(nullptr);
    }
}

void HashTable::insert(City data) {
    int h = hash_code(data.city_name);
    Node* new_node = new Node();
    new_node->district = data;
    new_node->next = buckets[h];
    buckets[h] = new_node;
}

City HashTable::get_city(const std::string name) {
    City district;

    //Iterates through the hash table until it finds the city data
    int h = hash_code(name);
    Node* trav = buckets[h];

    //Iterates through the linked list of the spot where the node is
    while (trav != nullptr) {
        if (buckets[h]->district.city_name == name) {
            district = buckets[h]->district;
            break;
        }
        trav = trav->next;
    }

    return district;
}

//copy paste this into "hash_table.cpp"
bool HashTable::find_city(std::string name)
{
    int h = hash_code(name);
    Node* trav = buckets[h];
    bool found = false;
    //Iterates through the linked list of the spot until it find the city or a null ptr(city does not exist)
    while (trav != nullptr) {
        if (buckets[h]->district.city_name == name) {
            found = true;
            break;
        }
    }
    return found;
}

void HashTable::delete_table() {
    Node* to_delete;
    //points the to_delete variable to buckets's array vector
    for (int i = 0; i < buckets.size(); i++) {
        to_delete = buckets[i];

        //Deletes each of the separate chaining nodes
        while (to_delete != nullptr) {
            Node* temp = to_delete->next;
            delete to_delete;
            to_delete = temp;
        }
        buckets[i] = nullptr;
    }
}