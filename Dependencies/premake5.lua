project "glad"
    -- Input
    files
    {
        "glad/**.h", "glad/**.c"
    }

    includedirs
    {
        "glad/include/"
    }

    -- Preprocessor
    defines { }

    -- Linker
    links {  }

    filter { "system:linux" }
        links { "GL" }
        libdirs { "/usr/bin", "%{wks.location}/lib/" }
    filter {}

    -- Language
    language    "C"
    cdialect  "C99"

    -- Compiler
    filter { "system:linux" }
        toolset "clang" 
    filter {}

    -- Output
    targetdir   "%{wks.location}/lib"
    objdir      "%{wks.location}/bin-int/"
    kind        "StaticLib"

    -- Config 
    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"
    filter{}

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
    filter{}