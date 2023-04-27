#ifndef CITY_H
#define CITY_H

struct City {
    std::string city_name;
    int population = 0;
    int gallons_per_capita = 0;
    int gallons_per_resident = 0;
};
#endif