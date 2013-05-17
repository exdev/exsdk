-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

-- general
module_add( "defs.lua" )

-- core
module_add( "core/css.lua", "css" )
module_add( "core/layout.lua" )
module_add( "core/element.lua" )

-- interactions
module_add( "interactions/draggable.lua" )

-- widgets
module_add( "widgets/widget.lua" )
