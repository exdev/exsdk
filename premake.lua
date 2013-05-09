-- ======================================================================================
-- File         : premake.lua
-- Author       : Wu Jie 
-- Last Change  : 01/05/2013 | 11:29:11 AM | Saturday,January
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- pre-defined variables
--/////////////////////////////////////////////////////////////////////////////

-- local __SCRIPT_DIR = path.getdirectory(_SCRIPT) .. "/"
local __DEST_DIR = "_build/" .. _ACTION .. "/"
local __PLATFORM = _ARGS[1] or "macosx"
local __COMMAND  = _ARGS[2] or "build"

--/////////////////////////////////////////////////////////////////////////////
-- pre-defined functions
--/////////////////////////////////////////////////////////////////////////////

local copy_builtin_files = function ( _destdir )
    -- NOTE: don't add '/' at the end, this will make os.isdir() failed 
    if os.isdir(_destdir.."/builtin") then os.rmdir(_destdir.."/builtin") end
    os.mkdir(_destdir.."/builtin")

    matches = os.matchfiles( "builtin/**")
    for i=1,#matches do
        -- print ( "copy " .. matches[i] )
        os.mkdir( _destdir.."/"..path.getdirectory(matches[i]) )
        os.copyfile( matches[i], _destdir..matches[i] )
    end

    -- for unit-test
    os.copyfile( "examples/main.lua", _destdir.."/main.lua" )
end

--
if __COMMAND == "update" then
    -- if __PLATFORM == "macosx" then
    --     copy_builtin_files ( __DEST_DIR.."ex_wiz/debug/bin/ex_wiz.app/" )
    --     copy_builtin_files ( __DEST_DIR.."ex_wiz/release/bin/ex_wiz.app/" )
    -- elseif __PLATFORM == "win32" then
        copy_builtin_files ( __DEST_DIR.."ex_wiz/debug/bin/" )
        copy_builtin_files ( __DEST_DIR.."ex_wiz/release/bin/" )
    -- end
    return
end

--/////////////////////////////////////////////////////////////////////////////
-- Solution: exSDK
--/////////////////////////////////////////////////////////////////////////////

