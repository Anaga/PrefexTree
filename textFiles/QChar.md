
Qt 5.10
Qt Core
C++ Classes
QChar

Qt 5.10.0 Reference Documentation

Contents
Public Types
Public Functions
Static Public Members
Related Non-Members
Detailed Description
QChar Class
The QChar class provides a 16-bit Unicode character. More...

Header:
#include <QChar> 
qmake:
QT += core

List of all members, including inherited members
Obsolete members
Note: All functions in this class are reentrant. 
Public Types

enum 
Category { Mark_NonSpacing, Mark_SpacingCombining, Mark_Enclosing, Number_DecimalDigit, ..., Symbol_Other }
enum 
Decomposition { NoDecomposition, Canonical, Circle, Compat, ..., Wide }
enum 
Direction { DirAL, DirAN, DirB, DirBN, ..., DirWS }
enum 
JoiningType { Joining_None, Joining_Causing, Joining_Dual, Joining_Right, Joining_Left, Joining_Transparent }
enum 
Script { Script_Unknown, Script_Inherited, Script_Common, Script_Latin, ..., Script_SignWriting }
enum 
SpecialCharacter { Null, Tabulation, LineFeed, CarriageReturn, ..., LastValidCodePoint }
enum 
UnicodeVersion { Unicode_1_1, Unicode_2_0, Unicode_2_1_2, Unicode_3_0, ..., Unicode_Unassigned }

Public Functions


QChar()

QChar(ushort code)

QChar(uchar cell, uchar row)

QChar(short code)

QChar(uint code)

QChar(int code)

QChar(SpecialCharacter ch)

QChar(QLatin1Char ch)

QChar(char16_t ch)

QChar(wchar_t ch)

QChar(char ch)

QChar(uchar ch)
Category 
category() const
uchar 
cell() const
unsigned char 
combiningClass() const
QString 
decomposition() const
Decomposition 
decompositionTag() const
int 
digitValue() const
Direction 
direction() const
bool 
hasMirrored() const
bool 
isDigit() const
bool 
isHighSurrogate() const
bool 
isLetter() const
bool 
isLetterOrNumber() const
bool 
isLowSurrogate() const
bool 
isLower() const
bool 
isMark() const
bool 
isNonCharacter() const
bool 
isNull() const
bool 
isNumber() const
bool 
isPrint() const
bool 
isPunct() const
bool 
isSpace() const
bool 
isSurrogate() const
bool 
isSymbol() const
bool 
isTitleCase() const
bool 
isUpper() const
JoiningType 
joiningType() const
QChar 
mirroredChar() const
uchar 
row() const
Script 
script() const
QChar 
toCaseFolded() const
char 
toLatin1() const
QChar 
toLower() const
QChar 
toTitleCase() const
QChar 
toUpper() const
ushort 
unicode() const
ushort &
unicode()
UnicodeVersion 
unicodeVersion() const

Static Public Members

Category 
category(uint ucs4)
unsigned char 
combiningClass(uint ucs4)
UnicodeVersion 
currentUnicodeVersion()
QString 
decomposition(uint ucs4)
Decomposition 
decompositionTag(uint ucs4)
int 
digitValue(uint ucs4)
Direction 
direction(uint ucs4)
QChar 
fromLatin1(char c)
bool 
hasMirrored(uint ucs4)
ushort 
highSurrogate(uint ucs4)
bool 
isDigit(uint ucs4)
bool 
isHighSurrogate(uint ucs4)
bool 
isLetter(uint ucs4)
bool 
isLetterOrNumber(uint ucs4)
bool 
isLowSurrogate(uint ucs4)
bool 
isLower(uint ucs4)
bool 
isMark(uint ucs4)
bool 
isNonCharacter(uint ucs4)
bool 
isNumber(uint ucs4)
bool 
isPrint(uint ucs4)
bool 
isPunct(uint ucs4)
bool 
isSpace(uint ucs4)
bool 
isSurrogate(uint ucs4)
bool 
isSymbol(uint ucs4)
bool 
isTitleCase(uint ucs4)
bool 
isUpper(uint ucs4)
JoiningType 
joiningType(uint ucs4)
ushort 
lowSurrogate(uint ucs4)
uint 
mirroredChar(uint ucs4)
bool 
requiresSurrogates(uint ucs4)
Script 
script(uint ucs4)
uint 
surrogateToUcs4(ushort high, ushort low)
uint 
surrogateToUcs4(QChar high, QChar low)
uint 
toCaseFolded(uint ucs4)
uint 
toLower(uint ucs4)
uint 
toTitleCase(uint ucs4)
uint 
toUpper(uint ucs4)
UnicodeVersion 
unicodeVersion(uint ucs4)

