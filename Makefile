
VERSION  := 0.1.0

CXX      ?= g++ 
CXXFLAGS := -std=c++0x -Iinclude $(CXXFLAGS)
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local
 
HEADERS    = $(wildcard include/*.h)
PRIVHDRS   = $(wildcard rjson/*.h) $(wildcard rjson/*.hpp) $(wildcard rjson/*.hh)
SOURCES    = $(wildcard rjson/*.cpp)
TESTSRCS   = $(wildcard test/*.cpp)

EXTRA_DIST = Makefile README.md rjson/JsonLexer.fpp rjson/JsonParser.ypp test/package.json
DIST_FILES = $(HEADERS) $(SOURCES) $(TESTSRCS) $(PRIVHDRS) $(EXTRA_DIST)
 
ifeq ($(OS), Windows_NT)
  EXEEXT    = .exe  
  LIBEXT    = .dll  
else
  EXEEXT    =
  LIBEXT    = .so 
  CXXFLAGS += -fPIC  
endif
 
.PHONY: all check clean install uninstall dist
 
all: librjson$(LIBEXT)

ifeq ($(OS), Windows_NT) 
librjson$(LIBEXT): $(patsubst %.cpp, .obj/%.o, $(SOURCES))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ -o $@ -Wl,--out-implib=$(patsubst %.dll,%.a, $@)
else
librjson$(LIBEXT): $(patsubst %.cpp, .obj/%.o, $(SOURCES))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ -o $@
endif 
 
check: rjson-test$(EXEEXT)	
	cd test && LD_LIBRARY_PATH=.. ../rjson-test$(EXEEXT)
 
rjson-test$(EXEEXT): $(patsubst %.cpp, .obj/%.o, $(TESTSRCS)) librjson$(LIBEXT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@
 
clean: 
	rm -rf .obj librjson$(LIBEXT) librjson.a rjson-test$(EXEEXT)
 
dist:
	mkdir rjson-$(VERSION)
	cp --parents $(DIST_FILES) rjson-$(VERSION)
	tar -czvf rjson-$(VERSION).tar.gz rjson-$(VERSION)
	rm -rf rjson-$(VERSION)

install: librjson$(LIBEXT)
	mkdir -p $(prefix)/include/rjson
	cp $(HEADERS) $(prefix)/include/rjson
ifeq ($(OS), Windows_NT)	
	mkdir -p $(prefix)/lib
	cp librjson.a $(prefix)/lib
	mkdir -p $(prefix)/bin
	cp librjson$(LIBEXT) $(prefix)/bin
else
	mkdir -p $(prefix)/lib
	cp librjson.$(LIBEXT) $(prefix)/lib
endif	
 
uninstall:
	rm -r $(prefix)/include/rjson	
ifeq ($(OS), Windows_NT)
	rm $(prefix)/lib/librjson.a
	rm $(prefix)/bin/librjson$(LIBEXT)
else
	rm $(prefix)/lib/librjson$(LIBEXT)	
endif	
 
.obj/%.o : %.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MD -c $< -o $@	
	
rjson/JsonLexer.fpp: rjson/JsonParser.cpp						
rjson/JsonLexer.cpp: rjson/JsonLexer.fpp
	$(FLEX) -o $@ $^

rjson/JsonParser.hpp: rjson/JsonParser.ypp
rjson/JsonParser.cpp: rjson/JsonParser.ypp
	$(BISON) -o $@ $^
 
ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, .obj/%.d, $(SOURCES))
-include $(patsubst %.cpp, .obj/%.d, $(TESTSRCS))
endif
