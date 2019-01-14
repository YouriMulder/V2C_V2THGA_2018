workspace "GameProject"
	configurations { "Debug", "Release" }
	location "build"

project "MindFuck"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.*" }
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.17763.0"
		filter "configurations:*"
			defines { "SFML_STATIC" }
			filter "system:windows"
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

			filter "system:linux"
				links {
					"sfml-graphics", 
					"sfml-window", 
					"sfml-system"
				}

		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"
			filter "system:windows"
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
			filter "system:windows"
				links {	
					"sfml-graphics-s",
					"sfml-window-s",
					"sfml-system-s",
					"sfml-audio-s",
					"sfml-network-s"
				}		
	