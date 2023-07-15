# Codegenerator GenTxtSrcCode
# Deutsch

Dieses Repository enthält den Codegenerator "GenTxtSrcCode" für die Programmiersprachen C/C++. Das Projekt wurde im Rahmen des Kurses TIK/TIM/TIS/TIT22 an der Dualen Hochschule Baden-Württemberg entwickelt.

## Software-Anforderungen

- C/C++ Compiler (GNU-C/C++, MinGW64)
- Standard C/C++ Libraries

## Installation

Um den Codegenerator zu verwenden, führen Sie die folgenden Schritte aus:

1. Klonen Sie das Repository auf Ihren lokalen Computer.
2. Kompilieren Sie den Code mithilfe eines C/C++ Compilers.
3. Führen Sie das generierte ausführbare Programm aus.

## Verwendung

Der Codegenerator "GenTxtSrcCode" liest eine oder mehrere Eingabedateien ein und generiert entsprechende Header- und Source-Dateien basierend auf dem darin enthaltenen Text und den angegebenen Optionen. Die Eingabedateien können entweder über die Kommandozeile oder über spezielle Tags innerhalb der Dateien angegeben werden. Die generierten Dateien enthalten Textbausteine, die für eine Anwendung verwendet werden können.

### Kommandozeilenoptionen

Der Codegenerator unterstützt verschiedene Kommandozeilenoptionen:

- Die Inputdateien werden ohne Option übermittelt.
- `-h` oder `--help`: Zeigt eine Hilfeanleitung mit Informationen zur Verwendung und den verfügbaren Optionen an.
- `-o`oder `--outputfile <dateiname>`: Bestimmt den Namen der generierten Dateien. Wenn nicht angegeben, wird ein Standardname verwendet.
- `-t`oder `--outputtype <typ>`: Legt den Dateityp für die generierten Dateien fest (C oder CPP). Der Standardwert ist CPP.
- `-d`oder `--headerdir <verzeichnis>`: Bestimmt das Verzeichnis für die generierte Header-Datei. Wenn das Verzeichnis nicht existiert, wird es automatisch erstellt.
- `-s`oder `--sourcedir <verzeichnis>`: Bestimmt das Verzeichnis für die generierte Source-Datei. Wenn das Verzeichnis nicht existiert, wird es automatisch erstellt.
- `-n`oder `--namespace <name>`: Definiert den Namespace für die C++-Dateien.
- `-l`oder `--signperline <anzahl>`: Legt die maximale Anzahl von Zeichen pro Zeile in den generierten Variablen fest. Der Standardwert ist 60.
- `-V`oder `--sortbyvarname`: Aktiviert die alphabetische Sortierung der Variablen im Output.
- `-v`oder `--version`: Gibt die Version aus.

### Beispiel

```
genTxtSrcCode --inputfile input.txt --outputfile output --outputtype CPP --headerdir include --sourcedir src
```

Dieses Beispiel liest die Datei "input.txt" ein und generiert die Dateien "output.h" und "output.cpp" im Verzeichnis "include" bzw. "src".

## Autoren

Dieses Projekt wurde von den folgenden Entwicklern entwickelt. 
- Silas Burgmaier
- Ben Felber
- Jannik Dangel
- David Oswald

# Code Generator GenTxtSrcCode
# English

This repository contains the code generator "GenTxtSrcCode" for the C/C++ programming languages. The project was developed as part of the TIK/TIM/TIS/TIT22 course at the Cooperative State University Baden-Württemberg.

## Software Requirements

- C/C++ Compiler (GNU-C/C++, MinGW64)
- Standard C/C++ Libraries

## Installation

To use the code generator, follow these steps:

1. Clone the repository to your local computer.
2. Compile the code using a C/C++ compiler.
3. Run the generated executable program.

## Usage

The code generator "GenTxtSrcCode" reads one or more input files and generates corresponding header and source files based on the text contained within them and the specified options. The input files can be specified either through the command line or using special tags within the files. The generated files contain text snippets that can be used for an application.

### Command Line Options

The code generator supports various command line options:

- Input files are passed without any option.
- `-h` or `--help`: Displays a help guide with information on usage and available options.
- `-o` or `--outputfile <filename>`: Specifies the name of the generated files. If not provided, a default name is used.
- `-t` or `--outputtype <type>`: Sets the file type for the generated files (C or CPP). The default value is CPP.
- `-d` or `--headerdir <directory>`: Specifies the directory for the generated header file. If the directory does not exist, it is created automatically.
- `-s` or `--sourcedir <directory>`: Specifies the directory for the generated source file. If the directory does not exist, it is created automatically.
- `-n` or `--namespace <name>`: Defines the namespace for the C++ files.
- `-l` or `--signperline <count>`: Sets the maximum number of characters per line in the generated variables. The default value is 60.
- `-V` or `--sortbyvarname`: Enables alphabetical sorting of variables in the output.
- `-v` or `--version`: Displays the version.

### Example

```
genTxtSrcCode --inputfile input.txt --outputfile output --outputtype CPP --headerdir include --sourcedir src
```

This example reads the file "input.txt" and generates the files "output.h" and "output.cpp" in the "include" and "src" directories, respectively.

## Authors

This project was developed by the following developers:
- Silas Burgmaier
- Ben Felber
- Jannik Dangel
- David Oswald
