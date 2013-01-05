== Changes ==

* allegro (http://alleg.sourceforge.net/)

    1. I rename the src/macosx/system.m to system_m.m, this will prevent
    premake generate the same file system.o, since there already have one in
    src/system.c. Premake says it will fix the same object name issue in 4.5
    or 5.0, so we can switch back when they update the version.  

    2. I copy alplatf.h directly from CMake generates. This file will be
    different when your platform or compiler changes.

* dlmalloc (http://gee.cs.oswego.edu/)

    1. Rename the header and source file from malloc to dlmalloc

    2. Just see those code commented as exSDK ADD.

* mtrace (http://gee.cs.oswego.edu/)

* lua (http://www.lua.org/)

* luaGL (http://luagl.sourceforge.net/)

* physfs (http://icculus.org/physfs/)
