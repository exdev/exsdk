-- ======================================================================================
-- File         : test_css.lua
-- Author       : Wu Jie 
-- Last Change  : 05/20/2013 | 14:09:10 PM | Monday,May
-- Description  : 
-- ======================================================================================

return {

    background = { 1, 1, 1 },
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        -- local text = "Hello World Yes I am"

        -- local r1 = text:find( " " )
        -- print ( "result 1 = " .. r1 ) 

        -- local r2 = text:find( " ", r1+1 )
        -- print ( "result 2 = " .. r2 ) 

        -- local r3 = text:find( " ", r2+1 )
        -- print ( "result 3 = " .. r3 ) 

        -- print ( "1 = " .. text:sub(1,r1) ) 
        -- print ( "2 = " .. text:sub(r1+1,r2) ) 
        -- print ( "3 = " .. text:sub(r2+1,r3) ) 

        local style = ui.css.build()
                            .font( "normal 20px MSYH, Bitstream Vera Sans Mono" )
                            -- .margin("0px 0px 0px 10px")
                            -- .border("20px 10px")
                            -- .padding("auto")
                            -- .color("rgb( 255, 0, 0) ")
                            .done()

        -- -- local style = ui.css.build()
        -- --                     .font_size("20px")
        -- --                     .text_outline("1px #000")
        -- --                     .color("#0f0")
        -- --                     .margin("0px 0px 0px 10px")
        -- --                     .done()

        debug.dump(style)
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
    end
}
