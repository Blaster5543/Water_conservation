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
 * Calculates the gallons used based on the user's yes or no answers
 * @param y_n_chain The string of answers from the user
 * @param least_gal The map that connect the answer to the 
*/
double calculation(std::string y_n_chain, std::unordered_map<std::string, double>& least_gal, 
        std::unordered_map<std::string, double> most_gal, double category_gallons[4]) {
    std::ifstream questions("questions.txt");
    std::string line;
    double gallons = 0;
    int pos = 0;
    int category = 0;
    int question = 0;

    //Gets the question and the gallons used
    while (getline(questions, line)) {
        //If user answered yes, adds the largest gallon used, otherwise adds the lesser one.
        if (y_n_chain[pos] == 'Y') {
            gallons += most_gal[line];
            category_gallons[category] += most_gal[line];
        } else {
            gallons += least_gal[line];
            category_gallons[category] += least_gal[line];
        }
        pos++;
        question++;
        //Changes the category based on the questions
        if (question == 3 || question == 7 || question == 11) {
            category++;
        }
    }

    return gallons;
}

//Dylan Chiu
//Last modified: 05/01/23
/**
 * Calculates the gallons used based on the user's inputted numbers
 * @param answer The double answer that is gained from the user
 * @param pos The question being asked
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

    //Calculates based on the time or frequency
    if (line.find("long") != std::string::npos) {
        gallons = stoi(gallon_amount);
        gallons *= ((answer / 60) * 3) * 365;
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

    //Changes the category based on the tips being found
    while (getline(tips_finder, line)) {
        if (line.find("Washroom") != std::string::npos) {
            category = washroom_category;
        } else if (line.find("Garden") != std::string::npos) {
            category = garden_category;
        } else if (line.find("Kitchen") != std::string::npos) {
            category = kitchen_category;
        } else if (line.find("Outdoor") != std::string::npos) {
            category = outdoor_category;
        } else if (line.find("General") != std::string::npos) {
            category = general_category;
        }

        //Checks if the line is not empty
        if (!line.empty()) {
            //Checks if the category is the same and does not contain the category name 
            //(prevents the category name from being added)
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

    //Adds each set to the part of the map
    survey[washroom_category] = washroom_tips;
    survey[garden_category] = garden_tips;
    survey[kitchen_category] = kitchen_tips;
    survey[outdoor_category] = outdoor_tips;
    survey[general_category] = general_tips;
}

//Dylan Chiu //Works
/**
 * Gets the gallons used for each question based on the answer.
*/
void set_up_survey_gallons(std::unordered_map <std::string, double>& survey_most, 
    std::unordered_map<std::string, double>& survey_least) {
        std::ifstream gallons("questions_gallons_used.txt");
        std::ifstream questions("questions.txt");
        std::string line;
        std::string question;
        //Gets the gallons for each question
        while (gallons >> line) {
            getline(questions, question);
            double gal = stoi(line);
            survey_least[question] = gal;
            gallons >> line;
            gal = stoi(line);
            survey_most[question] = gal;
        }
}

//Dylan Chiu
/**
 * Prints out the tips of a category the user wasted the most water on
 * @param num_code the categories the user has answered that they wasted the most water on
 * @param category_gallons the gallons wasted per category
 * @param survey_tips the tips to send to the user on what they can do on conserving water
*/
void print_categories_tips(std::string num_code, double category_gallons[],
    std::unordered_map <int, std::unordered_set<std::string>>& survey_tips, std::string y_n_chain) {
    std::vector<int> category;
    std::unordered_set<std::string> tips_to_print;
    double gallons;

    //Gets the category to print
    for (int i = 0; i < num_code.length(); i++) {
        std::string temp = num_code.substr(i, 1);
        category.push_back(stoi(temp));
    }

    //Finds which category wastes the most water
    while (category.size() != 0) {
        double most_gallons = category_gallons[0];
        int pos = 0;
        for (int i = 0; i < category.size(); i++) {
            if (category_gallons[category[i]] > most_gallons) {
                most_gallons = category_gallons[category[i]];
                pos = i;
            }
        }

        //Iterates through the set to print out the tips if the user answered yes.
        int string_pos;
        tips_to_print = survey_tips[pos];
        for (auto iter : tips_to_print) {
            if (y_n_chain[string_pos] == 'Y') {
                std::cout << iter << std::endl;
            }
            string_pos++;
        }

        //Holds the position of the category with the most gallons used then removes the category from the vector
        int temp = category[pos];
        category[pos] = category[category.size() - 1];
        category[category.size() - 1] = temp;
        category.pop_back();

        std::cout << "Would you like to view more tips? (Y/N) " << std::endl;
        std::string answer;
        std::cin >> answer;
        if (answer == "Y" && category.size() != 1) {
            continue;
        } else if (category.size() == 1) { //Breaks from the loop if there are no more tips
            std::cout << "We don't have any more tips for you!";
            break;
        } else {
            break;
        }
    }
}

