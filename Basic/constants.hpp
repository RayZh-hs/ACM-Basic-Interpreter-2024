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
        "| This is NBI (Norb's BASIC Interpreter).\n"
        "| Exactly why another BASIC interpreter?\n"
        "| Because -- Surprise! It is regex-based, not tokenScanner-based!\n"
        "| That makes it something new, doesn't it?\n"
    ;

    const std::regex regex_valid_variable_mode  (R"(^[a-zA-Z0-9]+$)");
    const std::regex regex_reserved_names       (R"(REM|LET|PRINT|INPUT|END|RUN|LIST|CLEAR|QUIT|HELP)");
    const std::regex regex_valid_number         (R"(^-?[0-9]+$)");
    const std::regex regex_valid_expr_mode      (R"(^[a-zA-Z0-9\+\-*\/\(\) ]+$)");
    const std::regex regex_discrete_letters     (R"([a-zA-Z0-9]+ +[a-zA-Z0-9]+)");
    const std::regex regex_concentrated_symbols (R"([\+\-*\/]+\s*[\+\-*\/]+)");
    const std::regex regex_connected_brackets   (R"((?:[a-zA-Z0-9\)] *\(|\) *[a-zA-Z0-9\(]))");
    const std::regex regex_leading_number       (R"(^[0-9]*)");

    const std::regex regex_sav_rem              (R"(^([0-9]+) *REM.+$)");
    const std::regex regex_sav_let              (R"(^([0-9]+) *LET ?(.*)=(.*)$)");
    const std::regex regex_sav_print            (R"(^([0-9]+) *PRINT ?(.*)$)");
    const std::regex regex_sav_input            (R"(^([0-9]+) *INPUT ?(\S+)$)");
    const std::regex regex_sav_goto             (R"(^([0-9]+)\s*GOTO\s*([0-9]+)$)");
    const std::regex regex_sav_if               (R"(^([0-9]+)\s*IF\s*(.*)([<>=])\s*(.*)THEN\s*([0-9]+)$)");
    const std::regex regex_sav_end              (R"(^([0-9]+)\s*END$)");
    const std::regex regex_sav_del              (R"(^([0-9]+$))");
    const std::regex regex_exe_let              (R"(^LET ?(.*)=(.*)$)");
    const std::regex regex_exe_print            (R"(^PRINT ?(.*)$)");
    const std::regex regex_exe_input            (R"(INPUT ?(\S+)$)");
    const std::regex regex_exe_run              (R"(^RUN$)");
    const std::regex regex_exe_list             (R"(^LIST$)");
    const std::regex regex_exe_clear            (R"(^CLEAR$)");
    const std::regex regex_exe_quit             (R"(^QUIT$)");
    const std::regex regex_exe_help             (R"(^HELP$)");

}

#endif //CONSTANTS_H