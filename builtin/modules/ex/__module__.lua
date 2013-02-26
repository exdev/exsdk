-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

-- generic
module_add( "canvas.lua", "canvas" )
module_add( "scene.lua", "scene" )

-- basic classes
module_add( "classes/vec2f.lua" )
module_add( "classes/color4f.lua" )
module_add( "classes/texture.lua" )
module_add( "classes/bitmapfont.lua" )

-- engine classes
module_add( "classes/entity.lua" )
module_add( "classes/component.lua" )
