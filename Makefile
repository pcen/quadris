# Commands
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -MMD
RM = rm -f
MKDIR = mkdir -p
LDFLAGS = -lX11 -L/usr/X11/lib -pthread

# Source locations
SRC_DIR = ./src

# Output files
BIN_DIR = ./bin
OUTPUT = quadris

# Wildcard all .cc files
OBJ_FILES = ${addsuffix .o, ${basename ${notdir \
${wildcard ${SRC_DIR}/blocks/*.cc}              \
${wildcard ${SRC_DIR}/game/*.cc}                \
${wildcard ${SRC_DIR}/graphics/*.cc}            \
${wildcard ${SRC_DIR}/levels/*.cc}              \
${wildcard ${SRC_DIR}/misc/*.cc}                \
${wildcard ${SRC_DIR}/views/*.cc}               \
${wildcard ${SRC_DIR}/window/*.cc}              \
${wildcard ${SRC_DIR}/*.cc}                     \
}}}
# Compile to bin/*.o
OBJ = ${addprefix ${BIN_DIR}/, ${OBJ_FILES}}
DEPENDS = ${OBJ:.o=.d}

.PHONY: all bin clean output

all: output

# ./views
${BIN_DIR}/%.o: ${SRC_DIR}/views/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

# ./window
${BIN_DIR}/%.o: ${SRC_DIR}/window/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

# ./game
${BIN_DIR}/%.o: ${SRC_DIR}/game/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

# ./generic
${BIN_DIR}/%.o: ${SRC_DIR}/generic/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

# ./main.cc
${BIN_DIR}/%.o: ${SRC_DIR}/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@

output: bin ${OBJ}
	@echo "linking ${OUTPUT}..."
	@${CXX} ${OBJ} -o ${OUTPUT} ${LDFLAGS}

-include ${DEPENDS}

run:
	./${OUTPUT}

test: ${OUTPUT}
	valgrind ./${OUTPUT}

bin:
ifeq (,${wildcard ${BIN_DIR}})
	@echo "creating binary directory..."
	@${MKDIR} ${BIN_DIR}
endif

clean:
	@echo "cleaning project..."
ifneq (,${wildcard ${BIN_DIR}})
	@${RM} ${BIN_DIR}/*
endif
	@${RM} ${OUTPUT}
