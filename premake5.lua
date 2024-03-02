vpaths { ["Sources"] = { "**.c", "**.cpp" }, ["Headers"] = "**.h" }

includedirs { "deps/glad/include", "deps/glfw/include", "commons" }

libdirs "deps/libs"

workspace "OpenGL Projects"
architecture "x64"
configurations { "Debug", "Release" }

startproject "Triangles"

include "deps/glad"

include "Creating a window"
include "Triangles"
-- ^^ Projets go here ^^

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    runtime "Release"
    optimize "on"

filter "system:windows"
	cppdialect "C++20"
	cdialect "C17"