Related Non-Members

bool 
operator!=(QChar c1, QChar c2)
bool 
operator<(QChar c1, QChar c2)
QDataStream &
operator<<(QDataStream &out, QChar chr)
bool 
operator<=(QChar c1, QChar c2)
bool 
operator==(QChar c1, QChar c2)
bool 
operator>(QChar c1, QChar c2)
bool 
operator>=(QChar c1, QChar c2)
QDataStream &
operator>>(QDataStream &in, QChar &chr)

Detailed Description
The QChar class provides a 16-bit Unicode character.
In Qt, Unicode characters are 16-bit entities without any markup or structure. This class represents such an entity. It is lightweight, so it can be used everywhere. Most compilers treat it like an unsigned short.
QChar provides a full complement of testing/classification functions, converting to and from other formats, converting from composed to decomposed Unicode, and trying to compare and case-convert if you ask it to.
The classification functions include functions like those in the standard C++ header <cctype> (formerly <ctype.h>), but operating on the full range of Unicode characters, not just for the ASCII range. They all return true if the character is a certain type of character; otherwise they return false. These classification functions are isNull() (returns true if the character is '\0'), isPrint() (true if the character is any sort of printable character, including whitespace), isPunct() (any sort of punctation), isMark() (Unicode Mark), isLetter() (a letter), isNumber() (any sort of numeric character, not just 0-9), isLetterOrNumber(), and isDigit() (decimal digits). All of these are wrappers around category() which return the Unicode-defined category of each character. Some of these also calculate the derived properties (for example isSpace() returns true if the character is of category Separator_* or an exceptional code point from Other_Control category).
QChar also provides direction(), which indicates the "natural" writing direction of this character. The joiningType() function indicates how the character joins with it's neighbors (needed mostly for Arabic or Syriac) and finally hasMirrored(), which indicates whether the character needs to be mirrored when it is printed in it's "unnatural" writing direction.
Composed Unicode characters (like ring) can be converted to decomposed Unicode ("a" followed by "ring above") by using decomposition().
In Unicode, comparison is not necessarily possible and case conversion is very difficult at best. Unicode, covering the "entire" world, also includes most of the world's case and sorting problems. operator==() and friends will do comparison based purely on the numeric Unicode value (code point) of the characters, and toUpper() and toLower() will do case changes when the character has a well-defined uppercase/lowercase equivalent. For locale-dependent comparisons, use QString::localeAwareCompare().
The conversion functions include unicode() (to a scalar), toLatin1() (to scalar, but converts all non-Latin-1 characters to 0), row() (gives the Unicode row), cell() (gives the Unicode cell), digitValue() (gives the integer value of any of the numerous digit characters), and a host of constructors.
QChar provides constructors and cast operators that make it easy to convert to and from traditional 8-bit chars. If you defined QT_NO_CAST_FROM_ASCII and QT_NO_CAST_TO_ASCII, as explained in the QString documentation, you will need to explicitly call fromLatin1(), or use QLatin1Char, to construct a QChar from an 8-bit char, and you will need to call toLatin1() to get the 8-bit value back.
For more information see "About the Unicode Character Database".
See also Unicode, QString, and QLatin1Char.
Member Type Documentation
enum QChar::Category
This enum maps the Unicode character categories.
The following characters are normative in Unicode:

Constant
Value
Description
QChar::Mark_NonSpacing
0
Unicode class name Mn
QChar::Mark_SpacingCombining
1
Unicode class name Mc
QChar::Mark_Enclosing
2
Unicode class name Me
QChar::Number_DecimalDigit
3
Unicode class name Nd
QChar::Number_Letter
4
Unicode class name Nl
QChar::Number_Other
5
Unicode class name No
QChar::Separator_Space
6
Unicode class name Zs
QChar::Separator_Line
7
Unicode class name Zl
QChar::Separator_Paragraph
8
Unicode class name Zp
QChar::Other_Control
9
Unicode class name Cc
QChar::Other_Format
10
Unicode class name Cf
QChar::Other_Surrogate
11
Unicode class name Cs
QChar::Other_PrivateUse
12
Unicode class name Co
QChar::Other_NotAssigned
13
Unicode class name Cn

The following categories are informative in Unicode:

