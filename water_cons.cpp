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

int calculation(std::string y_n_chain) {
    std::ifstream gallons_file("questions_gallons_used.txt");
    std::string line;
    int gallons = 0;
    int pos = 0;
    while (getline(gallons_file, line)) {
        if (y_n_chain[pos] == 'Y') {
            gallons += stoi(line);
        }
        pos++;
    }

    /*Calculate the user's gallons per day based on their yes or no question or personal information
    if (personal information) {
        Calculate each personal information into a gallons used per day
    } else {
        Calculate based on the yes or no question (assume the max gallons used)
    }
    return the gallons used per day
    */
   return gallons;
}

//Dylan Chiu //Works
//Last modified: 04/26/23
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
//Needs to be improved to be tailor made. Only prints out the general category.
void print_tips(std::string num_code, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
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

//Dylan Chiu
void survey_input(std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    const int DAYS_IN_YEAR = 365;
    const int HOUSE_WATER_PER_YEAR = 109500;
    const int EFFICIENT_WATER_PER_YEAR = 87600;
    std::ifstream questions("questions_input.txt");
    std::string line;
    int gallons;
    int total;
    std::cout << "Please gather the necessary data to input your gallons usage!" << std::endl;
    std::cout << "Here are the questions! (Input 0 if you do not use/have)" << std::endl;
    while (getline(questions, line)) {
        std::cout << line << std::endl;
        std::cin >> gallons;
        total += gallons;
    }

    total *= DAYS_IN_YEAR;
    std::cout << "This is how many gallons you would use per year! Gallons used: ";
    std::cout << total << std::endl;
    if (total > HOUSE_WATER_PER_YEAR) {
        std::cout << "You're using too much water! Consider buying more water efficient appliances!" << std::endl;
    } else if (total < HOUSE_WATER_PER_YEAR && total > EFFICIENT_WATER_PER_YEAR) {
        std::cout << "You're using the average amount. Not bad but you can cut it down more!" << std::endl;
    } else if (total < EFFICIENT_WATER_PER_YEAR) {
        std::cout << "You're doing great with water conservation! Keep up the good work!" << std::endl;
    }
}

//Dylan Chiu //Works
//Last modified: 04/29/23
void survey_question(BinaryTree& QNA_tree, std::string& choice, 
    std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    const int QUESTIONS_PER_CATEGORY = 5;
    const int HOUSE_WATER_PER_YEAR = 109500;
    const int EFFICIENT_WATER_PER_YEAR = 87600;
    using namespace std;
    string answer;
    string y_n_chain;
    string line;
    ifstream questions_parse("questions.txt");
    int gallons;

    //Gets 
    while (getline(questions_parse, line)) {
        cout << line << endl;
        cin >> answer;
        y_n_chain += answer;
    }

    //Find way without hardcoding or having a const
    string y_n_categories;
    y_n_categories += y_n_chain[0];
    y_n_categories += y_n_chain[QUESTIONS_PER_CATEGORY - 1];
    y_n_categories += y_n_chain[QUESTIONS_PER_CATEGORY * 2 - 1];
    y_n_categories += y_n_chain[QUESTIONS_PER_CATEGORY * 3 - 1];
    string num_code;

    num_code = QNA_tree.get_data(QNA_tree.get_root(), y_n_categories, 0);
    cout << "Combining with our survey, we have calculated how much water you used ";
    cout << "(This is how many gallons used per year assuming you use them everyday)!" << endl;
    gallons = calculation(y_n_chain);
    cout << "You use " << gallons << " gallons per year!" << endl;
    if (gallons > HOUSE_WATER_PER_YEAR) {
        cout << "You use more water than the average American household, consider cutting it down!" << endl;
    } else if (gallons <= HOUSE_WATER_PER_YEAR && gallons > EFFICIENT_WATER_PER_YEAR) {
        cout << "You use the average amount of water. Not bad but you can save more money and water!" << endl;
    } else if (gallons < EFFICIENT_WATER_PER_YEAR) {
        cout << "You use less water than the average! Keep up the great work!" << endl;
    }
    
    cout << "Above all, we also will give you some tips on how to save more water!" << endl;
    print_tips(num_code, survey_tips);
}

//Dylan Chiu
//Last modified 04/26/23
void survey(BinaryTree& QNA_tree, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    std::string choice;
    std::cout << "By taking the survey, you can get tips that are personalized to help you lower your water bill!" << std::endl;
    std::cout << "By lowering your water bill, you can help conserve water as well!" << std::endl;
    while (true) {
        std::cout << "Would you like to use your personal information or would you like to answer some yes or no questions? ";
        std::cout << "(1 for personal information, 2 for questions)" << std::endl;
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "Please input the information pertaining to these questions to the gallon." << std::endl;
            survey_input(survey_tips);
        } else {
            std::cout << "Answer these simple yes or no questions and we will calculate the gallons used by you! ";
            std::cout << "(All must be answered with Y/N)" << std::endl;
            survey_question(QNA_tree, choice, survey_tips);
        }

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

void timer() {
    /*
    */
}

void heap_sort() {

}

//Sana
//Edit: 4/25/23
//Edit2: 4/29/23
//Edit3: 5/1/23
void statistics(HashTable& dataset, const int WATER_RESEVOIR_LEVEL) {
    while (true) {
        std::string name;
        std::string choice;
        std::cout << "Do you want to see the statistics of a county or compare? (1 for a single county, 2 for compare) ";
        std::cin >> choice;
        if (choice == "1") 
        {
            std::cout << "What county do you want to view? (Type in the full name) ";
            std::cout << "if it is \"City of\", put City of first then the name) ";
            std::cin >> name;
            while (!dataset.find_city(name)) 
            {
                std::cout << "Could not find city name :(\nPlease try again(Type in the full name): ";
                std::cin >> name;
            }
            
            City temp = dataset.get_city(name);     //temp just holds the data for the city that we will display
            std::cout << temp.city_name << "\nPopulation: " << temp.population << "\nGallons per Capita: " << temp.gallons_per_capita << "\nGallons per Resident: " << temp.gallons_per_resident << "\n"; 
                                    
        } 
        if (choice == "2") 
        {
            name = "";
            bool done = false;
            Queue cities_to_be_compared;
            do
            {
                std::cout << "What counties do you want to compare? (Enter '0' to exit) ";
                std::cin >> name;
                
                if (name == "0") {done = true;}
                if (dataset.find_city(name)) //if the user input  matches our database name 
                {
                    cities_to_be_compared.push(name);
                }
                
            } while (!done);

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
 * 
*/
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
    std::string user_choice; //Holds the user's choice
    const int WATER_RESEVOIR_LEVEL = 16000000; //The current resevoir level
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