#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------------------
class Word_pair;
class Vocabulary;

//----------------------------------------------------------------------------------------------------------------------
///class Word_pair
class Word_pair : public std::pair<std::string, std::string>{
public:
    Word_pair(const std::string word, const std::string translate)  {
        this->first = word;
        this->second = translate;
    }

    void set_word(const std::string& word) {
        this->first = word;
    }

    void set_translate(const std::string& translate) {
        this->second = translate;
    }


    first_type word() const {
        return first;
    }

    second_type translate() const {
        return second;
    }

};


//----------------------------------------------------------------------------------------------------------------------
class Vocabulary : public std::vector<Word_pair>{
public:

    //--------------------------------------VARIABLES

    std::string vocab_directory;
    std::vector<std::string> vocabularies;
    std::string saves_Directory = "..saves/";
    std::string current_open_file = "";


    //--------------------------------------CONSTRUCTORS

    Vocabulary() {

    }


    //--------------------------------------METHODS

    void load(std::string file_name) {
        if (!empty())
            clear(); //if vocabulary was used,we clean it;

        //Clear vocabularis list before load
        if (vocabularies.size() != 0)
            vocabularies.clear();

        std::string path = vocab_directory + file_name;
        this->current_open_file = path;
        std::printf("Loading vocabulary from %s\n", path.c_str());
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "Could not open file " << file_name << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {

            size_t pos = line.find('-');

            if (pos != std::string::npos) {

                std::string line1 = line.substr(0, pos);
                std::string line2 = line.substr(pos + 1);
                Word_pair pair (line1, line2);
                push_back(pair);
            }
        }

        file.close();
    }


    void save(std::string file_name) {
        if (file_name.empty()) {
            std::cerr << "File name cannot be empty" << std::endl;
            return;
        }

        if (!empty()) {
            std::ofstream file(saves_Directory + file_name);

            if (!file.is_open()) {
                std::cerr << "Could not open new created file " << file_name << std::endl;
                return;
            }


            for (const Word_pair& pair: *this) {
                file << pair.word() << " " << pair.translate() << std::endl;
            }

            std::cout << "Vocabulary was saved to saves folder" << std::endl;
            file.close();
        }
        else {
            std::cerr << "Vocabulary is empty" << std::endl;
            return;
        }
    }


    void add(Word_pair &pair) {
        push_back(pair);
    }

    void delete_pair(size_t index){
        erase(this->begin() + index);
    }



    void initialize_vocabs_from_directory() {
        namespace fs = std::filesystem;

        try {
            for (const auto& entry : fs::directory_iterator(vocab_directory)) {
               // std::cout << entry.path().filename() << std::endl;
                vocabularies.push_back(entry.path().filename().string());
            }
        } catch (const fs::filesystem_error& e) {
            std::cout<< "Error: " << e.what() << std::endl;
        }
    }

    //this method loaded avaible vocabulary save
    void chose_vocabulary() {

        initialize_vocabs_from_directory();
        if (vocabularies.empty()) {
            std::cout<< "Vocabulary list is empty" << std::endl;
            return;
        }

        std::cout<< "Chose vocabulary from list: " << std::endl;
        for (int i = 0; i < vocabularies.size(); i++) {
            std::cout << i + 1 << " - " << vocabularies[i] << std::endl;
        }

        int choice;
        std::cout<<"Chosed :";
        std::cin >> choice;

        if (choice > 0 && choice - 1 <= vocabularies.size())
            load(vocabularies[choice - 1]);

    }




    //--------------------------------------GETTERS AND SETTERS

    [[nodiscard]] std::string get_vocab_directory() const {
        return vocab_directory;
    }

    void set_vocab_directory(const std::string &vocab_directory) {
        this->vocab_directory = vocab_directory;
    }


};

void pause () {
    std::cout << "\nPress any key to continue...";
    uint8_t a;
    std::cin>>a;
}

void clear_console() {
    if (system("clear")) system( "cls" );
}

