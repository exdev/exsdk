-- ======================================================================================
-- File         : defs.lua
-- Author       : Wu Jie 
-- Last Change  : 05/06/2013 | 10:46:34 AM | Monday,May
-- Description  : 
-- ======================================================================================

local __M = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local event_type = {
    none        = -1,

    -- repaint     = 0,

    mouse_down  = 10,
    mouse_up    = 11,
    mouse_move  = 12,

    key_up      = 20,
    key_down    = 21,
}
__M.event_type = event_type

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local keycode = {
    None = -1,

    -- key char,
    A = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    F = 6,
    G = 7,
    H = 8,
    I = 9,
    J = 10,
    K = 11,
    L = 12,
    M = 13,
    N = 14,
    O = 15,
    P = 16,
    Q = 17,
    R = 18,
    S = 19,
    T = 20,
    U = 21,
    V = 22,
    W = 23,
    X = 24,
    Y = 25,
    Z = 26,

    -- key num
    KEY_0 = 27,
    KEY_1 = 28,
    KEY_2 = 29,
    KEY_3 = 30,
    KEY_4 = 31,
    KEY_5 = 32,
    KEY_6 = 33,
    KEY_7 = 34,
    KEY_8 = 35,
    KEY_9 = 36,

    -- key pad num
    PAD_0 = 37,
    PAD_1 = 38,
    PAD_2 = 39,
    PAD_3 = 40,
    PAD_4 = 41,
    PAD_5 = 42,
    PAD_6 = 43,
    PAD_7 = 44,
    PAD_8 = 45,
    PAD_9 = 46,

    -- function key
    F1  = 47,
    F2  = 48,
    F3  = 49,
    F4  = 50,
    F5  = 51,
    F6  = 52,
    F7  = 53,
    F8  = 54,
    F9  = 55,
    F10 = 56,
    F11 = 57,
    F12 = 58,

    --
    Escape      = 59,
    Tilde       = 60,
    Minus       = 61,
    Equals      = 62,
    Backspace   = 63,
    Tab         = 64,
    Openbrace   = 65,
    Closebrace  = 66,
    Enter       = 67,
    Semicolon   = 68,
    Quote       = 69,
    Backslash   = 70,
    Backslash2  = 71, -- DirectInput calls this DIK_OEM_102: "< > | on UK/Germany keyboards"
    Comma       = 72,
    Fullstop    = 73,
    Slash       = 74,
    Space       = 75,

    --
    Insert  = 76,
    Delete  = 77,
    Home    = 78,
    End     = 79,
    Pgup    = 80,
    Pgdn    = 81,
    Left    = 82,
    Right   = 83,
    Up      = 84,
    Down    = 85,

    PAD_Slash    = 86,
    PAD_Asterisk = 87,
    PAD_Minus    = 88,
    PAD_Plus     = 89,
    PAD_Delete   = 90,
    PAD_Enter    = 91,

    Printscreen = 92,
    Pause       = 93,

    Abnt_C1     = 94,
    Yen         = 95,
    Kana        = 96,
    Convert     = 97,
    Noconvert   = 98,
    At          = 99,
    Circumflex  = 100,
    Colon2      = 101,
    Kanji       = 102,

    PAD_Equals  = 103, -- MacOS X
    Backquote   = 104, -- MacOS X
    Semicolon2  = 105, -- MacOS X
    Command     = 106, -- MacOS X
    Unknown     = 107,

    LShift      = 215,
    RShift      = 216,
    LCtrl       = 217,
    RCtrl       = 218,
    Alt         = 219,
    Altgr       = 220,
    LWin        = 221,
    RWin        = 222,
    Menu        = 223,
    Scrolllock  = 224,
    Numlock     = 225,
    Capslock    = 226,
}
__M.keycode = keycode

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
