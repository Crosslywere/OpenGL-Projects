vpaths { ["Sources"] = { "**.c", "**.cpp" }, ["Headers"] = "**.h", ["Resource"] = "**.shader.*" }

includedirs { "deps/glad/include", "deps/glfw/include", "commons" }

libdirs "deps/libs"

workspace "OpenGL Projects"
architecture "x64"
configurations { "Debug", "Release" }

startproject "Shaders"

include "deps/glad"

include "Creating a window"
include "Triangles"
include "Shaders"
-- ^^ Projets go here ^^

filter "configurations:Debug"
    runtime "Debug"
	defines { "_DEBUG" }
    symbols "on"

filter "configurations:Release"
    runtime "Release"
	defines { "NDEBUG" }
    optimize "on"

filter "system:windows"
	cppdialect "C++20"
	cdialect "C17"