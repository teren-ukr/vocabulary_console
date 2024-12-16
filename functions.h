// #ifndef FUNCTIONS_H
// #define FUNCTIONS_H
//
// #include <string>
// #include <filesystem>
// #include <iostream>
//
//
//
// namespace str {
//
//     int lengthUTF8 (const std::string &s) {
//         int count = 0;
//         for (size_t i = 0; i < s.size(); ++i) {
//             // Якщо це не байт продовження (0x80 - 0xBF), значить, це новий символ
//             if ((s[i] & 0xC0) != 0x80) {
//                 ++count;
//             }
//         }
//         return count;
//     }
//
//
//
//     int nms(const std::string &name, const uint8_t bnum) {
//         return bnum - lengthUTF8(name);
//     }
//
//
//     auto prs (const int &num, const char &symbol) {
//         for (int i = 0; i < num; ++i) {
//             std::cout << symbol;
//         }
//         return "";
//     }
//
//     int nmi (const int &id, const uint8_t &bnum) {
//         return bnum - std::to_string(id).length();
//     }
//
//
//
//
// }
//
//
// #endif //FUNCTIONS_H
