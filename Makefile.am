
ACLOCAL_AMFLAGS       = -I m4

include_HEADERS       = include/rjson.h

pkgconfigdir 		  = $(libdir)/pkgconfig
pkgconfig_DATA 	      = rjson.pc

noinst_HEADERS        = src/JsonLexer.h \
                        src/JsonParser.hpp \
						src/location.hh \
						src/position.hh \
						src/stack.hh

lib_LTLIBRARIES       = librjson.la
                    
librjson_la_LDFLAGS   = -no-undefined -version-info 0:0:0
librjson_la_SOURCES   = src/JsonLexer.cpp \
                        src/JsonParser.cpp \
                        src/Value.cpp \
                        src/serialisation.cpp

check_PROGRAMS        = rjson-test
TESTS                 = rjson-test

rjson_test_CXXFLAGS   = -Iinclude
rjson_test_LDADD      = librjson.la @TEST_LIBS@
rjson_test_SOURCES    = test/array.cpp \
                        test/object.cpp \
                        test/parse.cpp \
                        test/write.cpp \
                        test/main.cpp \
                        test/value.cpp

EXTRA_DIST            = README.md \
                        autogen.sh \
                        test/package.json \
						src/JsonLexer.fpp \
						src/JsonParser.ypp

MAINTAINERCLEANFILES  = src/JsonLexer.cpp \
						src/JsonParser.hpp \
						src/JsonParser.cpp \
						src/location.hh \
						src/position.hh \
						src/stack.hh
						
src/JsonLexer.cpp: src/JsonLexer.fpp
	$(AM_V_GEN) $(FLEX) $(LEXFLAGS) -o $@ $^

src/JsonParser.hpp: src/JsonParser.ypp
src/JsonParser.cpp: src/JsonParser.ypp
	$(AM_V_GEN) $(BISON) $(LEXFLAGS) -o $@ $^
	
