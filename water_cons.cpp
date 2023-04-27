#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "queue.h"
#include "hash_table.h"
#include "city.h"
#include "tree.h"
//Dylan Chiu
//Eric Huang
//Khwaja Sana Sidiqi

int calculation() {
    /*Calculate the user's gallons per day based on their yes or no question or personal information
    if (personal information) {
        Calculate each personal information into a gallons used per day
    } else {
        Calculate based on the yes or no question (assume the max gallons used)
    }
    return the gallons used per day
    */
   return 0;
}

//Dylan Chiu //Works
//Last modified: 04/26/23
void set_up_survey(std::unordered_map<int, std::unordered_set<std::string>>& survey) {
    std::unordered_map<int, std::unordered_set<std::string>> survey_categories;
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

    survey_categories[washroom_category] = washroom_tips;
    survey_categories[garden_category] = garden_tips;
    survey_categories[kitchen_category] = kitchen_tips;
    survey_categories[outdoor_category] = outdoor_tips;
    survey_categories[general_category] = general_tips;
}

//Dylan Chiu //Will remove later/Use for debugging
void print_map(std::unordered_map<int, std::unordered_set<std::string>>& tips) {
    std::unordered_map<int, std::unordered_set<std::string>>::iterator it = tips.begin();
    while (it != tips.end()) {
        std::unordered_set<std::string>::iterator it_tips = it->second.begin();
        while (it_tips != it->second.end()) {
            std::cout << *it_tips << std::endl;
            it_tips++;
        }
        // iterator incremented to point next item
        it++;
    }
}

//Dylan Chiu
void survey_input() {

}

//Dylan Chiu
void survey_question() {
    using namespace std;
    string answer;
    string y_n_chain;
    cout << "Do you constantly take baths? ";
    cin >> answer;
}

//Dylan Chiu
//Last modified 04/26/23
void survey() {
    std::string choice;
    while (true) {
        std::cout << "Would you like to use your personal information or would you like to answer some yes or no questions? ";
        std::cout << "(1 for personal information, 2 for questions) ";
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "Please input the information pertaining to these questions to the gallon." << std::endl;
            //survey_input();
        } else {
            std::cout << "Answer these simple yes or no questions and we will calculate the gallons used by you! ";
            std::cout << "(All must be answered with Y/N)" << std::endl;
            //survey_question();
        }

        std::cout << "Would you like to take the survey again? (Y/N) ";
        std::cin >> choice;
        if (choice == "Y") {
            continue;
        } else {
            break;
        }
    }
    /*Ask the user for personal information or simple yes or no question
   If (personal information) {
      Ask them each question pertaining their water consumption
   } Else {
      Ask them the available yes or no question
   }
   Calculation function
   Give the user the water conversation tips based on their responses
   Compare the user to the average user in water consumption
   Gives response to the user’s water consumption */
}

void timer() {
    /*
    */
}

//Sana
//Edit: 4/25/23
void statistics(HashTable& dataset, const int WATER_RESEVOIR_LEVEL) {
    while (true) {
        std::string name;
        std::string choice;
        std::cout << "Do you want to see the statistics of a county or compare? (1 for a single county, 2 for compare) ";
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "What county do you want to view? (Type in the full name, ";
            std::cout << "if it is \"City of\", put City of first then the name) ";
            std::cin >> name;
            City temp = dataset.get_city(name);     //temp just holds the data for the city that we will display
            std::cout << temp.city_name << "\nPopulation: " << temp.population << "\nGallons per Capita: " << temp.gallons_per_capita << "\nGallons per Resident: " << temp.gallons_per_resident << "\n"; 
        } else {
            Queue cities_to_be_compared;
            std::cout << "What county do you want to be the compared? ";
            std::cin >> name;
            
            while (name != "0")
            {
                std::cout << "What counties do you want to compare it with? (Type in the full name, )";
            } 
        }

        timer();

        std::cout << "Would you like to use the statistics again? (Y/N) ";
        std::cin >> choice;
        if (choice == "N") {
            break;
        }
    }

    /*Ask the user for what county they live in.
   Ask the user if they want just the county they live in statistics or to compare
   if(just statistics) {
      Print out statistics
   } else {
      While loop {
         Ask the user for what counties they want (use sentinel value to stop) 
         Put each of the name of the counties in a queue
      }
      Print out the table of the counties statistics compared to the county the user lives in
   }

   Print out the timer
*/
}

//Dylan Chiu
//Last updated: 04/26/23
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
                y_n_chain = line.substr(i, line.length() - i);
            }
        }

        QNA_tree.add_node(QNA_tree.get_root(), num_code, y_n_chain, 0);
    }

    combo.close();
}

//Dylan Chiu //Works
//Last updated: 04/24/23
void get_num_statistics(std::ifstream& file_reader, City& data, std::string& word) {
    std::string population;
    int pop;
    int gallons;
    int gallons_r;

    population = word;

    for (int i = 0; i < word.length(); i++) {
        if (word[i] == ',') {
            std::string temp = population.substr(0, i);
            temp += population.substr(i + 1, population.length() - temp.length());
            population = temp;
        }
        pop = stoi(population);
        data.population = pop;
    }

    file_reader >> word;
    gallons = stoi(word);
    data.gallons_per_capita = gallons;
    file_reader >> word;
    gallons_r = stoi(word);
    data.gallons_per_resident = gallons_r;
}

//Dylan Chiu //Works
//Last updated: 04/24/23
void file_parser(HashTable& dataset) {
    std::ifstream file_reader("water_table.txt");
    std::string word;

    while (file_reader >> word) {
        City data;
        std::string name;
        //Gets the name of the district
        while (!isdigit(word[0])) {
            //If a comma is found, takes the word and puts it into a temp. 
            //Places the "City of" in the front of the city name.
            if (word.find(",") != std::string::npos) {
                name = word;
                std::string temp = name;
                name = "City of ";
                name += temp;
                file_reader >> word;
                file_reader >> word;
                file_reader >> word;
            //Puts the name together normally.
            } else {
                name += word;
                name += " ";
                file_reader >> word;
            }
        }

        //concatenates any spaces or commas
        name = name.substr(0, name.length() - 1);
        data.city_name = name;
        //Gets the number statistics then insert the structure to the data set
        get_num_statistics(file_reader, data, word);
        dataset.insert(data);
        
        //Ignores the rest of the line if there are anything leftover, this assumes that the user has inputted 0 and % together.
        //IF ANY OF YOU GUYS HAVE A BETTER WAY TO DO THIS WITHOUT HARDCODING, LET ME KNOW
        if (file_reader >> word) {
            std::string line;
            getline(file_reader, line);
            int pos_cutoff;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '0' && line[i + 1] == '%') {
                    pos_cutoff = line.length() - i;
                    break;
                }
            }
            file_reader.ignore(pos_cutoff, '\n');
        }
    }
    file_reader.close();
}

//Dylan Chiu
//Last updated: 04/24/23
int main() {
    std::string user_choice;
    const int WATER_RESEVOIR_LEVEL = 16000000;
    const int NBUCKETS = 599;
    HashTable dataset(NBUCKETS);
    BinaryTree QNA_tree;
    file_parser(dataset);
    set_qna_tree(QNA_tree);
    std::unordered_map <int, std::unordered_set<std::string>> survey_questions;
    set_up_survey(survey_questions);
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
            survey();
        }

        std::cout << "Would you like to run the program again? (Y/N) ";
        std::cin >> user_choice;
    }

    std::cout << "We hope you enjoy using this program!" << std::endl;
    dataset.delete_table();
    QNA_tree.delete_tree(QNA_tree.get_root());
}