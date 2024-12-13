#include "Word_pair.h"
#include "Vocabulary.h"




//----------------------------------------------------------------------------------------------------------------------
void clear_console() {
    if (system("clear")) system( "cls" );
}

//----------------------------------------------------------------------------------------------------------------------
void vocabulary_menu(Vocabulary &vocabulary) {

    clear_console();

    while (true) {
        int choise;
        std::cout << "Please, chose what you want to do: " << std::endl;
        std::cout << "1. Print all words" << std::endl;
        std::cout << "2. Add" << std::endl;
        std::cout << "3. Remove" << std::endl;
        std::cout << "4. Save " << std::endl;
        std::cout << "5. Return to main menu " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;

        //print all words
        size_t index = -1;
        for (const Word_pair& pair : vocabulary) {
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
                for (const Word_pair& pair : vocabulary) {
                    index++;
                    std::cout <<"["<< index <<"]\t" << pair.word() << "\t\t\t\t - " << pair.translate() << std::endl;
                }

                system("pause");
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
                vocabulary.save(vocabulary.currentOpenVocabularyName);
                system("pause");
                break;
            }

            case 5: {
                return;
            }

        }
        clear_console();
    }

}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- MAIN
int main() {
    system("chcp 65001"); // Установити кодову сторінку UTF-8
    clear_console();


    Vocabulary vocabulary;


    while (true) {
        int choise;
        std::cout << "Please, chose what you want to do: " << std::endl;
        std::cout << "0. Create work space(prefer to use)" << std::endl;
        std::cout << "1. load vocabulary" << std::endl;

        std::cout << "4. exit" << std::endl;
        std::cin >> choise;

        switch (choise) {


            case 0: {
                vocabulary.createWorkSpace();
                system("pause");
                break;
            }

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

    //ВІДКРИТТЯ СЛОВНИКА З ФАЙЛУ        100%
    //ЗАХИСТ "ВІД ДУРАКА".              100%
    //ДОДАВАННЯ НОВОГО СЛОВА            100%
    //ЗБЕРЕЖЕННЯ СЛОВНИКА               100%
    //ВИДАЛЕННЯ СЛОВА                   100%


}
