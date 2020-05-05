#pragma once
#include <map>
#include <list>
#include <iomanip>
#include "assembly.hpp"

class Processor {
    std::map<Register, uint8_t> register_file;
    uint8_t output;
    size_t clock_cycle;
public:
    Processor(std::initializer_list<Register> registers) : clock_cycle(0), output(0) {
        for(auto reg: registers) register_file[reg] = 0;
    }

    void reset(){
        for(auto it = register_file.begin(), end = register_file.end(); it != end; it++){
            it->second = 0;
        }
        clock_cycle = 0;
        output = 0;
    }


    void run(const Instruction& instruction, bool verbose = false){
        uint8_t result = register_file[instruction.reg];
        switch (get_operation_narity(instruction.opcode))
        {
        case Narity::UNARY:{
            switch (instruction.opcode)
            {
            case Operation::OUT:
                output = result;
                break;
            case Operation::NEG:
                result = ~result + 1;
                break;
            case Operation::NOT:
                result = ~result;
                break;
            }
        }
        break;
        case Narity::BINARY:{
            uint8_t operand = instruction.operand.immediate ? instruction.operand.data.value : register_file[instruction.operand.data.reg];
            switch (instruction.opcode)
            {
            case Operation::MOV:
                result = operand;
                break;
            case Operation::ADD:
                result += operand;
                break;
            case Operation::SUB:
                result -= operand;
                break;
            case Operation::MUL:
                result *= operand;
                break;
            case Operation::IMUL:{
                bool sign_res = result & (1<<7);
                bool sign_op = operand & (1<<7);
                if(sign_res) result = ~result + 1;
                if(sign_op) operand = ~operand + 1;
                result *= operand;
                result &= ~(1<<7);
                if(sign_op != sign_res) result = ~result + 1;
            }
                break;
            case Operation::AND:
                result &= operand;
                break;
            case Operation::OR:
                result |= operand;
                break;
            case Operation::XOR:
                result ^= operand;
                break;
            case Operation::SHL:
                result <<= operand;
                break;
            case Operation::SHR:
                result >>= operand;
                break;
            }
        }
        }
        register_file[instruction.reg] = result;
        ++clock_cycle;
        if(verbose){
            std::cout << std::hex << std::setfill('0') << std::setw(2) << clock_cycle << ": ";
            std::cout << instruction << "\t\t(code: " << std::hex << std::setfill('0') << std::setw(4) << instruction.encode() << ")\t=>\t";
            for(auto it = register_file.begin(), end = register_file.end(); it != end; it++){
                std::cout << it->first << "=";
                std::cout << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)it->second << ",\t";
            }
            std::cout << "OUT=";
            std::cout << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)output << std::endl;
        }
        
    };

    void run(const std::list<Instruction>& instructions, bool verbose = false){
        for(auto it = instructions.cbegin(), end = instructions.cend(); it != end; ++it){
            run(*it, verbose);
        }
    };
};