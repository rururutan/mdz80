#ifndef MDZ80_H_
#define MDZ80_H_

#include <stdint.h>

/* If you comment out below semantic , this program outputs English Messages. */
//#define MESSAGETYPE_JAPANESE

typedef struct _regZ80 {
	uint8_t	a[2];
	uint8_t	b[2];
	uint8_t	c[2];
	uint8_t	d[2];
	uint8_t	e[2];
	uint8_t	h[2];
	uint8_t	l[2];
	uint16_t	ix;
	uint16_t	iy;
	union {
		uint8_t f;
		struct {
			uint8_t carry : 1;
			uint8_t zero : 1;
			uint8_t intr : 1;
			uint8_t dec : 1;
			uint8_t brk : 1;
			uint8_t resv : 1;
			uint8_t ovfl : 1;
			uint8_t sign : 1;
		};
	} f[2];
	uint16_t sp;
	uint16_t pc;
} regZ80;

typedef struct _memargstr {
	uint16_t staddr;			// 開始アドレス
	uint16_t edaddr;			// 終了アドレス
	int access;					// アクセス方法のフラグ
	const char *comment;		// コメントの内容
} memargstr;

typedef struct {
	int		len;				// 命令長
	int		index;				// オペランドが参照開始するデータの位置
	int		nimonic;			// ニーモニック文字列の番号
	int		op_num;				// オペランド数
	int		op0_type;			// 第1オペランド
	int		op1_type;			// 第2オペランド
	int		acc_type;			// アクセスタイプ(リード/ライト/イン/アウト)
} disZ80data;

// dis6502str.type = Address Type | Access Type;
// Address Type
enum {
	OT_NONE = 0,

	OT_REG_A,			// A Register
	OT_REG_B,			// B Register
	OT_REG_C,			// C Register
	OT_REG_D,			// D Register
	OT_REG_E,			// E Register
	OT_REG_H,			// H Register
	OT_REG_L,			// L Register
	OT_REG_F,			// F Register
	OT_REG_I,			// Interrupt Vector
	OT_REG_R,			// Refresh Counter

	OT_REG_AF,			// AF  Register
	OT_REG_RAF,			// AF' Register
	OT_REG_BC,			// BC  Register
	OT_REG_DE,			// DE  Register
	OT_REG_HL,			// HL  Register
	OT_REG_IX,			// HL  Register
	OT_REG_IXL,			// HL  Register
	OT_REG_IXH,			// HL  Register
	OT_REG_IY,			// HL  Register
	OT_REG_IYL,			// HL  Register
	OT_REG_IYH,			// HL  Register
	OT_REG_SP,			// SP  Register

	OT_PORT_C,			// ポート		(C)

	OT_ABS_BC,			// 絶対アドレス	(BC)
	OT_ABS_DE,			// 絶対アドレス	(DE)
	OT_ABS_HL,			// 絶対アドレス	(HL)
	OT_ABS_IX,			// 絶対アドレス	(IX)
	OT_ABS_IY,			// 絶対アドレス	(IY)
	OT_ABS_SP,			// 絶対アドレス	(SP)

	OT_NZ,				// コンディション non zero
	OT_Z,				// コンディション zero
	OT_NC,				// コンディション non carry
	OT_C,				// コンディション carry
	OT_PO,				// コンディション parity odd
	OT_PE,				// コンディション parity even
	OT_P,				// コンディション sign positive(plus)
	OT_M,				// コンディション sign negative(minaus)

	OT_BIT_0,			// bit操作用
	OT_BIT_1,			// bit操作用
	OT_BIT_2,			// bit操作用
	OT_BIT_3,			// bit操作用
	OT_BIT_4,			// bit操作用
	OT_BIT_5,			// bit操作用
	OT_BIT_6,			// bit操作用
	OT_BIT_7,			// bit操作用

	OT_IM_0,			// IM	0
	OT_IM_1,			// IM	1
	OT_IM_2,			// IM	2
/* hex byte data */
	OT_IMM_BYTE = 0x0100,	// 即値			d8
	OT_RST,					// rst
	OT_IMM_PORT,			// ポート		(d8)
	OT_UND,					// 未定義命令用1byte
	OT_NUL,					// 連続したデータの書き換え用
/* hex byte data(byte offset) */
	OT_IDX_IX	= 0x0200,	// IX間接		(IX+d8)
	OT_IDX_IY,				// IY間接		(IX+d8)
/* hex word data(byte offset) */
	OT_REL		= 0x0400,	// 相対アドレス	d8
/* hex word data	*/
	OT_IMM_WORD = 0x0800,	// 即値			d16
	OT_ABS,					// 絶対アドレス	(d16)
};

#define ADT_MASK 0xff

// Access Type
#define	ACT_NL	0
#define	ACT_RD	1
#define	ACT_WT	2
#define	ACT_OT	4
#define	ACT_IN	8
#define	ACT_AD	0x4000
#define	ACT_CL	0x8000

#define ACT_RW ( ACT_RD | ACT_WT )
#define ACT_IO ( ACT_IN | ACT_OT )

// Name Type
enum {
	NMT_UND = 0,
	NMT_NUL,
	NMT_LD,
	NMT_PUSH,
	NMT_POP,
	NMT_EX,
	NMT_EXX,
	NMT_LDI,
	NMT_LDIR,
	NMT_LDD,
	NMT_LDDR,
	NMT_CPI,
	NMT_CPIR,
	NMT_CPD,
	NMT_CPDR,
	NMT_ADD,
	NMT_ADC,
	NMT_SUB,
	NMT_SBC,
	NMT_AND,
	NMT_OR,
	NMT_XOR,
	NMT_CP,
	NMT_INC,
	NMT_DEC,
	NMT_DAA,
	NMT_CPL,
	NMT_NEG,
	NMT_CCF,
	NMT_SCF,
	NMT_NOP,
	NMT_HALT,
	NMT_DI,
	NMT_EI,
	NMT_IM,
	NMT_RLCA,
	NMT_RLA,
	NMT_RRCA,
	NMT_RRA,
	NMT_RLC,
	NMT_RL,
	NMT_RRC,
	NMT_RR,
	NMT_SLA,
	NMT_SLL,
	NMT_SRA,
	NMT_SRL,
	NMT_RLD,
	NMT_RRD,
	NMT_BIT,
	NMT_SET,
	NMT_RES,
	NMT_JP,
	NMT_JR,
	NMT_DJNZ,
	NMT_CALL,
	NMT_RET,
	NMT_RETI,
	NMT_RETN,
	NMT_RST,
	NMT_IN,
	NMT_INI,
	NMT_INIR,
	NMT_IND,
	NMT_INDR,
	NMT_OUT,
	NMT_OUTI,
	NMT_OTIR,
	NMT_OUTD,
	NMT_OTDR,
};

enum {
	INTEL,
	MOTOROLA,
	C_LANG,
};

#endif/*MDZ80_H_*/
