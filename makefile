EXEC_L = ligador
SRC_L = ligador.cpp

EXEC_M = montador
SRC_M = montador.cpp

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter

all: $(EXEC_L) $(EXEC_M)

$(EXEC_L): $(SRC_L)
	$(CXX) $(CXXFLAGS) -o $(EXEC_L) $(SRC_L)

$(EXEC_M): $(SRC_M)
	$(CXX) $(CXXFLAGS) -o $(EXEC_M) $(SRC_M)

clean:
	rm -f $(EXEC_L) $(EXEC_M)
