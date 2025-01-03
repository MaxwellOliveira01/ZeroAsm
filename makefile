EXEC_L = ligador
SRC_L = ligador.cpp

EXEC_M = montador
SRC_M = montador.cpp

CXX = g++

all: $(EXEC_L) $(EXEC_M)
$(EXEC_L): $(SRC_L)
	$(CXX) -o $(EXEC_L) $(SRC_L)

$(EXEC_M): $(SRC_M)
	$(CXX) -o $(EXEC_M) $(SRC_M)
clean:
	rm -f $(EXEC)