Constant
Value
Description
QChar::Letter_Uppercase
14
Unicode class name Lu
QChar::Letter_Lowercase
15
Unicode class name Ll
QChar::Letter_Titlecase
16
Unicode class name Lt
QChar::Letter_Modifier
17
Unicode class name Lm
QChar::Letter_Other
18
Unicode class name Lo
QChar::Punctuation_Connector
19
Unicode class name Pc
QChar::Punctuation_Dash
20
Unicode class name Pd
QChar::Punctuation_Open
21
Unicode class name Ps
QChar::Punctuation_Close
22
Unicode class name Pe
QChar::Punctuation_InitialQuote
23
Unicode class name Pi
QChar::Punctuation_FinalQuote
24
Unicode class name Pf
QChar::Punctuation_Other
25
Unicode class name Po
QChar::Symbol_Math
26
Unicode class name Sm
QChar::Symbol_Currency
27
Unicode class name Sc
QChar::Symbol_Modifier
28
Unicode class name Sk
QChar::Symbol_Other
29
Unicode class name So

See also category().
enum QChar::Decomposition
This enum type defines the Unicode decomposition attributes. See the Unicode Standard for a description of the values.

Constant
Value
QChar::NoDecomposition
0
QChar::Canonical
1
QChar::Circle
8
QChar::Compat
16
QChar::Final
6
QChar::Font
2
QChar::Fraction
17
QChar::Initial
4
QChar::Isolated
7
QChar::Medial
5
QChar::Narrow
13
QChar::NoBreak
3
QChar::Small
14
QChar::Square
15
QChar::Sub
10
QChar::Super
9
QChar::Vertical
11
QChar::Wide
12

See also decomposition().
enum QChar::Direction
This enum type defines the Unicode direction attributes. See the Unicode Standard for a description of the values.
In order to conform to C/C++ naming conventions "Dir" is prepended to the codes used in the Unicode Standard.

Constant
Value
Description
QChar::DirAL
13
 
QChar::DirAN
5
 
QChar::DirB
7
 
QChar::DirBN
18
 
QChar::DirCS
6
 
QChar::DirEN
2
 
QChar::DirES
3
 
QChar::DirET
4
 
QChar::DirFSI
21
Since Qt 5.3
QChar::DirL
0
 
QChar::DirLRE
11
 
QChar::DirLRI
19
Since Qt 5.3
QChar::DirLRO
12
 
QChar::DirNSM
17
 
QChar::DirON
10
 
QChar::DirPDF
16
 
QChar::DirPDI
22
Since Qt 5.3
QChar::DirR
1
 
QChar::DirRLE
14
 
QChar::DirRLI
20
Since Qt 5.3
QChar::DirRLO
15
 
QChar::DirS
8
 
QChar::DirWS
9
 

See also direction().
enum QChar::JoiningType
since 5.3
This enum type defines the Unicode joining type attributes. See the Unicode Standard for a description of the values.
In order to conform to C/C++ naming conventions "Joining_" is prepended to the codes used in the Unicode Standard.

Constant
Value
QChar::Joining_None
0
QChar::Joining_Causing
1
QChar::Joining_Dual
2
QChar::Joining_Right
3
QChar::Joining_Left
4
QChar::Joining_Transparent
5

See also joiningType().
enum QChar::Script
This enum type defines the Unicode script property values.
For details about the Unicode script property values see Unicode Standard Annex #24.
In order to conform to C/C++ naming conventions "Script_" is prepended to the codes used in the Unicode Standard.

Constant
Value
Description
QChar::Script_Unknown
0
For unassigned, private-use, noncharacter, and surrogate code points.
QChar::Script_Inherited
1
For characters that may be used with multiple scripts and that inherit their script from the preceding characters. These include nonspacing marks, enclosing marks, and zero width joiner/non-joiner characters.
QChar::Script_Common
2
For characters that may be used with multiple scripts and that do not inherit their script from the preceding characters.
QChar::Script_Latin
3
 
QChar::Script_Greek
4
 
QChar::Script_Cyrillic
5
 
QChar::Script_Armenian
6
 
QChar::Script_Hebrew
7
 
QChar::Script_Arabic
8
 
QChar::Script_Syriac
9
 
QChar::Script_Thaana
10
 
QChar::Script_Devanagari
11
 
QChar::Script_Bengali
12
 
QChar::Script_Gurmukhi
13
 
QChar::Script_Gujarati
14
 
QChar::Script_Oriya
15
 
QChar::Script_Tamil
16
 
QChar::Script_Telugu
17
 
QChar::Script_Kannada
18
 
QChar::Script_Malayalam
19
 
QChar::Script_Sinhala
20
 
QChar::Script_Thai
21
 
QChar::Script_Lao
22
 
QChar::Script_Tibetan
23
 
QChar::Script_Myanmar
24
 
QChar::Script_Georgian
25
 
