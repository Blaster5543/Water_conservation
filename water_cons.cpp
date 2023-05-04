#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "queue.h"
#include "hash_table.h"
#include "city.h"
#include "tree.h"
#include <iomanip>
#include <vector>
//Dylan Chiu
//Eric Huang
//Khwaja Sana Sidiqi

//Dylan Chiu //Works
//Last modified: 04/26/23
/**
 * Calculates the gallons used from the user's inputs
 * @param y_n_chain The string of answers from the user
*/
double calculation(std::string y_n_chain) {
    std::ifstream gallons_file("questions_gallons_used.txt");
    std::string line;
    double gallons = 0;
    int pos = 0;
    int line_pos = 0;
    while (getline(gallons_file, line)) {
        for(int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                line_pos = i;
                break;
            }
        }

        if (y_n_chain[pos] == 'Y') {
            line = line.substr(0, line_pos);
        } else {
            line = line.substr(line_pos + 1, line.length() - line_pos);
        }

        gallons += stoi(line);
        pos++;
    }

    return gallons;
}

//Dylan Chiu
//Last modified: 05/01/23
/**
 * Calculates using the answer from 
*/
double calculation(double answer, int pos) {
    std::ifstream input_gallons_file("questions_input.txt");
    std::ifstream gallons_used_file("questions_gallons_input_used.txt");
    std::string line;
    std::string gallon_amount;
    double gallons = 0;

    //Finds the question that is being asked.
    for (int i = 0; i < pos; i++) {
        getline(input_gallons_file, line);
        getline(gallons_used_file, gallon_amount);
    }

    //Assumes the answer if the user does not know.
    if (answer == -1) {
        if (line.find("long") != std::string::npos) {
            answer = 8;
        } else {
            if (line.find("day") != std::string::npos) {
                answer = 5;
            } else {
                answer = 3;
            }
        }
    }

    if (line.find("long") != std::string::npos) {
        gallons = stoi(gallon_amount);
        gallons *= ((answer / 60) * 24) * 365;
    } else if (line.find("many") != std::string::npos) {
        gallons = stoi(gallon_amount);
        if (line.find("day") != std::string::npos) {
            gallons *= answer * 365;
        } else {
            gallons *= answer * 52;
        }
    }

    return gallons;
}

//Dylan Chiu //Works
//Last modified: 04/29/23
/**
 * Sets up the tips for the survey
 * @param survey unordered map that contains a number associated with an unordered set of tips
*/
void set_up_survey(std::unordered_map<int, std::unordered_set<std::string>>& survey) {
    int washroom_category = 1;
    int garden_category = 2;
    int kitchen_category = 3;
    int outdoor_category = 4;
    int general_category = 5;
    std::unordered_set<std::string> washroom_tips;
    std::unordered_set<std::string> garden_tips;
    std::unordered_set<std::string> kitchen_tips;
    std::unordered_set<std::string> outdoor_tips;
    std::unordered_set<std::string> general_tips;
    std::ifstream tips_finder("recommend.txt");
    std::string line;
    int category = 0;

    while (getline(tips_finder, line)) {
        if (line.find("Washroom") != std::string::npos) {
            category = 1;
        } else if (line.find("Garden") != std::string::npos) {
            category = 2;
        } else if (line.find("Kitchen") != std::string::npos) {
            category = 3;
        } else if (line.find("Outdoor") != std::string::npos) {
            category = 4;
        } else if (line.find("General") != std::string::npos) {
            category = 5;
        }

        if (!line.empty()) {
            if (category == 1 && line.find("Washroom") == std::string::npos) {
                washroom_tips.insert(line);
            } else if (category == 2 && line.find("Garden") == std::string::npos) {
                garden_tips.insert(line);
            } else if (category == 3 && line.find("Kitchen") == std::string::npos) {
                kitchen_tips.insert(line);
            } else if (category == 4 && line.find("Outdoor") == std::string::npos) {
                outdoor_tips.insert(line);
            } else if (category == 5 && line.find("General") == std::string::npos) {
                general_tips.insert(line);
            }
        }
    }

    survey[washroom_category] = washroom_tips;
    survey[garden_category] = garden_tips;
    survey[kitchen_category] = kitchen_tips;
    survey[outdoor_category] = outdoor_tips;
    survey[general_category] = general_tips;
}

