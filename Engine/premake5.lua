project "App"
    -- Input
    files
    {
        "src/**.h", "src/**.cpp",
        "backend/**.h", "backend/**.cpp"
    }

    includedirs
    {
        "src/",
        "backend",
        "./",
        "%{wks.location}/Dependencies/glad/include",
        "%{wks.location}/Dependencies/stb/",
        "%{wks.location}/Dependencies/"
    }

    -- Preprocessor
    defines { "GLFW_INCLUDE_NONE" }

    -- Linker
    links { "glad", "stb" }

    filter { "system:linux" }
        links { "glfw", "GL" }
        libdirs { "/usr/bin", "%{wks.location}/lib/" }
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
    targetdir   "%{wks.location}/bin/"
    objdir      "%{wks.location}/bin-int/"
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