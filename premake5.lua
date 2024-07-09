workspace "LuaInCpp"
	architecture "x64"
	configurations { "Debug", "Rel", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "LuaInCpp"
	location "LuaInCpp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	links { "LuaStatic" } 

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "LuaInCpp/**.h", "LuaInCpp/**.cpp" }

	includedirs {
		"spdlog/include",
		"sol2/include",
		"Lua/src"
	}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Rel"
		defines { "NDEBUG", "REL" }
		symbols "Off"
		optimize "On"

	filter "configurations:Dist"
		defines { "NDEBUG", "DIST" }
		symbols "Off"
		optimize "Speed"

project "LuaStatic"
 	location "Lua"
 	kind "StaticLib"
 	language "C"
 	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
 	
	files { "Lua/src/**.c", "Lua/src/**.h"}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"		

	filter "configurations:Rel"
		defines { "NDEBUG", "REL" }
		symbols "Off"
		optimize "On"
	
	filter "configurations:Dist"
		defines { "NDEBUG", "DIST" }
		symbols "Off"
		optimize "Speed"
