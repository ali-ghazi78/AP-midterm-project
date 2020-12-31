CXX = g++
CXXFLAGS = -std=c++2a   -O3  -I./h  -c 
LXXFLAGS = -std=c++2a -I./h -pthread
OBJECTS = ./obj/main.o ./obj/bfs.o ./obj/menu.o ./obj/dls.o   
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) 
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/bfs.o: ./cpp/bfs.cpp ./h/bfs.h
	$(CXX) $(CXXFLAGS) ./cpp/bfs.cpp -o ./obj/bfs.o
./obj/menu.o: ./cpp/menu.cpp ./h/menu.h
	$(CXX) $(CXXFLAGS) ./cpp/menu.cpp -o ./obj/menu.o
./obj/dls.o:  ./h/dls.h
	$(CXX) $(CXXFLAGS) ./cpp/dls.cpp -o ./obj/dls.o

clean:
	rm -fv $(TARGET) $(OBJECTS)
