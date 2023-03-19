//
// Created by Administrator on 9.03.2023.
//

#include "factory.h"

void Application::create() {
    pDocument = createDoc();
}

void Application::open() {
    pDocument = createDoc();
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

DocumentPtr TextApplication::createDoc() {
    return std::make_unique<TextDocument>();
}

void SpreadSheetDocument::write() {
    std::cout << __FUNCSIG__ << std::endl;
}

void SpreadSheetDocument::read() {
    std::cout << __FUNCSIG__ << std::endl;
}

DocumentPtr SpreadSheetApplication::createDoc() {
    return std::make_unique<SpreadSheetDocument>();;
}

void Factory::executeSample() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    TextApplication app{};
    app.create();
    app.open();
    app.save();

    SpreadSheetApplication app2{};
    app2.create();
    app2.open();
    app2.save();
}
