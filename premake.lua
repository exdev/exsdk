-- ======================================================================================
-- File         : premake.lua
-- Author       : Wu Jie 
-- Last Change  : 01/05/2013 | 11:29:11 AM | Saturday,January
-- Description  : 
-- ======================================================================================

local destdir = "_build/" .. _ACTION .. "/"

--/////////////////////////////////////////////////////////////////////////////
-- Solution: exSDK
--/////////////////////////////////////////////////////////////////////////////

solution "exSDK"

    configurations { "Debug", "Release" }
    location (destdir)

    defines {
        -- allegro defins
        "MAC_OS_X_VERSION_MIN_REQUIRED=1060",
        "ALLEGRO_LIB_BUILD",
        "ALLEGRO_SRC",

        -- exsdk defines
        "EX_USE_DL_MALLOC",
        "EX_USE_MEMORY_MANAGER",
    }

    -- ======================================================== 
    -- Project: Allegro (library) 
    -- ======================================================== 

    project "Allegro"
        kind "StaticLib"
        language "C"
        targetname "allegro"

        includedirs {
            -- "/System/Library/Frameworks/AppKit.framework/Headers/",
            -- "/System/Library/Frameworks/AudioToolbox.framework/Headers/",
            -- "/System/Library/Frameworks/IOKit.framework/Headers/",
            -- "/System/Library/Frameworks/OpenAL.framework/Headers/",
            -- "/System/Library/Frameworks/OpenGL.framework/Headers/",
            -- "/System/Library/Frameworks/AGL.framework/Headers/",
            "ext/allegro-5.0.8/include/",
        } 

        files { 
            -- "ext/allegro-5.0.8/addons/**.c",
            "ext/allegro-5.0.8/src/**.c",
            "ext/allegro-5.0.8/src/**.m",
        }

        excludes {
            "ext/allegro-5.0.8/src/gp2xwiz/**",
            "ext/allegro-5.0.8/src/iphone/**",
            "ext/allegro-5.0.8/src/linux/**",
            -- "ext/allegro-5.0.8/src/macosx/**",
            -- "ext/allegro-5.0.8/src/unix/**",
            "ext/allegro-5.0.8/src/win/**",
            "ext/allegro-5.0.8/src/x/**",
        }

        configuration "Debug"
            objdir ( destdir .. "Allegro/debug/objs/" )
            targetdir ( destdir .. "Allegro/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( destdir .. "Allegro/release/objs/" )
            targetdir ( destdir .. "Allegro/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    
 
    -- ======================================================== 
    -- Project: exSDK (exec)
    -- ======================================================== 

    project "exSDK"
        kind "ConsoleApp"
        language "C"
        targetname "exsdk"

        includedirs {
            "ext/dlmalloc-2.8.6/",
            "ext/allegro-5.0.8/include/",
            -- "ext/physfs-2.0.3/include/",
            "ext/lua-5.2.1/",
            -- "ext/luagl/",
            "src/"
        } 

        files { 
            "ext/dlmalloc-2.8.6/**.c",
            -- "ext/physfs-2.0.3/**.c",
            "ext/lua-5.2.1/**.c",
            -- "ext/luagl-1.8/**.c",
            "src/**.c",
        }

        excludes {
            "ext/lua-5.2.1/lua.c",
            "ext/lua-5.2.1/luac.c",
        }

        links {
            "AppKit.framework/",
            "AudioToolbox.framework/",
            "IOKit.framework/",
            "OpenAL.framework/",
            "OpenGL.framework/",
            "AGL.framework/",
            "Allegro",
        }

        configuration "Debug"
            objdir ( destdir .. "exSDK/debug/objs/" )
            targetdir ( destdir .. "exSDK/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( destdir .. "exSDK/release/objs/" )
            targetdir ( destdir .. "exSDK/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    
