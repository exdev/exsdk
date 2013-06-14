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
        -- 
        _root_el
        :add( "label", "Hello World", ui.css.build()
            .margin("10px")
            .border("2px solid #f00")
            -- .border("3px assets/box.png #fff")
            .font_size("20px")
            .done()
        )

        --
        _root_el.children[1]
        :add( "label", "1st Child", ui.css.build()
            .font_size("16px")
            .text_outline("1px #000")
            .color("#0f0")
            .margin("0px 0px 0px 10px")
            .border("5px solid #00f")
            .done()
        )
        :add( "label", "2nd Child", ui.css.build()
            .font_size("30px")
            .border("2px solid #0f0")
            .color("#000")
            .done()
        )
        :add( "label", "3rd Child", ui.css.build()
            .color("#f00")
            .margin("10px 100px 0px 0px")
            .padding("10px 10px 2px 10px")
            .border("1px 1px 1px 5px")
            .border_color("#000")
            .done()
        )
        :add( "label", "4rd Child", ui.css.build()
            .border("5px solid #000")
            .margin("auto")
            .width("200px")
            .done()
        )

        -- setup debug draw
        -- _root_el.children[1]:debug_draw()
        _root_el.children[1].children[3]:debug_draw()
        -- _root_el:debug_draw()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
    end
}