//Dylan Chiu
/**
 * Prints a response to how much water the user used
*/
void response(double gallons, const int HOUSE_WATER_PER_YEAR, const int EFFICIENT_WATER_PER_YEAR, const double COST_PER_GALLON) {
    using namespace std;
    cout << "Combining with our survey, we have calculated how much water you used ";
    cout << "(This is how many gallons used per year assuming you use them everyday)!" << endl;
    cout << "You use " << gallons << " gallons per year!" << endl;
    //Gives a response based on the const int
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

    //Prints out the amount of money they could save
    if (gallons > EFFICIENT_WATER_PER_YEAR) {
        cout << endl;
        cout << "And this is how much money you could save! ";
        double money_saved = (gallons * COST_PER_GALLON) - (EFFICIENT_WATER_PER_YEAR * COST_PER_GALLON);
        cout << "$" << money_saved << endl;
    }
}

//Dylan Chiu //Works
//Last modified 04/30/23
/**
 * Prints out the general tips to conserve water
 * @param survey_tips: The map needed to print out the general tips
 */
void print_general_tips(std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    std::unordered_set<std::string> tips_to_print;
    tips_to_print = survey_tips[5];
    for (auto iter : tips_to_print) {
        std::cout << iter << std::endl;
    }
}

//Dylan Chiu
/**
 * Prints out the tips for the input survey
*/
std::string print_input_tips(double answer, int pos) {
    std::ifstream recommend_gal("input_recommend_use.txt");
    std::ifstream tips("recommend_input.txt");
    std::string gal;
    std::string tip;
    double gallons = 0.0;
    for (int i = 0; i <= pos; i++) {
        getline(recommend_gal, gal);
        getline(tips, tip);
    }

    gallons = stod(gal, NULL);

    if (gallons > answer) {
        return tip;
    } else {
        return "";
    }
}

