-- ======================================================================================
-- File         : test_layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/10/2013 | 00:08:12 AM | Friday,May
-- Description  : 
-- ======================================================================================

local ttf_VeraMono

return {

    background = { 1, 1, 1 },
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        ttf_VeraMono = wiz.asset_db.load("assets/VeraMono.ttf")
        _root_el:add( {
            style = {
                min_width = 100,
                min_height = 100,
            }
        },

        {
            style = {
                min_width = 200,
                min_height = 100,
            }
        }
        
        )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        ttf_VeraMono.size = 14
        text = "Draw Elements" 
        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_text( text, ttf_VeraMono, 10, 10 ) 

        ui.layout(_root_el)
        _root_el:debug_draw()
    end
}

