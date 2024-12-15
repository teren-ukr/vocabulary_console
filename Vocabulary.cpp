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

    // std::string path = vocab_directory +
    //std::string path = vocabulariesFolder.generic_string() + file_name;

    std::string path = vocabulariesFolder.generic_string() +"\\" +file_name;

    //saved paths data
    //this->current_open_file = path;
    this->currentOpenVocabularyName = file_name;

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
        fs::path save = saveFolder / file_name;

        std::ofstream outFile1(save);
        for (const Word_pair& pair: *this) {
            outFile1 << pair.word() << " - " << pair.translate() << std::endl;
        }
        outFile1.close();

        std::cout << "Vocabulary saved successfully" << std::endl;
    }
    else {
        std::cout<<"Vocabulary is empty."<<std::endl;
    }

}


//----------------------------------------------------------------------------------------------------------------------
///Create new vocabulary in vocabulary directory
void Vocabulary::createVocabulary(std::string name) {
    if (name.empty()) {
        std::cerr << "File name cannot be empty" << std::endl;
        return;
    }


    fs::path save = vocabulariesFolder / name;

    std::ofstream outFile1(save);
    outFile1.close();

    std::cout << "Vocabulary created successfully" << std::endl;
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
        for (const auto& entry : fs::directory_iterator(vocabulariesFolder)) {
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

    auto lengthUTF8 = [](const std::string &s) {
        int count = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            // Якщо це не байт продовження (0x80 - 0xBF), значить, це новий символ
            if ((s[i] & 0xC0) != 0x80) {
                ++count;
            }
        }
        return count;
    };
    auto nms =[lengthUTF8](const std::string &name, const uint8_t bnum) {
        return bnum - lengthUTF8(name); ;
    };
    auto nmi =[](const int &id, const uint8_t &bnum) {
        return bnum - std::to_string(id).length();
    };
    auto prs =[](const int &num, const char &symbol ) {
        for (int i = 0; i < num; ++i) {
            std::cout << symbol;
        }
        return "";
    };



    initialize_vocabs_from_directory();
    if (vocabularies.empty()) {
        std::cout<< "Vocabulary list is empty" << std::endl;
        return;
    }

    std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║ Chose vocabulary from list:                                                         ║" << std::endl;
    std::cout << "╬════╬════════════════════════════════════════════════════════════════════════════════╬" << std::endl;
    std::cout << "║ No ╬ Vocabulary Name                                                                ║" << std::endl;
    std::cout << "╬════╬════════════════════════════════════════════════════════════════════════════════╬" << std::endl;


    for (int i = 0; i < vocabularies.size(); i++) {
        // Виведення індексу та назви, обмеженої max_length символами
        // std::string truncated_vocab = vocabularies[i];
        // printf("║ %-3d ╬ %-*s ║\n", i, 80, truncated_vocab.c_str());

        int ad_to_id = nmi(i,3);
        int ad_to_vocub = nms(vocabularies[i],79);

        //printf("║ %-*d ╬ %-*s ║\n", nmi(i), i, nms(vocabularies[i]), vocabularies[i].c_str());
        //std::cout << vocabularies[i]<<lengthUTF8(vocabularies[i]) << std::endl;

        std::cout << "║ "<< i << prs(ad_to_id,' ') <<"╬ " <<vocabularies[i] <<prs(ad_to_vocub,' ') <<"║"<<std::endl;
    }

    std::cout << "╬════╬════════════════════════════════════════════════════════════════════════════════╬" << std::endl;
    std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;




    std::cout << "► Enter your choice: ";  // Створка для введення дії
    int choice;
    std::cin >> choice;

    if (choice > 0 && choice - 1 <= vocabularies.size())
        load(vocabularies[choice - 1]);

}

//----------------------------------------------------------------------------------------------------------------------
/// Allow to get path to current vocabulary's directory
std::string Vocabulary::get_vocab_directory() const {
    return vocabulariesFolder.generic_string();
}

//----------------------------------------------------------------------------------------------------------------------
/// Allow to set directory from which vocabularies will be loaded
void Vocabulary::set_vocab_directory(const std::string &vocab_directory) {
    this->vocabulariesFolder.generic_string() = vocab_directory;
}
