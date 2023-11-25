#ifndef DOCUMENTH
#define DOCUMENTH
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <exception>


class Document{
    private:
    std::string nameFile; // имя файла записывается всегда без расширения .txt (document)
    double type; // тип документа может содержать в себе "." (2.3) или может быть просто целым числом (4)
    std::string place; // местополодение документа записывается 1 словом
    long int date; // дата записывается без разделительных знаков в формате ГГГГММДД (20040517)
    public:
    Document();
    Document(const char* file, double type, const char* place, int date); // вводится имя файла, тип документа, местоположение, дата сдачи
    Document(std::string& file, double type, std::string& place, int date);
    Document(std::string& file, double type, const char* place, int date);
    Document(Document& a);
    ~Document();

    void setName(std::string& name);
    void setType(double type);
    void setPlace(std::string& place);
    void setDate(int date);

    std::string getName();
    double getType();
    std::string getPlace();
    int getDate();

    // void writeToDocument(std::string& nameFile);
    // void writeDocument(std::string& nameFile);
    // void renameDocument(std::string& newNameFile);
    // void deleteDocument(std::string& nameFile);
    void createFile();
};

void init(std::vector<std::shared_ptr<Document>>& a);

void readBinFile(std::string& name, double* fType, int* fDate, int sizePlace, char* fPlace);

bool menu(std::vector<std::shared_ptr<Document>>& a);
void outputDocs(std::vector<std::shared_ptr<Document>>& a);
void createNewFile(std::vector<std::shared_ptr<Document>>& a);
void writeFile();
void addToFile();
void renameFile(std::vector<std::shared_ptr<Document>>& a);
void deleteFile(std::vector<std::shared_ptr<Document>>& a);
void searchByType(std::vector<std::shared_ptr<Document>>& a);
void searchPlaceByName(std::vector<std::shared_ptr<Document>>& a);
void groupByDate(std::vector<std::shared_ptr<Document>>& a);

#endif