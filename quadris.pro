TEMPLATE = app
TARGET = quadris
INCLUDEPATH += .
OBJECTS_DIR = ./bin

# Warn deprecated Qt features
DEFINES += QT_DEPRECATED_WARNINGS

# Files
SOURCES = $$files(*.cc, true)
HEADERS = $$files(*.h, true)
