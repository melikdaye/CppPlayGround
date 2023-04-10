//
// Created by Administrator on 27.03.2023.
//

#include "builder.h"

void BuilderPattern::executeBasicExample() {
    ConcreteBuilder builder;
    Director director{&builder};
    director.construct();
    Product *p = builder.getResult();
    delete p;
}

void BuilderPattern::executeFileExample() {

    SimpleFileBuilder builder{};
    FileDirector director{&builder};

    director.create("../test.txt",FILE_GENERIC_WRITE);
    File file = builder.build();
    file.write("Hello",5);
}

void BuilderPattern::executeModernFluentExample(){
    SECURITY_ATTRIBUTES sa{} ;
    ModernFluentFileBuilder::Builder builder{"../classes.cpp", FILE_GENERIC_READ} ;
    auto f = builder.FlagsAttributes(FILE_ATTRIBUTE_NORMAL)
            .CreationDisposition(OPEN_EXISTING)
            .ShareMode(FILE_SHARE_READ)
            .SecurityAttributes(&sa)
            .Build() ;
    char buffer[1024]{} ;
    f.read(buffer, 1024) ;
    std::cout << buffer ;


    std::string name{"Melik"} ;
    int id{1001} ;
    std::cout << "Name:" << name << std::endl ;
    std::cout << "Id:" << id << std::endl;

    std::cout << "Name:" ;
    std::cout << name ;
    std::cout << std::endl ;

    std::cout << "Id:" ;
    std::cout << id ;
    std::cout << std::endl;
}

ConcreteBuilder::ConcreteBuilder() {
    std::cout << "[ConcreteBuilder] created" << std::endl;
}

void ConcreteBuilder::buildPart() {
    std::cout << "[ConcreteBuilder] Building..." << std::endl;
    std::cout << "Part A" << std::endl;
    std::cout << "Part B" << std::endl;
    std::cout << "Part C" << std::endl;

    product = new Product{};
}

Product *ConcreteBuilder::getResult() {
    std::cout << "[ConcreteBuilder] Returning result" << std::endl;
    return product;
}

Director::Director(Builder *pBuilder):builder{pBuilder} {
    std::cout << "[Director] created" << std::endl;
}

void Director::construct() {
    std::cout << "[Director] construction process started" << std::endl;
    builder->buildPart();
}

File::File(const char *fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES pSa,
           DWORD creationDisposition, DWORD flagsAttributes, HANDLE hTemplateFile) : _FileName(fileName),
                                                                                    _desiredAccess(desiredAccess),
                                                                                    _shareMode(shareMode), _pSA(pSa),
                                                                                    _creationDisposition(
                                                                                            creationDisposition),
                                                                                    _flagsAttributes(flagsAttributes),
                                                                                    _hTemplateFile(hTemplateFile) {

    _hFile = CreateFileA(fileName, desiredAccess, shareMode, pSa, creationDisposition, flagsAttributes,hTemplateFile);
    if(_hFile == INVALID_HANDLE_VALUE){
        throw std::runtime_error("File error");
    }

}

DWORD File::read(char *buffer, DWORD size) {
    DWORD read{};
    ZeroMemory(buffer,size);
    if(ReadFile(_hFile,buffer,size-1,&read, nullptr) == FALSE){
        throw std::runtime_error{"Error while reading"};
    }
    return read;
}

DWORD File::write(const char *buffer, DWORD size) {
    DWORD written{};
    if(WriteFile(_hFile,buffer,size-1,&written, nullptr) == FALSE){
        throw std::runtime_error{"Error while writing"};
    }
    return written;
}

void File::close() {
    CloseHandle(_hFile);
    _hFile = nullptr;
}

File::~File() {
    if(_hFile)
        CloseHandle(_hFile);
}

BOOL File::isOpen() const {
    return _hFile != nullptr;
}

void SimpleFileBuilder::setFileName(const char *pFile) {
     pFileName = pFile;
}

void SimpleFileBuilder::setDesiredAccess(DWORD access) {
    desiredAccess = access;
}

void SimpleFileBuilder::setShareMode() {

}

void SimpleFileBuilder::setSecurityAttributes() {

}

void SimpleFileBuilder::setCreationDisposition() {

}

void SimpleFileBuilder::setFlagsAttributes() {

}

void SimpleFileBuilder::setTemplateFile() {

}

File SimpleFileBuilder::build() {
    return File(pFileName, desiredAccess, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

void FileDirector::create(const char *pFileName, DWORD desiredAccess) {
        fileBuilder->setFileName(pFileName);
        fileBuilder->setDesiredAccess(desiredAccess);
        fileBuilder->setShareMode();
        fileBuilder->setSecurityAttributes();
        fileBuilder->setCreationDisposition();
        fileBuilder->setFlagsAttributes();
        fileBuilder->setTemplateFile();
}