QChar::Script_Hangul
26
 
QChar::Script_Ethiopic
27
 
QChar::Script_Cherokee
28
 
QChar::Script_CanadianAboriginal
29
 
QChar::Script_Ogham
30
 
QChar::Script_Runic
31
 
QChar::Script_Khmer
32
 
QChar::Script_Mongolian
33
 
QChar::Script_Hiragana
34
 
QChar::Script_Katakana
35
 
QChar::Script_Bopomofo
36
 
QChar::Script_Han
37
 
QChar::Script_Yi
38
 
QChar::Script_OldItalic
39
 
QChar::Script_Gothic
40
 
QChar::Script_Deseret
41
 
QChar::Script_Tagalog
42
 
QChar::Script_Hanunoo
43
 
QChar::Script_Buhid
44
 
QChar::Script_Tagbanwa
45
 
QChar::Script_Coptic
46
 
QChar::Script_Limbu
47
 
QChar::Script_TaiLe
48
 
QChar::Script_LinearB
49
 
QChar::Script_Ugaritic
50
 
QChar::Script_Shavian
51
 
QChar::Script_Osmanya
52
 
QChar::Script_Cypriot
53
 
QChar::Script_Braille
54
 
QChar::Script_Buginese
55
 
QChar::Script_NewTaiLue
56
 
QChar::Script_Glagolitic
57
 
QChar::Script_Tifinagh
58
 
QChar::Script_SylotiNagri
59
 
QChar::Script_OldPersian
60
 
QChar::Script_Kharoshthi
61
 
QChar::Script_Balinese
62
 
QChar::Script_Cuneiform
63
 
QChar::Script_Phoenician
64
 
QChar::Script_PhagsPa
65
 
QChar::Script_Nko
66
 
QChar::Script_Sundanese
67
 
QChar::Script_Lepcha
68
 
QChar::Script_OlChiki
69
 
QChar::Script_Vai
70
 
QChar::Script_Saurashtra
71
 
QChar::Script_KayahLi
72
 
QChar::Script_Rejang
73
 
QChar::Script_Lycian
74
 
QChar::Script_Carian
75
 
QChar::Script_Lydian
76
 
QChar::Script_Cham
77
 
QChar::Script_TaiTham
78
 
QChar::Script_TaiViet
79
 
QChar::Script_Avestan
80
 
QChar::Script_EgyptianHieroglyphs
81
 
QChar::Script_Samaritan
82
 
QChar::Script_Lisu
83
 
QChar::Script_Bamum
84
 
QChar::Script_Javanese
85
 
QChar::Script_MeeteiMayek
86
 
QChar::Script_ImperialAramaic
87
 
QChar::Script_OldSouthArabian
88
 
QChar::Script_InscriptionalParthian
89
 
QChar::Script_InscriptionalPahlavi
90
 
QChar::Script_OldTurkic
91
 
QChar::Script_Kaithi
92
 
QChar::Script_Batak
93
 
QChar::Script_Brahmi
94
 
QChar::Script_Mandaic
95
 
QChar::Script_Chakma
96
 
QChar::Script_MeroiticCursive
97
 
QChar::Script_MeroiticHieroglyphs
98
 
QChar::Script_Miao
99
 
QChar::Script_Sharada
100
 
QChar::Script_SoraSompeng
101
 
QChar::Script_Takri
102
 
QChar::Script_CaucasianAlbanian
103
 
QChar::Script_BassaVah
104
 
QChar::Script_Duployan
105
 
QChar::Script_Elbasan
106
 
QChar::Script_Grantha
107
 
QChar::Script_PahawhHmong
108
 
QChar::Script_Khojki
109
 
QChar::Script_LinearA
110
 
QChar::Script_Mahajani
111
 
QChar::Script_Manichaean
112
 
QChar::Script_MendeKikakui
113
 
QChar::Script_Modi
114
 
QChar::Script_Mro
115
 
QChar::Script_OldNorthArabian
116
 
QChar::Script_Nabataean
117
 
QChar::Script_Palmyrene
118
 
QChar::Script_PauCinHau
119
 
QChar::Script_OldPermic
120
 
QChar::Script_PsalterPahlavi
121
 
QChar::Script_Siddham
122
 
QChar::Script_Khudawadi
123
 
QChar::Script_Tirhuta
124
 
QChar::Script_WarangCiti
125
 
QChar::Script_Ahom
126
 
QChar::Script_AnatolianHieroglyphs
127
 
QChar::Script_Hatran
128
 
QChar::Script_Multani
129
 
QChar::Script_OldHungarian
130
 