//Dylan Chiu
/**
 * Allows the user to input their own information into the survey
 * @param survey_tips: The map needed to print out the general tips
*/
void survey_input() {
    using namespace std;
    const int HOUSE_WATER_PER_YEAR = 65000;
    const int EFFICIENT_WATER_PER_YEAR = 45000;
    const double COST_PER_GALLON = 0.007;
    ifstream questions("questions_input.txt");
    string line;
    double answer = 0;
    double total = 0;
    int pos = 0;
    Queue tips_to_print;

    //Gets the input from the user along with the question and tips
    cout << "Here are the questions!" << endl;
    cout << "(Input 0 if you do not use/have, input -1 if you aren't sure (This assume standard or average))" << endl;
    while (getline(questions, line)) {
        cout << line << endl;
        cin >> answer;
        total += calculation(answer, pos);
        double gal = calculation(answer, pos);
        std::string tip = print_input_tips(gal, pos);
        tips_to_print.push(tip);
        pos++;
    }

    response(total, HOUSE_WATER_PER_YEAR, EFFICIENT_WATER_PER_YEAR, COST_PER_GALLON); //Responds to the user's water usage

    //Prints out three tips
    std::cout << "We also have some tips for you!" << std::endl;
    for(int i = 0; i < tips_to_print.size(); i++) {
        if (i == 2) {
            break;
        }
        std::string tip = tips_to_print.front();
        std::cout << tip << std::endl;
        tips_to_print.remove();
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
    const int HOUSE_WATER_PER_YEAR = 65000;
    const int EFFICIENT_WATER_PER_YEAR = 45000;
    const double COST_PER_GALLON = 0.007;
    using namespace std;
    string answer;
    string y_n_chain;
    string line;
    ifstream questions_parse("questions.txt");
    double gallons;
    string num_code;
    std::unordered_map<std::string, double> survey_most_gallons_used;
    std::unordered_map<std::string, double> survey_least_gallons_used;
    double category_gallons[4];

    set_up_survey_gallons(survey_most_gallons_used, survey_least_gallons_used);

    //Gets the questions from the text file to give to the user to answer
    while (getline(questions_parse, line)) {
        if (line == "\n") {
            break;
        } else {
            cout << line << endl;
            cin >> answer;
            if (islower(answer[0])) {
                answer = toupper(answer[0]);
            }
            y_n_chain += answer; //Adds user's answers to the string
        }
    }

    //Gets the answers from the user and puts them into the category they answered in
    string y_n_categories;
    for (int i = 0; i < y_n_chain.length(); i++) {
        int questions_per_category = 0;
        bool category_answered = false;
        if (i == 1) {
            questions_per_category = 3;
        } else {
            questions_per_category = 4;
        }

        for (int j = 0; j < questions_per_category; j++) {
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
    gallons = calculation(y_n_chain, survey_most_gallons_used, survey_least_gallons_used, category_gallons);

    //Outputs how much gallons the user uses and tells them if they're above average, average, or efficient
    response(gallons, HOUSE_WATER_PER_YEAR, EFFICIENT_WATER_PER_YEAR, COST_PER_GALLON);

    cout << endl;
    cout << "Above all, we also will give you some tips on how to save more water!" << endl;
    cout << "Would you like to see them? (Y/N)";
    cin >> answer;
    if (answer == "Y") {
        print_general_tips(survey_tips);
    }
}

//Dylan Chiu
//Last modified 04/26/23
void survey(BinaryTree& QNA_tree, std::unordered_map <int, std::unordered_set<std::string>>& survey_tips) {
    std::string choice;
    std::cout << "By taking the survey, you can get tips that are personalized to help you lower your water bill!" << std::endl;
    std::cout << "By lowering your water bill, you can help conserve water as well!" << std::endl;
    //Gives the user a choice for personal information or questions
    while (true) {
        std::cout << "Would you like to use your personal information or would you like to answer some yes or no questions? ";
        std::cout << "(1 for personal information, 2 for questions, enter 3 to go back)" << std::endl;
        std::cin >> choice;
        if (choice == "1") {
            std::cout << "Please input the information pertaining to these questions to the gallon." << std::endl;
            survey_input();
        } else if (choice == "2") {
            std::cout << "Answer these simple yes or no questions and we will calculate the gallons used by you! ";
            std::cout << "(All must be answered with Y/N, if you aren't sure, type in N)" << std::endl;
            survey_question(QNA_tree, survey_tips);
        } else if (choice == "3") {
            return;
        }

        std::cout << "Would you also like some general tips to save water? (Y/N) ";
        std::cin >> choice;
        if (choice == "Y") {
            print_general_tips(survey_tips);
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
    cout << " " << setw(10) << temp.city_name << " " << setw(50) << compare.city_name << endl;
    cout << "Population: " << temp.population  << setw(50) << compare.population << endl;
    cout << "Gallons per Capita: " << temp.gallons_per_capita << setw(40) << compare.gallons_per_capita << endl;
    cout << "Gallons per Resident: " << temp.gallons_per_resident << setw(39) << compare.gallons_per_resident << endl;
}

//Sana //Works
//Last updated: 05/03/23
/**
 * Prints the amount of years the city has left before it runs out of water.
*/
void timer(City city_data, int resLevel) 
{
    int years_left = resLevel / (city_data.gallons_per_capita);
    std::cout << "City's water level will last them " << years_left << " years!\n";
}

void swap(std::vector<City>& vec, int x, int y)
{  
   City temp = vec[x];
   vec[x] = vec[y];
   vec[y] = temp;
}

int partition(std::vector<City>& a, int from, int to)
{
   int pivot = a[from].gallons_per_capita;
   int i = from - 1;
   int j = to + 1;
   while (i < j)
   {
      i++; while (a[i].gallons_per_capita < pivot) { i++; }
      j--; while (a[j].gallons_per_capita > pivot) { j--; }
      if (i < j) { swap(a, i, j); }
   }
   return j;
}

void quicksort(std::vector<City>& city_list, int from, int to)
{
   if (from >= to) { return; }
   int p = partition(city_list, from, to);
   quicksort(city_list, from, p);
   quicksort(city_list, p + 1, to);
}

//Sana
//Edit: 4/25/23
//Edit2: 4/29/23
//Edit3: 5/1/23
void statistics(HashTable& dataset, const int WATER_RESEVOIR_LEVEL, std::vector<City>& city_info) {
    while (true) {
        const int CITIES_PER_LINE = 5;
        std::string name = "";
        std::string choice;
        std::cout << "Do you want to see the statistics of a county, compare mutiply counties, or a sorted list of the most wasteful counties? ";
        std::cout << "(1 for a single county, 2 for compare specific counties, 3 sorted list, 4 to go back):\n";
        std::cin >> choice;
        if (choice == "1") {
            std::cin.ignore(1,'\n');
            std::cout << "What county do you want to view? (Type in the full name exactly as it shows)" << std::endl;
            for (int i = 0; i < city_info.size() - 1; i++) {
                for (int j = 0; j < CITIES_PER_LINE; j++) {
                    std::cout << city_info[i].city_name << " | ";
                    i++;
                }
                std::cout << std::endl;
            }
            getline(std::cin, name);
            while (!dataset.find_city(name)) {
                std::cout << "Could not find city name " << name << ". Please type in the name again. ";
                getline(std::cin, name);
            }
            print_city_info(dataset.get_city(name));
            timer(dataset.get_city(name), WATER_RESEVOIR_LEVEL);
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
                    cities_to_be_compared.remove();
                }

        } else if (choice == "3") {
            quicksort(city_info, 0, city_info.size());
            std::cout << "The top 10 most wasteful cities are: \n";
            for (int i = city_info.size() - 1; i > city_info.size() - 10; i--)
            {
                std::cout << city_info[i].city_name << ":\nGallons per Capita: " << city_info[i].gallons_per_capita << "\n\n";
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
//Sana 5/6/23: added a vector to store all of our city to quicksort later
/**
 * Gets the data from the text files
 * @param HashTable dataset: The HashTable to put the data of the text file into
*/
void file_parser(HashTable& dataset, std::vector<City>& city_vec) {
    std::ifstream file_reader("water_table.txt");
    std::string word;

    int city_counter = 0;

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

        city_vec.push_back(data); //adds to vector for quicksorting

        if (file_reader >> word) {
            file_reader.ignore(300, '\n');
        }
    }


    file_reader.close();
}

//Dylan Chiu
//Last updated: 04/24/23
int main() {
    std::vector<City> city_data; //vector that stores all the city info
    std::string user_choice; //Holds the user's choice
    const int WATER_RESEVOIR_LEVEL = 42069; //The current resevoir level
    const int NBUCKETS = 599; //The hashtable size
    HashTable dataset(NBUCKETS);
    BinaryTree QNA_tree;
    file_parser(dataset, city_data); //inserts the data set into the hash table
    set_qna_tree(QNA_tree); //initializes the binary decision tree
    std::unordered_map <int, std::unordered_set<std::string>> survey_tips;
    set_up_survey(survey_tips);

    std::cout << "Welcome user! This program is designed to help you understand";
    std::cout << " the importance of water conservation! Would you like to use it? (Y/N) ";
    std::cin >> user_choice;
    if (std::cin.fail() || (user_choice != "Y" && user_choice != "N")) {
        std::cout << "Choice does not correspond with any, terminating program" << std::endl;
    }

    while (user_choice == "Y") {
        std::cout << "Great! Would you like to see the statistics of the average water consumption ";
        std::cout << "or take a survey to see your water consumption statistics? (1 for Statistics, 2 for survey) ";
        std::cin >> user_choice;
        if (user_choice == "1") {
            statistics(dataset, WATER_RESEVOIR_LEVEL, city_data);
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