#include "Word_pair.h"
#include "Vocabulary.h"
#include <windows.h>




//----------------------------------------------------------------------------------------------------------------------
void clear_console() {
    if (system("clear")) system( "cls" );
}

//----------------------------------------------------------------------------------------------------------------------
void vocabulary_menu(Vocabulary &vocabulary) {
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

    auto grs =[](const int &num, const char &symbol) {
        std::string s = "";
        for (int i = 0; i < num; ++i) {
            s.append(" ");
        }
        return s;
    };
    auto mdls =[lengthUTF8, grs](const std::string &str, const uint8_t &num) {
        uint8_t everangeNum = (num - lengthUTF8(str))/2;
         if (everangeNum%2 != 0)
             return grs(everangeNum, ' ') + str + grs(everangeNum+1, ' ');
        return grs(everangeNum, ' ') + str + grs(everangeNum, ' ');
    };

    clear_console();

    while (true) {
        int choise;


        std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "╬═════╬═════════════════════════════════════════════════════╬═════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "║ id   Word                                                  Translate                                            ║" << std::endl;
        std::cout << "╬═════╬═════════════════════════════════════════════════════╬═════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "╬─────────────────────────────────────────────────────────────────────────────────────────────────────────────────╬" << std::endl;


        const uint8_t id_l = 4;
        const uint8_t word_l = 52;
        const uint8_t translate_l = 52;

        //print all words
        size_t index = -1;
        for (const Word_pair& pair : vocabulary) {
            index++;
            //std::cout <<"["<< index <<"]\t" << pair.word() << "\t\t\t\t - " << pair.translate() << std::endl;

            const uint8_t add_index = nmi(index, id_l);
            const uint8_t add_word = nms(pair.word(),word_l);
            const uint8_t add_translate = nms(pair.translate(),translate_l);

            std::cout
            <<"║ "<<index << prs(add_index,' ')
            <<"║ "<<pair.word() <<prs(add_word,' ')
            <<"║ "<<pair.translate() <<prs(add_translate,' ')
            <<"║"
            <<std::endl;
            std::cout << "╬═════╬═════════════════════════════════════════════════════╬═════════════════════════════════════════════════════╬" << std::endl;

        }
        std::cout << "║                                                                                                                 ║" << std::endl;
        std::cout << "║"                                 <<mdls(vocabulary.currentOpenVocabularyName,113)                       <<"║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;

        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ Please, choose what you want to do:                                                                             ║" << std::endl;
        std::cout << "╬═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "║ 1. Print all words                                                                                              ║" << std::endl;
        std::cout << "║ 2. Add                                                                                                          ║" << std::endl;
        std::cout << "║ 3. Remove                                                                                                       ║" << std::endl;
        std::cout << "║ 4. Save                                                                                                         ║" << std::endl;
        std::cout << "║ 5. Save as                                                                                                      ║" << std::endl;
        std::cout << "║ 6. Return to main menu                                                                                          ║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;


        std::cout << "► Enter your choice: ";
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


                std::cout << "╔════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║ Create name to your vocabulary                                         ║" << std::endl;
                std::cout << "╬════════════════════════════════════════════════════════════════════════╬" << std::endl;
                std::cout << "║ You can enter any file type (.txt .mp4 .floppa). Or not to add at all, ║" << std::endl;
                std::cout << "║ program will read id any case.                                         ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "► Enter file name: ";
                std::string filename;
                std::cin >> filename;

                vocabulary.saveAs(vocabulary.saveFolder,filename);

                std::cout << "╔════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║ Show in explorer ?                                                     ║" << std::endl;
                std::cout << "╬════════════════════════════════════════════════════════════════════════╬" << std::endl;
                std::cout << "║ 1  Yes                                                                 ║" << std::endl;
                std::cout << "║ 2. No                                                                  ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "► Enter your choice: ";

                int choice;
                std::cin >> choice;
                if (choice == 1) {
                    vocabulary.openFolder(vocabulary.saveFolder.generic_string());
                    std::cout<<"Opening folder..."<<std::endl;
                }
                else {
                    break;
                }
                system("pause");
                break;
            }

            case 6: {
                return;
            }

        }
        clear_console();
    }

}

