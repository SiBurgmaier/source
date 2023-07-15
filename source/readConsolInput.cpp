#include "readConsolInput.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include "getopt.h"
#include <string>
#include <string.h>


void printHelp() {
    std::cout << "\n"
        << "The program supports the following command-line parameters:\n"
        << "-h, --help\t\tDisplays this help. No argument is expected.\n"
        << "-o, --outputfilename\tSets the output filename. The output filename should follow this parameter.\n"
        << "-t, --outputtype\tSets the output type. The output filename should follow this parameter. Either C or CPP.\n"
        << "-d, --headerdir\t\tSets the header directory. The directory for the header file should follow this parameter.\n"
        << "-s, --sourcedir\t\tSets the source code directory. The directory for the source file should follow this parameter.\n"
        << "-n, --namespace\t\tSets the \"namespace\" in the output file. The name should follow this parameter.\n"
        << "-l, --signperline\tSets the number of characters per line. A number should follow this parameter.\n"
        << "-V, --sortbyvarname\tEnables sorting by variable names. No argument is expected.\n"
        << "-v, --version\t\tDisplays the program version. No argument is expected.\n\n"
        << "The input file should be specified without any option. If no argument or too many arguments without an option are provided, the program will terminate.\n\n"
        << "Author Team:\n"
        << "Silas Burgmaier, Jannik Dangel, Ben Felber, David Oswald\n"
        << "Email Address:\nsilasburgmaier@gmx.de\n\n\n";
}

int parameterParsing(int argc, char* argv[]) {
    int16_t opt;

    // Define options and their arguments
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"outputfilename", required_argument, 0, 'o'},
        {"outputtype", required_argument, 0, 't'},
        {"headerdir", required_argument, 0, 'd'},
        {"sourcedir", required_argument, 0, 's'},
        {"namespace", required_argument, 0, 'n'},
        {"signperline", required_argument, 0, 'l'},
        {"sortbyvarname", no_argument, 0, 'V'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ho:t:d:s:n:l:vV", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 1;
            case 'o':
                optionGlobalCMDline.outputfilename = optarg;
                break;
            case 't':
                if (optarg == std::string("C") || optarg == std::string("CPP")) {
                    optionGlobalCMDline.outputtype = optarg;
                } else {
                    std::cout << "\nThe input after -t/--outputtype is incorrect. It must be either C or CPP!\n";
                    return 1;
                }
                break;
            case 'd':
                optionGlobalCMDline.headerdir = optarg;
                break;
            case 's':
                optionGlobalCMDline.sourcedir = optarg;
                break;
            case 'n':
                optionGlobalCMDline.ns = optarg;
                break;
            case 'l':
                optionGlobalCMDline.signperline = atoi(optarg);
                break;
            case 'v':
                std::cout << "Version 1.0\n";
                break;
            case 'V':
                optionGlobalCMDline.sortbyvarname = 1;
                break;
            default:
                std::cout << "Invalid option";
                return 1;
        }
    }
    // Make sure that there is no option before the input filename.
    if (optind + 1 == argc)
        optionGlobalCMDline.inputfilename = argv[optind];

    // Include logic for multiple input files here
    else if (optind + 1 < argc) {
        std::string txtFiles;
        for (int i = optind; i < argc; i++) {
            txtFiles += std::string(argv[i]) + "\n";
        }
        optionGlobalCMDline.inputfilename = txtFiles;
    }

    // Error: No input file specified
    else if (optind == argc) {
        std::cout << "No argument without option was passed. Therefore, no input file could be found.\n";
        return 1;
    } else {
        do {
        } while (0); // NOP --> do-while loop without content
    }

    return 0;
}

