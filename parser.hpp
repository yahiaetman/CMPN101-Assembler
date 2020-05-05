#pragma once
#include <optional>
#include <list>
#include <peglib.h>
#include "grammar.hpp"
#include "assembly.hpp"

inline uint8_t convert_hex_char_to_num(char hex){
    if(hex >= '0' && hex <= '9') return hex - '0';
    else if(hex >= 'A' && hex <= 'F') return hex - 'A' + 10;
    else if(hex >= 'a' && hex <= 'f') return hex - 'a' + 10;
    else throw std::invalid_argument("Invalid hex character");
}

inline char convert_num_to_hex_char(uint8_t num){
    if(num >= 0 && num <= 9) return num + '0';
    else return num - 10 + 'a';
}

template<typename T>
T parse_num(const std::string& token, T base){
    T value = 0;
    for(auto it = token.begin(), end = token.end(); it != end; ++it){
        value = value * base + convert_hex_char_to_num(*it);
    }
    return value;
}

inline peg::parser create_parser(){
    auto parser = peg::parser(GRAMMAR);

    parser["dec"] = [](const peg::SemanticValues& sv) -> uint8_t { return parse_num(sv.token(), 10); };
    parser["bin"] = [](const peg::SemanticValues& sv) -> uint8_t { return parse_num(sv.token(), 2); };
    parser["oct"] = [](const peg::SemanticValues& sv) -> uint8_t { return parse_num(sv.token(), 8); };
    parser["hex"] = [](const peg::SemanticValues& sv) -> uint8_t { return parse_num(sv.token(), 16); };

    parser["num"] = [](const peg::SemanticValues& sv) -> uint8_t {
        if(sv.size() > 1){
            return ~std::any_cast<uint8_t>(sv[1]) + 1;    
        } else {
            return std::any_cast<uint8_t>(sv[0]);
        }
    };
    
    parser["reg"] = [](const peg::SemanticValues& sv) -> Register {
        std::string token = sv.token();
        std::transform(token.begin(), token.end(), token.begin(), [](char c) -> char { return std::toupper(c); });
        if(auto it = register_lookup_table.find(token); it != register_lookup_table.end()){
            return it->second;
        } else {
            throw std::invalid_argument("Invalid Register");
        }
    };

    parser["operand"] = [](const peg::SemanticValues& sv) -> Operand {
        Operand operand;
        if(sv.choice() == 0){
            operand.immediate = true;
            operand.data.value = std::any_cast<uint8_t>(sv[0]);
        } else {
            operand.immediate = false;
            operand.data.reg = std::any_cast<Register>(sv[0]);
        }
        return operand;
    };

    parser["binary_op"] = parser["unary_op"] = [](const peg::SemanticValues& sv) -> Operation {
        std::string token = sv.token();
        std::transform(token.begin(), token.end(), token.begin(), [](char c) -> char { return std::tolower(c); });
        if(auto it = operation_lookup_table.find(token); it != operation_lookup_table.end()){
            return it->second;
        } else {
            throw std::invalid_argument("Invalid Operation");
        }
    };

    parser["binary_instruction"] = [](const peg::SemanticValues& sv) -> Instruction {
        return { std::any_cast<Operation>(sv[0]), std::any_cast<Register>(sv[1]), std::any_cast<Operand>(sv[2]) };
    };

    
    parser["unary_instruction"] = [](const peg::SemanticValues& sv) -> Instruction {
        return { std::any_cast<Operation>(sv[0]), std::any_cast<Register>(sv[1]), {} };
    };

    parser["line"] = [](const peg::SemanticValues& sv) -> std::optional<Instruction> {
        return sv.choice() == 0 ? std::optional(std::any_cast<Instruction>(sv[0])) : std::nullopt;
    };

    parser["code"] = [](const peg::SemanticValues& sv) -> std::list<Instruction> {
        std::list<Instruction> code(
            sv.choice() == 0 ? 
            std::move(*std::any_cast<std::list<Instruction>>(&sv[1])) : 
            std::list<Instruction>());
        auto instruction = std::any_cast<std::optional<Instruction>>(sv[0]);
        if (instruction) code.push_front(*instruction);
        return std::move(code);
    };

    parser.log = [](size_t line, size_t col, const std::string& msg) {
        std::cerr << line << ":" << col << ": " << msg << "\n";
    };

    parser.enable_packrat_parsing();
    return parser;
}