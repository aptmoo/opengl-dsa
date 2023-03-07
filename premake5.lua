workspace "mercury"
   configurations { "Debug", "Release" }

project "app"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/"

   includedirs {"src/", "include/", "src/ext/"}

   filter { "system:linux", "action:gmake" }
      buildoptions { "--std=gnu++17 -Winvalid-pch" }
      libdirs {"lib/", "/usr/lib/"}


   links { "glfw", "GL", "dl", "pthread" }

   defines { "GLFW_INCLUDE_NONE" }

   files { "src/**.cpp", "src/**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"