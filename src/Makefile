CXX = g++
CXXFLAGS = -std=c++11 -Wall -DDEBUG -g

SRC = $(wildcard *.cpp */*.cpp)
HDR = $(wildcard *.hpp */*.hpp)
OBJ = $(SRC:.cpp=.o)
EXE = catangame

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HDR)  # Add $(HDR) here
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)