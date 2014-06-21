
Rioki's JSON Library
==================

[![wercker status](https://app.wercker.com/status/a886d8f1173ec97a5ae3bc7121b27290/m "wercker status")](https://app.wercker.com/project/bykey/a886d8f1173ec97a5ae3bc7121b27290)

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
        
        std::cout << std::setw(2) << message;
    }

The above code will output:

    {
      "broadcast": true,
      "from": "rioki",
      "message": "JSON beats XML hands down!",
      "theAwnser": 42,
      "to": "world"
    }

Building (POSIX)
----------------

To build rjson you need a C++ compiter (e.g. gcc), make, bison and flex. These 
are things you should have lying around anyway. 

The build the library simply run make in the root directory of rjson:
    
    make

If you want to check the consistency library on your machine you may also 
want to run the `check` target.

    make check
    
To install the library into your system you simply call the `install`
target:

    make install
    
If you want to control where the library is installed you can specify this
with the `prefix` variables, like so:

    prefix=$HOME/libs make install

If you want to remove the library from your system, use the `uninstall` target:

    make uninstall
    
As with the `install target you can specify the `prefix` variable.
    
Building (Visual Studio)
------------------------

The project contains VS2013 build configuration for 32 and 64 Bit builds. 

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

To write JSON you use the stream insertion operator `<<` with a ostream. You can 
insert either a Value, Array or Object.

Indentation is controlled through the width parameter on the `std::ostream`. 
The easy way to set this is by using `std::setw`. The given value indicates the
indentation width.

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

### Unicode Sequences

The current implementation lacks support for unescaping Unicode sequences 
(e.g. \u2623). This will be amended soon.

License
-------

Copyright (c) 2013-2014 Sean Farrell <sean.farrell@rioki.org>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

