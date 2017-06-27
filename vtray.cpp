#include <iostream>
#include <vector>
#include <QString>
#include <string>
#include "interpreter.hpp"

int main(int argc, char*argv[]){
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; i++){
        arguments.push_back(argv[i]);
    }

    if (argc == 3){
        Interpreter i;
        bool pass = i.parse(arguments[1]);
        if (!pass){
            return EXIT_FAILURE;
        }
        i.render(1);
        QString str = QString::fromStdString(arguments[2]);
        i.saveImage(str);
        return EXIT_SUCCESS;
    }
    
    if (argc == 5){
        if (arguments[1] != "-t"){
            std::cerr << "Invalid arguments";
            return EXIT_FAILURE;
        }
        Interpreter i;
        bool pass = i.parse(arguments[3]);
        if (!pass){
            return EXIT_FAILURE;
        }
        int threads = std::stoi(arguments[2]);
        i.render(threads);
        QString str = QString::fromStdString(arguments[4]);
        i.saveImage(str);
        return EXIT_SUCCESS;
    }
    std::cerr << "Invalid arguments";
    return EXIT_FAILURE;
}
