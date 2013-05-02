-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

-- generic
module_add( "enums.lua" )

-- basic classes
module_add( "classes/canvas.lua" )
module_add( "classes/vec2f.lua" )
module_add( "classes/rect.lua" )
module_add( "classes/color4f.lua" )
module_add( "classes/texture.lua" )
module_add( "classes/bitmapfont.lua" )
module_add( "classes/font.lua" )

-- engine classes
module_add( "classes/node.lua" )
module_add( "classes/component.lua" )

--
module_add( "scene.lua", "scene" )
module_add( "event.lua", "event" )
module_add( "gui.lua", "gui" )
