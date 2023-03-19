//
// Created by Administrator on 9.03.2023.
//

#ifndef CPPPLAYGROUND_PARAMETERISEDFACTORY_H
#define CPPPLAYGROUND_PARAMETERISEDFACTORY_H
#include <iostream>
namespace ParameterisedFactory{
    class Document{
    public:
        virtual void write()=0;
        virtual void read()=0;
    };

    class TextDocument : public Document{
    public:
        void write() override;
        void read() override;
    };

    class SpreadSheetDocument:public Document{
    public:
        void write() override;

        void read() override;

    };

    using DocumentPtr = std::unique_ptr<Document>;
    class Application{
        DocumentPtr pDocument;
        std::string pType;
    public:
        Application(const std::string &type){
            pType = type;
        }
        void create();
        void open();
        void save();
    };

    class DocumentFactory{
    public:
        static DocumentPtr create(const std::string &type);
    };



    void executeSample();
}
#endif //CPPPLAYGROUND_PARAMETERISEDFACTORY_H
