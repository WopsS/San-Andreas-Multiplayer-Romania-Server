function file_check(file_name)
  local file_found=io.open(file_name, "r")      

  if file_found==nil then
    return false
  end
  return true
end

solution "San Andreas Multiplayer Romania"
 
    ------------------------------------------------------------------
    -- setup common settings
    ------------------------------------------------------------------
	configurations 
	{ 
		"Debug", 
		"Release"
	}
	
    location "projects"
    platforms { "x86" }
	
    configuration {"gmake"}
		defines { "LINUX", "HAVE_STDINT_H" }
		buildoptions {"-m32 -std=c++14" } 
	
    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
		links { "cppformat_d" }
        targetsuffix "_d"
		
	configuration "Release"
        defines { "NDEBUG" }
		flags { "Symbols" } -- Debug Propose
		links { "cppformat" }
        optimize "On"
 
	------------------------------------------------------------------
    -- logic projects
    ------------------------------------------------------------------	
	project "San Andreas Multiplayer Romania"
		targetname "SAMPRomania"
		kind "SharedLib"
		language "C++"
		targetdir "../Build/bin"
		pchheader "stdafx.hpp"
		pchsource "../Code/stdafx.cpp"
		
		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}
		
		includedirs 
		{ 
			"../Code/",
			"../Includes/cppformat",
			"../Includes/MySQL",
			"../Includes/sampgdk"
		}
		
		files 
		{ 
			"../Code/**.hpp", 
			"../Code/**.cpp",
			"../Code/**.def"
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
				"../Build/libs/"
			}
		
			links 
			{ 
				"libmysql",
				"sampgdk4"
			}
		