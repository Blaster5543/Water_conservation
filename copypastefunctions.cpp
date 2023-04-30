 
 /**
    * Checks if city data already exists
    * @return a 1 if city exists or 0 if it does not exist
   */
   bool find_city(std::string); 
//put this into "hash_table.h"


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
