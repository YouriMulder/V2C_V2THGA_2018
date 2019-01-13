workspace "GameProject"
	configurations { "Debug", "Release" }
	location "build"

project "MindFuck"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.*" }

	filter "configurations:*"
		defines { "SFML_STATIC" }
		includedirs { "dependencies/SFML-2.5.1/include" }
		libdirs { "dependencies/SFML-2.5.1/lib" }
		links {
			"opengl32",
			"freetype",
			"winmm",
			"gdi32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg",
			"ws2_32"
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		links {	
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			"sfml-audio-s-d",
			"sfml-network-s-d"
		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		links {	
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"sfml-audio-s",
			"sfml-network-s"
		}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.17763.0"