QChar::Script_SignWriting
131
 

This enum was introduced or modified in Qt 5.1.
See also script().
enum QChar::SpecialCharacter

Constant
Value
Description
QChar::Null
0x0000
A QChar with this value isNull().
QChar::Tabulation
0x0009
Character tabulation.
QChar::LineFeed
0x000a
 
QChar::CarriageReturn
0x000d
 
QChar::Space
0x0020
 
QChar::Nbsp
0x00a0
Non-breaking space.
QChar::SoftHyphen
0x00ad
 
QChar::ReplacementCharacter
0xfffd
The character shown when a font has no glyph for a certain codepoint. A special question mark character is often used. Codecs use this codepoint when input data cannot be represented in Unicode.
QChar::ObjectReplacementCharacter
0xfffc
Used to represent an object such as an image when such objects cannot be presented.
QChar::ByteOrderMark
0xfeff
 
QChar::ByteOrderSwapped
0xfffe
 
QChar::ParagraphSeparator
0x2029
 
QChar::LineSeparator
0x2028
 
QChar::LastValidCodePoint
0x10ffff
 

enum QChar::UnicodeVersion
Specifies which version of the Unicode standard introduced a certain character.

Constant
Value
Description
QChar::Unicode_1_1
1
Version 1.1
QChar::Unicode_2_0
2
Version 2.0
QChar::Unicode_2_1_2
3
Version 2.1.2
QChar::Unicode_3_0
4
Version 3.0
QChar::Unicode_3_1
5
Version 3.1
QChar::Unicode_3_2
6
Version 3.2
QChar::Unicode_4_0
7
Version 4.0
QChar::Unicode_4_1
8
Version 4.1
QChar::Unicode_5_0
9
Version 5.0
QChar::Unicode_5_1
10
Version 5.1
QChar::Unicode_5_2
11
Version 5.2
QChar::Unicode_6_0
12
Version 6.0
QChar::Unicode_6_1
13
Version 6.1
QChar::Unicode_6_2
14
Version 6.2
QChar::Unicode_6_3
15
Version 6.3 Since Qt 5.3
QChar::Unicode_7_0
16
Version 7.0 Since Qt 5.5
QChar::Unicode_8_0
17
Version 8.0 Since Qt 5.6
QChar::Unicode_Unassigned
0
The value is not assigned to any character in version 8.0 of Unicode.

