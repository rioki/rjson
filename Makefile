
VERSION  := 0.1.0

CXX      ?= g++ 
CXXFLAGS := -std=c++11 -Iinclude -Icontrib $(CXXFLAGS)
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local
 
HEADERS    = $(wildcard include/*.h)
PRIVHDRS   = $(wildcard rjson/*.h) $(wildcard rjson/*.hpp) $(wildcard rjson/*.hh) $(wildcard contrib/include/*.h)
SOURCES    = $(wildcard rjson/*.cpp)
TESTSRCS   = $(wildcard test/*.cpp) contrib/src/rtest.cpp

EXTRA_DIST = Makefile README.md rjson/JsonLexer.fpp rjson/JsonParser.ypp test/package.json
DIST_FILES = $(HEADERS) $(SOURCES) $(TESTSRCS) $(PRIVHDRS) $(EXTRA_DIST)
 
ifeq ($(OS), Windows_NT)
  EXEEXT    = .exe  
  LIBEXT    = .dll
else
  EXEEXT    =
  LIBEXT    = .so  
endif
 
.PHONY: all check clean install uninstall dist
 
all: rjson$(LIBEXT)
 
rjson$(LIBEXT): $(patsubst %.cpp, .obj/%.o, $(SOURCES))
	$(CXX) -shared -fPIC $(CXXFLAGS) $(LDFLAGS) $^ -o $@
 
check: rjson-test$(EXEEXT)	
	cd test && ../rjson-test$(EXEEXT)
 
rjson-test$(EXEEXT): $(patsubst %.cpp, .obj/%.o, $(TESTSRCS)) rjson$(LIBEXT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@
 
clean: 
	rm -rf .obj rjson$(LIBEXT) rjson-test$(EXEEXT)	
 
dist:
	mkdir rjson-$(VERSION)
	cp --parents $(DIST_FILES) rjson-$(VERSION)
	tar -czvf rjson-$(VERSION).tar.gz rjson-$(VERSION)
	rm -rf rjson-$(VERSION)
 
install: rjson$(LIBEXT)
	mkdir -p $(prefix)/include/rjson
	cp $(HEADERS) $(prefix)/include/rjson
	mkdir -p $(prefix)/lib
	cp rjson$(LIBEXT) $(prefix)/lib
ifeq ($(OS), Windows_NT)
	mkdir -p $(prefix)/bin
	cp rjson$(LIBEXT) $(prefix)/bin
endif	
 
uninstall:
	rm -r $(prefix)/include/rjson
	rm $(prefix)/lib/rjson$(LIBEXT)
ifeq ($(OS), Windows_NT)
	rm $(prefix)/bin/rjson$(LIBEXT)
endif	
 
.obj/%.o : %.cpp
	mkdir -p $(shell dirname $@)
	$(CXX) $(CXXFLAGS) -MD -c $< -o $@	
	
src/JsonLexer.fpp: src/JsonParser.cpp						
src/JsonLexer.cpp: src/JsonLexer.fpp
	$(FLEX) -o $@ $^

src/JsonParser.hpp: src/JsonParser.ypp
src/JsonParser.cpp: src/JsonParser.ypp
	$(BISON) -o $@ $^
 
ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.cpp, .obj/%.d, $(SOURCES))
-include $(patsubst %.cpp, .obj/%.d, $(TESTSRCS))
endif