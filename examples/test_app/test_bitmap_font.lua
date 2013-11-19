-- ======================================================================================
-- File         : test_bitmap_font.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 19:00:27 PM | Thursday,May
-- Description  : 
-- ======================================================================================

local assets = wiz.assets
local btfont1
local btfont2

local lines = {}

return {

    width = 1280,
    height = 720,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        -- load bitmap fonts
        btfont1 = assets.load("assets/BerlinSansFB_MonoOutline.bft")
        btfont2 = assets.load("assets/MolotShadow.bft")
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        local x, y = 10, 10
        local text = "Hello World"

        -- ======================================================== 
        -- normal test
        -- ======================================================== 

        ex.canvas.color = ex.color4f.white
        text = "abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ_?<>{}" 
        ex.canvas.draw_bitmap_text( text, btfont1, x, y )

        y = y + 30
        ex.canvas.color = ex.color4f.white
        text = "abcdefghijklmnopqrstuvwxyz" 
        ex.canvas.draw_bitmap_text( text, btfont2, x, y )

        -- ======================================================== 
        -- multiline test
        -- ======================================================== 

        y = y + 60
        ex.canvas.color = ex.color4f.white
        text = "Hello World\nSystem Initialized\nJohnny Wu Logged in." 
        ex.canvas.draw_bitmap_text( text, btfont1, x, y )

        -- ======================================================== 
        -- page test
        -- ======================================================== 

        y = y + 120
        ex.canvas.color = ex.color4f.yellow
        ex.canvas.draw_rect( x, y, btfont2.pageInfos[0].width, btfont2.pageInfos[0].height, 1.0 )
        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_image( btfont2.pageInfos[0], x, y )

        x = x + btfont2.pageInfos[0].width + 5
        ex.canvas.color = ex.color4f.yellow
        ex.canvas.draw_rect( x, y, btfont1.pageInfos[0].width, btfont1.pageInfos[0].height, 1.0 )
        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_image( btfont1.pageInfos[0], x, y )
    end
}

