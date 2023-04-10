//
// Created by Administrator on 27.03.2023.
//

#ifndef CPPPLAYGROUND_BUILDER_H
#define CPPPLAYGROUND_BUILDER_H
/*
 * If a class become complex as it may encapsulate more functionality
 * Class structure become complex and requires class objects to have different representations at run time
 * so class has to be instantiated with different structures or different internal states
 * This may require a multitude of constructors with lot of parameters
 * The main problem is object construction becomes complex and error prone
 *
 * To solve this, builder pattern can be used
 * Construction of a complex object can be simplified through builder
 * Builder encapsulates the construction logic in a different class
 * The object is constructed step-by-step other creational patterns construct object in one shot
 *
 *
 * */


#include <windows.h>
#include <iostream>

namespace BuilderPattern{
    void executeBasicExample();
    void executeFileExample();
    void executeModernFluentExample();
}


class Builder{
public:
    virtual void buildPart() = 0;
    virtual ~Builder()=default;

};

class Product{

};

class ConcreteBuilder:public Builder{
    Product * product;
public:
    ConcreteBuilder();
    void buildPart() override;
    Product * getResult();
};

class Director{
    Builder * builder;
public:
    Director(Builder * pBuilder);
    void construct();
};


class File{
    const char * _FileName{};
    DWORD _desiredAccess{};
    DWORD _shareMode{};
    LPSECURITY_ATTRIBUTES _pSA{};
    DWORD _creationDisposition{};
    DWORD _flagsAttributes{};
    HANDLE _hTemplateFile{};

    HANDLE _hFile{};

public:
    File(const char *fileName, DWORD desiredAccess, DWORD shareMode, const LPSECURITY_ATTRIBUTES pSa,
         DWORD creationDisposition, DWORD flagsAttributes, HANDLE hTemplateFile);

    DWORD read(char *buffer,DWORD size);
    DWORD write(const char *buffer,DWORD size);
    void close();
    ~File();
    BOOL isOpen() const;


};

class FileBuilder{
public:
    virtual void setFileName(const char * pFile) = 0;
    virtual void setDesiredAccess(DWORD access) = 0;
    virtual void setShareMode() = 0;
    virtual void setSecurityAttributes() = 0;
    virtual void setCreationDisposition() = 0;
    virtual void setFlagsAttributes() = 0;
    virtual void setTemplateFile() = 0;
    virtual ~FileBuilder()=default;
    virtual File build() = 0;
};

class SimpleFileBuilder:public FileBuilder{
    const char *pFileName{};
    DWORD desiredAccess{};
public:
    void setFileName(const char *pFile) override;

    void setDesiredAccess(DWORD access) override;

    void setShareMode() override;

    void setSecurityAttributes() override;

    void setCreationDisposition() override;

    void setFlagsAttributes() override;

    void setTemplateFile() override;

    File build() override;
};

class FileDirector{
    FileBuilder * fileBuilder;
public:
    FileDirector(FileBuilder *builder);
    void create(const char *pFileName,DWORD desiredAccess);
};

class ModernFluentFileBuilder:public File
{
public:

    class Builder {
        const char* m_pFileName{};
        DWORD m_DesiredAccess{};
        DWORD m_ShareMode{};
        LPSECURITY_ATTRIBUTES m_pSA{};
        DWORD m_CreationDisposition{CREATE_ALWAYS};
        DWORD m_FlagsAttributes{FILE_ATTRIBUTE_NORMAL};
        HANDLE m_hTemplateFile{};
    public:

        Builder(const Builder& other) = delete;

        Builder(Builder&& other) noexcept
                : m_pFileName{other.m_pFileName},
                  m_DesiredAccess{other.m_DesiredAccess},
                  m_ShareMode{other.m_ShareMode},
                  m_pSA{other.m_pSA},
                  m_CreationDisposition{other.m_CreationDisposition},
                  m_FlagsAttributes{other.m_FlagsAttributes},
                  m_hTemplateFile{other.m_hTemplateFile} {
            other.m_pFileName = nullptr ;
            other.m_DesiredAccess = 0 ;
            other.m_ShareMode = 0 ;
            other.m_pSA = nullptr ;
            other.m_CreationDisposition = 0 ;
            other.m_FlagsAttributes = 0 ;
            other.m_hTemplateFile = nullptr ;
        }

        Builder& operator=(const Builder& other) = delete;

        Builder& operator=(Builder&& other) noexcept {
            if (this == &other)
                return *this;
            m_pFileName = other.m_pFileName;
            m_DesiredAccess = other.m_DesiredAccess;
            m_ShareMode = other.m_ShareMode;
            m_pSA = other.m_pSA;
            m_CreationDisposition = other.m_CreationDisposition;
            m_FlagsAttributes = other.m_FlagsAttributes;
            m_hTemplateFile = other.m_hTemplateFile;
            other.m_pFileName = nullptr ;
            other.m_DesiredAccess = 0 ;
            other.m_ShareMode = 0 ;
            other.m_pSA = nullptr ;
            other.m_CreationDisposition = 0 ;
            other.m_FlagsAttributes = 0 ;
            other.m_hTemplateFile = nullptr ;
            return *this;
        }

        Builder(const char *pFileName, DWORD desiredAcces):
                m_pFileName{pFileName},
                m_DesiredAccess{desiredAcces} {

        }
        Builder & ShareMode(DWORD shareMode) {
            m_ShareMode = shareMode ;
            return *this;
        }
        Builder & SecurityAttributes(LPSECURITY_ATTRIBUTES lpsa) {
            m_pSA = lpsa ;
            return *this;
        }
        Builder & CreationDisposition(DWORD creationDisposition) {
            m_CreationDisposition = creationDisposition ;
            return *this;
        }
        Builder & FlagsAttributes(DWORD flagsAttributes) {
            m_FlagsAttributes = flagsAttributes ;
            return *this;
        }
        Builder & TemplateFile(HANDLE templateFile) {
            m_hTemplateFile = templateFile ;
            return *this;
        }
        File Build() {
            return File{m_pFileName, m_DesiredAccess, m_ShareMode,m_pSA,
                        m_CreationDisposition, m_FlagsAttributes, m_hTemplateFile} ;
        }
    };
};


#endif //CPPPLAYGROUND_BUILDER_H