See also unicodeVersion() and currentUnicodeVersion().
Member Function Documentation
QChar::QChar()
Constructs a null QChar ('\0').
See also isNull().
QChar::QChar(ushort code)
Constructs a QChar for the character with Unicode code point code.
QChar::QChar(uchar cell, uchar row)
Constructs a QChar for Unicode cell cell in row row.
See also cell() and row().
QChar::QChar(short code)
Constructs a QChar for the character with Unicode code point code.
QChar::QChar(uint code)
Constructs a QChar for the character with Unicode code point code.
QChar::QChar(int code)
Constructs a QChar for the character with Unicode code point code.
QChar::QChar(SpecialCharacter ch)
Constructs a QChar for the predefined character value ch.
QChar::QChar(QLatin1Char ch)
Constructs a QChar corresponding to ASCII/Latin-1 character ch.
QChar::QChar(char16_t ch)
Constructs a QChar corresponding to the UTF-16 character ch.
Note: This constructor is not available on MSVC 2013.
This function was introduced in Qt 5.10.
QChar::QChar(wchar_t ch)
Constructs a QChar corresponding to the wide character ch.
Note: This constructor is only available on Windows.
This function was introduced in Qt 5.10.
QChar::QChar(char ch)
Constructs a QChar corresponding to ASCII/Latin-1 character ch.
Note: This constructor is not available when QT_NO_CAST_FROM_ASCII is defined.
See also QT_NO_CAST_FROM_ASCII.
QChar::QChar(uchar ch)
Constructs a QChar corresponding to ASCII/Latin-1 character ch.
Note: This constructor is not available when QT_NO_CAST_FROM_ASCII or QT_RESTRICTED_CAST_FROM_ASCII is defined.
See also QT_NO_CAST_FROM_ASCII and QT_RESTRICTED_CAST_FROM_ASCII.
Category QChar::category() const
Returns the character's category.
[static] Category QChar::category(uint ucs4)
This is an overloaded function.
Returns the category of the UCS-4-encoded character specified by ucs4.
uchar QChar::cell() const
Returns the cell (least significant byte) of the Unicode character.
See also row().
unsigned char QChar::combiningClass() const
Returns the combining class for the character as defined in the Unicode standard. This is mainly useful as a positioning hint for marks attached to a base character.
The Qt text rendering engine uses this information to correctly position non-spacing marks around a base character.
[static] unsigned char QChar::combiningClass(uint ucs4)
This is an overloaded function.
Returns the combining class for the UCS-4-encoded character specified by ucs4, as defined in the Unicode standard.
[static] UnicodeVersion QChar::currentUnicodeVersion()
Returns the most recent supported Unicode version.
QString QChar::decomposition() const
Decomposes a character into it's constituent parts. Returns an empty string if no decomposition exists.
[static] QString QChar::decomposition(uint ucs4)
This is an overloaded function.
Decomposes the UCS-4-encoded character specified by ucs4 into it's constituent parts. Returns an empty string if no decomposition exists.
Decomposition QChar::decompositionTag() const
Returns the tag defining the composition of the character. Returns QChar::NoDecomposition if no decomposition exists.
[static] Decomposition QChar::decompositionTag(uint ucs4)
This is an overloaded function.
Returns the tag defining the composition of the UCS-4-encoded character specified by ucs4. Returns QChar::NoDecomposition if no decomposition exists.
int QChar::digitValue() const
Returns the numeric value of the digit, or -1 if the character is not a digit.
[static] int QChar::digitValue(uint ucs4)
This is an overloaded function.
Returns the numeric value of the digit specified by the UCS-4-encoded character, ucs4, or -1 if the character is not a digit.
Direction QChar::direction() const
Returns the character's direction.
[static] Direction QChar::direction(uint ucs4)
This is an overloaded function.
Returns the direction of the UCS-4-encoded character specified by ucs4.
[static] QChar QChar::fromLatin1(char c)
Converts the Latin-1 character c to its equivalent QChar. This is mainly useful for non-internationalized software.
An alternative is to use QLatin1Char.
See also toLatin1() and unicode().
bool QChar::hasMirrored() const
Returns true if the character should be reversed if the text direction is reversed; otherwise returns false.
A bit faster equivalent of (ch.mirroredChar() != ch).
See also mirroredChar().
[static] bool QChar::hasMirrored(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 should be reversed if the text direction is reversed; otherwise returns false.
A bit faster equivalent of (QChar::mirroredChar(ucs4) != ucs4).
This function was introduced in Qt 5.0.
See also mirroredChar().
[static] ushort QChar::highSurrogate(uint ucs4)
Returns the high surrogate part of a UCS-4-encoded code point. The returned result is undefined if ucs4 is smaller than 0x10000.
bool QChar::isDigit() const
Returns true if the character is a decimal digit (Number_DecimalDigit); otherwise returns false.
See also isNumber().
[static] bool QChar::isDigit(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a decimal digit (Number_DecimalDigit); otherwise returns false.
This function was introduced in Qt 5.0.
See also isNumber().
bool QChar::isHighSurrogate() const
Returns true if the QChar is the high part of a UTF16 surrogate (for example if its code point is in range [0xd800..0xdbff]); false otherwise.
[static] bool QChar::isHighSurrogate(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is the high part of a UTF16 surrogate (for example if its code point is in range [0xd800..0xdbff]); false otherwise.
bool QChar::isLetter() const
Returns true if the character is a letter (Letter_* categories); otherwise returns false.
[static] bool QChar::isLetter(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a letter (Letter_* categories); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isLetterOrNumber() const
Returns true if the character is a letter or number (Letter_* or Number_* categories); otherwise returns false.
[static] bool QChar::isLetterOrNumber(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a letter or number (Letter_* or Number_* categories); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isLowSurrogate() const
Returns true if the QChar is the low part of a UTF16 surrogate (for example if its code point is in range [0xdc00..0xdfff]); false otherwise.
[static] bool QChar::isLowSurrogate(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is the low part of a UTF16 surrogate (for example if its code point is in range [0xdc00..0xdfff]); false otherwise.
bool QChar::isLower() const
Returns true if the character is a lowercase letter, for example category() is Letter_Lowercase.
See also isUpper(), toLower(), and toUpper().
[static] bool QChar::isLower(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a lowercase letter, for example category() is Letter_Lowercase.
This function was introduced in Qt 5.0.
See also isUpper(), toLower(), and toUpper().
bool QChar::isMark() const
Returns true if the character is a mark (Mark_* categories); otherwise returns false.
See QChar::Category for more information regarding marks.
[static] bool QChar::isMark(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a mark (Mark_* categories); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isNonCharacter() const
Returns true if the QChar is a non-character; false otherwise.
Unicode has a certain number of code points that are classified as "non-characters:" that is, they can be used for internal purposes in applications but cannot be used for text interchange. Those are the last two entries each Unicode Plane ([0xfffe..0xffff], [0x1fffe..0x1ffff], etc.) as well as the entries in range [0xfdd0..0xfdef].
This function was introduced in Qt 5.0.
[static] bool QChar::isNonCharacter(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a non-character; false otherwise.
Unicode has a certain number of code points that are classified as "non-characters:" that is, they can be used for internal purposes in applications but cannot be used for text interchange. Those are the last two entries each Unicode Plane ([0xfffe..0xffff], [0x1fffe..0x1ffff], etc.) as well as the entries in range [0xfdd0..0xfdef].
This function was introduced in Qt 5.0.
bool QChar::isNull() const
Returns true if the character is the Unicode character 0x0000 ('\0'); otherwise returns false.
bool QChar::isNumber() const
Returns true if the character is a number (Number_* categories, not just 0-9); otherwise returns false.
See also isDigit().
[static] bool QChar::isNumber(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a number (Number_* categories, not just 0-9); otherwise returns false.
This function was introduced in Qt 5.0.
See also isDigit().
bool QChar::isPrint() const
Returns true if the character is a printable character; otherwise returns false. This is any character not of category Other_*.
Note that this gives no indication of whether the character is available in a particular font.
[static] bool QChar::isPrint(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a printable character; otherwise returns false. This is any character not of category Other_*.
Note that this gives no indication of whether the character is available in a particular font.
This function was introduced in Qt 5.0.
bool QChar::isPunct() const
Returns true if the character is a punctuation mark (Punctuation_* categories); otherwise returns false.
[static] bool QChar::isPunct(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a punctuation mark (Punctuation_* categories); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isSpace() const
Returns true if the character is a separator character (Separator_* categories or certain code points from Other_Control category); otherwise returns false.
[static] bool QChar::isSpace(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a separator character (Separator_* categories or certain code points from Other_Control category); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isSurrogate() const
Returns true if the QChar contains a code point that is in either the high or the low part of the UTF-16 surrogate range (for example if its code point is in range [0xd800..0xdfff]); false otherwise.
This function was introduced in Qt 5.0.
[static] bool QChar::isSurrogate(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 contains a code point that is in either the high or the low part of the UTF-16 surrogate range (for example if its code point is in range [0xd800..0xdfff]); false otherwise.
This function was introduced in Qt 5.0.
bool QChar::isSymbol() const
Returns true if the character is a symbol (Symbol_* categories); otherwise returns false.
[static] bool QChar::isSymbol(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a symbol (Symbol_* categories); otherwise returns false.
This function was introduced in Qt 5.0.
bool QChar::isTitleCase() const
Returns true if the character is a titlecase letter, for example category() is Letter_Titlecase.
See also isLower(), toUpper(), toLower(), and toTitleCase().
[static] bool QChar::isTitleCase(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is a titlecase letter, for example category() is Letter_Titlecase.
This function was introduced in Qt 5.0.
See also isLower(), toUpper(), toLower(), and toTitleCase().
bool QChar::isUpper() const
Returns true if the character is an uppercase letter, for example category() is Letter_Uppercase.
See also isLower(), toUpper(), and toLower().
[static] bool QChar::isUpper(uint ucs4)
This is an overloaded function.
Returns true if the UCS-4-encoded character specified by ucs4 is an uppercase letter, for example category() is Letter_Uppercase.
This function was introduced in Qt 5.0.
See also isLower(), toUpper(), and toLower().
JoiningType QChar::joiningType() const
Returns information about the joining type attributes of the character (needed for certain languages such as Arabic or Syriac).
This function was introduced in Qt 5.3.
[static] JoiningType QChar::joiningType(uint ucs4)
This is an overloaded function.
Returns information about the joining type attributes of the UCS-4-encoded character specified by ucs4 (needed for certain languages such as Arabic or Syriac).
This function was introduced in Qt 5.3.
[static] ushort QChar::lowSurrogate(uint ucs4)
Returns the low surrogate part of a UCS-4-encoded code point. The returned result is undefined if ucs4 is smaller than 0x10000.
QChar QChar::mirroredChar() const
Returns the mirrored character if this character is a mirrored character; otherwise returns the character itself.
See also hasMirrored().
[static] uint QChar::mirroredChar(uint ucs4)
This is an overloaded function.
Returns the mirrored character if the UCS-4-encoded character specified by ucs4 is a mirrored character; otherwise returns the character itself.
See also hasMirrored().
[static] bool QChar::requiresSurrogates(uint ucs4)
Returns true if the UCS-4-encoded character specified by ucs4 can be split into the high and low parts of a UTF16 surrogate (for example if its code point is greater than or equals to 0x10000); false otherwise.
uchar QChar::row() const
Returns the row (most significant byte) of the Unicode character.
See also cell().
Script QChar::script() const
Returns the Unicode script property value for this character.
This function was introduced in Qt 5.1.
[static] Script QChar::script(uint ucs4)
This is an overloaded function.
Returns the Unicode script property value for the character specified in its UCS-4-encoded form as ucs4.
This function was introduced in Qt 5.1.
[static] uint QChar::surrogateToUcs4(ushort high, ushort low)
Converts a UTF16 surrogate pair with the given high and low values to it's UCS-4-encoded code point.
[static] uint QChar::surrogateToUcs4(QChar high, QChar low)
This is an overloaded function.
Converts a UTF16 surrogate pair (high, low) to it's UCS-4-encoded code point.
QChar QChar::toCaseFolded() const
Returns the case folded equivalent of the character. For most Unicode characters this is the same as toLower().
[static] uint QChar::toCaseFolded(uint ucs4)
This is an overloaded function.
Returns the case folded equivalent of the UCS-4-encoded character specified by ucs4. For most Unicode characters this is the same as toLower().
char QChar::toLatin1() const
Returns the Latin-1 character equivalent to the QChar, or 0. This is mainly useful for non-internationalized software.
Note: It is not possible to distinguish a non-Latin-1 character from a Latin-1 0 (NUL) character. Prefer to use unicode(), which does not have this ambiguity.
See also unicode().
QChar QChar::toLower() const
Returns the lowercase equivalent if the character is uppercase or titlecase; otherwise returns the character itself.
[static] uint QChar::toLower(uint ucs4)
This is an overloaded function.
Returns the lowercase equivalent of the UCS-4-encoded character specified by ucs4 if the character is uppercase or titlecase; otherwise returns the character itself.
QChar QChar::toTitleCase() const
Returns the title case equivalent if the character is lowercase or uppercase; otherwise returns the character itself.
[static] uint QChar::toTitleCase(uint ucs4)
This is an overloaded function.
Returns the title case equivalent of the UCS-4-encoded character specified by ucs4 if the character is lowercase or uppercase; otherwise returns the character itself.
QChar QChar::toUpper() const
Returns the uppercase equivalent if the character is lowercase or titlecase; otherwise returns the character itself.
[static] uint QChar::toUpper(uint ucs4)
This is an overloaded function.
Returns the uppercase equivalent of the UCS-4-encoded character specified by ucs4 if the character is lowercase or titlecase; otherwise returns the character itself.
ushort QChar::unicode() const
Returns the numeric Unicode value of the QChar.
ushort &QChar::unicode()
Returns a reference to the numeric Unicode value of the QChar.
UnicodeVersion QChar::unicodeVersion() const
Returns the Unicode version that introduced this character.
[static] UnicodeVersion QChar::unicodeVersion(uint ucs4)
This is an overloaded function.
Returns the Unicode version that introduced the character specified in its UCS-4-encoded form as ucs4.
Related Non-Members
bool operator!=(QChar c1, QChar c2)
Returns true if c1 and c2 are not the same Unicode character; otherwise returns false.
bool operator<(QChar c1, QChar c2)
Returns true if the numeric Unicode value of c1 is less than that of c2; otherwise returns false.
QDataStream &operator<<(QDataStream &out, QChar chr)
Writes the char chr to the stream out.
See also Serializing Qt Data Types.
bool operator<=(QChar c1, QChar c2)
Returns true if the numeric Unicode value of c1 is less than or equal to that of c2; otherwise returns false.
bool operator==(QChar c1, QChar c2)
Returns true if c1 and c2 are the same Unicode character; otherwise returns false.
bool operator>(QChar c1, QChar c2)
Returns true if the numeric Unicode value of c1 is greater than that of c2; otherwise returns false.
bool operator>=(QChar c1, QChar c2)
Returns true if the numeric Unicode value of c1 is greater than or equal to that of c2; otherwise returns false.
QDataStream &operator>>(QDataStream &in, QChar &chr)
Reads a char from the stream in into char chr.
See also Serializing Qt Data Types. 
© 2017 The Qt Company Ltd. Documentation contributions included herein are the copyrights of their respective owners.
The documentation provided herein is licensed under the terms of the GNU Free Documentation License version 1.3 as published by the Free Software Foundation.
Qt and respective logos are trademarks of The Qt Company Ltd. in Finland and/or other countries worldwide. All other trademarks are property of their respective owners. 