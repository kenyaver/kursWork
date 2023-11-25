// #pragma once
#include "document.h"

Document::Document() = default; // дефолтный конструктор создания объекта. при создании объекта без параметров, просто выделяется память под все поля, не давая им никаких значений

Document::Document(const char* file, double type, const char* place, int date){ // конструктор создания объекта, создающий файлы, в случае их отсутствия
    this->nameFile = file;
    this->type = type;
    this->place = place;
    this->date = date;
    std::ifstream existing(nameFile + ".txt", std::ios::in); // проверка на существование файла и создание его в случае отсутствия
    if (!existing.is_open()) {
        createFile();
    }
    existing.close();
}

Document::Document(std::string& file, double type, std::string& place, int date){
    this->nameFile = file;
    this->type = type;
    this->place = place;
    this->date = date;
    std::ifstream existing(nameFile + ".txt", std::ios::in);
    if (!existing.is_open()) {
        createFile();
    }
    existing.close();
}

Document::Document(std::string& file, double type, const char* place, int date){
    this->nameFile = file;
    this->type = type;
    this->place = place;
    this->date = date;
    std::ifstream existing(nameFile + ".txt", std::ios::in);
    if (!existing.is_open()) {
        createFile();
    }
    existing.close();
}

Document::~Document() = default; // дефолтный деструктор


Document::Document(Document& a){ // конструктор копирования
    nameFile = a.nameFile;
    type = a.type;
    place = a.place;
    date = a.date;
}

void Document::setName(std::string& name){
    this->nameFile = name;
}

void Document::setType(double type){
    this->type = type;
}

void Document::setPlace(std::string& place){
    this->place = place;
}

void Document::setDate(int date){
    this->date = date;
}

std::string Document::getName(){
    return nameFile;
}

double Document::getType(){
    return type;
}

std::string Document::getPlace(){
    return place;
}

int Document::getDate(){
    return date;
}

// void Document::writeToDocument(std::string& nameFile){
//     std::ofstream file(nameFile, std::ios::app);
//     std::string buffer;
//     std::getline(std::cin, buffer);
//     file << buffer;
//     file.close();
// }

// void Document::writeDocument(std::string& nameFile){
//     std::ofstream file(nameFile, std::ios::out);
//     std::string buffer;
//     std::getline(std::cin, buffer);
//     file << buffer;
//     file.close();
// }

// void Document::deleteDocument(std::string& nameFile){
//     char name[255];
//     strcpy(name, nameFile.c_str());
//     remove(name);
// }

void Document::createFile(){
    std::string txtFile = nameFile + ".txt";
    std::ofstream createTxtFile(txtFile);
    createTxtFile.close();

    std::string binnFile = nameFile + ".bin";
    std::fstream binFile(binnFile, std::ios::binary | std::ios::out);
    binFile.write((char*)&type, sizeof(type));
    binFile.write((char*)&date, sizeof(date));
    int sizePlace = sizeof(place.c_str());
    binFile.write((char*)&sizePlace, sizeof(sizePlace));
    binFile.write(place.c_str(), sizePlace);
    binFile.close();
}

