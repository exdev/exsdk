-- ======================================================================================
-- File         : test_rect.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 20:18:52 PM | Thursday,May
-- Description  : 
-- ======================================================================================

return {

    background = "checkerboard",
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function () 
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        local x, y = 10, 10
        local w, h = 180, 30

        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_rect ( x, y, w, h, 1 )

        ex.canvas.color = ex.color4f ( 1.0, 0.0, 1.0, 0.8 )
        ex.canvas.draw_filled_rect ( x, y, w, h )

        y = y + 30 + 10
        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_rect ( x, y, w, h )

        ex.canvas.color = ex.color4f ( 1.0, 1.0, 1.0, 0.8 )
        ex.canvas.draw_filled_rect ( x, y, w, h )
    end
}

