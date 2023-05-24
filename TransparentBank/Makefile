CFLAGS = -Wall -Werror -DRELEASE
objects = main1 main2

all: $(objects) main3

main1: Initializer.o
	g++ $(CFLAGS) Initializer.o -o main1

main2: Client.o 
	g++ $(CFLAGS) Client.o -o main2

main3: Deinitializer.o
	g++ $(CFLAGS) Deinitializer.o -o main3

Initializer.o: Initializer.cpp Account.hpp
	g++ $(CFLAGS) -c Initializer.cpp

Client.o: Client.cpp Account.hpp
	g++ $(CFLAGS) -c Client.cpp

Deinitializer.o: Deinitializer.cpp Account.hpp
	g++ $(CFLAGS) -c Deinitializer.cpp

clean:
	rm -rf *.o main


