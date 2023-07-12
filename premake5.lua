workspace "opengl"
    configurations { "Debug", "Release" }

project "App"
    -- Input
    files
    {
        "src/**.h", "src/**.cpp"
    }

    includedirs
    {
        "src/",
        "ext/glad/include",
        "ext/"
    }

    -- Preprocessor
    defines { "GLFW_INCLUDE_NONE" }

    -- Linker
    links { "glad" }

    filter { "system:linux" }
        links { "glfw", "GL" }
        libdirs { "/usr/bin", "lib/" }
    filter {}

    -- Language
    language    "C++"
    cppdialect  "GNU++17"

    -- Compiler
    filter { "system:linux" }
        toolset "clang" 
    filter {}

    -- Output
    targetname  "App.out"
    targetdir   "bin/"
    objdir      "bin-int/"
    kind        "ConsoleApp"

    -- Config 
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"
    filter{}

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
    filter{}

include "ext"

include "ext"