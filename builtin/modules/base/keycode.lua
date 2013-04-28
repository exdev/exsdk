-- ======================================================================================
-- File         : keycode.lua
-- Author       : Wu Jie 
-- Last Change  : 04/28/2013 | 11:52:20 AM | Sunday,April
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

__M.none = -1

-- key char
__M.A = 1
__M.B = 2
__M.C = 3
__M.D = 4
__M.E = 5
__M.F = 6
__M.G = 7
__M.H = 8
__M.I = 9
__M.J = 10
__M.K = 11
__M.L = 12
__M.M = 13
__M.N = 14
__M.O = 15
__M.P = 16
__M.Q = 17
__M.R = 18
__M.S = 19
__M.T = 20
__M.U = 21
__M.V = 22
__M.W = 23
__M.X = 24
__M.Y = 25
__M.Z = 26

-- key num
__M.KEY_0 = 27
__M.KEY_1 = 28
__M.KEY_2 = 29
__M.KEY_3 = 30
__M.KEY_4 = 31
__M.KEY_5 = 32
__M.KEY_6 = 33
__M.KEY_7 = 34
__M.KEY_8 = 35
__M.KEY_9 = 36

-- key pad num
__M.PAD_0 = 37
__M.PAD_1 = 38
__M.PAD_2 = 39
__M.PAD_3 = 40
__M.PAD_4 = 41
__M.PAD_5 = 42
__M.PAD_6 = 43
__M.PAD_7 = 44
__M.PAD_8 = 45
__M.PAD_9 = 46

-- function key
__M.F1  = 47
__M.F2  = 48
__M.F3  = 49
__M.F4  = 50
__M.F5  = 51
__M.F6  = 52
__M.F7  = 53
__M.F8  = 54
__M.F9  = 55
__M.F10 = 56
__M.F11 = 57
__M.F12 = 58

--
__M.Escape      = 59
__M.Tilde       = 60
__M.Minus       = 61
__M.Equals      = 62
__M.Backspace   = 63
__M.Tab         = 64
__M.Openbrace   = 65
__M.Closebrace  = 66
__M.Enter       = 67
__M.Semicolon   = 68
__M.Quote       = 69
__M.Backslash   = 70
__M.Backslash2  = 71 -- DirectInput calls this DIK_OEM_102: "< > | on UK/Germany keyboards"
__M.Comma       = 72
__M.Fullstop    = 73
__M.Slash       = 74
__M.Space       = 75

--
__M.Insert  = 76
__M.Delete  = 77
__M.Home    = 78
__M.End     = 79
__M.Pgup    = 80
__M.Pgdn    = 81
__M.Left    = 82
__M.Right   = 83
__M.Up      = 84
__M.Down    = 85

__M.PAD_Slash    = 86
__M.PAD_Asterisk = 87
__M.PAD_Minus    = 88
__M.PAD_Plus     = 89
__M.PAD_Delete   = 90
__M.PAD_Enter    = 91

__M.Printscreen = 92
__M.Pause       = 93

__M.Abnt_C1     = 94
__M.Yen         = 95
__M.Kana        = 96
__M.Convert     = 97
__M.Noconvert   = 98
__M.At          = 99
__M.Circumflex  = 100
__M.Colon2      = 101
__M.Kanji       = 102

__M.PAD_Equals  = 103 -- MacOS X
__M.Backquote   = 104 -- MacOS X
__M.Semicolon2  = 105 -- MacOS X
__M.Command     = 106 -- MacOS X
__M.Unknown     = 107

__M.LShift      = 215
__M.RShift      = 216
__M.LCtrl       = 217
__M.RCtrl       = 218
__M.Alt         = 219
__M.Altgr       = 220
__M.LWin        = 221
__M.RWin        = 222
__M.Menu        = 223
__M.Scrolllock  = 224
__M.Numlock     = 225
__M.Capslock    = 226

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
