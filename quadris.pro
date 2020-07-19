TEMPLATE = app

TARGET = quadris

INCLUDEPATH += .

OBJECTS_DIR = ./bin
MOC_DIR = ./bin

CONFIG += c++17

QT += core gui widgets

# Warn deprecated Qt features
DEFINES += QT_DEPRECATED_WARNINGS

# Files
SOURCES = $$files(*.cc, true)
HEADERS = $$files(*.h, true)
