project "Shaders"
kind "ConsoleApp"
language "C++"
files { "src/**.cpp", "src/**.h", "res/**.shader.*" }
targetdir "%{prj.location}/bin/%{cfg.buildcfg}"
objdir "%{prj.location}/obj/%{cfg.buildcfg}"
links { "glad", "glfw3" }
defines { "APP_NAME=\"Shaders\"" }