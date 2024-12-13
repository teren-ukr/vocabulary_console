
#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "Word_pair.h"
namespace fs = std::filesystem;

class Vocabulary : public std::vector<Word_pair>{
public:

    //--------------------------------------VARIABLES

    std::string vocab_directory;
    std::vector<std::string> vocabularies;

    std::string saves_Directory = "..saves/";
    std::string current_open_file = "";


    fs::path currentPath = fs::current_path();
    fs::path vocabulariesFolder = currentPath / "vocabularies";
    fs::path saveFolder = currentPath / "saves";



    //--------------------------------------CONSTRUCTORS

    Vocabulary() {

    }


    //--------------------------------------METHODS

    void createWorkSpace() const;


    void load(std::string file_name);
    void save(std::string file_name);


    void add(Word_pair &pair);
    void delete_pair(size_t index);



    void initialize_vocabs_from_directory();

    //this method loaded avaible vocabulary save
    void chose_vocabulary();


    //--------------------------------------GETTERS AND SETTERS

    [[nodiscard]] std::string get_vocab_directory() const;

    void set_vocab_directory(const std::string &vocab_directory);
};



#endif //VOCABULARY_H
