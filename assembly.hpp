#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

enum class Narity {
    UNARY = 1,
    BINARY = 2
};

enum class Operation: uint8_t {
    MOV = 0,
    OUT = 1,
    ADD = 8,
    SUB = 9,
    NEG = 10,
    MUL = 12,
    IMUL = 13,
    NOT = 32,
    AND = 33,
    OR = 34,
    XOR = 35,
    SHL = 36,
    SHR = 37
};

const std::unordered_map<std::string, Operation> operation_lookup_table = {
    {"mov", Operation::MOV},
    {"out", Operation::OUT},
    {"add", Operation::ADD},
    {"sub", Operation::SUB},
    {"neg", Operation::NEG},
    {"mul", Operation::MUL},
    {"imul", Operation::IMUL},
    {"not", Operation::NOT},
    {"and", Operation::AND},
    {"or", Operation::OR},
    {"xor", Operation::XOR},
    {"shl", Operation::SHL},
    {"shr", Operation::SHR}
};

inline Narity get_operation_narity(Operation op){
    switch (op)
    {
    case Operation::OUT:
    case Operation::NEG:
    case Operation::NOT:
        return Narity::UNARY;
    default:
        return Narity::BINARY;
    }
}

enum class Register: uint8_t {
    A = 0,
    B = 1,
    C = 2,
    D = 3
};

const std::unordered_map<std::string, Register> register_lookup_table = {
    {"A", Register::A},
    {"B", Register::B},
    {"C", Register::C},
    {"D", Register::D},
};

struct Operand {
    bool immediate;
    union
    {
        Register reg;
        uint8_t value;
    } data;

    uint16_t encode() const {
        return immediate << 8 | (immediate ? data.value : static_cast<uint8_t>(data.reg));
    }
};

struct Instruction {
    Operation opcode;
    Register reg;
    Operand operand;

    uint16_t encode() const{
        return  static_cast<uint8_t>(opcode) << 11 | 
                static_cast<uint8_t>(reg) << 9 |
                operand.encode();
    }
};

inline std::ostream& operator<<(std::ostream& os, const Operation& operation){
    auto it = std::find_if(
        operation_lookup_table.cbegin(), operation_lookup_table.cend(), 
        [&](const std::unordered_map<std::string, Operation>::value_type& v){ return v.second == operation; });
    if(it != operation_lookup_table.end()){
        return os << it->first;
    } else {
        throw std::invalid_argument("Invalid Operation");
    }
}

inline std::ostream& operator<<(std::ostream& os, const Register& reg){
    auto it = std::find_if(
        register_lookup_table.cbegin(), register_lookup_table.cend(), 
        [&](const std::unordered_map<std::string, Register>::value_type& v){ return v.second == reg; });
    if(it != register_lookup_table.end()){
        return os << it->first;
    } else {
        throw std::invalid_argument("Invalid Register");
    }
}

inline std::ostream& operator<<(std::ostream& os, const Operand& operand){
    if(operand.immediate) return os << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)operand.data.value << 'h';
    else return os << operand.data.reg;
}

inline std::ostream& operator<<(std::ostream& os, const Instruction& instruction){
    os << instruction.opcode << " " << instruction.reg;
    if(get_operation_narity(instruction.opcode) == Narity::BINARY)
        os << ", " << instruction.operand;
    return os;
}