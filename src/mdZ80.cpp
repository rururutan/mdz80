/*
 * Minachun Disassembler for Sega mkIII(SMS)
 *
 * (c) Manbow-J / RuRuRu
 */

#include <stdio.h>
#include <string.h>

#include "mdZ80.h"

const char	*nimonic[] = {
	"db",
	"db",
	"ld",
	"push",
	"pop",
	"ex",
	"exx",
	"ldi",
	"ldir",
	"ldd",
	"lddr",
	"cpi",
	"cpir",
	"cpd",
	"cpdr",
	"add",
	"adc",
	"sub",
	"sbc",
	"and",
	"or",
	"xor",
	"cp",
	"inc",
	"dec",
	"daa",
	"cpl",
	"neg",
	"ccf",
	"scf",
	"nop",
	"halt",
	"di",
	"ei",
	"im",
	"rlca",
	"rla",
	"rrca",
	"rra",
	"rlc",
	"rl",
	"rrc",
	"rr",
	"sla",
	"sll",
	"sra",
	"srl",
	"rld",
	"rrd",
	"bit",
	"set",
	"res",
	"jp",
	"jr",
	"djnz",
	"call",
	"ret",
	"reti",
	"retn",
	"rst",
	"in",
	"ini",
	"inir",
	"ind",
	"indr",
	"out",
	"outi",
	"otir",
	"outd",
	"otdr",
};

const char	*optype0[] = {
	"",
	"a",
	"b",
	"c",
	"d",
	"e",
	"h",
	"l",
	"f",
	"i",
	"r",

	"af",
	"af'",
	"bc",
	"de",
	"hl",
	"ix",
	"ixl",
	"ixh",
	"iy",
	"iyl",
	"iyh",
	"sp",

	"(c)",

	"(bc)",
	"(de)",
	"(hl)",
	"(ix)",
	"(iy)",
	"(sp)",

	"nz",
	"z",
	"nc",
	"c",
	"po",
	"pe",
	"p",
	"m",

	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",

	"0",
	"1",
	"2",
};

