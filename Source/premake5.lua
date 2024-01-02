project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/"
    staticruntime "off"

    files { "./**.h", "./**.cpp" }

    includedirs
    {
        "./",
        "../Dependencies/GLFW/include",
        "../Dependencies/glad/include",
        "../Dependencies/glm/"
    }

    links
    {
        "GLFW", "glad"
    }

    targetdir ("../Binaries/")
    objdir ("../Intermediates/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS" }

    filter "system:linux"
        defines { "PLATFORM_LINUX" }
        libdirs { "/usr/lib", "../lib", }
        links { "dl", "m", "pthread", "GL" }
        targetname "App.out"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"