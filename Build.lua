workspace "Console IDLE"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


files { ".clang-format", ".gitignore", "README.md" }

vpaths {
      ["Solution Items/*"] = { ".clang-format", ".gitignore", "README.md"}
   }


include "App/Build-App.lua"