disZ80data disz80[7][256] = {
	{
		// 00-0F
		{  1, 0, NMT_NOP,	0,	OT_NONE,	OT_NONE,	ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_BC,	OT_IMM_WORD,ACT_RD	},
		{  1, 1, NMT_LD,	2,	OT_ABS_BC,	OT_REG_A,	ACT_WT	},
		{  1, 0, NMT_INC,	1,	OT_REG_BC,	OT_NONE,	ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_B,	OT_NONE,	ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_B,	OT_NONE,	ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_B,	OT_IMM_BYTE,ACT_NL	},
		{  1, 0, NMT_RLCA,	0,	OT_NONE,	OT_NONE,	ACT_NL	},
		{  1, 0, NMT_EX,	2,	OT_REG_AF,	OT_REG_RAF,	ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_HL,	OT_REG_BC,	ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_ABS_BC,	ACT_RD	},
		{  1, 0, NMT_DEC,	1,	OT_REG_BC,	OT_NONE,	ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_C,	OT_NONE,	ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_C,	OT_NONE,	ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_C,	OT_IMM_BYTE,ACT_NL	},
		{  1, 0, NMT_RRCA,	0,	OT_NONE,	OT_NONE,	ACT_NL	},
		// 10-1F
		{  2, 1, NMT_DJNZ,	1,	OT_REL,		OT_NONE		,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_DE,	OT_IMM_WORD	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_ABS_DE,	OT_REG_A	,ACT_WT	},
		{  1, 0, NMT_INC,	1,	OT_REG_DE,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_D,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_RLA,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_JR,	1,	OT_REL,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_HL,	OT_REG_DE	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_ABS_DE	,ACT_RD	},
		{  1, 0, NMT_DEC,	1,	OT_REG_DE,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_E,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_RRA,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		// 20-2F
		{  2, 1, NMT_JR,	2,	OT_NZ,		OT_REL		,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_HL,	OT_IMM_WORD	,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_ABS,		OT_REG_HL	,ACT_WT	},
		{  1, 0, NMT_INC,	1,	OT_REG_HL,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_H,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_DAA,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_JR,	2,	OT_Z,		OT_REL		,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_HL,	OT_REG_HL	,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_HL,	OT_ABS		,ACT_RD	},
		{  1, 0, NMT_DEC,	1,	OT_REG_HL,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_L,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_CPL,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		// 30-3F
		{  2, 1, NMT_JR,	2,	OT_NC,		OT_REL		,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_SP,	OT_IMM_WORD	,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_ABS,		OT_REG_A	,ACT_WT	},
		{  1, 0, NMT_INC,	1,	OT_REG_SP,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_ABS_HL,	OT_NONE		,ACT_WT	},
		{  1, 0, NMT_DEC,	1,	OT_ABS_HL,	OT_NONE		,ACT_WT	},
		{  2, 1, NMT_LD,	2,	OT_ABS_HL,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_SCF,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_JR,	2,	OT_C,		OT_REL		,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_HL,	OT_REG_SP	,ACT_NL	},
		{  3, 1, NMT_LD,	2,	OT_REG_A,	OT_ABS		,ACT_RD	},
		{  1, 0, NMT_DEC,	1,	OT_REG_SP,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_INC,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_DEC,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_LD,	2,	OT_REG_A,	OT_IMM_BYTE ,ACT_NL	},
		{  1, 0, NMT_CCF,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		// 40-4F
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_A	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_A	,ACT_NL	},
		// 50-5F
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_A	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_A	,ACT_NL	},
		// 60-6F
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_H,	OT_REG_A	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_L,	OT_REG_A	,ACT_NL	},
		// 70-7F
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_B	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_C	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_D	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_E	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_H	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_L	,ACT_WT	},
		{  1, 0, NMT_HALT,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_ABS_HL,	OT_REG_A	,ACT_WT	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_A	,ACT_NL	},
		// 80-8F
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_A	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_A	,ACT_NL	},
		// 90-9F
		{  1, 0, NMT_SUB,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SUB,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_SUB,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_B	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_C	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_D	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_E	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_H	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_L	,ACT_NL	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_ABS_HL	,ACT_RD	},
		{  1, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_A	,ACT_NL	},
		// A0-AF
		{  1, 0, NMT_AND,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_AND,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_AND,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_XOR,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_XOR,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// B0-BF
		{  1, 0, NMT_OR,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_OR,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_OR,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_CP,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_CP,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// C0-CF
		{  1, 0, NMT_RET,	1,	OT_NZ,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_POP,	1,	OT_REG_BC,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_NZ,		OT_IMM_WORD	,ACT_NL	},
		{  3, 1, NMT_JP,	1,	OT_IMM_WORD,OT_NONE		,ACT_NL	},
		{  3, 1, NMT_CALL,	2,	OT_NZ,		OT_IMM_WORD	,ACT_CL	},
		{  1, 0, NMT_PUSH,	1,	OT_REG_BC,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_ADD,	2,	OT_REG_A,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RET,	1,	OT_Z,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RET,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_Z,		OT_IMM_WORD	,ACT_NL	},
		{ -1, 0, 0,			0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_CALL,	2,	OT_Z,		OT_IMM_WORD	,ACT_CL	},
		{  3, 1, NMT_CALL,	1,	OT_IMM_WORD,OT_NONE		,ACT_CL	},
		{  2, 1, NMT_ADC,	2,	OT_REG_A,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		// D0-DF
		{  1, 0, NMT_RET,	1,	OT_NC,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_POP,	1,	OT_REG_DE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_NC,		OT_IMM_WORD	,ACT_NL	},
		{  2, 1, NMT_OUT,	2,	OT_IMM_PORT,OT_REG_A	,ACT_OT	},
		{  3, 1, NMT_CALL,	2,	OT_NC,		OT_IMM_WORD	,ACT_CL	},
		{  1, 0, NMT_PUSH,	1,	OT_REG_DE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_SUB,	1,	OT_IMM_BYTE,OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RET,	1,	OT_C,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_EXX,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_C,		OT_IMM_WORD	,ACT_NL	},
		{  2, 1, NMT_IN,	2,	OT_REG_A,	OT_IMM_PORT	,ACT_IN	},
		{  3, 1, NMT_CALL,	2,	OT_C,		OT_IMM_WORD	,ACT_CL	},
		{ -2, 0, 0,			0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_SBC,	2,	OT_REG_A,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		// E0-EF
		{  1, 0, NMT_RET,	1,	OT_PO,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_POP,	1,	OT_REG_HL,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_PO,		OT_IMM_WORD	,ACT_NL	},
		{  1, 0, NMT_EX,	2,	OT_ABS_SP,	OT_REG_HL	,ACT_RW	},
		{  3, 1, NMT_CALL,	2,	OT_PO,		OT_IMM_WORD	,ACT_CL	},
		{  1, 0, NMT_PUSH,	1,	OT_REG_HL,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_AND,	1,	OT_IMM_BYTE,OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RET,	1,	OT_PE,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_JP,	1,	OT_ABS_HL,	OT_NONE		,ACT_RD	},
		{  3, 1, NMT_JP,	2,	OT_PE,		OT_IMM_WORD	,ACT_NL	},
		{  1, 0, NMT_EX,	2,	OT_REG_DE,	OT_REG_HL	,ACT_NL	},
		{  3, 1, NMT_CALL,	2,	OT_PE,		OT_IMM_WORD	,ACT_CL	},
		{ -3, 0, 0,			0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_XOR,	1,	OT_IMM_BYTE,OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		// F0-FF
		{  1, 0, NMT_RET,	1,	OT_P,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_POP,	1,	OT_REG_AF,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_P,		OT_IMM_WORD	,ACT_NL	},
		{  1, 1, NMT_DI,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_CALL,	2,	OT_P,		OT_IMM_WORD	,ACT_CL	},
		{  1, 0, NMT_PUSH,	1,	OT_REG_AF,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_OR,	1,	OT_IMM_BYTE,OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RET,	1,	OT_M,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_LD,	2,	OT_REG_SP,	OT_REG_HL	,ACT_NL	},
		{  3, 1, NMT_JP,	2,	OT_M,		OT_IMM_WORD	,ACT_NL	},
		{  1, 1, NMT_EI,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  3, 1, NMT_CALL,	2,	OT_M,		OT_IMM_WORD	,ACT_CL	},
		{ -4, 0, 0,			0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 1, NMT_CP,	1,	OT_IMM_BYTE,OT_NONE		,ACT_NL	},
		{  1, 0, NMT_RST,	1,	OT_RST,		OT_NONE		,ACT_NL	},
	},{
		// CB:00-0F
		{  2, 0, NMT_RLC,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLC,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_RLC,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRC,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_RRC,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// CB:10-1F
		{  2, 0, NMT_RL,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RL,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_RL,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RR,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_RR,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// CB:20-2F
		{  2, 0, NMT_SLA,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLA,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_SLA,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRA,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_SRA,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// CB:30-3F
		{  2, 0, NMT_SLL,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_ABS_HL,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SLL,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_B,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_C,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_D,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_E,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_H,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_REG_L,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SRL,	1,	OT_ABS_HL,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_SRL,	1,	OT_REG_A,	OT_NONE		,ACT_NL	},
		// CB:40-4F
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_0,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_1,	OT_REG_A	,ACT_NL	},
		// CB:50-5F
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_2,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_3,	OT_REG_A	,ACT_NL	},
		// CB:60-6F
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_4,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_5,	OT_REG_A	,ACT_NL	},
		// CB:70-7F
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_6,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_BIT,	2,	OT_BIT_7,	OT_REG_A	,ACT_NL	},
		// CB:80-8F
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_0,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_1,	OT_REG_A	,ACT_NL	},
		// CB:90-9F
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_2,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_3,	OT_REG_A	,ACT_NL	},
		// CB:A0-AF_3
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_4,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_5,	OT_REG_A	,ACT_NL	},
		// CB:B0-BF
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_6,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_ABS_HL	,ACT_RD	},
		{  2, 0, NMT_RES,	2,	OT_BIT_7,	OT_REG_A	,ACT_NL	},
		// CB:C0-CF
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_0,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_1,	OT_REG_A	,ACT_NL	},
		// CB:D0-DF
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_2,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_3,	OT_REG_A	,ACT_NL	},
		// CB:E0-EF
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_4,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_5,	OT_REG_A	,ACT_NL	},
		// CB:F0-FF
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_6,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_H	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_L	,ACT_NL	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_ABS_HL	,ACT_RW	},
		{  2, 0, NMT_SET,	2,	OT_BIT_7,	OT_REG_A	,ACT_NL	},
	},{
		// DD:00-0F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IX,	OT_REG_BC	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:10-1F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IX,	OT_REG_DE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:20-2F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_IX,	OT_IMM_WORD	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_IX	,ACT_WT	},
		{  2, 0, NMT_INC,	1,	OT_REG_IX,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_INC,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_IXH,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IX,	OT_REG_IX	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_IX,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IX,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_INC,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_IXL,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:30-3F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  3, 2, NMT_INC,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  3, 2, NMT_DEC,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  4, 2, NMT_LD,	2,	OT_IDX_IX,	OT_IMM_BYTE	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IX,	OT_REG_SP	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:40-4F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_B,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_C,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:50-5F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_D,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_E,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:60-6F
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_H,	OT_IDX_IX	,ACT_RD	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXH,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXL,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXL,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXL,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_L,	OT_IDX_IX	,ACT_RD	},
		{  2, 0, NMT_LD,	2,	OT_REG_IXL,	OT_REG_A	,ACT_NL	},
		// DD:70-7F
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_B	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_C	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_D	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_E	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_H	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_L	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IX,	OT_REG_A	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_A,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:80-8F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_A,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_ADD,	2,	OT_REG_A,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_ADC,	2,	OT_REG_A,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:90-9F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SUB,	2,	OT_REG_A,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_SUB,	2,	OT_REG_A,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_SUB,	1,	OT_IDX_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_IXH	,ACT_NL	},
		{  2, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_IXL	,ACT_NL	},
		{  3, 2, NMT_SBC,	2,	OT_REG_A,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:A0-AF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_AND,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_AND,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_AND,	1,	OT_IDX_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_XOR,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_XOR,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_XOR,	1,	OT_IDX_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:B0-BF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_OR,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_OR,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_OR,	1,	OT_IDX_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_CP,	1,	OT_REG_IXH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_CP,	1,	OT_REG_IXL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_CP,	1,	OT_IDX_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:C0-CF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{ -5, 0, NMT_UND,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:D0-DF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:E0-EF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_POP,	1,	OT_REG_IX,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_EX,	2,	OT_ABS_SP,	OT_REG_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_PUSH,	1,	OT_REG_IX,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_JP,	1,	OT_ABS_IX,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD:F0-FF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_SP,	OT_REG_IX	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
	},{
		// ED:00-0F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:10-1F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:20-2F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:30-3F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:40-4F
		{  2, 0, NMT_IN,	2,	OT_REG_B,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_B	,ACT_OT	},
		{  2, 0, NMT_SBC,	2,	OT_REG_HL,	OT_REG_BC	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_BC	,ACT_WT	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_0,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_I,	OT_REG_A	,ACT_NL	},
		{  2, 0, NMT_IN,	2,	OT_REG_C,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_C	,ACT_OT	},
		{  2, 0, NMT_ADC,	2,	OT_REG_HL,	OT_REG_BC	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_BC,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_NEG,	1,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETI,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_0,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_R,	OT_REG_A	,ACT_NL	},
		// ED:50-5F
		{  2, 0, NMT_IN,	2,	OT_REG_D,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_D	,ACT_OT	},
		{  2, 0, NMT_SBC,	2,	OT_REG_HL,	OT_REG_DE	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_DE	,ACT_WT	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_1,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_I	,ACT_NL	},
		{  2, 0, NMT_IN,	2,	OT_REG_E,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_E	,ACT_OT	},
		{  2, 0, NMT_ADC,	2,	OT_REG_HL,	OT_REG_DE	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_DE,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_2,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_R	,ACT_NL	},
		// ED:60-6F
		{  2, 0, NMT_IN,	2,	OT_REG_H,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_H	,ACT_OT	},
		{  2, 0, NMT_SBC,	2,	OT_REG_HL,	OT_REG_HL	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_HL	,ACT_WT	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_0,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RRD,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IN,	2,	OT_REG_L,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_L	,ACT_OT	},
		{  2, 0, NMT_ADC,	2,	OT_REG_HL,	OT_REG_HL	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_HL,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_0,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RLD,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		// ED:70-7F
		{  2, 0, NMT_IN,	2,	OT_REG_F,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_BIT_0	,ACT_OT	},
		{  2, 0, NMT_SBC,	2,	OT_REG_HL,	OT_REG_SP	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_SP	,ACT_WT	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_1,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_NOP,	0,	OT_NONE,	OT_NONE,	ACT_NL	},
		{  2, 0, NMT_IN,	2,	OT_REG_A,	OT_PORT_C	,ACT_IN	},
		{  2, 0, NMT_OUT,	2,	OT_PORT_C,	OT_REG_A	,ACT_OT	},
		{  2, 0, NMT_ADC,	2,	OT_REG_HL,	OT_REG_SP	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_SP,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_NEG,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_RETN,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_IM,	1,	OT_IM_2,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_NOP,	0,	OT_NONE,	OT_NONE,	ACT_NL	},
		// ED:80-8F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:90-9F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:A0-AF
		{  2, 0, NMT_LDI,	0,	OT_NONE,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_CPI,	0,	OT_NONE,	OT_NONE		,ACT_RD	},
		{  2, 0, NMT_INI,	0,	OT_NONE,	OT_NONE		,ACT_IN	},
		{  2, 0, NMT_OUTI,	0,	OT_NONE,	OT_NONE		,ACT_OT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LDD,	0,	OT_NONE,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_CPD,	0,	OT_NONE,	OT_NONE		,ACT_RD	},
		{  2, 0, NMT_IND,	0,	OT_NONE,	OT_NONE		,ACT_IN	},
		{  2, 0, NMT_OUTD,	0,	OT_NONE,	OT_NONE		,ACT_OT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:B0-BF
		{  2, 0, NMT_LDIR,	0,	OT_NONE,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_CPIR,	0,	OT_NONE,	OT_NONE		,ACT_RD	},
		{  2, 0, NMT_INIR,	0,	OT_NONE,	OT_NONE		,ACT_IN	},
		{  2, 0, NMT_OTIR,	0,	OT_NONE,	OT_NONE		,ACT_OT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LDDR,	0,	OT_NONE,	OT_NONE		,ACT_RW	},
		{  2, 0, NMT_CPDR,	0,	OT_NONE,	OT_NONE		,ACT_RD	},
		{  2, 0, NMT_INDR,	0,	OT_NONE,	OT_NONE		,ACT_IN	},
		{  2, 0, NMT_OTDR,	0,	OT_NONE,	OT_NONE		,ACT_OT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:C0-CF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:D0-DF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:E0-EF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// ED:F0-FF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
	},{
		// FD:00-0F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IY,	OT_REG_BC	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:10-1F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IY,	OT_REG_DE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:20-2F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_IY,	OT_IMM_WORD	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_ABS,		OT_REG_IY	,ACT_WT	},
		{  2, 0, NMT_INC,	1,	OT_REG_IY,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_INC,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_IYH,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IY,	OT_REG_IY	,ACT_NL	},
		{  4, 2, NMT_LD,	2,	OT_REG_IY,	OT_ABS		,ACT_RD	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IY,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_INC,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_DEC,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_IYL,	OT_IMM_BYTE	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:30-,ACT_NL	3F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  3, 2, NMT_INC,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  3, 2, NMT_DEC,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  4, 2, NMT_LD,	2,	OT_IDX_IY,	OT_IMM_BYTE	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADD,	2,	OT_REG_IY,	OT_REG_SP	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:40-4F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_B,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_B,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_C,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_C,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:50-5F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_D,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_D,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_E,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_E,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:60-6F
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_H,	OT_IDX_IY	,ACT_RD	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYH,	OT_REG_A	,ACT_NL	},	// IYH
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_B	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_C	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_D	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_E	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_REG_L,	OT_IDX_IY	,ACT_RD	},
		{  2, 0, NMT_LD,	2,	OT_REG_IYL,	OT_REG_A	,ACT_NL	},
		// FD:70-7F
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_B	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_C	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_D	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_E	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_H	,ACT_WT	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_L	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  3, 2, NMT_LD,	2,	OT_IDX_IY,	OT_REG_A	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},	// IYH
		{  2, 0, NMT_LD,	2,	OT_REG_A,	OT_REG_IYL	,ACT_NL	},	// IYL
		{  3, 2, NMT_LD,	2,	OT_REG_A,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:80-8F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_AND,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_AND,	2,	OT_REG_A,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_ADD,	2,	OT_REG_A,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_ADC,	2,	OT_REG_A,	OT_REG_IYL		,ACT_NL	},
		{  3, 2, NMT_ADC,	2,	OT_REG_A,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:90-9F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SUB,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_SUB,	2,	OT_REG_A,	OT_REG_IYL	,ACT_NL	},
		{  3, 2, NMT_SUB,	1,	OT_IDX_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},
		{  2, 0, NMT_SBC,	2,	OT_REG_A,	OT_REG_IYH	,ACT_NL	},
		{  3, 2, NMT_SBC,	2,	OT_REG_A,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:A0-AF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_AND,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_AND,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_AND,	1,	OT_IDX_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_XOR,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_XOR,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_XOR,	1,	OT_IDX_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:B0-BF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_OR,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_OR,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_OR,	1,	OT_IDX_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_CP,	1,	OT_REG_IYH,	OT_NONE		,ACT_NL	},
		{  2, 0, NMT_CP,	1,	OT_REG_IYL,	OT_NONE		,ACT_NL	},
		{  3, 2, NMT_CP,	1,	OT_IDX_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:C0-CF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{ -6, 0, NMT_UND,	0,	OT_NONE,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:D0-DF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:E0-EF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_POP,	1,	OT_REG_IY,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_EX,	2,	OT_ABS_SP,	OT_REG_IY	,ACT_WT	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_PUSH,	1,	OT_REG_IY,	OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 2, NMT_JP,	1,	OT_ABS_IY,	OT_NONE		,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD:F0-FF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  2, 0, NMT_LD,	2,	OT_REG_SP,	OT_REG_IY	,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
	},{
		// DD CB xx :00-0F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RLC,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RRC,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :10-1F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RL,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RR,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :20-2F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SLA,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SRA,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :30-3F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SRL,	1,	OT_IDX_IX,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :40-4F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_0,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_1,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :50-5F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_2,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_3,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :60-6F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_4,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_5,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :70-7F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_6,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_7,	OT_IDX_IX	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :80-8F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_0,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_1,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :90-9F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_2,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_3,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :A0-AF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_4,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_5,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :B0-BF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_6,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_7,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :C0-CF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_0,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_1,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :D0-DF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_2,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_3,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :E0-EF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_4,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_5,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// DD CB xx :F0-FF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_6,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_7,	OT_IDX_IX	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
	},{
		// FD CB xx :00-0F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RLC,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RRC,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :10-1F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RL,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RR,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :20-2F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SLA,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SRA,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :30-3F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SRL,	1,	OT_IDX_IY,	OT_NONE		,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :40-4F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_0,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_1,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :50-5F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_2,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_3,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :60-6F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_4,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_5,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :70-7F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_6,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_BIT,	2,	OT_BIT_7,	OT_IDX_IY	,ACT_RD	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :80-8F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_0,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_1,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :90-9F
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_2,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_3,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :A0-AF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_4,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_5,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :B0-BF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_6,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_SET,	2,	OT_BIT_7,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :C0-CF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_0,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_1,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :D0-DF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_2,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_3,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :E0-EF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_4,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_5,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		// FD CB xx :F0-FF
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_6,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
		{  4, 2, NMT_RES,	2,	OT_BIT_7,	OT_IDX_IY	,ACT_RW	},
		{  1, 0, NMT_UND,	1,	OT_UND,		OT_NONE		,ACT_NL	},
	}
};

memargstr mapper_undefined_com[] = {
	{ 0xFFFF,0x0000,ACT_NL,NULL },
};


memargstr mapper_sms[] = {
#ifdef MESSAGETYPE_JAPANESE
/* Japanese */
	{ 0x0000,0x0000,ACT_AD," リセット"},
	{ 0x0038,0x0038,ACT_AD," V Blank割り込み(RST 38)"},
	{ 0x0066,0x0066,ACT_AD," SEGA Master System ポーズ割り込み(NMI)"},

	{ 0xfffc,0xfffc,ACT_RW," C000-FFFF:バンク切り替え"},
	{ 0xfffd,0xfffd,ACT_RW," 0000-3FFF:バンク切り替え"},
	{ 0xfffe,0xfffe,ACT_RW," 4000-7FFF:バンク切り替え"},
	{ 0xffff,0xffff,ACT_RW," 8000-BFFF:バンク切り替え"},

	{ 0xdc,0xdc,ACT_IN," JoyPad1 Reg"},
	{ 0xc0,0xc0,ACT_IN," JoyPad1 Reg(mirror)"},
	{ 0xdd,0xdd,ACT_IN," JoyPad2 Reg"},
	{ 0xc1,0xc1,ACT_IN," JoyPad2 Reg(Mirror)"},
	{ 0x00,0x00,ACT_IN," GameGear:Startボタン/カントリーコード Reg"},
	{ 0xbe,0xbe,ACT_IO," VDP:データレジスタ"},
	{ 0xbf,0xbf,ACT_IN," V-ブランクフラグ"},
	{ 0xbd,0xbd,ACT_IN," V-ブランクフラグ"},
	{ 0xbf,0xbf,ACT_OT," VDPアドレスレジスタ"},
	{ 0xbd,0xbd,ACT_OT," VDPアドレスレジスタ"},
	{ 0x7e,0x7e,ACT_IN," スキャンライン"},
	{ 0x7f,0x7f,ACT_IN," スキャンライン"},
	{ 0x7e,0x7e,ACT_OT," PSGポート Reg(mirror)"},
	{ 0x7f,0x7f,ACT_OT," PSGポート Reg"},
	{ 0xf0,0xf0,ACT_OT," FM Unitアドレス書き込み Reg"},
	{ 0xf1,0xf1,ACT_OT," FM Unitデータ書き込み Reg"},
	{ 0xf1,0xf1,ACT_OT," FM Unitデータ読み込み Reg"},
	{ 0xf2,0xf2,ACT_IO," FM Unit存在チェック Reg"},
#else
/* English */
	{ 0x0000,0x0000,ACT_AD," Reset vector"},
	{ 0x0038,0x0038,ACT_AD," V Blank interrupt vector (RST 38)"},
	{ 0x0066,0x0066,ACT_AD," SEGA Master System pause interrupt vector(NMI)"},

	{ 0xfffc,0xfffc,ACT_RW," C000-FFFF:Bank Control"},
	{ 0xfffd,0xfffd,ACT_RW," 0000-3FFF:Bank Control"},
	{ 0xfffe,0xfffe,ACT_RW," 4000-7FFF:Bank Control"},
	{ 0xffff,0xffff,ACT_RW," 8000-BFFF:Bank Control"},

	{ 0xdc,0xdc,ACT_IN," JoyPad1 Reg"},
	{ 0xc0,0xc0,ACT_IN," JoyPad1 Reg(mirror)"},
	{ 0xdd,0xdd,ACT_IN," JoyPad2 Reg"},
	{ 0xc1,0xc1,ACT_IN," JoyPad2 Reg(Mirror)"},
	{ 0x00,0x00,ACT_IN," GameGear:Start Button/Country Code Reg"},
	{ 0xbe,0xbe,ACT_IO," VDP:Data Reg"},
	{ 0xbf,0xbf,ACT_IN," V-Blank Flag"},
	{ 0xbd,0xbd,ACT_IN," V-Blank Flag"},
	{ 0xbf,0xbf,ACT_OT," VDP Address Reg"},
	{ 0xbd,0xbd,ACT_OT," VDP Address Reg"},
	{ 0x7e,0x7e,ACT_IN," Scan Line Data"},
	{ 0x7e,0x7e,ACT_OT," PSG Port Reg(mirror)"},
	{ 0x7f,0x7f,ACT_IO," PSG Port Reg"},
	{ 0xf0,0xf0,ACT_OT," FM Unit Address Write Reg"},
	{ 0xf1,0xf1,ACT_OT," FM Unit Data Write Reg"},
	{ 0xf1,0xf1,ACT_IN," FM Unit Data Read Reg"},
	{ 0xf2,0xf2,ACT_IO," FM Unit Enable Check Reg"},
#endif // MESSAGETYPE
	{ 0xFFFF,0x0000,ACT_NL,NULL},
};

memargstr mapper_msx[] = {
#ifdef MESSAGETYPE_JAPANESE
/* Japanese */
	{ 0x0005,0x0005,ACT_CL, " DOS Call"},
	{ 0x000C,0x000C,ACT_CL, " BIOS : RDSLT(SLOT/読み込み)"},
	{ 0x0014,0x0014,ACT_CL, " BIOS : WRSLT(SLOT/書き込み)"},
	{ 0x001C,0x001C,ACT_CL, " BIOS : CALSLT(SLOT/サブルーチンコール)"},
	{ 0x0020,0x0020,ACT_CL, " BIOS : DCOMPR(HLとDEを比較)"},
	{ 0x0024,0x0024,ACT_CL, " BIOS : ENASLT(SLOT/有効化)"},
	{ 0x0030,0x0030,ACT_CL, " BIOS : CALLF(他のスロットのルーチンの呼び出し)"},
	{ 0x003B,0x003B,ACT_CL, " BIOS : INITIO(デバイス初期化)"},
	{ 0x0041,0x0041,ACT_CL, " BIOS : DISSCR(スクリーン停止)"},
	{ 0x0044,0x0044,ACT_CL, " BIOS : ENASCR(スクリーン有効)"},
	{ 0x0047,0x0047,ACT_CL, " BIOS : WRTVDP(VDPレジスタ書き込み)"},
	{ 0x004A,0x004A,ACT_CL, " BIOS : RDVRM(VRAM読み込み)"},
	{ 0x004D,0x004D,ACT_CL, " BIOS : WRTVRM(VRAM書き込み)"},
	{ 0x0056,0x0056,ACT_CL, " BIOS : FILVRM(VRAM指定領域のフィル"},
	{ 0x0059,0x0059,ACT_CL, " BIOS : LDIRMV(ブロック転送[VRAM->メモリ])"},
	{ 0x005C,0x005C,ACT_CL, " BIOS : LDIRVM(ブロック転送[メモリ->VRAM])"},
	{ 0x005F,0x005F,ACT_CL, " BIOS : CHGMOD(スクリーンモード変更)"},
	{ 0x0062,0x0062,ACT_CL, " BIOS : CHGCLR(画面の色変更)"},
	{ 0x0069,0x0069,ACT_CL, " BIOS : CLRSPR(スプライト初期化)"},
	{ 0x0072,0x0072,ACT_CL, " BIOS : INIGRP(画面を高解像グラフィックに初期化)"},
	{ 0x0090,0x0090,ACT_CL, " BIOS : GICINI(PSG/演奏初期化)"},
	{ 0x0093,0x0093,ACT_CL, " BIOS : WRTPSG(PSG/レジスタ書き込み)"},
	{ 0x0096,0x0096,ACT_CL, " BIOS : RDPSG (PSG/レジスタ読み込み)"},
	{ 0x0098,0x0099,ACT_CL, " BIOS : STRTMS(バックグランド演奏開始)"},
	{ 0x009C,0x009C,ACT_CL, " BIOS : CHSNS(キーボードバッファのチェック)"},
	{ 0x00C0,0x00C0,ACT_CL, " BIOS : BEEP(ブザーを鳴らす)"},
	{ 0x00C3,0x00C3,ACT_CL, " BIOS : CLS(画面クリア)"},
	{ 0x00C6,0x00C6,ACT_CL, " BIOS : POSIT(カーソルの移動)"},
	{ 0x00D5,0x00D5,ACT_CL, " BIOS : GTSTCK(ジョイスティック状態の取得)"},
	{ 0x00D8,0x00D8,ACT_CL, " BIOS : GTTRIG(トリガボタン状態の取得)"},
	{ 0x0135,0x0135,ACT_CL, " BIOS : CHGSND(1bitサウンドポート状態変更)"},
	{ 0x0138,0x0138,ACT_CL, " BIOS : RSLREG(基本SLOTレジスタ読み込み)"},
	{ 0x013B,0x013B,ACT_CL, " BIOS : WSLREG(基本SLOTレジスタ書き込み)"},
	{ 0x013E,0x013E,ACT_CL, " BIOS : RDVDP(VDPステータスレジスタ読み込み)"},
	{ 0x0141,0x0141,ACT_CL, " BIOS : SNSMAT(キーボード・マトリクス読み込み)"},
	{ 0x0156,0x0156,ACT_CL, " BIOS : KILBUF(キーボード・バッファをクリア)"},
	{ 0x015C,0x015C,ACT_CL, " BIOS : SUBROM(SUB-ROMコール)"},
	{ 0x015F,0x015F,ACT_CL, " BIOS : EXTROM(SUB-ROMコール)"},
	{ 0x0183,0x0183,ACT_CL, " BIOS : GETCPU(turboR)"},
	{ 0xf37d,0xf37d,ACT_CL, " Disk Basic"},

	{ 0x9800,0x981f,ACT_RW, " SCC 波形メモリデータ0(ch.A)"},
	{ 0x9820,0x983f,ACT_RW, " SCC 波形メモリデータ1(ch.B)"},
	{ 0x9840,0x985f,ACT_RW, " SCC 波形メモリデータ2(ch.C)"},
	{ 0x9860,0x987f,ACT_RW, " SCC 波形メモリデータ3(ch.D/E)"},
	{ 0x9880,0x9889,ACT_WT, " SCC 周波数データ Reg"},
	{ 0x988a,0x988e,ACT_WT, " SCC 音量 Reg"},
	{ 0x988f,0x988f,ACT_WT, " SCC 出力フラグ Reg"},
	{ 0x98e0,0x98ff,ACT_WT, " SCC テスト Reg"},

	{ 0x7c,0x7c,ACT_OT," FM-PACK (MSX MUSIC) アドレス Reg"},
	{ 0x7d,0x7d,ACT_IO," FM-PACK (MSX MUSIC) データ Reg"},
	{ 0x7e,0x7f,ACT_OT," Moonblaster FM アドレス Reg"},
	{ 0x7f,0x7f,ACT_IN," Moonblaster FM ステータス Reg"},
	{ 0x7f,0x7f,ACT_OT," Moonblaster FM データ Reg"},
	{ 0x80,0x80,ACT_IO," RS232C データ Reg"},
	{ 0x81,0x81,ACT_IO," RS232C コマンド/ステータス Reg"},
	{ 0x82,0x82,ACT_IO," RS232C CTS,Timer/Counter2,RI,CDフラグ / 設定 Reg"},
	{ 0x83,0x83,ACT_IO," RS232C Clock 0/1/2 読み込み / 受信割り込み許可 Reg"},
	{ 0x84,0x84,ACT_IO," I8253(RS232C Baud gener.)カウンタ0(受信クロック)"},
	{ 0x85,0x85,ACT_IO," I8253(RS232C Baud gener.)カウンタ1(送信クロック)"},
	{ 0x86,0x86,ACT_IO," I8253(RS232C Baud gener.)カウンタ2"},
	{ 0x86,0x86,ACT_OT," I8253(RS232C Baud gener.)モード Reg"},
	{ 0x89,0x8b,ACT_IO," MSX1 MVDP 9938 アダプタ用ポート"},
	{ 0x90,0x90,ACT_IN," ULA5RA087 Centronic プリンタビジーフラグ Reg"},
	{ 0x90,0x90,ACT_OT," ULA5RA087 Centronic プリンタストローブ Reg"},
	{ 0x91,0x91,ACT_OT," ULA5RA087 Centronic プリンタデータ Reg"},
	{ 0x98,0x98,ACT_IN," VRAM data read"},
	{ 0x98,0x98,ACT_OT," VRAM data write"},
	{ 0x99,0x99,ACT_OT," VDP (割り込み/スプライト衝突検出)ステータス"},
	{ 0x99,0x99,ACT_IN," VDP アドレス/レジスタ書き込み"},
	{ 0x9A,0x9A,ACT_OT," MVDP カラーパレット Reg"},
	{ 0xa0,0xa0,ACT_OT," AY-3-8910 PSG レジスタ選択"},
	{ 0xa1,0xa1,ACT_OT," AY-3-8910 PSG データ書き込み Reg"},
	{ 0xa2,0xa2,ACT_IO," AY-3-8910 PSG データ読み込み Reg"},
	{ 0xa8,0xa8,ACT_IO," I 8255A/ULA9RA041 Port A メモリースロット Reg"},
	{ 0xa9,0xa9,ACT_IO," I 8255A/ULA9RA041 Port B キーボードマトリクスカラム Reg"},
	{ 0xaa,0xaa,ACT_IO," I 8255A/ULA9RA041 Port C キーボードマトリクスロー選択 Reg"},
	{ 0xab,0xab,ACT_IO," I 8255A/ULA9RA041 モード Reg"},
	{ 0xb0,0xb3,ACT_IO," External 8255 (SONY data RAM pack)"},
	{ 0xb4,0xb4,ACT_OT," RP 5C01 RTC レジスタ選択"},
	{ 0xb5,0xb5,ACT_IO," RP 5C01 RTC データ Reg"},
	{ 0xb8,0xbb,ACT_IO," SANYO ライトペンインタフェース Reg"},
	{ 0xbc,0xbf,ACT_IO," VHD コントロール Reg"},
	{ 0xc0,0xc1,ACT_IO," MSX Audio Reg"},
	{ 0xc4,0xc4,ACT_IN," Moonblaster PCM ステータス Reg(Master)"},
	{ 0xc4,0xc4,ACT_OT," Moonblaster PCM アドレス Reg(Master)"},
	{ 0xc5,0xc5,ACT_OT," Moonblaster PCM データ Reg(Master)"},
	{ 0xc6,0xc6,ACT_IN," Moonblaster PCM ステータス Reg(Slave)"},
	{ 0xc6,0xc6,ACT_OT," Moonblaster PCM アドレス Reg(Slave)"},
	{ 0xc7,0xc7,ACT_OT," Moonblaster PCM データ Reg(Slave)"},
	{ 0xd0,0xd7,ACT_IO," 外部フロッピーコントロール Reg"},
	{ 0xd8,0xdb,ACT_IO," 漢字ROM Reg"},
	{ 0xf5,0xf5,ACT_IO," システムコントロール Reg"},
	{ 0xf7,0xf7,ACT_OT," Audio/Videoコントロール Reg"},
	{ 0xfc,0xff,ACT_IO," メモリーマッパー Reg"},
#else
/* English */
	{ 0x0005,0x0005,ACT_CL, " DOS Call"},
	{ 0x000C,0x000C,ACT_CL, " BIOS : RDSLT(SLOT/read)"},
	{ 0x0014,0x0014,ACT_CL, " BIOS : WRSLT(SLOT/write)"},
	{ 0x001C,0x001C,ACT_CL, " BIOS : CALSLT(SLOT/subroutine call)"},
	{ 0x0020,0x0020,ACT_CL, " BIOS : DCOMPR(compare HL and DE)"},
	{ 0x0024,0x0024,ACT_CL, " BIOS : ENASLT(SLOT/enable)"},
	{ 0x0090,0x0090,ACT_CL, " BIOS : GICINI(PSG/play initialize)"},
	{ 0x0093,0x0093,ACT_CL, " BIOS : WRTPSG(PSG register write)"},
	{ 0x0096,0x0096,ACT_CL, " BIOS : RDPSG (PSG register read)"},
	{ 0x0098,0x0099,ACT_CL, " BIOS : STRTMS(background play start)"},
	{ 0x00C0,0x00C0,ACT_CL, " BIOS : BEEP"},
	{ 0x00C3,0x00C3,ACT_CL, " BIOS : CLS"},
	{ 0x00C6,0x00C6,ACT_CL, " BIOS : POSIT(move cursor)"},
	{ 0x00D5,0x00D5,ACT_CL, " BIOS : GTSTCK(get stick status)"},
	{ 0x00D8,0x00D8,ACT_CL, " BIOS : GTTRIG(get button status )"},
	{ 0x0135,0x0135,ACT_CL, " BIOS : CHGSND(1bit sound port)"},
	{ 0x0183,0x0183,ACT_CL, " BIOS : GETCPU(turboR)"},
	{ 0xf37d,0xf37d,ACT_CL, " Disk Basic"},

	{ 0x9800,0x981f,ACT_RW, " SCC wave memory data 0(ch.A)"},
	{ 0x9820,0x983f,ACT_RW, " SCC wave memory data 1(ch.B)"},
	{ 0x9840,0x985f,ACT_RW, " SCC wave memory data 2(ch.C)"},
	{ 0x9860,0x987f,ACT_RW, " SCC wave memory data 3(ch.D/E)"},
	{ 0x9880,0x9889,ACT_WT, " SCC freq. data Reg"},
	{ 0x988a,0x988e,ACT_WT, " SCC output volume Reg"},
	{ 0x988f,0x988f,ACT_WT, " SCC output select Reg"},
	{ 0x98e0,0x98ff,ACT_WT, " SCC test Reg"},

	{ 0x7c,0x7c,ACT_OT," FM-PACK (MSX MUSIC) address Reg"},
	{ 0x7d,0x7d,ACT_IO," FM-PACK (MSX MUSIC) data Reg"},
	{ 0x7e,0x7f,ACT_OT," Moonblaster FM Address Reg"},
	{ 0x7f,0x7f,ACT_IN," Moonblaster FM Status Reg"},
	{ 0x7f,0x7f,ACT_OT," Moonblaster FM Data Reg"},
	{ 0x80,0x80,ACT_IO," RS232C data Reg"},
	{ 0x81,0x81,ACT_IO," RS232C command/status Reg"},
	{ 0x82,0x82,ACT_IO," RS232C CTS,Timer/Counter2,RI,CD flag / setting Reg"},
	{ 0x83,0x83,ACT_IO," RS232C Clock 0/1/2 read Reg / recv.irq enable Reg"},
	{ 0x84,0x84,ACT_IO," I8253(RS232C Baud gener.)counter0(recv.clock)"},
	{ 0x85,0x85,ACT_IO," I8253(RS232C Baud gener.)counter1(send.clock)"},
	{ 0x86,0x86,ACT_IO," I8253(RS232C Baud gener.)counter2"},
	{ 0x86,0x86,ACT_OT," I8253(RS232C Baud gener.)mode Reg"},
	{ 0x89,0x8b,ACT_IO," MSX1 MVDP 9938 adapter port"},
	{ 0x90,0x90,ACT_IN," ULA5RA087 Centronic printer busy Reg"},
	{ 0x90,0x90,ACT_OT," ULA5RA087 Centronic printer strobe Reg"},
	{ 0x91,0x91,ACT_OT," ULA5RA087 Centronic printer data Reg"},
	{ 0x98,0x98,ACT_IN," VRAM data read"},
	{ 0x98,0x98,ACT_OT," VRAM data write"},
	{ 0x99,0x99,ACT_OT," VDP (interrupt/spr conc.)status"},
	{ 0x99,0x99,ACT_IN," VDP address/reg. write"},
	{ 0x9A,0x9A,ACT_OT," MVDP color palette Reg"},
	{ 0xa0,0xa0,ACT_OT," AY-3-8910 PSG address Reg"},
	{ 0xa1,0xa1,ACT_OT," AY-3-8910 PSG data write Reg"},
	{ 0xa2,0xa2,ACT_IO," AY-3-8910 PSG data read Reg"},
	{ 0xa8,0xa8,ACT_IO," I 8255A/ULA9RA041 Port A memory slot Reg"},
	{ 0xa9,0xa9,ACT_IO," I 8255A/ULA9RA041 Port B keybord matrix column Reg"},
	{ 0xaa,0xaa,ACT_IO," I 8255A/ULA9RA041 Port C keybord matrix row select Reg"},
	{ 0xab,0xab,ACT_IO," I 8255A/ULA9RA041 mode Reg"},
	{ 0xb0,0xb3,ACT_IO," External 8255 (SONY data RAM pack)"},
	{ 0xb4,0xb4,ACT_OT," RP 5C01 RTC address Reg"},
	{ 0xb5,0xb5,ACT_IO," RP 5C01 RTC data Reg"},
	{ 0xb8,0xbb,ACT_IO," SANYO light pen interface Reg"},
	{ 0xbc,0xbf,ACT_IO," VHD control Reg"},
	{ 0xc0,0xc1,ACT_IO," MSX Audio Reg"},
	{ 0xc4,0xc4,ACT_IN," Moonblaster PCM status Reg(Master)"},
	{ 0xc4,0xc4,ACT_OT," Moonblaster PCM address Reg(Master)"},
	{ 0xc5,0xc5,ACT_OT," Moonblaster PCM data Reg(Master)"},
	{ 0xc6,0xc6,ACT_IN," Moonblaster PCM status Reg(Slave)"},
	{ 0xc6,0xc6,ACT_OT," Moonblaster PCM address Reg(Slave)"},
	{ 0xc7,0xc7,ACT_OT," Moonblaster PCM data Reg(Slave)"},
	{ 0xd0,0xd7,ACT_IO," External floppy disk control Reg"},
	{ 0xd8,0xdb,ACT_IO," KANJI ROM Reg"},
	{ 0xf5,0xf5,ACT_IO," System control Reg"},
	{ 0xf7,0xf7,ACT_OT," Audio/Video control Reg"},
	{ 0xfc,0xff,ACT_IO," memory mapper Reg"},
#endif // MESSAGETYPE
	{ 0xFFFF,0x0000,ACT_NL,NULL},
};

memargstr mapper_pc88[] = {
	{ 0x00,0x0e,ACT_IN," キーボード"},
	{ 0x31,0x31,ACT_IN," システムポート1"},
	{ 0x32,0x32,ACT_IO," システムポート2"},
	{ 0x40,0x40,ACT_IO," システムポート3"},
	{ 0x44,0x44,ACT_IO," YM2203/2608 アドレス Reg"},
	{ 0x45,0x45,ACT_IO," YM2203/2608 データ Reg"},
	{ 0x44,0x46,ACT_IO," YM2608 拡張アドレス Reg"},
	{ 0x45,0x47,ACT_IO," YM2608 拡張データ Reg"},
	{ 0x5c,0x5c,ACT_IN," GVRAMステータス"},
	{ 0x5c,0x5f,ACT_OT," GVRAM選択"},
	{ 0x60,0x68,ACT_IO," DMAC"},
	{ 0x70,0x70,ACT_OT," メモリウインドウオフセットアドレス"},
	{ 0x71,0x71,ACT_IO," 拡張ROMセレクト"},
	{ 0x80,0x87,ACT_IO," HAL研 響 : YM3802 Reg"},
	{ 0x88,0x88,ACT_IO," HAL研 響 : YM2151 アドレス Reg"},
	{ 0x89,0x89,ACT_IO," HAL研 響 : YM2151 データ Reg"},
	{ 0xa0,0xa1,ACT_IO," 8801-10 : AY8910 アドレス Reg"},
	{ 0xa2,0xa3,ACT_IO," 8801-10 : AY8910 データ Reg"},
	{ 0xa8,0xa8,ACT_IO," SB2 アドレス Reg"},
	{ 0xa9,0xa9,ACT_IO," SB2 データ Reg"},
	{ 0xaa,0xaa,ACT_IO," SB2 割り込みマスク"},
	{ 0xac,0xac,ACT_IO," SB2 拡張アドレス Reg"},
	{ 0xad,0xad,ACT_IO," SB2 拡張データ Reg"},
	{ 0xe4,0xe4,ACT_OT," 8214モード割り込み制御"},
	{ 0xe6,0xe6,ACT_OT," 8214モード割り込みマスク"},
	{ 0xfc,0xff,ACT_IO," インテリジェントFDD"},
};

memargstr mapper_coleco[] = {
	{ 0x0213,0x0213,ACT_CL, " BIOS : サウンド初期化"},
	{ 0x025e,0x025e,ACT_CL, " BIOS : サウンドコード設定"},
	{ 0x027f,0x027f,ACT_CL, " BIOS : サウンドコードプレイ1"},
	{ 0x0300,0x0300,ACT_CL, " BIOS : サウンドコードプレイ2"},
	{ 0x1ff4,0x1ff4,ACT_CL, " BIOS : サウンドコードプレイ1"},
	{ 0x1f61,0x1f61,ACT_CL, " BIOS : サウンドコードプレイ2"},
	{ 0x1ff1,0x1ff1,ACT_CL, " BIOS : サウンドコード設定"},
	{ 0x1fee,0x1fee,ACT_CL, " BIOS : サウンド初期化"},

	{ 0xff,0xff,ACT_OT," PSG データ書き込み Reg"},

	{ 0xFFFF,0x0000,ACT_NL,NULL},
};

#define MAX_MAPPERS 8
#define MAX_MAPPERNUMS 16

memargstr *mapcom[MAX_MAPPERNUMS+1] = {
	mapper_sms,					// 00 SEGA Master System
	mapper_msx,					// 01 MSX
	mapper_pc88			,		// 02 PC-8801 mkII SR
	mapper_coleco,				// 03 Coleco Vision
	mapper_undefined_com,		// 04
	mapper_undefined_com,		// 05
	mapper_undefined_com,		// 06
	mapper_undefined_com,		// 07
	mapper_undefined_com,		// 08
	mapper_undefined_com,		// 09
	mapper_undefined_com,		// 0A
	mapper_undefined_com,		// 0B
	mapper_undefined_com,		// 0C
	mapper_undefined_com,		// 0D
	mapper_undefined_com,		// 0E
	mapper_undefined_com,		// 0F
	mapper_undefined_com,		// 10
};

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
void make_byte( int sw, char *buf, int num )
{
	switch( sw ) {
	case INTEL:
		sprintf( buf, "0%02XH", num&0xff );
		break;
	case MOTOROLA:
		sprintf( buf, "$%02X", num&0xff );
		break;
	case C_LANG:
		sprintf( buf, "0x%02X", num&0xff );
		break;
	}
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
void make_ofs_byte( int sw, char *buf, int num )
{
	if( num >= 0x80 ) {
		*buf = '-';
		num = (num^0xff)+1;
	} else {
		*buf = '+';
	}
	buf++;
	switch( sw ) {
	case INTEL:
		sprintf( buf, "0%02XH", num&0xff );
		break;
	case MOTOROLA:
		sprintf( buf, "$%02X", num&0xff );
		break;
	case C_LANG:
		sprintf( buf, "0x%02X", num&0xff );
		break;
	}
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
void make_word( int sw, char *buf, int num )
{
	switch( sw ) {
	case INTEL:
		sprintf( buf, "0%04XH", num&0xffff );
		break;
	case MOTOROLA:
	sprintf( buf, "$%04X", num&0xffff );
		break;
	case C_LANG:
		sprintf( buf, "0x%04X", num&0xffff );
		break;
	}
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
disZ80data *getOPdata( uint8_t *buf, uint32_t addr )
{
	int	ofstbl[] = { 0, 1, 3 };
	int	n = 0, ofs = 0;

	while( disz80[n][buf[addr+ofstbl[ofs]]].len < 0 ) {
		n = -disz80[n][buf[addr+ofstbl[ofs]]].len;
		ofs++;
	}

	return &(disz80[n][buf[addr+ofstbl[ofs]]]);
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
int disasmZ80( uint8_t *buf, uint32_t base, uint32_t addr, char *stream, int sw, int nullcheck )
{
	disZ80data	*data;
	int		i, st;
	int		*op_type;
	char	temp[256];
	int		ofs;
	int		line;
	int		rel;
	disZ80data NullData = { 0, 0, NMT_NUL, 0, OT_NUL, OT_NONE, ACT_NL };

	// output for address
	st = sprintf( stream, "%04X :", base+addr );
	// get opdata structur
	data = getOPdata( buf, addr );
	// exeption by nullcheck and 0xff,0xff data
	if( nullcheck && (buf[addr] == 0xff) && (buf[addr+1] == 0xff) ) {
		data = &NullData;
		ofs = 0;
		while( buf[addr+ofs] == 0xff ) {
			data->len++;
			data->op_num++;
			ofs++;
			if( ofs == 4 ) break;
		}
	}
	// write instruction binary data
	for ( i = 0; i < data->len; i++ ) {
		st += sprintf( &stream[st], " %02X", buf[addr+i] );
	}
	switch( data->len ) {
	case 4:
		st += sprintf( &stream[st], "\t" );
		break;
	default:
		st += sprintf( &stream[st], "\t\t" );
		break;
	}
	// write nimonic
	st += sprintf( &stream[st], "%s\t", nimonic[data->nimonic] );
	line = 32;					// ここまででtab8で32桁になっているはず
	if( data->op_num != 0 ) {
		op_type = &(data->op0_type);
		ofs = data->index;
		for( i = 0; i < data->op_num; i++ ) {
			if( i != 0 ) {
				st += sprintf( &stream[st], "," );
				line++;
			}
			if( *op_type < OT_IMM_BYTE ) {
				st += sprintf( &stream[st], optype0[*op_type] );
				line += strlen( optype0[*op_type] );
				op_type++;
			} else {
				switch( *op_type ) {
				case OT_NUL:
					make_byte( sw, temp, buf[addr+ofs] );
					st += sprintf( &stream[st], temp );
					line += strlen( temp );
					ofs++;
					break;
				case OT_IMM_BYTE:
				case OT_UND:
					make_byte( sw, temp, buf[addr+ofs] );
					st += sprintf( &stream[st], temp );
					line += strlen( temp );
					ofs++;
					op_type++;
					break;
				case OT_IMM_PORT:
					make_byte( sw, temp, buf[addr+ofs] );
					st += sprintf( &stream[st], "(%s)", temp );
					line += strlen( temp )+2;
					ofs++;
					op_type++;
					break;
				case OT_RST:
					make_byte( sw, temp, buf[addr]-0xc7 );
					st += sprintf( &stream[st], temp );
					line += strlen( temp );
					op_type++;
					break;
				case OT_IDX_IX:
					make_ofs_byte( sw, temp, buf[addr+ofs] );
					st += sprintf( &stream[st], "(ix%s)", temp );
					line += strlen( temp )+4;
					ofs++;
					op_type++;
					break;
				case OT_IDX_IY:
					make_ofs_byte( sw, temp, buf[addr+ofs] );
					st += sprintf( &stream[st], "(iy%s)", temp );
					line += strlen( temp )+4;
					ofs++;
					op_type++;
					break;
				case OT_REL:
					rel = buf[addr+ofs];
					if( rel >= 0x80 ) rel -= 0x100;
					make_word( sw, temp, base+addr+rel+2 );
					st += sprintf( &stream[st], temp );
					line += strlen( temp );
					ofs++;
					op_type++;
					break;
				case OT_IMM_WORD:
					make_word( sw, temp, (buf[addr+ofs+1]<<8)+buf[addr+ofs] );
					st += sprintf( &stream[st], temp );
					line += strlen( temp );
					ofs += 2;
					op_type++;
					break;
				case OT_ABS:
					make_word( sw, temp, (buf[addr+ofs+1]<<8)+buf[addr+ofs] );
					st += sprintf( &stream[st], "(%s)", temp );
					line += strlen( temp )+2;
					ofs += 2;
					op_type++;
					break;
				}
			}
		}
	}
	while( line < 48 ) {
		st += sprintf( &stream[st],"\t" );
		line += 8;
	}
	// コメント処理
	// 下の関数に移した
	st += sprintf( &stream[st],";\n" );
	return data->len;
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
void comchkZ80( uint8_t *buf, uint32_t base, uint32_t addr, char *stream, int mapper[] )
{
	// コメント付加
	int i, abs, io;
	int st;

	// コメントまで飛ばす
	for ( st = 0 ; stream[st] != ';' ; st++ );
	st++;

	disZ80data	*data = getOPdata( buf, addr );
	abs = buf[addr+data->index]+buf[addr+data->index+1]*256;
	io  = buf[addr+data->index]&0xff;
	mapper--;
	do {
		mapper++;
		for( i = 0; mapcom[*mapper][i].comment != NULL; i++ ) {
			// アドレスに対してのコメント(Ver 0.05)
			if( ((mapcom[*mapper][i].staddr <= (base+addr)) && ((base+addr) <= mapcom[*mapper][i].edaddr))
			 && (ACT_AD&mapcom[*mapper][i].access) ) break;
			// メモリマップ のコメントチェック
			if( (data->op0_type == OT_ABS) || (data->op1_type == OT_ABS)
				&& (data->acc_type&ACT_RW) ) {
				if( ((mapcom[*mapper][i].staddr <= abs) && (abs <= mapcom[*mapper][i].edaddr))
				 && (data->acc_type&mapcom[*mapper][i].access) ) break;
			}
			// I/Oマップ のコメントチェック
			if( (data->op0_type == OT_IMM_PORT) || (data->op1_type == OT_IMM_PORT)
				&& (data->acc_type&ACT_IO) ) {
				if( ((mapcom[*mapper][i].staddr <= io ) && (io  <= mapcom[*mapper][i].edaddr))
				 && (data->acc_type&mapcom[*mapper][i].access) ) break;
			}
			// BIOS CALLのコメントチェック
			if( data->nimonic == NMT_CALL ) {
				if( ((mapcom[*mapper][i].staddr <= abs) && (abs <= mapcom[*mapper][i].edaddr))
				 && (ACT_CL&mapcom[*mapper][i].access) ) break;
			}
		}
		if( mapcom[*mapper][i].comment != NULL ) break;
	} while ( *mapper != MAX_MAPPERNUMS );
	if ( mapcom[*mapper][i].comment != NULL ) {
		st += sprintf(&stream[st],mapcom[*mapper][i].comment);
	}
	st += sprintf( &stream[st],"\n" );
}

#if 0
int tablechk6502(uint8_t *buf,uint32_t base,uint32_t addr,char *stream)
{
	// 特殊テーブルのチェック
	int ret;
	int st,i,j;
	
	ret = 0;
	// まずは命令のチェック
	if ( dis6502[buf[addr]].nimonic == nimonic[NMT_RTS] ||
		 dis6502[buf[addr]].nimonic == nimonic[NMT_JMP]
		) {
		addr += opbytelength[dis6502[buf[addr]].type];
		// 音程テーブルのチェック これだと、DQ はだめなんだよなぁ...
		j = -1;
		if ( buf[addr+0]+buf[addr+1]*256 == 0x06AE &&
			  buf[addr+2]+buf[addr+3]*256 == 0x064E ) j = 1;
		if ( buf[addr+1]+buf[addr+0]*256 == 0x06AE &&
			  buf[addr+3]+buf[addr+2]*256 == 0x064E ) j = 0;
		if ( j >= 0 ) {
			for ( st = 0 ; stream[st] != 0x0a ; st++);
			st++;
			st += sprintf(&stream[st],";;多分音程テーブル\n");
			for ( i = 0 ; i < 24 ; i+=2 ) {
				st += sprintf(&stream[st],"%04X : %02X %02X\t\tdw\t$%04X\t\t;\n",
					base+addr+i,buf[addr+i],buf[addr+i+1],
					buf[addr+i+(1-j)]+buf[addr+i+j]*256);
			}
			ret = i;
		}
	}
	return ret;
}
#endif

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
void printhelp( void )
{
	printf("Manbow-J Disassembler for Z80.  Version 0.08\n"
	       "Original by Minachun Disassembler Version 0.04\n"
	       "Usage:mdZ80.exe [input file] [output file] [options]\n"
#ifdef MESSAGETYPE_JAPANESE
	       "入力バイナリを Z80 バイナリと見なして逆アセンブルします。\n"
	       "[input file] : 入力ファイル名\n"
	       "[output file] : 出力ファイル名 指定しない場合は標準出力へ\n"
	       "[options] : -s????...逆アセンブル開始アドレスを指定する。デフォルトは、\n"
	       "                     ファイルの最後が 0xffff となるようにする。\n"
	       "            -l????...逆アセンブルするバイト長を指定する。デフォルトは、\n"
	       "                     ファイルすべてを読み込むまで出力する。\n"
	       "            -o????...逆アセンブル開始オフセットを指定する。デフォルトは、\n"
	       "                     ファイルの先頭、つまり 0 。\n"
	       "            -m??...マッパー番号を指定します。デフォルトでは、マッパー別の\n"
	       "                   コメントを出力しません。最大8つまで複数の指定が可能です。\n"
	       "                   Ex) -m0 ... Sega Master System\n"
	       "                       -m1 ... MSX\n"
	       "                       -m2 ... NEC PC-8801\n"
	       "                       -m3 ... Coleco Vision\n"
	       "            -ni   ...数値をインテル形式(0nnnnH)で出力する。\n"
	       "            -nm   ...数値をモトローラ形式($nnnn)で出力する。\n"
	       "            -nc   ...数値をC言語形式(0xnnnn)で出力する。\n"
	       "            -r    ...RST38Hが連続してある場合単なるヌルデータとして扱う。\n"
#else
	       "DIsassemble regarding the input file as Z80 binary file.\n"
	       "[input file] : input filename want to disassemble\n"
	       "[output file] : output filename.if don't set , output stream is stdout.\n"
	       "[options] : -s????...Start Address of disassemble. Default is the value\n"
	       "                     which the last addr. is 0xffff.\n"
	       "            -l????...Byte length of disassemble. Default reads until the\n"
	       "                     whole input file is disassembled.\n"
	       "            -o????...Start offset Addr. of disassemble. Default is Zero ; \n"
	       "                     the head of the input file.\n"
	       "            -m????...Mapper number.If set, output uniq comment of each mapper.\n"
	       "                   Default is off. Multiple # is O.K. until 8 times.\n"
	       "                   Ex) -m0 ... Sega Master System\n"
	       "                       -m1 ... MSX\n"
	       "                       -m2 ... NEC PC-8801\n"
	       "                       -m3 ... Coleco Vision\n"
	       "            -ni   ...Output numerical value by Intel form.(0nnnnH).\n"
	       "            -nm   ...Output numerical value by Motorola form.($nnnn).\n"
	       "            -nc   ...Output numerical value by C-Languege form.(0xnnnn).\n"
	       "            -r    ...treated as mere null data when there is continuously RST 38H.\n"
#endif
	);
	return;
}

/*------------------------------------------------------------------------------

------------------------------------------------------------------------------*/
int main(int argc,char *argv[])
{
	FILE *f, *g;
	size_t siz;
	uint32_t base, addr;
	int	nullcheck = 0;
	int i,j;
	int	sw = INTEL;
	int tablef, mapperf[MAX_MAPPERS+1], mapperidx;
	char outst[1024];

	if ( argv[1] == NULL ) {
		printhelp();
		return -1;
	}
	f = fopen( argv[1], "rb" );
	if( f ) {
		// ファイルサイズを求める
		fseek( f, 0, SEEK_END );
		siz = ftell( f );
		// オプション判定
		i = 2;
		// デフォルト出力先は標準出力
		g = stdout;
		if ( argv[i] != NULL && argv[i][0] != '-' ) {
			// 出力ファイルを作る
			g = fopen(argv[i],"w");
			i++;
		}
		base = 0xffffffff;
		j = 0;				// オフセット
		tablef = 0;
		mapperf[0] = MAX_MAPPERNUMS;
		mapperidx = 0;
		while ( argv[i] != NULL ) {
			if ( argv[i][0] == '-' ) {
				switch ( argv[i][1] ) {
					case 's':
						sscanf(&argv[i][2],"%x",&base);
						break;
					case 'l':
						sscanf(&argv[i][2],"%zx",&siz);
						break;
					case 'o':
						sscanf(&argv[i][2],"%x",&j);
						break;
					case 'n':
						switch ( argv[i][2] ) {
						case 'i':
							sw = INTEL;
							break;
						case 'm':
							sw = MOTOROLA;
							break;
						case 'c':
							sw = C_LANG;
							break;
						default:
#ifdef MESSAGETYPE_JAPANESE
							fprintf(stderr,"数値設定オプションの値が異常です:%s\n",argv[i]);
#else
							fprintf(stderr,"abnormal number Option:%s\n",argv[i]);
#endif
							break;
						}
						break;
					case 'm':
						if ( mapperidx <= MAX_MAPPERS ) {
							sscanf(&argv[i][2],"%x",&mapperf[mapperidx]);
							if( mapperf[mapperidx] >= MAX_MAPPERNUMS ) {
								mapperf[mapperidx] = 0;
							}
							mapperf[++mapperidx] = MAX_MAPPERNUMS;
						} else {
#ifdef MESSAGETYPE_JAPANESE
							fprintf(stderr,"指定したマッパーの数が多すぎます。無視します。\n");
#else
							fprintf(stderr,"Too many mapper#.Max # is 8.This # is ignored.\n");
#endif
						}
						break;
					case 'r':
						nullcheck = 1;
						break;
					default:
#ifdef MESSAGETYPE_JAPANESE
						fprintf(stderr,"未定義なオプション:%s\n",argv[i]);
#else
						fprintf(stderr,"Undefined Option:%s\n",argv[i]);
#endif
				}
			}
			i++;
		}
		// ベースアドレスの調整
		if ( base == 0xffffffff ) base = 0x10000u - uint32_t(siz);
		// メモリを確保して読み込む
		uint8_t *buf = new uint8_t[siz+2];
		fseek( f, j, SEEK_SET );
		siz = fread( buf, 1, siz, f );
		fclose( f );
		// 念の為の初期化
		buf[siz] = 0xff;
		buf[siz+1] = 0xff;
#ifdef MESSAGETYPE_JAPANESE
		printf("逆アセンブル範囲:%04X - %04X\n",base,base+uint32_t(siz)-1);
#else
		printf("Disassemble renge:%04X - %04X\n",base,base+siz-1);
#endif
		if( g ) {
			for( addr = 0 ; addr < siz ; ) {
				// 逆アセンブル
				j = disasmZ80( buf, base, addr, outst, sw, nullcheck );
				// コメントつけ加え
				comchkZ80( buf, base, addr, outst, mapperf );
#if 0
				// 特殊テーブル処理
				if ( tablef ) j += tablechk6502( buf, base, addr, outst );
#endif
				fprintf( g, outst );
				addr += j;
			}
			if( g != stdout ) fclose( g );
		} else {
#ifdef MESSAGETYPE_JAPANESE
			fprintf( stderr, "出力ファイル %s が作れませんでした。\n", argv[2] );
#else
			fprintf( stderr, "Can't write file : %s .\n", argv[2] );
#endif
		}
		delete [] buf;
	} else {
#ifdef MESSAGETYPE_JAPANESE
		fprintf( stderr, "入力ファイル %s が開けませんでした。\n", argv[1] );
#else
		fprintf( stderr, "Can't open intput file : %s .\n", argv[1] );
#endif
	}
	return 0;
}
