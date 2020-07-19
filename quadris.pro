TEMPLATE = app
TARGET = quadris
INCLUDEPATH += .
OBJECTS_DIR = ./bin

QT += gui widgets core

# Warn deprecated Qt features
DEFINES += QT_DEPRECATED_WARNINGS

# Files
SOURCES = $$files(*.cc, true)
HEADERS = $$files(*.h, true)
