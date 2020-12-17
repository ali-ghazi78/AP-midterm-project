CXX = g++
CXXFLAGS = -std=c++2a -Wall -I./h -c -g
LXXFLAGS = -std=c++2a -I./h -pthread
OBJECTS = ./obj/main.o ./obj/board.o  
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) 
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/board.o: ./cpp/board.cpp ./h/board.h
	$(CXX) $(CXXFLAGS) ./cpp/board.cpp -o ./obj/board.o

clean:
	rm -fv $(TARGET) $(OBJECTS)
