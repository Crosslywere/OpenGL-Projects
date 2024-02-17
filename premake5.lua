vpaths { ["Sources"] = { "**.c", "**.cpp" }, ["Headers"] = "**.h" }

includedirs { "deps/glad/include", "deps/glfw/include" }

libdirs "deps/libs"

workspace "OpenGL Projects"
architecture "x64"
configurations { "Debug", "Release" }

startproject "Creating a window"

include "deps/glad"

include "Creating a window"

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    runtime "Release"
    optimize "on"