#ifndef WORD_PAIR_H
#define WORD_PAIR_H

#include <string>


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



#endif //WORD_PAIR_H
