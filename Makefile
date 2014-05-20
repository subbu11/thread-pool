LIBS=-lpthread

all : threadPool

threadPool : ThreadPool.o
	g++ -o threadPool main.cpp ThreadPool.o $(LIBS)

ThreadPool.o :
	g++ -c ThreadPool.cpp  $(LIBS)

clean :
	rm -f *.o threadPool
