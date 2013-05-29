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
        table.deepcopy ( _root_el.style, ui.css.build() 
            .margin( "10px 10px 10px 10px" )
            .border( "2px 2px 2px 2px" )
            .done()
        )

        -- first class children
        _root_el
        :add( "label", "Hello World!", ui.css.build()
            .font_size("20px")
            .text_outline("1px #000")
            .color("#0f0")
            .margin("0px 0px 0px 10px")
            .done()
        )
        :add( "label", "I'm Johnny", ui.css.build()
            .color("#f00")
            .done()
        )
        :add( "label", "Test Padding", ui.css.build()
            .color("#f00")
            .margin("10px 100px 0px 0px")
            .padding("10px 10px 1px 10px")
            .border("1px 1px 1px 5px")
            .border_color("#000")
            .done()
        )

        -- do layout
        ui.layout(_root_el, 0, 0, ex.canvas.width, ex.canvas.height)

        -- setup debug draw
        _root_el.children[3]:debug_draw()
        -- _root_el:debug_draw()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        ui.layout(_root_el, 0, 0, ex.canvas.width, ex.canvas.height)
    end
}

