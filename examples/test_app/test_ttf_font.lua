-- ======================================================================================
-- File         : test_ttf_font.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 11:09:41 AM | Thursday,May
-- Description  : 
-- ======================================================================================

local assets = wiz.assets
local ttf_VeraMono
local ttf_yahei

local lines = {}

return {

    background = { 0.5, 0.5, 0.5 },

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        -- load fonts
        ttf_VeraMono = assets.load("assets/VeraMono.ttf")
        ttf_yahei = assets.load("assets/yahei.ttf")

        file = io.open( wiz.app.sys_path("assets/content.txt"), "r" )
        for line in file:lines() do 
            table.add( lines, line )
        end
        file:close()
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

        ttf_VeraMono.size = 14
        text = "abcdefghijklmnopqrstuvwxyz-ABCDEFGHIJKLMNOPQRSTUVWXYZ_?<>{}" 
        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_text( text, ttf_VeraMono, x, y ) 

        y = y + 30
        ttf_VeraMono.size = 16
        text = wiz.app.cwd
        ex.canvas.draw_outline_text( text, ttf_VeraMono, ex.color4f.green, ex.color4f.black, 2.0, x, y ) 

        y = y + 30
        ttf_VeraMono.size = 18
        text = wiz.cwd
        ex.canvas.draw_shadow_text( text, ttf_VeraMono, ex.color4f.red, ex.color4f.black, ex.vec2f(1,1), 10, 60 ) 

        -- ======================================================== 
        -- multiline test
        -- ======================================================== 

        y = y + 30
        ttf_VeraMono.size = 14
        text = "Hello World\nSystem Initialized\nJohnny Wu Logged in." 
        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_text( text, ttf_VeraMono, x, y ) 

        x = x + 200
        ttf_VeraMono.size = 14
        text = "Hello World\nSystem Initialized\nJohnny Wu Logged in." 
        ex.canvas.draw_outline_text( text, ttf_VeraMono, ex.color4f.black, ex.color4f.yellow, 1.5, x, y ) 

        -- ======================================================== 
        -- Chinese test
        -- ======================================================== 

        x = 10
        y = y + 80
        ttf_yahei.size = 20
        for i=1,#lines do 
            line = lines[i]
            ex.canvas.draw_outline_text( line, ttf_yahei, ex.color4f.blue, ex.color4f.white, 2.0, x, y ) 
            y = y + ttf_yahei.size + 5
        end
    end
}