//Dylan Chiu
//Only prints out the general category.
void print_categories_tips(std::string num_code, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    int category;
    std::unordered_set<std::string> tips_to_print;
    for (int i = 0; i < num_code.length(); i++) {
        std::string temp = num_code.substr(i, 1);
        category = stoi(temp);
        tips_to_print = survey_tips[category];
        for (auto iter : tips_to_print) {
            std::cout << iter << std::endl;
        }
    }
}

//Dylan Chiu //Works
//Last modified 04/30/23
/**
 * Prints out the general tips to conserve water
 * @param unordered_map survey_tips: The map needed to print out the general tips
 */
void print_general_tips(std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    std::unordered_set<std::string> tips_to_print;
    tips_to_print = survey_tips[5];
    for (auto iter : tips_to_print) {
        std::cout << iter << std::endl;
    }
}

//Dylan Chiu
void survey_input(std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    using namespace std;
    const int HOUSE_WATER_PER_YEAR = 69350;
    const int EFFICIENT_WATER_PER_YEAR = 52012;
    ifstream questions("questions_input.txt");
    string line;
    double answer = 0;
    double total = 0;
    int pos = 0;

    cout << "Here are the questions!" << endl;
    cout << "(Input 0 if you do not use/have, input -1 if you aren't sure (This assume standard or average))" << endl;
    while (getline(questions, line)) {
        cout << line << endl;
        cin >> answer;
        total += calculation(answer, pos);
        pos++;
    }

    cout << "This is how many gallons you would use per year! Gallons used: ";
    cout << total << endl;
    if (total > HOUSE_WATER_PER_YEAR) {
        cout << "You're using too much water! Consider buying more water efficient appliances!" << endl;
    } else if (total < HOUSE_WATER_PER_YEAR && total > EFFICIENT_WATER_PER_YEAR) {
        cout << "You're using the average amount. Not bad but you can cut it down more!" << endl;
    } else if (total < EFFICIENT_WATER_PER_YEAR) {
        cout << "You're doing great with water conservation! Keep up the good work!" << endl;
    }
}

