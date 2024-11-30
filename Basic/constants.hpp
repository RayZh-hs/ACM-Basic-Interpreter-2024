//
// Created by Rayzh on 2024/11/30.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <regex>
#include <string>

namespace Basic {
    constexpr int null_line_number = -1;

    const std::string help_msg =
        "This is NBI (Norb's BASIC Interpreter).\n"
        "Why another BASIC interpreter?\n"
        "Because -- Surprise! It is regex-based, not tokenScanner-based!\n"
        "That makes it something new, doesn't it?\n"
    ;

    const std::regex regex_valid_variable_name  (R"(^[a-zA-Z0-9]$)");
    const std::regex regex_valid_number         (R"(^[0-9]$)");
    const std::regex regex_discrete_letters     (R"([a-zA-Z_0-9]+ +[a-zA-Z_0-9]+)");
    const std::regex regex_leading_number       (R"(^[0-9]*)");

    const std::regex regex_sav_rem              (R"(^[0-9]+ ?REM.+)");
    const std::regex regex_sav_let              (R"()");
    const std::regex regex_sav_print            (R"()");
    const std::regex regex_sav_input            (R"()");
    const std::regex regex_sav_goto             (R"()");
    const std::regex regex_sav_if               (R"()");
    // const std::regex regex_sav_let              (R"()");
}

#endif //CONSTANTS_H