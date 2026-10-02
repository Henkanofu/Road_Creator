QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Имя приложения
TARGET = MyApp
TEMPLATE = app

# Исходные файлы
SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h
