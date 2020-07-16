# Commands
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
RM = rm -f
MKDIR = mkdir -p

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

${BIN_DIR}/%.o: ${SRC_DIR}/window/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@ ${GTKFLAGS}

${BIN_DIR}/%.o: ${SRC_DIR}/misc/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@ ${GTKFLAGS}

${BIN_DIR}/%.o: ${SRC_DIR}/%.cc
	@echo "building $@..."
	@${CXX} ${CXXFLAGS} -c $< -o $@ ${GTKFLAGS}

output: bin ${OBJ}
	@echo "linking ${OUTPUT}..."
	@${CXX} ${OBJ} ${LDFLAGS} -o ${OUTPUT} ${GTKFLAGS}

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
