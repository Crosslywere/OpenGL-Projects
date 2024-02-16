project "Creating a window"
kind "ConsoleApp"
language "C++"
files { "src/**.cpp", "src/**.h" }
targetdir "%{prj.location}/bin/%{cfg.buildcfg}"
objdir "%{prj.location}/obj/%{cfg.buildcfg}"
includedirs "%{wks.location}/deps/glad/include"
links { "glad", "glfw3" }