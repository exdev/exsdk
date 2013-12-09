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

local copy_files = function ( _src_dirname, _dest_dirpath )
    local destpath =  _dest_dirpath.."/".._src_dirname

    -- NOTE: don't add '/' at the end of _src_dirname, this will make os.isdir() failed 
    if os.isdir(destpath) then os.rmdir(destpath) end
    os.mkdir(destpath)

    matches = os.matchfiles( _src_dirname.."/**")
    for i=1,#matches do
        -- print ( "copy " .. matches[i] )
        os.mkdir( _dest_dirpath.."/"..path.getdirectory(matches[i]) )
        os.copyfile( matches[i], _dest_dirpath..matches[i] )
    end

    -- TEST: for unit-test
    os.copyfile( "examples/main.lua", _dest_dirpath.."/main.lua" )
end

--
if __COMMAND == "update" then
    copy_files ( "builtin", __DEST_DIR.."ex_wiz/debug/bin/" )
    copy_files ( "builtin", __DEST_DIR.."ex_wiz/release/bin/" )
    return
end

--/////////////////////////////////////////////////////////////////////////////
-- Solution: exSDK
--/////////////////////////////////////////////////////////////////////////////

solution "exSDK"

    configurations { "Debug", "Release" }
    location (__DEST_DIR)

    defines {
        -- SDL, SDL_image
        "SDL_IMAGE_USE_COMMON_BACKEND",
        "LOAD_PNG",
        -- "SAVE_PNG", -- NOTE: this is always defined in the source code
        "LOAD_BMP",
        "SAVE_BMP",
        "LOAD_JPG",
        "SAVE_JPG",
        -- "LOAD_TIF",
        -- "SAVE_TIF",
        -- "LOAD_WEBP",
        -- "SAVE_WEBP",

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
            "HAVE_LIBC",
            "GLEW_STATIC", -- for glew
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
            "ext/zlib-1.2.8/",
            "ext/libpng-1.6.7/",
            "ext/jpeg-9/",
            "ext/physfs-2.0.3/",
            "ext/lua-5.2.2/",
            "ext/yajl-2.0.1/include/",
            "ext/utf8proc-1.1.5/",
            "ext/expat-2.1.0/",
        } 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/glew-1.10.0/include/",
            }
        end

        -- source
        files { 
            "ext/zlib-1.2.8/**.c",
            "ext/libpng-1.6.7/**.c",
            "ext/jpeg-9/**.c",
            "ext/physfs-2.0.3/**.c",
            "ext/lua-5.2.2/**.c",
            "ext/luagl-1.8/**.c",
            "ext/lua_yajl/**.c",
            "ext/lpeg-0.10.2/**.c",
            "ext/utf8proc-1.1.5/utf8proc.c",
            "ext/expat-2.1.0/**.c",
        }
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            files {
                "ext/glew-1.10.0/src/**.c",
            }
        end

        -- source exclude
        excludes {
            "ext/libpng-1.6.7/pngtest.c",
            "ext/libpng-1.6.7/example.c",
            "ext/jpeg-9/cdjpeg.c",
            "ext/jpeg-9/cjpeg.c",
            "ext/jpeg-9/ckconfig.c",
            "ext/jpeg-9/djpeg.c",
            "ext/jpeg-9/example.c",
            "ext/jpeg-9/jmemdos.c",
            "ext/jpeg-9/jmemmac.c",
            "ext/jpeg-9/jmemname.c",
            "ext/jpeg-9/jmemnobs.c",
            "ext/jpeg-9/jpegtran.c",
            "ext/jpeg-9/rdjpgcom.c",
            "ext/jpeg-9/wrjpgcom.c",
            "ext/lua-5.2.2/lua.c",
            "ext/lua-5.2.2/luac.c",
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
    -- Project: SDL (library) 
    -- ======================================================== 

    project "SDL"
        kind "StaticLib"
        language "C"
        targetname "SDL"

        -- include
        includedirs {
            "ext/libpng-1.6.7/",
            "ext/jpeg-9/",
            "ext/SDL-2.0.1/include/",
            "ext/SDL_image-2.0.0/",
        } 
        if __PLATFORM == "win32" then
            includedirs {
                "C:/Program Files/Microsoft DirectX SDK (June 2010)/Include/",
            } 
        end

        -- source
        files { 
            "ext/SDL-2.0.1/src/*.c",
            "ext/SDL-2.0.1/src/atomic/*.c",
            "ext/SDL-2.0.1/src/audio/*.c",
            "ext/SDL-2.0.1/src/cpuinfo/*.c",
            "ext/SDL-2.0.1/src/events/*.c",
            "ext/SDL-2.0.1/src/file/*.c",
            "ext/SDL-2.0.1/src/haptic/*.c",
            "ext/SDL-2.0.1/src/input/**.c",
            "ext/SDL-2.0.1/src/joystick/*.c",
            "ext/SDL-2.0.1/src/libm/*.c",
            "ext/SDL-2.0.1/src/power/*.c",
            "ext/SDL-2.0.1/src/render/*.c",
            "ext/SDL-2.0.1/src/stdlib/*.c",
            "ext/SDL-2.0.1/src/thread/*.c",
            "ext/SDL-2.0.1/src/timer/*.c",
            "ext/SDL-2.0.1/src/video/*.c",
            "ext/SDL_image-2.0.0/**.c",
        }
        if __PLATFORM == "macosx" then
            files { 
                "ext/SDL-2.0.1/src/audio/coreaudio/*.c",
                "ext/SDL-2.0.1/src/audio/disk/*.c",
                "ext/SDL-2.0.1/src/audio/dummy/*.c",
                "ext/SDL-2.0.1/src/file/cocoa/*.m",
                "ext/SDL-2.0.1/src/filesystem/cocoa/*.m",
                "ext/SDL-2.0.1/src/haptic/darwin/*.c",
                "ext/SDL-2.0.1/src/joystick/darwin/*.c",
                "ext/SDL-2.0.1/src/loadso/dlopen/*.c",
                "ext/SDL-2.0.1/src/main/dummy/*.c",
                "ext/SDL-2.0.1/src/power/macosx/*.c",
                "ext/SDL-2.0.1/src/render/opengl/*.c",
                "ext/SDL-2.0.1/src/render/opengles/*.c",
                "ext/SDL-2.0.1/src/render/opengles2/*.c",
                "ext/SDL-2.0.1/src/render/software/*.c",
                "ext/SDL-2.0.1/src/thread/pthread/*.c",
                "ext/SDL-2.0.1/src/timer/unix/*.c",
                "ext/SDL-2.0.1/src/video/cocoa/*.m",
                "ext/SDL-2.0.1/src/video/dummy/*.c",
            }
        elseif __PLATFORM == "win32" then
            files { 
                "ext/SDL-2.0.1/src/audio/directsound/*.c",
                "ext/SDL-2.0.1/src/audio/disk/*.c",
                "ext/SDL-2.0.1/src/audio/dummy/*.c",
                "ext/SDL-2.0.1/src/audio/winmm/*.c",
                "ext/SDL-2.0.1/src/audio/xaudio2/*.c",
                "ext/SDL-2.0.1/src/core/windows/*.c",
                "ext/SDL-2.0.1/src/filesystem/windows/*.c",
                "ext/SDL-2.0.1/src/haptic/windows/*.c",
                "ext/SDL-2.0.1/src/joystick/windows/*.c",
                "ext/SDL-2.0.1/src/loadso/windows/*.c",
                "ext/SDL-2.0.1/src/main/windows/*.c",
                "ext/SDL-2.0.1/src/power/windows/*.c",
                "ext/SDL-2.0.1/src/render/direct3d/*.c",
                "ext/SDL-2.0.1/src/render/opengl/*.c",
                "ext/SDL-2.0.1/src/render/software/*.c",
                "ext/SDL-2.0.1/src/thread/generic/SDL_syscond.c",
                "ext/SDL-2.0.1/src/thread/windows/*.c",
                "ext/SDL-2.0.1/src/timer/windows/*.c",
                "ext/SDL-2.0.1/src/video/dummy/*.c",
                "ext/SDL-2.0.1/src/video/windows/*.c",
            }
        end

        -- configurations
        configuration "Debug"
            objdir ( __DEST_DIR .. "SDL/debug/objs/" )
            targetdir ( __DEST_DIR .. "SDL/debug/bin/" )

            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            objdir ( __DEST_DIR .. "SDL/release/objs/" )
            targetdir ( __DEST_DIR .. "SDL/release/bin/" )

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
            "ext/SDL-2.0.1/include/",
            "ext/SDL_image-2.0.0/",
            "ext/physfs-2.0.3/",
            "ext/lua-5.2.2/",
            "ext/utf8proc-1.1.5/",
            "ext/expat-2.1.0/",
            "core/"
        } 
        if __PLATFORM == "macosx" then
        elseif __PLATFORM == "win32" then
            includedirs {
                "ext/glew-1.10.0/include/",
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
            "ext/SDL-2.0.1/include/",
            "ext/SDL_image-2.0.0/",
            "ext/lua-5.2.2/",
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
            "SDL",
            "ex_core",
        }
        if __PLATFORM == "macosx" then
            links {
                "AppKit.framework/",
                "AudioToolbox.framework/",
                "AudioUnit.framework/",
                "CoreAudio.framework/",
                "ForceFeedback.framework/",
                "Carbon.framework/",
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
                -- "d3d9",
                -- "d3dx9",
                -- "dinput8",
                -- "dsound",
                "winmm",
                "imm32",
                "version",
                "psapi",
                "shlwapi",
                "opengl32",
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

        -- post copies
        copy_files ( "builtin", __DEST_DIR.."ex_wiz/debug/bin/" )
        copy_files ( "builtin", __DEST_DIR.."ex_wiz/release/bin/" )

    -- ======================================================== 
    -- TEST
    -- ======================================================== 

    matches = os.matchfiles("tests/test_*.c")
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
                "ext/SDL-2.0.1/include/",
                "ext/SDL_image-2.0.0/",
                "ext/lua-5.2.2/",
                "core/"
            } 
            if __PLATFORM == "macosx" then
            elseif __PLATFORM == "win32" then
                includedirs {
                    "ext/glew-1.10.0/include/",
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
                "SDL",
                "ex_core",
            }
            if __PLATFORM == "macosx" then
                links {
                    "AppKit.framework/",
                    "AudioToolbox.framework/",
                    "AudioUnit.framework/",
                    "CoreAudio.framework/",
                    "ForceFeedback.framework/",
                    "Carbon.framework/",
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
                    "winmm",
                    "imm32",
                    "version",
                    "psapi",
                    "shlwapi",
                    "opengl32",
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