//Dylan Chiu //Works
//Last modified: 04/29/23
/**
 * Asks the user to use yes or no question and prints out the resulting gallons used
 * Proceeds to print out tips for them to save water
 * @param BinaryTree QNA_tree: Binary decision tree to help with the major categories checks
 * @param std::unordered_map survey_tips: The unordered map containing an unordered set of survey_tips
*/
void survey_question(BinaryTree& QNA_tree, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    const int QUESTIONS_PER_CATEGORY = 5;
    const int HOUSE_WATER_PER_YEAR = 69350;
    const int EFFICIENT_WATER_PER_YEAR = 52012;
    const double COST_PER_GALLON = 0.007;
    using namespace std;
    string answer;
    string y_n_chain;
    string line;
    ifstream questions_parse("questions.txt");
    double gallons;
    string num_code;

    //Gets the questions from the text file to give to the user to answer
    while (getline(questions_parse, line)) {
        cout << line << endl;
        cin >> answer;
        if (islower(answer[0])) {
            answer = toupper(answer[0]);
        }
        y_n_chain += answer;
    }

    string y_n_categories;
    for (int i = 0; i < y_n_chain.length(); i++) {
        bool category_answered = false;
        for (int j = 0; j < QUESTIONS_PER_CATEGORY; j++) {
            if (y_n_chain[j] == 'Y') {
                category_answered = true;
            }
        }
        if (category_answered) {
            y_n_categories += "Y";
        } else {
            y_n_categories += "N";
        }
    }

    num_code = QNA_tree.get_data(QNA_tree.get_root(), y_n_categories, 0);
    gallons = calculation(y_n_chain);

    //Outputs how much gallons the user uses and tells them if they're above average, average, or efficient
    cout << "Combining with our survey, we have calculated how much water you used ";
    cout << "(This is how many gallons used per year assuming you use them everyday)!" << endl;
    cout << "You use " << gallons << " gallons per year!" << endl;
    if (gallons > HOUSE_WATER_PER_YEAR) {
        cout << "You use more water than the average American household, consider cutting it down!" << endl;
    } else if (gallons <= HOUSE_WATER_PER_YEAR && gallons > EFFICIENT_WATER_PER_YEAR) {
        cout << "You use the average amount of water. Not bad but you can save more money and water!" << endl;
    } else if (gallons < EFFICIENT_WATER_PER_YEAR) {
        cout << "You use less water than the average! Keep up the great work!" << endl;
    }

    cout << endl;

    //Outputs the amount of money the user is spending.
    cout << "This is how much money you're spending on water per year! ";
    cout << "$" << fixed << setprecision(2) << gallons * COST_PER_GALLON << endl;

    //Prints out the amount of money 
    if (gallons > EFFICIENT_WATER_PER_YEAR) {
        cout << endl;
        cout << "And this is how much money you could save! ";
        double money_saved = (gallons * COST_PER_GALLON) - (EFFICIENT_WATER_PER_YEAR * COST_PER_GALLON);
        cout << "$" << money_saved << endl;
    }

    cout << endl;
    cout << "Above all, we also will give you some tips on how to save more water!" << endl;
    print_categories_tips(num_code, survey_tips);
}

//Dylan Chiu
//Last modified 04/26/23
void survey(BinaryTree& QNA_tree, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    std::string choice;
    std::cout << "By taking the survey, you can get tips that are personalized to help you lower your water bill!" << std::endl;
    std::cout << "By lowering your water bill, you can help conserve water as well!" << std::endl;
    while (true) {
        std::cout << "Would you like to use your personal information or would you like to answer some yes or no questions? ";
        std::cout << "(1 for personal information, 2 for questions, enter 3 to go back)" << std::endl;
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "Please input the information pertaining to these questions to the gallon." << std::endl;
            survey_input(survey_tips);
        } else if (choice == "2") {
            std::cout << "Answer these simple yes or no questions and we will calculate the gallons used by you! ";
            std::cout << "(All must be answered with Y/N, if you aren't sure, type in N)" << std::endl;
            survey_question(QNA_tree, survey_tips);
        } else if (choice == "3") {
            return;
        }

        std::cout << "Here are also some general tips to save water!";
        print_general_tips(survey_tips);

        std::cout << "Would you like to take the survey again? (Y/N) ";
        std::cin >> choice;
        if (islower(choice[0])) {
            choice = toupper(choice[0]);
        }
        if (choice == "Y") {
            continue;
        } else {
            break;
        }
    }
}

//Prints the city info of one city
void print_city_info(City city) {
    std::cout << city.city_name << std::endl;
    std::cout << "Population: " << city.population << std::endl;
    std::cout << "Gallons per Capita: " << city.gallons_per_capita << std::endl;
    std::cout << "Gallons per Resident: " << city.gallons_per_resident << std::endl;
}

//Prints the city info side by side for comparison
void print_city_info(City temp, City compare)
{
    using namespace std;
    cout << " " << setw(10) << temp.city_name << " " << setw(10) << compare.city_name << endl;
    cout << "Population: " << temp.population  << setw(50) << compare.population << endl;
    cout << "Gallons per Capita: " << temp.gallons_per_capita << setw(40) << compare.gallons_per_capita << endl;
    cout << "Gallons per Resident: " << temp.gallons_per_resident << setw(39) << compare.gallons_per_resident << endl;
}

