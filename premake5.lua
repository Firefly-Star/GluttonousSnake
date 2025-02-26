workspace "GluttonousSnake"
    architecture "x64"
    configurations {"Debug", "Release", "Release with Debug Information"}
    outputfold = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "GluttonousSnake"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        toolset "v143"
        staticruntime "off"
        systemversion "latest"

        targetdir (path.join("bin", outputfold, "%{prj.name}"))
        objdir (path.join("obj", outputfold, "%{prj.name}"))

        files
        {
            "GluttonousSnake/Src/**.cpp",
            "GluttonousSnake/Src/**.h"
        }

        includedirs
        {
            "GluttonousSnake/Src"
        }

        filter "configurations:Debug"
        symbols "On"         
        optimize "Off"       

        filter "configurations:Release"
            symbols "Off"
            optimize "Full"        

        filter "configurations: Release with Debug Information"
            symbols "On"
            optimize "On"

        filter {}