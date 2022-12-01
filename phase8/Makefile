CXX		= g++
CXXFLAGS 	= -Wall -std=c++11

OBJS 		= main.o Node.o Server.o Client.o Message.o NodeList.o MessageIDBuffer.o
PROG 		= scc
all:		$(PROG)

$(PROG):	$(OBJS)
		$(CXX) -o $(PROG) $(OBJS)
clean:;		$(RM) $(PROG) core *.o
		
