#include <iostream>
#include <fstream>
#include <iterator>
#include <flags.h>
#include "processor.hpp"
#include "parser.hpp"

const char* HELP_MESSAGE = R"(
Assembler and Virtual Processor for A Simplified Processor Module (Project for CMPN101).

Usage:
    assembler.exe <input_file> [-o <output_hex>]
    assembler.exe -h | --help
    assembler.exe --version

Options:
    -h --help           Show this screen.
    --version           Show version.
    -o <output_hex>     Write a hex file to the given path if assembling was successful.
)";


int main(int argc, char** argv) {
    auto args = flags::args(argc, argv);

    if(args.get<bool>("version", false)){
        std::cout << "Assembler v1.0.0" << std::endl;
        exit(0);
    }

    if(args.get<bool>("h", false) || args.get<bool>("help", false)){
        std::cout << HELP_MESSAGE << std::endl;
        exit(0);
    }

    auto code_file_path = args.get<std::string_view>(0);

    std::string code;
    if (code_file_path) {
        auto istream = std::ifstream(&(*code_file_path)[0], std::ios::in);
        if(istream.bad()){
            std::cerr << "Failed to open file:" << *code_file_path << std::endl;
            exit(1);
        }
        code = std::string(std::istreambuf_iterator<char>(istream), {});
    } else {
        std::cerr << "ERROR: File path for the code must be supplied" << std::endl;
        std::cout << "Help:" << HELP_MESSAGE << std::endl;
        exit(1);
    }

    auto parser = create_parser();

    std::list<Instruction> result;
    if(parser.parse(code.c_str(), result)){
        std::cout << "Simulation Result:" << std::endl; 
        Processor processor({Register::A, Register::B, Register::C, Register::D});
        processor.reset();
        processor.run(result, true);
        
        if(auto hex_path = args.get<std::string_view>("o")){
            auto ostream = std::ofstream(&(*hex_path)[0], std::ios::out);
            ostream << "v2.0 raw" << std::endl;
            for(auto it = result.begin(), end = result.end(); it != end; ++it){
                 ostream << std::hex << it->encode() << std::endl;
            }
        }
    } else {
        std::cerr << "Failed to parse the code" << std::endl;
        
    }
    
    

}
