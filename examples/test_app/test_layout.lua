-- ======================================================================================
-- File         : test_layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/10/2013 | 00:08:12 AM | Friday,May
-- Description  : 
-- ======================================================================================

local ttf_VeraMono

return {

    background = { 0.8, 0.8, 0.8 },
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        ttf_VeraMono = wiz.asset_db.load("assets/VeraMono.ttf")
        _root_el:add( "label", "Hello World!", { font_size = 20 } )
                :add( "label", "I'm Johnny", { color = { 1.0, 0.0, 0.0, 1.0 } }  )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        ui.layout(_root_el)
        _root_el:debug_draw()
    end
}

