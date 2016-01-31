workspace "San Andreas Multiplayer Romania"
    architecture "x86"
    platforms { "x86" }
    location "projects"
    
	configurations
	{ 
		"Debug", 
		"Release"
	}
    
    filter "action:gmake"
		defines { "LINUX", "HAVE_STDINT_H" }
        linkoptions { "-L../../Build/libs" }
		buildoptions { "-m32 -std=c++14" } 
	
    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
        targetsuffix "_d"
		
    filter "configurations:Release"
        defines { "NDEBUG" }
		flags { "Symbols" } -- Debug Propose
        optimize "On"
        
    links 
    {
        "cppformat",
    }
        
    filter "system:not windows"
        links 
        {
            "mysqlclient",
            "sampgdk"
        }
        
    filter "system:windows"
        libdirs 
        {
            "../Build/libs/",
            "C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/lib"
        }
    
        links 
        { 
            "libmysql",
            "sampgdk4"
        }

project "San Andreas Multiplayer Romania"
    kind "SharedLib"
    language "C++"
    targetname "SAMPRomania"
    targetdir "../Build/bin"
    pchheader "stdafx.hpp"
    pchsource "../Code/stdafx.cpp"
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    includedirs 
    { 
        "../Code",
        "../Includes/cppformat",
        "../Includes/sampgdk",
        os.pathsearch("mysql.h", "C:/Program Files (x86)/MySQL/MySQL Connector C 6.1/include", "/usr/include/mysql")
    }
    
    files 
    { 
        "../Code/**.hpp", 
        "../Code/**.cpp",
        "../Code/**.def"
    }