#include "CTextToCPP.h"

// Basisklasse
CTextToCPP::CTextToCPP(VariableSettings& varsettings) {
    this->varsettings = varsettings;
}

CTextToCPP *CTextToCPP::create(VariableSettings &varsettings) {
    if (varsettings.seq == "ESC") {
        return new CTextToEscSeq(varsettings);
    }
    else if (varsettings.seq == "HEX") {
        return new CTextToHexSeq(varsettings);
    }
    else if (varsettings.seq == "OCT") {
        return new CTextToOctSeq(varsettings);
    }
    else if (varsettings.seq == "RAWHEX") {
        return new CTextToRawHexSeq(varsettings);
    }
    else {
        std::cout << "Error: outputtype not found" << std::endl;
        return nullptr;
    }
}

CTextToCPP::~CTextToCPP() {}

std::string CTextToCPP::getdoxygen() {
    std::string doxygen = varsettings.doxygen;
    if (this->getAddTextpos()) {
        doxygen = doxygen + "//TextPos:" + std::to_string(varsettings.textpos);
    }
    return doxygen;
}

std::string CTextToCPP::getvarname() {
    return varsettings.varname;
}

bool CTextToCPP::getAddTextpos() {
    return varsettings.addtextpos;
}

int CTextToCPP::getTextpos() {
    return varsettings.textpos;
}

std::string CTextToCPP::getText() {
    return varsettings.text;
}

void CTextToCPP::addElement(CTextToCPP* obj) {
    CTextToCPP* current = this;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = obj;
}

void CTextToCPP::writeDeclaration(GlobalSettings& settings) {
    std::string filename = settings.headerdir + settings.outputfilename + ".h"; //TODO angabe des headers
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "#ifndef _" << toUpper(settings.outputfilename) << "_H_" << std::endl;
        file << "#define _" << toUpper(settings.outputfilename) << "_H_" << std::endl;
        if (settings.outputtype == "CPP") {
            file << "namespace " << toUpper(settings.ns) << " {" << std::endl;
        }
        file << this->declaration();
        CTextToCPP* current = this->next;
        while (current != nullptr) {
            file << current->declaration();
            current = current->next;
        }
        if (settings.outputtype == "CPP") {
            file << "}" << std::endl;
        }
        file << "#endif" << std::endl;
        file.close();
    }
    else {
        std::cout << "Error opening the file." << std::endl;
    }
}

void CTextToCPP::writeImplementation(GlobalSettings& settings) {
    std::string filename;
    if (settings.outputtype == "CPP") {
        filename = settings.sourcedir + settings.outputfilename + ".cpp";
    }
    else {
        filename = settings.sourcedir + settings.outputfilename + ".c";
    }
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "#include <" << settings.outputfilename << ".h>" << std::endl; //TODO: Realativer pfad
        if (settings.outputtype == "CPP") {
            file << "namespace " << toUpper(settings.ns) << " {" << std::endl;
        }
        file << this->definition();
        this->writeImplementationSub(file, settings);
        CTextToCPP* current = this->next;
        while (current != nullptr) {
            file << current->definition();
            current->writeImplementationSub(file, settings);
            current = current->next; // TODO: Orignaltext rein weilk chatcpt is retarded
        }
        file << "}" << std::endl;
        file.close();
    }
    else {
        std::cout << "Error opening the file." << std::endl;
    }
}

void CTextToCPP::clear() {
    if (this->next != nullptr) {
        this->next->clear();
    }
    delete this;
}

std::string CTextToCPP::getVariableName() {
    return this->varsettings.varname;
}

CTextToCPP* CTextToCPP::getNext() {
    return next;
}

void CTextToCPP::sort(CTextToCPP** first) {
    if (first == nullptr || *first == nullptr || (*first)->next == nullptr) {
        return;
    }

    bool swapped;
    CTextToCPP** link;
    CTextToCPP* temp = nullptr;

    do {
        swapped = false;
        link = first;

        while ((*link)->next != temp) {
            if ((*link)->getVariableName() > (*link)->next->getVariableName()) {
                CTextToCPP* swap = (*link)->next;
                (*link)->next = swap->next;
                swap->next = *link;
                *link = swap;
                swapped = true;
            }
            else {
                link = &(*link)->next;
            }
        }
        temp = *link;
    } while (swapped);
}

std::string CTextToCPP::convertText(char text) {
    return std::to_string(text);
}

void CTextToCPP::writeImplementationSub(std::ofstream& file, GlobalSettings& settings) {}

std::string CTextToCPP::declaration() {
    return "/**" + this->getdoxygen() + "*/\n" + "extern const char* " + toUpper(this->getVariableName()) + ";\n";
}

std::string CTextToCPP::definition() {
    return "extern const char* " + toUpper(this->getVariableName()) + " = {\n";
}

std::string CTextToCPP::writeTextsegment() {
    return "\n/*\nOrginaltext aus Der Variablenfunktion '" + toUpper(this->getVariableName()) + "'\n\n" + varsettings.text + "\n*/\n";
}

std::string CTextToCPP::toUpper(std::string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] -= 32 * (text[i] >= 'a' && text[i] <= 'z');
    }
    return text;
   
}

// CTextToEscSeq child class
CTextToEscSeq::CTextToEscSeq(VariableSettings& varsettings) : CTextToCPP(varsettings) {}

