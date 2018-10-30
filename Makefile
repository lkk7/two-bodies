EXECUTABLE_NAME = two_bodies
CXX = g++
CXXFLAGS = -Wall -Iinclude
LIBS = -lSDL2 -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJ)
		$(CXX) -o $@ $^ $(LIBS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
		rm $(OBJ)
