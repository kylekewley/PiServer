OBJS := ServerTests.o  PiServer.o 
CFLAGS := -std=c++11 -pthread 
EXENAME := PiServer.out
LINKFLAGS := -lpthread
# link
PiServer: $(OBJS)
	g++ $(OBJS) -o $(EXENAME) $(LINKFLAGS)

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.cpp
	g++ -c $(CFLAGS) $*.cpp -o $*.o 
	g++ -MM $(CFLAGS) $*.cpp > $*.d

.c.o:
	$(CC) -c $*.c -o $*.o


# remove compilation products
clean:
	rm -f PiServer *.o *.d