void checkWorkFolders() {
    fs::path currentPath = fs::current_path();
    fs::path savefolder = currentPath / "saves";
    fs::path vocabularyfolder = currentPath / "vocabularies";


    if (!fs::exists(savefolder) or fs::exists(vocabularyfolder)) {
        std::cout << savefolder << " the work folders was not created" << std::endl;
        std::cout << "╔════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ the work folders was not created. Create it?                           ║" << std::endl;
        std::cout << "╬════════════════════════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "║ 1  Yes (Folders will be create in the same folder as this program)     ║" << std::endl;
        std::cout << "║ 2. No                                                                  ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "► Enter your choice: ";

    }

}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- MAIN
int main() {
    system("chcp 65001"); // Установити кодову сторінку UTF-8
    clear_console();


    Vocabulary vocabulary;


    while (true) {
        int choise;
        std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║██╗    ██╗ ██████╗  ██████╗ █████╗ ██████╗ ██╗   ██╗██╗      █████╗ ██████╗ ██╗   ██╗║" << std::endl;
        std::cout << "║██║    ██║██╔═══██╗██╔════╝██╔══██╗██╔══██╗██║   ██║██║     ██╔══██╗██╔══██╗╚██╗ ██╔╝║" << std::endl;
        std::cout << "║╚██╗  ██╔╝██║   ██║██║     ███████║██████╔╝██║   ██║██║     ███████║██████╔╝ ╚████╔╝ ║" << std::endl;
        std::cout << "║ ╚██╗██╔╝ ██║   ██║██║     ██╔══██║██╔══██╗██║   ██║██║     ██╔══██║██╔══██╗  ╚██╔╝  ║" << std::endl;
        std::cout << "║  ╚███╔╝  ╚██████╔╝╚██████╗██║  ██║██████╔╝╚██████╔╝███████╗██║  ██║██║  ██║   ██║   ║" << std::endl;
        std::cout << "║   ╚═╝     ╚═════╝  ╚═════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   ║" << std::endl;
        std::cout << "╬═════════════════════════════════════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "║                        Created by https://github.com/teren-ukr                      ║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
        //std::cout << "***If it your first run, use 0 to create work space***" << std::endl;
        std::cout <<  std::endl;
        std::cout << "╔═════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║ Please, choose what you want to do:                                                 ║" << std::endl;
        std::cout << "╬═════════════════════════════════════════════════════════════════════════════════════╬" << std::endl;
        std::cout << "║ 0  Create work space (prefer to use)                                                ║" << std::endl;
        std::cout << "║ 1. Load vocabulary                                                                  ║" << std::endl;
        std::cout << "║ 2. Add new vocabulary                                                               ║" << std::endl;
        std::cout << "║ 3. Open vocabularies folder                                                         ║" << std::endl;
        std::cout << "║ 4. Open saves folder                                                                ║" << std::endl;
        std::cout << "║ 5. Exit                                                                             ║" << std::endl;
        std::cout << "╚═════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "► Enter your choice: ";  // Створка для введення дії
        std::cin >> choise;


        switch (choise) {


            case 0: {
                vocabulary.createWorkSpace();
                system("pause");
                break;
            }

            case 1: {

                vocabulary.chose_vocabulary();
                vocabulary_menu(vocabulary);
                break;
            }

            case 2: {
                std::string name;
                std::cout << "Enter vocabulary name: ";
                std::cin >> name;

                vocabulary.createVocabulary(name);
                std::cout << "Created successful. You can load it. " << std::endl;

                system("pause");
                break;

            }

            case 3: {
                vocabulary.openFolder(vocabulary.vocabulariesFolder.generic_string());
                std::cout << "Open successful." << std::endl;
                system("pause");
            }

            case 4: {
                vocabulary.openFolder(vocabulary.saveFolder.generic_string());
                std::cout << "Open successful." << std::endl;
                system("pause");
            }

            case 5: {
                std::cout << "\n\n\nProgram was finished, for exit type any key";
                uint8_t exit;
                std::cin >> exit;
                break;
            }

        }
       clear_console();
    }


    //todo - Зробити збереження одразу на папку словників а не сейв, сейв перероробити на сейв ес.

    //ВІДКРИТТЯ СЛОВНИКА З ФАЙЛУ        100%
    //ЗАХИСТ "ВІД ДУРАКА".              100%
    //ДОДАВАННЯ НОВОГО СЛОВА            100%
    //ЗБЕРЕЖЕННЯ СЛОВНИКА               100%
    //ВИДАЛЕННЯ СЛОВА                   100%



}