void init(std::vector<std::shared_ptr<Document>>& a){
    std::string directory = "/home/it4ml/Documents/kurs";
    std::string extension = ".txt";
    try{
        for(auto &i: std::filesystem::directory_iterator(directory)){
            if(!std::filesystem::is_regular_file(i.status())){
                continue;
            }

            std::string txtName(i.path().filename());

            bool match = !txtName.compare(txtName.size() - extension.size(), extension.size(), extension);
            if (!match){
               continue;
            }

            std::string name = txtName.erase(txtName.find_first_of("."));
            
            std::string binName = name + ".bin"; 
            double ftype;
            int fdate;
            int size;
            char fplace[256];
            readBinFile(binName, &ftype, &fdate, size, fplace);
            a.push_back(std::make_shared<Document>(name, ftype, fplace, fdate));
        }
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

void readBinFile(std::string& name, double* fType, int* fDate, int sizePlace, char* fPlace){
    std::ifstream file(name, std::ios::binary | std::ios::in);
    file.read((char*)fType, sizeof(fType));
    file.read((char*)fDate, sizeof(fDate));
    file.read((char*)&sizePlace, sizeof(sizePlace));
    file.read(fPlace, sizePlace);
}

void createNewFile(std::vector<std::shared_ptr<Document>>& a){
    std::string name;
    double type;
    std::string place;
    int date;
    std::cout << "\ninput name: ";
    std::cin >> name;
    std::cout << "input type: ";
    std::cin >> type;
    std::cout << "input place: ";
    std::cin >> place;
    std::cout << "input date: ";
    std::cin >> date;
    a.push_back(std::make_shared<Document>(name, type, place, date));
    std::cout << "done!\n";
}

// void Document::writeDocument(std::string& nameFile){
//     std::ofstream file(nameFile, std::ios::out);
//     std::string buffer;
//     std::getline(std::cin, buffer);
//     file << buffer;
//     file.close();
// }

void writeFile(){
    std::string name;
    std::cout << "input name of file: ";
    std::cin >> name;
    std::ofstream file(name, std::ios::out);
    std::string buffer;
    std::cin.ignore();
    std::getline(std::cin, buffer);
    file << buffer;
    file.close();
}

// void Document::writeToDocument(std::string& nameFile){
//     std::ofstream file(nameFile, std::ios::app);
//     std::string buffer;
//     std::getline(std::cin, buffer);
//     file << buffer;
//     file.close();
// }

void addToFile(){
    std::string name;
    std::cout << "\ninput name: ";
    std::cin >> name;
    std::ofstream file(name, std::ios::app);
    std::string buffer;
    std::cin.ignore();
    std::getline(std::cin, buffer);
    file << ' ';
    file << buffer;
    file.close();
}

// void Document::renameDocument(std::string& newNameFile){
//     char newName[255];
//     strcpy(newName, newNameFile.c_str());
//     char oldName[255];
//     strcpy(oldName, nameFile.c_str());
//     rename(oldName, newName);
// }

void renameFile(std::vector<std::shared_ptr<Document>>& a){
    std::string nameFile;
    std::cout << "input name of file without expansion: ";
    std::cin >> nameFile;

    std::string oldNameBin = nameFile + ".bin";
    std::string oldNameTxt = nameFile + ".txt";
    
    std::string newName;
    std::cout << "input new name without expansion: ";
    std::cin >> newName;

    std::string nameT = newName + ".txt";
    std::string nameB = newName + ".bin";

    for(int i = 0; i < a.size(); i++){
        if (a[i]->getName() == nameFile){
            if(rename(oldNameTxt.c_str(), nameT.c_str()) == 0){
                rename(oldNameBin.c_str(), nameB.c_str());
                a[i]->setName(newName);
                std::cout << "OK\n";
            } else {
                std::cout << "not Ok(\n";
            }
            
        }
    }
    std::cout << "done!\n";
}

// void Document::deleteDocument(std::string& nameFile){
//     char name[255];
//     strcpy(name, nameFile.c_str());
//     remove(name);
// }

void deleteFile(std::vector<std::shared_ptr<Document>>& a){
    std::string name;
    std::cout << "input name file without expansion: ";
    std::cin >> name;

    auto iter = a.begin();

    for(int i = 0; i < a.size(); i++){
        if (a[i]->getName() == name){
            std::string nameT = name + ".txt";
            remove(nameT.c_str());
            std::string nameB = name + ".bin";
            remove(nameB.c_str());
            a.erase(iter + i);
        }
    }
    std::cout << "done!\n";    
}

void searchByType(std::vector<std::shared_ptr<Document>>& a){
    double type;
    std::cout << "input type: ";
    std::cin >> type;
    for(auto i: a){
        if(i->getType() == type){
            std::cout << i->getName() << '\t' << i->getType() << '\t' << i->getPlace() << '\t' << i->getDate() << '\n';
        }
    }
    std::cout << '\n';
}

void searchPlaceByName(std::vector<std::shared_ptr<Document>>& a){
    std::string name;
    std::cout << "input name: ";
    std::cin >> name;
    for(auto i: a){
        if(strcmp(i->getName().c_str(), name.c_str()) == 0){
            std::cout << i->getPlace() << '\n';
        }
    }
    std::cout << '\n';
}

void groupByDate(std::vector<std::shared_ptr<Document>>& a){
    int date = 0;
    std::cout << "\ninput date: ";
    std::cin >> date;
    for(auto i: a){
        if(i->getDate() == date){
            std::cout << i->getName() << '\t' << i->getType() << '\t' << i->getPlace() << '\t' << i->getDate() << '\n';
        }
    }
    std::cout << '\n';
}

void outputDocs(std::vector<std::shared_ptr<Document>>& a){
    std::cout << "Documents:-------------------------------\n";
    for(auto i: a){
        std::cout << i->getName() << '\t'
            << i->getType() << '\t'
            << i->getPlace() << '\t'
            << i->getDate() << '\n';
    }
    std::cout << "-----------------------------------------\n";
}

bool menu(std::vector<std::shared_ptr<Document>>& a){
    while(true){
        std::cout << "\nDOCUMENT SYSTEM:\n"
            << "menu:\n"
            << "0) exit\n" // OK
            << "1) create new file\n" // OK
            << "2) write file\n" // OK
            << "3) add to file\n" // OK
            << "4) rename file\n" // OK
            << "5) delete file\n" // OK
            << "6) search by type\n" // OK
            << "7) search place by name\n" // OK
            << "8) group by date\n" // OK
            << "9) output all files\n"; // OK
        int variant = 0;
        std::cout << "input: ";
        std::cin >> variant;
        switch (variant){
            case 0:
                return false;
                break;
            case 1:
                createNewFile(a);
                break;
            case 2:
                writeFile();
                break;
            case 3:
                addToFile();
                break;
            case 4:
                renameFile(a);
                break;
            case 5:
                deleteFile(a);
                break;
            case 6:
                searchByType(a);
                break;
            case 7:
                searchPlaceByName(a);
                break;
            case 8:
                groupByDate(a);
                break;
            case 9:
                outputDocs(a);
                break;
            default:
                std::cout << "\nerror number(\n";
                break;
        }
    }
return true;
}