solution "exSDK"

    configurations { "Debug", "Release" }
    location (__DEST_DIR)

    defines {
        -- allegro
        "ALLEGRO_STATICLINK",
        "ALLEGRO_LIB_BUILD",
        "ALLEGRO_SRC",

        -- physfs
        "PHYSFS_SUPPORTS_ZIP",

        -- lua
        "LUA_COMPAT_ALL",
        -- "LPEG_DEBUG_PRINT",

        -- exsdk defines
        "EX_USE_DL_MALLOC",
        "EX_USE_MEMORY_MANAGER",
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
    -- Project: Deps
    -- ======================================================== 

    project "Deps"
        kind "StaticLib"
        language "C"
        targetname "Deps"

        -- build options
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            buildoptions { "/wd4996" }
        end

        -- include
        includedirs {
            "ext/zlib-1.2.7/",
            "ext/lpng1514/",
            "ext/physfs-2.0.3/",
            "ext/lua-5.2.1/",
            "ext/yajl-2.0.1/include/",
        } 

        -- source
        files { 
            "ext/zlib-1.2.7/**.c",
            "ext/lpng1514/**.c",
            "ext/physfs-2.0.3/**.c",
            "ext/lua-5.2.1/**.c",
            "ext/luagl-1.8/**.c",
            "ext/lua_yajl/**.c",
            "ext/lpeg-0.10.2/**.c",
        }

        -- source exclude
        excludes {
            "ext/lpng1514/pngtest.c",
            "ext/lua-5.2.1/lua.c",
            "ext/lua-5.2.1/luac.c",
            "ext/physfs-2.0.3/lzma/**.c",
            "ext/physfs-2.0.3/zlib123/**.c",
        }

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "ext/debug/objs/" )
            targetdir ( __DEST_DIR .. "ext/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "ext/release/objs/" )
            targetdir ( __DEST_DIR .. "ext/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    

    -- ======================================================== 
    -- Project: Allegro (library) 
    -- ======================================================== 

    project "Allegro"
        kind "StaticLib"
        language "C"
        targetname "allegro"

        -- build options
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            buildoptions { "/wd4996" }
        end

        -- include
        includedirs {
            "ext/allegro-5.0.8/include/",
            "ext/allegro-5.0.8/addons/primitives/",
            "ext/allegro-5.0.8/addons/image/",
            "ext/zlib-1.2.7/",
            "ext/lpng1514/",
        } 
        if __PLATFORM == "macosx" then
            includedirs {
                -- "/System/Library/Frameworks/AppKit.framework/Headers/", NOTE: in Mac, if we have include problem, uncomment this
            } 
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/jpeg-6b/include/",
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include/",
            } 
        end

        -- source
        files { 
            "ext/allegro-5.0.8/src/**.c",
            "ext/allegro-5.0.8/addons/primitives/**.c",
            "ext/allegro-5.0.8/addons/image/**.c",
            "ext/allegro-5.0.8/addons/main/**.c",
        }
        if __PLATFORM == "macosx" then
            files { 
                "ext/allegro-5.0.8/src/**.m",
                "ext/allegro-5.0.8/addons/image/**.m",
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
                "ext/allegro-5.0.8/addons/image/jpg.c",
                "ext/allegro-5.0.8/addons/image/iphone.m",
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

        -- configurations
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
    -- Project: ex_core
    -- ======================================================== 

    project "ex_core"
        kind "StaticLib"
        language "C"
        targetname "ex_core"

        -- include
        includedirs {
            "ext/freetype-2.4.11/include/",
            "ext/allegro-5.0.8/include/",
            "ext/allegro-5.0.8/addons/primitives/",
            "ext/allegro-5.0.8/addons/image/",
            "ext/physfs-2.0.3/",
            "ext/lua-5.2.1/",
            "core/"
        } 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/glew-1.9.0/include/",
                "ext/glut/include/",
            }
        end

        -- source
        files { 
            "core/**.c",
        }

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "ex_core/debug/objs/" )
            targetdir ( __DEST_DIR .. "ex_core/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "ex_core/release/objs/" )
            targetdir ( __DEST_DIR .. "ex_core/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }    

    -- ======================================================== 
    -- Project: ex_wiz
    -- ======================================================== 

    project "ex_wiz"
        kind "ConsoleApp"
        language "C"
        targetname "ex_wiz"

        -- include
        includedirs {
            "ext/allegro-5.0.8/include/",
            "ext/lua-5.2.1/",
            "core/"
        } 

        -- source
        files { 
            "wiz/**.c",
        }

        -- library path ( for link to search ) 
        libdirs {
            "ext/libs/" .. __PLATFORM .. "/",
        }

        -- link
        links {
            "freetype",
            "yajl_s",
            "Deps",
            "Allegro",
            "ex_core",
        }
        if __PLATFORM == "macosx" then
            links {
                "AppKit.framework/",
                "AudioToolbox.framework/",
                "IOKit.framework/",
                "OpenAL.framework/",
                "OpenGL.framework/",
                "AGL.framework/",
                "bz2",
                "z",
            }
        elseif __PLATFORM == "win32" then
            links {
                "jpeg",
                -- "d3d9",
                -- "d3dx9",
                -- "dinput8",
                -- "dsound",
                "winmm",
                "psapi",
                "shlwapi",
                "opengl32",
                "glew32",
                "glu32",
                "glut32",
            }
        end

        -- linkoptions
        if _ACTION:match("vs.*") ~= nil then
            linkoptions  { 
                "/nodefaultlib:libcmt.lib", 
                "/nodefaultlib:libcmtd.lib", 
            }
        end

        -- flags
        flags { "StaticRuntime" }

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "ex_wiz/debug/objs/" )
            targetdir ( __DEST_DIR .. "ex_wiz/debug/bin/" )
            -- debugdir ( __SCRIPT_DIR .. __DEST_DIR .. "ex_wiz/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "ex_wiz/release/objs/" )
            targetdir ( __DEST_DIR .. "ex_wiz/release/bin/" )
            -- debugdir ( __SCRIPT_DIR .. __DEST_DIR .. "ex_wiz/release/bin/" )

            defines { "NDEBUG" }
            flags { "Optimize" }

        -- if __PLATFORM == "macosx" then
        --     copy_builtin_files ( __DEST_DIR.."ex_wiz/debug/bin/ex_wiz.app/" )
        --     copy_builtin_files ( __DEST_DIR.."ex_wiz/release/bin/ex_wiz.app/" )
        -- elseif __PLATFORM == "win32" then
            copy_builtin_files ( __DEST_DIR.."ex_wiz/debug/bin/" )
            copy_builtin_files ( __DEST_DIR.."ex_wiz/release/bin/" )
        -- end

    -- ======================================================== 
    -- TEST
    -- ======================================================== 

    matches = os.matchfiles("tests/*.c")
    for i=1,#matches do
        -- print ( path.getbasename(matches[i]) )
        local projectName = path.getbasename(matches[i]) 
        local destDir = __DEST_DIR .. projectName .. "/"

        project ( projectName )
            kind "ConsoleApp"
            language "C"
            targetname ( projectName )

            -- include
            includedirs {
                "ext/allegro-5.0.8/include/",
                "ext/allegro-5.0.8/addons/primitives/",
                "ext/allegro-5.0.8/addons/image/",
                "ext/lua-5.2.1/",
                "core/"
            } 
            if __PLATFORM == "macosx" then
            elseif __PLATFORM == "win32" then
                includedirs {
                    "ext/glew-1.9.0/include/",
                    "ext/glut/include/",
                }
            end

            -- source
            files { 
                matches[i],
            }

            -- library path ( for link to search ) 
            libdirs {
                "ext/libs/" .. __PLATFORM .. "/",
            }

            -- link
            links {
                "freetype",
                "yajl_s",
                "Deps",
                "Allegro",
                "ex_core",
            }
            if __PLATFORM == "macosx" then
                links {
                    "AppKit.framework/",
                    "AudioToolbox.framework/",
                    "IOKit.framework/",
                    "OpenAL.framework/",
                    "OpenGL.framework/",
                    "GLUT.framework/",
                    "AGL.framework/",
                    "bz2",
                    "z",
                }
            elseif __PLATFORM == "win32" then
                links {
                    "jpeg",
                    "winmm",
                    "psapi",
                    "shlwapi",
                    "opengl32",
                    "glew32",
                    "glu32",
                    "glut32",
                }
            end

            -- linkoptions
            if _ACTION:match("vs.*") ~= nil then
                linkoptions  { 
                    "/nodefaultlib:libcmt.lib", 
                    "/nodefaultlib:libcmtd.lib" 
                }
            end

            -- configurations
            configuration "Debug"
                objdir ( destDir .. "debug/objs/" )
                targetdir ( destDir .. "debug/bin/" )

                defines { "DEBUG" }
                flags { "Symbols" }

            configuration "Release"
                objdir ( destDir .. "release/objs/" )
                targetdir ( destDir .. "release/bin/" )

                defines { "NDEBUG" }
                flags { "Optimize" }
    end