void timer(City city_data, int resLevel) 
{
    int years_left = resLevel / (city_data.gallons_per_capita);
    std::cout << "City's water level will last them " << years_left << " years!\n";
}


/**
   Swaps two integers.
   @param x the first integer to swap
   @param y the second integer to swap
*/

/*
void swap(City& x, City & y)
{  
   City temp = x;
   x = y;
   y = temp;
}*/

/**
   Partitions a portion of an array.
   @param a the array to partition
   @param from the first index of the portion to be partitioned
   @param to the last index of the portion to be partitioned
   @return the last index of the first partition
*/

/*
int partition(City a[], int from, int to)
{
   int pivot = a[from].gallons_per_capita;
   int i = from - 1;
   int j = to + 1;
   while (i < j)
   {
      i++; while (a[i].gallons_per_capita < pivot) { i++; }
      j--; while (a[j].gallons_per_capita > pivot) { j--; }
      if (i < j) { swap(a[i], a[j]); }
   }
   return j;
} */

/**
   Sorts a portion of an array, using quick sort.
   @param a the array to sort
   @param from the first index of the portion to be sorted
   @param to the last index of the portion to be sorted
*/
/*
void quicksort(City a[], int from, int to)
{
   if (from >= to) { return; }
   int p = partition(a, from, to);
   quicksort(a, from, p);
   quicksort(a, p + 1, to);
}
*/

//Sana
//Edit: 4/25/23
//Edit2: 4/29/23
//Edit3: 5/1/23
void statistics(HashTable& dataset, const int WATER_RESEVOIR_LEVEL) {
    while (true) {
        std::string name = "";
        std::string choice;
        std::cout << "Do you want to see the statistics of a county or compare? (1 for a single county, 2 for compare, 3 to go back) ";
        std::cin >> choice;
        if (choice == "1") {
            std::cin.ignore(1,'\n');
            std::cout << "What county do you want to view? (Type in the full name exactly as it shows) ";
            getline(std::cin, name);
            while (!dataset.find_city(name)) {
                std::cout << "Could not find city name " << name << ". Please type in the name again. ";
                getline(std::cin, name);
            }

            print_city_info(dataset.get_city(name));
        } else if (choice == "2") {
                std::string compare_name = "";
                bool done = false;
                Queue cities_to_be_compared;
                std::cout << "What county do you want to be the compared? ";
                std::cin.ignore(1,'\n');
                getline(std::cin, compare_name);
                std::cout << "What counties do you want to compare? (Enter '0' to exit) ";
                while (name != "0")
                do {  

                    getline(std::cin, name); 
                    if (name == "0") {done = true;} //Terminates loop if user inputs 0
                    if (dataset.find_city(name)) {//if the user input matches our database name pushes the city into the queue
                        cities_to_be_compared.push(name);
                    }

                } while (!done);


                while(cities_to_be_compared.size() > 0) {
                    print_city_info(dataset.get_city(cities_to_be_compared.front()), dataset.get_city(compare_name));
                    timer(dataset.get_city(cities_to_be_compared.front()), WATER_RESEVOIR_LEVEL);
                    cities_to_be_compared.remove();
                }
        } else {
            return;
        }

        std::cout << "Would you like to look at some statistics again? (Y/N) ";
        std::cin >> choice;
        if (choice == "Y") {
            continue;
        } else {
            break;
        }
    }
}

