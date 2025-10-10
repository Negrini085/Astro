CXXFLAGS:= -Wall -pedantic

CC = g++

compila: main.x

%.x: %.o
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) ${CXXFLAGS} $< -c

clean :
	rm *.o main.x
