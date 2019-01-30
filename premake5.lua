workspace "GameProject"
	configurations { "Debug", "Release" }
	location "build"

project "MindFuck"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.*" }
	flags { "FatalCompileWarnings", "FatalLinkWarnings", "FatalWarnings",  }
	cppdialect "C++17"
	optimize "On"

	
	filter { "system:windows" }
		systemversion "10.0.17763.0"
	filter "configurations:*"
		defines { "SFML_STATIC" }
	filter "system:windows"
		includedirs { "dependencies/SFML-2.5.1/include" }
		libdirs { "dependencies/SFML-2.5.1/lib" }

	filter { "system:linux" }
		links {
			"sfml-graphics", 
			"sfml-window", 
			"sfml-system",
			"sfml-audio"
		}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"
	filter { "configurations:Debug", "system:windows" }
		links {	
			"sfml-graphics-s-d.lib",
			"sfml-window-s-d.lib",
			"sfml-system-s-d.lib",
			"opengl32.lib",
			"freetype.lib",
			"winmm.lib",
			"gdi32.lib",
			"openal32.lib",
			"flac.lib",
			"vorbisenc.lib",
			"vorbisfile.lib",
			"vorbis.lib",
			"ogg.lib",
			"ws2_32.lib",
			"sfml-audio-s-d.lib",
		}
	
	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
	filter { "configurations:Release", "system:windows" }
		links {	
			"sfml-graphics-s.lib",
			"sfml-window-s.lib",
			"sfml-system-s.lib",
			"opengl32.lib",
			"freetype.lib",
			"winmm.lib",
			"gdi32.lib",
			"openal32.lib",
			"flac.lib",
			"vorbisenc.lib",
			"vorbisfile.lib",
			"vorbis.lib",
			"ogg.lib",
			"ws2_32.lib",
			"sfml-audio-s.lib",
		}		
	