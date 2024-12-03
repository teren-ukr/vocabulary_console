#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <sstream>

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


    //--------------------------------------CONSTRUCTORS

    Vocabulary() {

    }


    //--------------------------------------METHODS

    void load(std::string file_name)  {

        std::string path = "../vocabularies/" + file_name;
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

    void chose_vocabulary_from_directory() {

    }












    //--------------------------------------GETTERS AND SETTERS

    [[nodiscard]] std::string get_vocab_directory() const {
        return vocab_directory;
    }

    void set_vocab_directory(const std::string &vocab_directory) {
        this->vocab_directory = vocab_directory;
    }


};




//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- MAIN
int main() {

    system("chcp 65001"); // Установити кодову сторінку UTF-8


    Word_pair s ("s","s");

    std::cout << s.first << " " << s.second << std::endl;


    Vocabulary vocabulary;
    vocabulary.set_vocab_directory("vocabulary");

    vocabulary.load("example.txt");

    for (const auto& pair : vocabulary) {
        std::cout << pair.word() << " " << pair.translate() << std::endl;
    }

    //todo - оформити запис в словник








    return 0;
}
