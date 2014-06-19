LIBFILES :=  PiServer.cc PiParser.cc PiMessage.cc PiErrorMessage.cc PiHeader.pb.cc TestMessage.pb.cc Ping.pb.cc ParseError.pb.cc  GroupRegistration.pb.cc TestParser.cc PingParser.cc GroupRegistrationParser.cc ClientManager.cc CustomParserWrapper.cc

SRCDIR = src
HEADERDIR := include
LIBDIRECTORY := lib
EXAMPLEDIR = example
SOURCES := $(LIBFILES:%=$(SRCDIR)/%)

OBJS = $(SOURCES:%.cc=%.o)
HEADERS = $(LIBFILES:%.cc=$(HEADERDIR)/%.h)
DEPEND = $(SOURCES:%.cc=%.d)

CFLAGS := -I$(HEADERDIR) -std=c++11 -pthread -Wall -Winit-self 
LIBNAME := PiServer
LINKFLAGS := -lpthread -lprotobuf

EXAMPLESOURCES := $(EXAMPLEDIR)/ServerTests.cc
EXAMPLEOBJS = $(EXAMPLESOURCES:%.cc=%.o)
EXAMPLEEXE = ServerTests
EXAMPLELINKFLAGS = -L$(LIBDIRECTORY) -l$(LIBNAME) -lprotobuf -lpthread -I$(HEADERDIR)

# link
PiServer: $(OBJS)
	mkdir -p $(LIBDIRECTORY)
	ar rvs $(LIBDIRECTORY)/lib$(LIBNAME).a $(OBJS)


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
	rm -f $(EXAMPLEDIR)/$(EXAMPLEEXE) $(LIBDIRECTORY)/lib$(LIBNAME).a $(SRCDIR)/*.o $(SRCDIR)/*.d $(EXAMPLEDIR)/*.o $(EXAMPLEDIR)/*.d

debug:
	echo $(SOURCES)

example: PiServer $(EXAMPLEOBJS)
	g++ $(EXAMPLEOBJS) -o $(EXAMPLEDIR)/$(EXAMPLEEXE) $(EXAMPLELINKFLAGS)