void vocabulary_menu(Vocabulary &vocabulary) {

    clear_console();

    while (true) {
        int choise;
        std::cout << "Please, chose what you want to do: " << std::endl;
        std::cout << "1. Print all words" << std::endl;
        std::cout << "2. Add" << std::endl;
        std::cout << "3. Remove" << std::endl;
        std::cout << "4. Save " << std::endl;
        std::cout << "5. Delete windows OS " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;

        //print all words
        size_t index = -1;
        for (Word_pair pair : vocabulary) {
            index++;
            std::cout <<"["<< index <<"]\t" << pair.word() << "\t\t\t\t - " << pair.translate() << std::endl;
        }

        std::cout << "-----------------------------------------------------------------------------------" << std::endl;


        //Get chosen
        std::cout << "Please, chose what you want to do: " << std::endl;
        std::cin >> choise;





        //vocabulary menu
        switch (choise) {
            case 1: {


                size_t index = -1;
                for (Word_pair pair : vocabulary) {
                    index++;
                    std::cout <<"["<< index <<"]\t" << pair.word() << "\t\t\t\t - " << pair.translate() << std::endl;
                }


                pause();
                break;
            }

            case 2: {

                std::string word;
                std::string translate;

                std::cout <<"Enter a word:";
                std::cin >> word;
                std::cout <<"Enter a translate:";
                std::cin >> translate;

                Word_pair pair (word, translate);
                vocabulary.add(pair);
                break;
            }

            case 3: {
                int word_id;
                std::cout << "Enter word ID: "  ;
                std::cin >> word_id;

                if (word_id >= 0 && word_id <= vocabulary.size()) {
                    vocabulary.delete_pair(word_id);
                }
                else
                    {std::cout<< "Invalid word ID" << std::endl;}

                break;
            }

            case 4: {
                std::cout << "\n\n\nSaving..." << std::endl;
                vocabulary.save(vocabulary.current_open_file);
                break;
            }

            case 5: {
                std::cout << "\n\n\nProgram was finished, for exit type any key";
                uint8_t exit;
                std::cin >> exit;
                return;
                break;
            }

        }
        clear_console();
    }

}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- MAIN
int main() {
    system("chcp 65001"); // Установити кодову сторінку UTF-8

    Vocabulary vocabulary;



    while (true) {
        int choise;
        std::cout << "Please, chose what you want to do: " << std::endl;
        std::cout << "1. load vocabulary" << std::endl;
        std::cout << "2. save vocabulary" << std::endl;
        std::cout << "3. chose directory" << std::endl;
        std::cout << "4. exit" << std::endl;
        std::cin >> choise;

        switch (choise) {
            case 1: {
                std::cout << "Do you would prefer use basic vocabulary or load your own?" << std::endl;
                std::cout << "1. Basic vocabulary" << std::endl;
                std::cout << "2. Load your own" << std::endl;

                int ch;
                std::cin >> ch;
                if (ch == 1) {
                    vocabulary.set_vocab_directory("../vocabularies/");
                } else {
                    std::cout << "write your directory path" << std::endl;
                    noskipws(std::cin); //disabled spase skip
                    std::string path;
                    std::cin >> path;
                    vocabulary.set_vocab_directory(path);
                    break;
                }


                vocabulary.chose_vocabulary();
                vocabulary_menu(vocabulary);
                pause();
                break;
            }


            case 2: {
                std::cout << "this function is not available" << std::endl;
                break;
            }

            case 3: {
                std::cout << "write your directory path" << std::endl;
                noskipws(std::cin); //disabled spase skip
                std::string path;
                std::cin >> path;
                vocabulary.set_vocab_directory(path);
                break;
            }

            case 4: {
                std::cout << "\n\n\nProgram was finished, for exit type any key";
                uint8_t exit;
                std::cin >> exit;
                break;
            }

        }
       clear_console();
    }


    //todo - доробити збереження і додавання, додає каряво дублює файли скоріше за все проблема в шляху. додати пауезу до роботи з файлами

    //ВІДКРИТТЯ СЛОВНИКА З ФАЙЛУ        90% доробити відкриття по посиланню на папку

    //ДОДАВАННЯ НОВОГО СЛОВА            100%
    //ЗБЕРЕЖЕННЯ СЛОВНИКА               20% створено клас
    //ВИДАЛЕННЯ СЛОВА                   100%


}
