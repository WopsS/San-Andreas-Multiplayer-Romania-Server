# San Andreas Multiplayer Romania Server #

A gamemode written in C++ for San Andreas Multiplayer Romania ([www.sa-mp.ro](http://www.sa-mp.ro)).

### How do I build? ###

1. Download and install **[Visual Studio 2015 Community edition](https://www.visualstudio.com/)** or higher. 
2. Clone this repository.
3. Create project files (**premake\MakeVS2015Projects.bat**).
4. Open solution (**San Andreas Multiplayer Romania.sln**) located in **premake\projects**.
5. Build the generated project files.

**Note**: The plugin has to be a 32-bit library. That means all required libraries have to be compiled in 32-bit and the compiler has to support 32-bit.

### Credits ###

* **MySQL Community** - [MySQL Connector/C](https://dev.mysql.com/downloads/connector/c/)
* **Victor Zverovich** - [cppformat](https://github.com/cppformat/cppformat)
* **Zeex** - [sampgdk](https://github.com/Zeex/sampgdk)