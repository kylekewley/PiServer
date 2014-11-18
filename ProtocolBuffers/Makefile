PROTO_SRC := $(wildcard *.proto)
GEN_H := $(PROTO_SRC:.proto=.pb.h)
GEN_CC := $(PROTO_SRC:.proto=.pb.cc)
GEN_JAVA := $(PROTO_SRC:.proto=.java)

CPP_GEN := $(GEN_CC) $(GEN_H)

PROTO_GEN := $(GEN_CC) $(GEN_H) $(GEN_JAVA)

JAVA_INSTALL= ./		#~/AndroidStudioProjects/TemperatureClient/app/src/main/java/kylekewley/garagedooropener/protocolbuffers
CPP_INSTALL_H=../include
CPP_INSTALL_CC=../src

WIRE_COMPILER_JAR=/opt/java/lib/wire-compiler.jar
PROTOC_CPP_COMPILER=protoc

all: $(PROTO_GEN)

cpp: $(CPP_GEN)

java: $(GEN_JAVA)

%.pb.cc: %.proto
	$(PROTOC_CPP_COMPILER) --cpp_out=./ $<
	cp $(subst .proto,.pb.h,$<) $(CPP_INSTALL_H)
	cp $(subst .proto,.pb.cc,$<) $(CPP_INSTALL_CC)

%.java: %.proto
	java -jar $(WIRE_COMPILER_JAR) --java_out=./ --proto_path=./ $<
	cp $(subst .proto,.java,$<) $(JAVA_INSTALL)

clean:
	rm -f $(PROTO_GEN)