void CTextToEscSeq::writeImplementationSub(std::ofstream &file, GlobalSettings &settings)  {
    int linecount = settings.signperline - 4, writtenchar = 0;
    std::string text = this->getText();
    int length = text.length();
    int extra = 0;
    while (length - writtenchar > 0) {
        file << "\"";
        extra = 0;
        //std::cout << length - writtenchar << std::endl;
        for(int i = 0; i < linecount - extra; i++) {
            if( writtenchar + 1 > length) {
                writtenchar++;
                break;
            } else if(text[writtenchar + 1] == '\n') {
                file << "\\n\n";
                writtenchar++;
                break;
            } else {
                char text2 = text[writtenchar];
                switch (text2) {
                    case '\n':
                        file << "\\n";
                        extra++;
                    case '\t':
                        file << "\\t";
                        extra++;
                    case '\v':
                        file << "\\v";
                        extra++;
                    case '\b':
                        file << "\\b";
                        extra++;
                    case '\r':
                        file << "\\r";
                        extra++;
                    case '\f':
                        file << "\\f";
                        extra++;
                    case '\a':
                        file << "\\a";
                        extra++;
                    case '\\':
                        file << "\\\\";
                        extra++;
                    case '\?':
                        file << "\\?";
                        extra++;
                    case '\'':
                        file << "\\\'";
                        extra++;
                    case '\"':
                        file << "\\";
                        extra++;
                    default:
                        file << text2;
                    }
                writtenchar ++;
            }
        }
        if(length - writtenchar > 0){
            file << "\" \\\n";
        } else {
            break;
        }
    }
    file << "\" };\n\n";//TODO: requirement 26 Zeilenumbruche sollen so gehandhabt werden wie ¨ uber den Parameter nl (DOS, ¨MAC, UNIX) aus dem Tag @variable vorgegeben (DOS = CR LF, MAC = CR, UNIX = LF). Der Defaultwert dieser Einstellung ist UNIX.
}


// CTextToOctSeq child class
CTextToOctSeq::CTextToOctSeq(VariableSettings& varsettings) : CTextToCPP(varsettings) {}

void CTextToOctSeq::writeImplementationSub(std::ofstream &file, GlobalSettings &settings) {
    int linecount = settings.signperline - 4, writtenchar = 0, linelength = 0;
    std::string text = this->getText();
    int length = text.length();
    while (length - writtenchar > 0) {
        file << "\"";
        for(int i = 0; i < linecount; i++) {
            if( writtenchar + 1 > length)  { 
                writtenchar++;
                break;
            }else if (linecount - linelength < 4) {
                break;
            } else if(text[writtenchar] == '\n') {
                file << "\\" << convertText('\n') << "\n";	
                writtenchar++;
                linelength += 4;
                break;
            } else {
                file << "\\" << this->convertText(text[writtenchar]) ;
                writtenchar ++;
                linelength += 4;
            }
            
        }
        if(length - writtenchar > 0){
            file << "\" \\\n";
            linelength = 0;
        } else {
            break;
        }
    }
    file << "\" };\n\n";
}

std::string CTextToOctSeq::convertText(char text) {
    std::ostringstream oss;
    oss << std::oct << std::setw(3) << std::setfill('0') << static_cast<unsigned int>(text);
    return oss.str();
}

// CTextToHexSeq child class
CTextToHexSeq::CTextToHexSeq(VariableSettings& varsettings) : CTextToCPP(varsettings) {}

void CTextToHexSeq::writeImplementationSub(std::ofstream &file, GlobalSettings &settings) {
    int linecount = settings.signperline - 4, writtenchar = 0, linelength = 0;
    std::string text = this->getText();
    int length = text.length();
    while (length - writtenchar > 0) {
        file << "\"";
        for(int i = 0; i < linecount; i++) {
            if( writtenchar + 1 > length)  { 
                writtenchar++;
                break;
            }else if (linecount - linelength < 4) {
                break;
            } else if(text[writtenchar] == '\n') {
                file << "\\" << convertText('\n') << "\n";	
                writtenchar++;
                linelength += 4;
                break;
            } else {
                file << "\\" << this->convertText(text[writtenchar]); // TODO: @endvariable weg und -1 am anfang
                writtenchar ++;
                linelength += 4;
            }
            
        }
        if(length - writtenchar > 0){
            file << "\" \\\n";
            linelength = 0;
        } else {
            break;
        }
    }
    file << "\" };\n\n"; 
}

std::string CTextToHexSeq::convertText(char text) {
    std::stringstream stream;
    stream << "x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(text);
    return stream.str();
}

// CTextToRawHexSeq child class
CTextToRawHexSeq::CTextToRawHexSeq(VariableSettings& varsettings) : CTextToCPP(varsettings) {}

void CTextToRawHexSeq::writeImplementationSub(std::ofstream &file, GlobalSettings &settings) {
    int linecount = settings.signperline - 4, writtenchar = 0, linelength = 0;
    std::string text = this->getText();
    int length = text.length();
    while (length - writtenchar > 0) {
        for(int i = 0; i < linecount; i++) {
            if( writtenchar + 1 > length)  { 
                writtenchar++;
                break;
            }else if (linecount - linelength < 6) {
                break;
            } else if(text[writtenchar] == '\n') {
                file << convertText('\n') << ", " << "\n";	
                writtenchar++;
                linelength += 6;
                break;
            } else {
                file << this->convertText(text[writtenchar]) << ", "; // TODO: @endvariable weg und -1 am anfang
                writtenchar ++;
                linelength += 6;
            }
            
        }
        if(length - writtenchar > 0){
            file << "\\\n";
            linelength = 0;
        } else {
            break;
        }
    }
    file << "};\n\n"; 
}

std::string CTextToRawHexSeq::convertText(char text) {
    std::stringstream stream;
    stream << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(text);
    return stream.str();
}

std::string CTextToRawHexSeq::declaration() {
    return "/**" + this->getdoxygen() + "*/\n" + "extern const char " + toUpper(this->getVariableName()) + "[];\n";
}

std::string CTextToRawHexSeq::definition() {
    return "extern const char " + toUpper(this->getVariableName()) + "[] = {\n";
}
