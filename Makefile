
CXX        ?= g++
CXXFLAGS   += -g -Wall -std=c++0x -Iinclude -Igen/src -Isrc
LDFLAGS    += 

headers     := $(wildcard include/*.h)
srcs        := $(wildcard src/*.cpp)
check_srcs  := $(wildcard test/*.cpp)
priv_header := $(wildcard src/*.h) $(wildcard test/*.h)
extra_dist  := Makefile README.md COPYING.txt

ifeq ($(MSYSTEM), MINGW32)
  EXEEXT    = .exe  
  LIBEXT    = .dll
else
  EXEEXT    =
  LIBEXT    = .so  
endif

.PHONY: all check clean

all: bin/rjson$(LIBEXT)

bin/rjson$(LIBEXT): $(patsubst %.cpp, obj/%.o, $(srcs)) obj/gen/src/JsonLexer.o obj/gen/src/JsonParser.o
	mkdir -p bin/
	mkdir -p lib/
	$(CXX) -shared -fPIC $(CXXFLAGS) $^ $(LDFLAGS) -Wl,--out-implib=lib/librjson.a -o $@
	
# we need to help make a bit here
obj/gen/src/JsonLexer.o: gen/src/JsonLexer.cpp
gen/src/JsonLexer.cpp: src/JsonLexer.fpp
obj/gen/src/JsonParser.o: gen/src/JsonParser.cpp
gen/src/JsonParser.cpp: src/JsonParser.ypp
gen/src/JsonParser.hpp: gen/src/JsonParser.cpp
src/serialisation.cpp: gen/src/JsonParser.hpp

lib/librjson.a: bin/rjson$(LIBEXT)	
	
check: bin/rjson-check$(EXEEXT)	
	./bin/rjson-check$(EXEEXT)

bin/rjson-check$(EXEEXT): $(patsubst %.cpp, obj/%.o, $(check_srcs)) lib/librjson.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -rf bin lib obj

obj/%.o : %.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MD -c $< -o $@
	
gen/%.cpp: %.fpp
	mkdir -p $(shell dirname $@)
	flex -o $@ $^

gen/%.cpp: %.ypp
	mkdir -p $(shell dirname $@)
	bison -o $@	$^

ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, obj/%.d, $(srcs))
-include $(patsubst %.cpp, obj/%.d, $(check_srcs))
endif