//Dylan Chiu //Works
//Last updated: 04/26/23
/**
 * Initializes the QNA tree for the survey function
 * @param BinaryTree QNA_tree the binary tree to be initialized
*/
void set_qna_tree(BinaryTree& QNA_tree) {
    std::ifstream combo("combo_recommend.txt");
    std::string line;
    std::string num_code;
    std::string y_n_chain;

    //Gets the letter and the binary string associated with them and adds to the tree
    while (getline(combo, line)) { 
        int i = 0;
        for(int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                num_code = line.substr(0, i);
                y_n_chain = line.substr(i + 1, line.length() - i);
            }
        }

        QNA_tree.add_node(QNA_tree.get_root(), num_code, y_n_chain, 0);
    }

    //QNA_tree.print2D(QNA_tree.get_root());

    combo.close();
}

//Dylan Chiu //Works
//Last updated: 04/24/23
/**
 * Gets the numerical statistics from the text file to aid the file parser in
 * @param ifstream file_reader: The file that will be read from
 * @param City data: The city struct that the file is currently on
 * @param string word: The numerical statistic
*/
void get_num_statistics(std::ifstream& file_reader, City& data, std::string& word) {
    std::string population;
    int pop;
    int gallons;
    int gallons_r;

    population = word;

    //Gets rid of any commas in the numerical statistic of population
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == ',') {
            std::string temp = population.substr(0, i);
            temp += population.substr(i + 1, population.length() - temp.length());
            population = temp;
        }
        pop = stoi(population);
        data.population = pop;
    }

    //Reads the next two statistics of gallons per capita use and gallons per resident use
    file_reader >> word;
    gallons = stoi(word);
    data.gallons_per_capita = gallons;
    file_reader >> word;
    gallons_r = stoi(word);
    data.gallons_per_resident = gallons_r;
}

//Dylan Chiu //Works
//Last updated: 04/24/23
/**
 * Gets the data from the text files
 * @param HashTable dataset: The HashTable to put the data of the text file into
*/
void file_parser(HashTable& dataset) {
    std::ifstream file_reader("water_table.txt");
    std::string word;

    while (file_reader >> word) {
        City data;
        std::string name;
        //Gets the name of the district
        while (!isdigit(word[0])) {
            name += word;
            name += " ";
            file_reader >> word;
        }

        name = name.substr(0, name.length() - 1);
        

        data.city_name = name;
        //Gets the number statistics then insert the structure to the data set
        get_num_statistics(file_reader, data, word);
        dataset.insert(data);
        
        if (file_reader >> word) {
            file_reader.ignore(300, '\n');
        }
    }
    file_reader.close();
}

//Dylan Chiu
//Last updated: 04/24/23
int main() {
    std::string user_choice; //Holds the user's choice
    const int WATER_RESEVOIR_LEVEL = 41237; //The current resevoir level
    const int NBUCKETS = 599; //The hashtable size
    HashTable dataset(NBUCKETS);
    BinaryTree QNA_tree;
    file_parser(dataset); //inserts the data set into the hash table
    set_qna_tree(QNA_tree); //initializes the binary decision tree
    std::unordered_map <int, std::unordered_set<std::string>> survey_tips;
    set_up_survey(survey_tips);
    //print_map(survey_questions);

    std::cout << "Welcome user! This program is designed to help you understand";
    std::cout << " the importance of water conservation! Would you like to use it? (Y/N) ";
    std::cin >> user_choice;
    if (std::cin.fail() || (user_choice != "Y" && user_choice != "N")) {
        std::cout << "Choice does not correspond with any, terminating program";
    }

    while (user_choice == "Y") {
        std::cout << "Great! Would you like to see the statistics of the average water consumption ";
        std::cout << "or take a survey to see your water consumption statistics? (1 for Statistics, 2 for survey) ";
        std::cin >> user_choice;
        if (user_choice == "1") {
            statistics(dataset, WATER_RESEVOIR_LEVEL);
        } else {
            survey(QNA_tree, survey_tips);
        }

        std::cout << "Would you like to run the program again? (Y/N) ";
        std::cin >> user_choice;
    }

    std::cout << "We hope you enjoy using this program!" << std::endl;
    dataset.delete_table();
    QNA_tree.delete_tree(QNA_tree.get_root());
}