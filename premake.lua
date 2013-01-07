-- ======================================================================================
-- File         : premake.lua
-- Author       : Wu Jie 
-- Last Change  : 01/05/2013 | 11:29:11 AM | Saturday,January
-- Description  : 
-- ======================================================================================

local __DEST_DIR = "_build/" .. _ACTION .. "/"
local __PLATFORM = _ARGS[1] or "macosx"

--/////////////////////////////////////////////////////////////////////////////
-- Solution: exSDK
--/////////////////////////////////////////////////////////////////////////////

solution "exSDK"

    configurations { "Debug", "Release" }
    location (__DEST_DIR)

    defines {
        -- allegro defins
        "ALLEGRO_STATICLINK",
        "ALLEGRO_LIB_BUILD",
        "ALLEGRO_SRC",
    }
    if __PLATFORM == "macosx" then
        defines {
            "MAC_OS_X_VERSION_MIN_REQUIRED=1060",
        }
    elseif __PLATFORM == "win32" then
        defines {
            "WIN32",
            "_WINDOWS",
            "_CRT_SECURE_NO_DEPRECATE", -- msvc treat sprintf, strcpy, ... functions as no safe, we don't want the compile keep warning us
        }
    end

    -- ======================================================== 
    -- Project: Allegro (library) 
    -- ======================================================== 

    project "Allegro"
        kind "StaticLib"
        language "C"
        targetname "allegro"

        -- Build Options
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            buildoptions { "/wd4996" }
        end

        -- include
        includedirs {
            -- "/System/Library/Frameworks/AppKit.framework/Headers/", NOTE: in Mac, if we have include problem, uncomment this
            "ext/allegro-5.0.8/include/",
        } 
        if __PLATFORM == "macosx" then
            includedirs {
                -- "/System/Library/Frameworks/AppKit.framework/Headers/", NOTE: in Mac, if we have include problem, uncomment this
            } 
        elseif __PLATFORM == "win32" then
            includedirs {
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include/",
            } 
        end

        -- source
        files { 
            "ext/allegro-5.0.8/src/**.c",
            "ext/allegro-5.0.8/addons/primitives/**.c",
            "ext/allegro-5.0.8/addons/main/**.c",
        }
        if __PLATFORM == "macosx" then
            files { 
                "ext/allegro-5.0.8/src/**.m",
                "ext/allegro-5.0.8/addons/main/**.m",
            }
        elseif __PLATFORM == "win32" then
        end

        -- source exclude
        excludes {
            "ext/allegro-5.0.8/src/optimized.c", -- We never use GP2XWIZ, so we never want this
        }
        if __PLATFORM == "macosx" then
            excludes {
                "ext/allegro-5.0.8/src/gp2xwiz/**",
                "ext/allegro-5.0.8/src/iphone/**",
                "ext/allegro-5.0.8/src/linux/**",
                -- "ext/allegro-5.0.8/src/macosx/**",
                -- "ext/allegro-5.0.8/src/unix/**",
                "ext/allegro-5.0.8/src/win/**",
                "ext/allegro-5.0.8/src/x/**",
            }
        elseif __PLATFORM == "win32" then
            excludes {
                "ext/allegro-5.0.8/src/gp2xwiz/**",
                "ext/allegro-5.0.8/src/iphone/**",
                "ext/allegro-5.0.8/src/linux/**",
                "ext/allegro-5.0.8/src/macosx/**",
                "ext/allegro-5.0.8/src/unix/**",
                -- "ext/allegro-5.0.8/src/win/**",
                "ext/allegro-5.0.8/src/x/**",
            }
        end

        configuration "Debug"
            objdir ( __DEST_DIR .. "Allegro/debug/objs/" )
            targetdir ( __DEST_DIR .. "Allegro/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "Allegro/release/objs/" )
            targetdir ( __DEST_DIR .. "Allegro/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    
 
    -- ======================================================== 
    -- Project: exSDK
    -- ======================================================== 

    project "exSDK"
        kind "ConsoleApp"
        language "C"
        targetname "exsdk"

        -- define
        defines {
            -- lua
            "LUA_COMPAT_ALL",

            -- exsdk defines
            "EX_USE_DL_MALLOC",
            "EX_USE_MEMORY_MANAGER",
        }

        -- include
        includedirs {
            "ext/dlmalloc-2.8.6/",
            "ext/allegro-5.0.8/include/",
            "ext/allegro-5.0.8/addons/primitives/",
            -- "ext/physfs-2.0.3/include/",
            "ext/lua-5.2.1/",
            "ext/luagl/",
            "src/"
        } 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/glut/include/",
            }
        end

        -- source
        files { 
            "ext/dlmalloc-2.8.6/**.c",
            -- "ext/physfs-2.0.3/**.c",
            "ext/lua-5.2.1/**.c",
            "ext/luagl-1.8/**.c",
            "src/**.c",
        }

        -- source exclude
        excludes {
            "ext/lua-5.2.1/lua.c",
            "ext/lua-5.2.1/luac.c",
        }

        -- library path ( for link to search ) 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            libdirs {
                "ext/glut/lib/win32/",
            }
        end

        -- link
        links {
            "Allegro",
        }
        if __PLATFORM == "macosx" then
            links {
                "AppKit.framework/",
                "AudioToolbox.framework/",
                "IOKit.framework/",
                "OpenAL.framework/",
                "OpenGL.framework/",
                "AGL.framework/",
            }
        elseif __PLATFORM == "win32" then
            links {
                -- "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9",
                -- "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9",
                -- "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86/dinput8",
                -- "C:/Program Files/Microsoft DirectX SDK (June 2010)/Lib/x86/dsound",
                "psapi",
                "shlwapi",
                "opengl32",
                "glu32",
                "glut32",
            }
        end

        configuration "Debug"
            objdir ( __DEST_DIR .. "exSDK/debug/objs/" )
            targetdir ( __DEST_DIR .. "exSDK/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "exSDK/release/objs/" )
            targetdir ( __DEST_DIR .. "exSDK/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    

    -- -- ======================================================== 
    -- -- Project: exTerminal
    -- -- ======================================================== 

    -- project "exTerminal"
    --     kind "ConsoleApp"
    --     language "C"
    --     targetname "exterminal"

    --     -- link
    --     links {
    --         "exSDK",
    --     }

    --     configuration "Debug"
    --         objdir ( __DEST_DIR .. "exSDK/debug/objs/" )
    --         targetdir ( __DEST_DIR .. "exSDK/debug/bin/" )

    --         defines { "DEBUG" }
    --         flags { "Symbols" }

    --     configuration "Release"
    --         objdir ( __DEST_DIR .. "exSDK/release/objs/" )
    --         targetdir ( __DEST_DIR .. "exSDK/release/bin/" )

    --         defines { "NDEBUG" }
    --         flags { "Optimize" }    
