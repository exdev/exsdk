// ======================================================================================
// File         : textutil.h
// Author       : Wu Jie 
// Last Change  : 02/17/2014 | 11:33:23 AM | Monday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TEXTUTIL_H_1392608008
#define TEXTUTIL_H_1392608008
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// http://baike.baidu.com/view/40801.htm
// http://www.ipmtea.net/javascript/201009/23_294.html
// ------------------------------------------------------------------ 

static inline bool ex_is_chinese ( int _ch ) {
    return (0x2E80 <= _ch && _ch <= 0xFAFF) 
        && (
           (0x4E00 <= _ch && _ch <= 0x9FBF) // CJK Unified Ideographs (*most frequency) 
        || (0x2E80 <= _ch && _ch <= 0x2EFF) // CJK Radicals Supplement
        || (0x2F00 <= _ch && _ch <= 0x2FDF) // Kangxi Radicals
        || (0x3000 <= _ch && _ch <= 0x303F) // CJK Symbols and Punctuation
        || (0x31C0 <= _ch && _ch <= 0x31EF) // CJK Strokes
        || (0x3200 <= _ch && _ch <= 0x32FF) // Enclosed CJK Letters and Months
        || (0x3300 <= _ch && _ch <= 0x33FF) // CJK Compatibility
        || (0x3400 <= _ch && _ch <= 0x4DBF) // CJK Unified Ideographs Extension A
        || (0x4DC0 <= _ch && _ch <= 0x4DFF) // Yijing Hexagrams Symbols
        || (0xF900 <= _ch && _ch <= 0xFAFF) // CJK Compatibility Ideographs
        );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline bool ex_is_japanese ( int _ch ) {
    return (0x3040 <= _ch && _ch <= 0x309F) // Hiragana 
        || (0x30A0 <= _ch && _ch <= 0x30FF) // Katakana
        || (0x31F0 <= _ch && _ch <= 0x31FF) // Katakana Phonetic Extensions
        ;
}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END TEXTUTIL_H_1392608008
// #################################################################################
