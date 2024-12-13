#include "Vocabulary.h"

//----------------------------------------------------------------------------------------------------------------------
///Created workspace.
///Prefer to use to forego errors with path`s
void Vocabulary::createWorkSpace() const {

    try {

        if (!fs::exists(vocabulariesFolder)) {
            fs::create_directory(vocabulariesFolder);
            std::cout << "Created vocabularies folder " << vocabulariesFolder << "\n";
        }
        if (!fs::exists(saveFolder)) {
            fs::create_directory(saveFolder);
            std::cout << "Created save folder " << saveFolder << "\n";
        }


        fs::path testVocabulary = vocabulariesFolder / "testVocabulary.txt";
        fs::path testSave = saveFolder / "testSave.txt";


        std::ofstream outFile1(testVocabulary);
        outFile1 <<"ThisIsYourTestVocabulary - ЦеТвійТестовийСловник";
        outFile1.close();

        std::ofstream outFile2(testSave);
        outFile2 <<"ThisIsYourTestSave - ЦеТвійТестовийФайлЗбереження";
        outFile2.close();

        std::cout << "Files created successfully" << std::endl;


    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}


//----------------------------------------------------------------------------------------------------------------------
///This method load vocabularies a from file system directory
void Vocabulary::load(std::string file_name) {

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

//----------------------------------------------------------------------------------------------------------------------
///Saved current vocabulary in save directory
void Vocabulary::save(std::string file_name) {
    if (file_name.empty()) {
        std::cerr << "File name cannot be empty" << std::endl;
        return;
    }

    if (!empty()) {
        //std::ofstream file(saves_Directory + file_name);
        std::ofstream file("testFloppa.txt");

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

//----------------------------------------------------------------------------------------------------------------------
///Added new word pair in current vocabulary
void Vocabulary::add(Word_pair &pair) {
    push_back(pair);
}

//----------------------------------------------------------------------------------------------------------------------
///Deleted word pair from vocabulary by id
void Vocabulary::delete_pair(size_t index) {
    erase(this->begin() + index);
}

//----------------------------------------------------------------------------------------------------------------------
///Loaded names of vocabularies from chosen directory in vector.
void Vocabulary::initialize_vocabs_from_directory() {


    try {
        for (const auto& entry : fs::directory_iterator(vocab_directory)) {
            // std::cout << entry.path().filename() << std::endl;
            vocabularies.push_back(entry.path().filename().string());
        }
    } catch (const fs::filesystem_error& e) {
        std::cout<< "Error: " << e.what() << std::endl;
    }
}

//----------------------------------------------------------------------------------------------------------------------
/// Allow to select vocabulary from list of available ones that was loaded before
void Vocabulary::chose_vocabulary() {

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

//----------------------------------------------------------------------------------------------------------------------
/// Allow to get path to current vocabulary's directory
std::string Vocabulary::get_vocab_directory() const {
    return vocab_directory;
}

//----------------------------------------------------------------------------------------------------------------------
/// Allow to set directory from which vocabularies will be loaded
void Vocabulary::set_vocab_directory(const std::string &vocab_directory) {
    this->vocab_directory = vocab_directory;
}
