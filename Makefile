SOURCES := ServerTests.cc  PiServer.cc PiParser.cc PiHeader.pb.cc TestMessage.pb.cc Ping.pb.cc TestParser.cc PingParser.cc ClientManager.cc
OBJS = $(SOURCES:%.cc=%.o)

CFLAGS := -std=c++11 -pthread 
EXENAME := PiServer.out
LINKFLAGS := -lpthread -lprotobuf 

# link
PiServer: $(OBJS)
	g++ $(OBJS) -o $(EXENAME) $(LINKFLAGS)

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.cc
	g++ -c $(CFLAGS) $*.cc -o $*.o 
	g++ -MM $(CFLAGS) $*.cc > $*.d

.c.o:
	$(CC) -c $*.c -o $*.o


# remove compilation products
clean:
	rm -f PiServer *.o *.d

debug:
	echo $(OBJS)
