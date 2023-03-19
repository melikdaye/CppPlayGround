//
// Created by Administrator on 9.03.2023.
//

#include "parameterisedFactory.h"
using namespace ParameterisedFactory;
void Application::create() {

    pDocument = DocumentFactory::create(pType);
}

void Application::open() {

    pDocument = DocumentFactory::create(pType);
    pDocument->read();
}

void Application::save() {
    pDocument->write();
}

void TextDocument::write() {
    std::cout << __FUNCSIG__ << std::endl;
}

void TextDocument::read() {
    std::cout << __FUNCSIG__ << std::endl;
}



void SpreadSheetDocument::write() {
    std::cout << __FUNCSIG__ << std::endl;
}

void SpreadSheetDocument::read() {
    std::cout << __FUNCSIG__ << std::endl;
}


DocumentPtr DocumentFactory::create(const std::string &type) {
    if (type == "text")
        return std::make_unique<TextDocument>();
    else if(type == "spreadsheet")
        return std::make_unique<SpreadSheetDocument>();
    return nullptr;
}

void ParameterisedFactory::executeSample() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Application app{"text"};
    app.create();
    app.open();
    app.save();

    Application app2{"spreadsheet"};
    app2.create();
    app2.open();
    app2.save();
}