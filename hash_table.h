#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <vector>
#include <string>
#include "city.h"

struct Node {
    City district;
    Node* next = nullptr;
};

class HashTable
{
public:
   /**
      Constructs a hash table.
      @param nbuckets the number of buckets
   */
   HashTable(int nbuckets);

   /**
      Adds an element to this hash table if it is not already present.
      @param x the element to add
      @param pos the position of the element.
   */
   void insert(City data);

   /**
    * Gets the hash code from the table
    * @return the statistics of the city
   */
   City get_city(std::string);

   /**
    * Checks if city data already exists
    * @return a 1 if city exists or 0 if it does not exist
   */
   bool find_city(std::string); 

   /**
    * Deletes the entire table.
   */
   void delete_table();

private:

   /**
    * Gets the hash key
    * @param c the character to add
   */
   int hash_code(std::string name);

   std::vector<Node*> buckets;
};
#endif