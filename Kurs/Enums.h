#pragma once

typedef enum Statement { S0, S1, S2, S3, S4, S5, S6 } Statement; // Набор состояний

typedef enum Output { O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15, O16, O17, O18, O19, O20, O21, O22, O23, 
			O24, O25, O26, O27, O28, O29, O30, O31, O32, O33, O34, O35, O36, O37, O38, O39, O40, O41, O42} Output; // Набор выходных сигналов

typedef enum TokenType { IDENT, DEC, STR, COMMA, PLUS, MINUS, MUL, DIV, LBR, RBR, LFBR, RFBR, COL, SCOL, MTHAN, LTHAN, EQUAL, DOT, EXC, 
			PACKAGE, BSLASH, FUNC, VAR, FLOAT64, INT, ASS, RETURN, FOR, IMPORT, IF, AND, OR, ELSE, LEQUAL, MEQUAL, DEQUAL, EXEQUAL, 
			FPRINTLN, FSQRT, MAIN, LSQBR, RSQBR} TokenType; //Типы лексем
