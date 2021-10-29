CC := g++
RM := rm

SRC_DIR := ./src
OBJ_DIR := ./obj
EXE := main

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
HEAD_FILES := $(wildcard $(SRC_DIR)/*.hpp)
SOURCES := $(SRC_FILES) $(HEAD_FILES)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
LDFLAGS := -std=c++14
CPPFLAGS := $(WARNINGS) -std=c++14 -O0

$(EXE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SOURCES)
	$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_DIR)/*
	$(RM) $(EXE)