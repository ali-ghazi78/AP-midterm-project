CXX = g++
CXXFLAGS = -std=c++2a -Wall -I./h -c 
LXXFLAGS = -std=c++2a -I./h -pthread
OBJECTS = ./obj/main.o ./obj/board.o ./obj/menu.o  
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) 
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/board.o: ./cpp/board.cpp ./h/board.h
	$(CXX) $(CXXFLAGS) ./cpp/board.cpp -o ./obj/board.o
./obj/menu.o: ./cpp/menu.cpp ./h/menu.h
	$(CXX) $(CXXFLAGS) ./cpp/menu.cpp -o ./obj/menu.o
# ./obj/color.o:  ./h/color.h
# 	$(CXX) $(CXXFLAGS) ./cpp/color.cpp -o ./obj/color.o

clean:
	rm -fv $(TARGET) $(OBJECTS)
