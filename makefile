EXEC_L = ligador.exe
SRC_L = ligador.cpp

EXEC_M = montador.exe
SRC_M = montador.cpp

CXX = g++

all: $(EXEC_L) $(EXEC_M)
$(EXEC_L): $(SRC_L)
	$(CXX) -o $(EXEC_L) $(SRC_L)

$(EXEC_M): $(SRC_M)
	$(CXX) -o $(EXEC_M) $(SRC_M)
clean:
	rm -f $(EXEC)
