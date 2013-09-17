
Rioki's JSON Library
==================

This library implements JSON serialisation for C++.

Examples
--------

Let us assume you need to parse [package.json] files and output some basic info 
about a node package. (Note that error handling was omitted.)

[package.json]: http://package.json.nodejitsu.com/

    #include <iostream>
    #include <fstream>
    #include <rjson.h>
   
    int main()
    {
        rjson::Object package;
        
        std::ifstream input("package.json");
        input >> package;
        
        std::string name    = package["name"];
        std::string version = package["version"];
        bool preferGlobal   = package["preferGlobal"];
        rjson::Array tags   = package["tags"];
        
        std::cout << name << " " << version << std::endl;
        if (preferGlobal) 
        {
            std::cout << "  global package" << std::endl;
        }
        std::cout << "  tags: ";
        for (size_t i = 0; i < tags.size(); i++)
        {
            std::string tag = tags[i];
            std::cout << tag;
            if (i != tags.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        return 0;
    }

As you can see, the use of rjson is almost as simple as writing JavaScript. 
There is to note that `rjson::Object` is actually a `std::map<std::string, rjson::Value>`
and `rjson::Array` is actually a `std::vector<rjson::Value>`. This means that 
you can use all the well known STL manipulation functions.

Writing JSON is also straight forward:

    #include <iostream>   
    #include <rjson.h>
   
    int main()
    {
        rjson::Object message;
        message["from"]      = "rioki";
        message["to"]        = "world";
        message["message"]   = "JSON beats XML hands down!"
        message["broadcast"] = true;
        message["theAwnser"] = 42;
        
        std::cout << message;
    }

The above code will output:

    {"broadcast":true,"from":"rioki","message":"JSON beats XML hands down!","theAwnser":42,"to":"world"}

Granted, it is not formatted for human readability, but it is valid JSON. 
(Formatting will be added in a later stage.)

Building
--------

To build rjson you need a C++ compiter (e.g. gcc), make, bison and flex. These 
are things you should have lying around anyway. 

The build the library simply run make in the root directory of rjson:
    
    make

If you want to check the consistency library on your machine you may also 
want to run the `check` target.

    make check
    
(Install and uninstall targets not yet realised.)

Building (Visual Studio)
------------------------

Building under Visual Studio is not actively supported, but should work with 
little extra effort. (Tested with Visual Studio 2010.)

First you need bison and flex. Although you can get bison and flex standalone for
windows (e.g. [though MinGW32][1]), I strongly advise to install MinGW32 with 
MSys and the MSys-Developer Tool Kit. This can easily be done with the automated
installer [mingw-get]. (You need mingw32-base, msys-base and msys-developer-toolkit)

Now that you have bison and flex, you need to generate the lexer and parser. 
To do that you either open cmd window or WinGW Shell (bash). 

    cd <location of rjson>
    cd src
    flex -o JsonLexer.cpp JsonLexer.fpp
    bison -o JsonParser.cpp JsonParser.ypp
    
This will create a two source files and a bunch of header files. 

As a final step you need to copy the FlexLexer.h file to the src folder. This 
file is located where you installed mingw32, for example `C:\MinGW\msys\1.0\include\FlexLexer.h`

Now that all source code is generated and in one place you can move onto vanilla 
Visual Studio. 

The first step is to create a "Win32 Console Application" project and it should 
be a "Static Library" without "recompiled Headers" and obviously no "MFC".

For the second step you remove all sources, if any. 

The third is to add all sources under `src` to the project. If you want you can
also add `rjson.h` that is located under the include folder.

The fourth and final step in creating the project is, you need to fix the include
locations. In the project properties, you change the value of "C/C++ > General >
Additional Include Directories" to "include;src".

This is it, you can now build rjson under Visual Studio.

[1]: http://sourceforge.net/projects/mingw/files/MSYS/Extension/
[mingw-get]: https://sourceforge.net/projects/mingw/files/latest/download 

Reference
---------

rjson is built up of three classes:

* Value
* Object
* Array

### Value

The Value class represents an container for JSON values. These can be null, 
boolean, number, string, array or object. To facilitate conversion to and from 
C++, the value class implements implicit constructor and cast operators. 

### Value Type

To get the value type stored in a Value you use the `get_type()` method. It returns 
the Type enum and has the following values:

* TYPE_NULL
* TYPE_BOOLEAN
* TYPE_NUMBER
* TYPE_STRING
* TYPE_ARRAY
* TYPE_OBJECT

The mapping is as follows:

* TYPE_NULL: no usable value
* TYPE_BOOLEAN: bool
* TYPE_NUMBER: short, unsinged short, int, unsinged int, long, unsinged long
  long long, unsinged long long, float, double
* TYPE_STRING: const char*, std::string
* TYPE_ARRAY: Array
* TYPE_OBJECT: Object

### Object

The Object class is actually a typedef of `std::map<std::string, rjson::Value>`.
As such all methods of `std::map` may be used.

### Array

The Array class is actually a typedef of `std::vector<rjson::Value>`.
As such all methods of `std::vector` may be used.

### Reading JSON

To read JSON you use the stream extraction operator `>>` with a istream. 
The general case, is to use the Value class, since JSON may either be an object 
or array. If you know which type to expect you may use the Array and Object 
class instead.

### Writing JSON

To write JSON you use the stream insertion operator '<<' with a ostream. You can 
insert either a Value, Array or Object.

Caveats
-------

### Numbers

Like JavaScript the numbers are stored in a double floating point value. This 
may result in loss of data with large numbers. If you really require exact 
transport of numbers, encode the number in a string for transport. 

### Object Members

Because the underlying implementation of an object is a `std::map`, the order 
of the members is not recorded. As a result reading and writing a JSON file 
will probably reorder the members. Semantically the files are equal, yet it 
may not be what was expected.

### Human Readable Output

Currently the library outputs JSON without any formatting. This may not be 
what was expected, but it is valid JSON.

License
-------

rjson is distributed under the MIT license. See COPYING.txt for details.
