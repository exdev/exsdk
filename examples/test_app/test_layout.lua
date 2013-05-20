-- ======================================================================================
-- File         : test_layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/10/2013 | 00:08:12 AM | Friday,May
-- Description  : 
-- ======================================================================================

local ttf_VeraMono

return {

    background = { 1, 1, 1 },
    -- background = "checkerboard",
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        ttf_VeraMono = wiz.asset_db.load("assets/VeraMono.ttf")

        -- root el
        table.deepcopy ( _root_el.style, { 
            margin = { 10, 10, 10, 10 },
            border = { 2, 2, 2, 2 }
        } )

        -- first class children
        _root_el
        :add( "label", "Hello World!", { 
            font_size = 20, 
            text_outline = { 1, { 0, 0, 0, 255 } },
            color = { 0, 255, 0 }, 
            margin = { 0, 0, 0, 10 },
        } )
        :add( "label", "I'm Johnny", { 
            color = { 255, 0, 0 } 
        } )
        :add( "label", "Test Padding", { 
            color = { 255, 0, 0 }, 
            margin = { 10, 100, 0, 0 },
            padding = { 10, 10, 1, 10 },
            border = { 1, 1, 1, 5 },
            border_color = { 0, 0, 0 }
        } )

        -- do layout
        ui.layout(_root_el)

        -- setup debug draw
        _root_el.children[3]:debug_draw()
        -- _root_el:debug_draw()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        ui.layout(_root_el)
    end
}

