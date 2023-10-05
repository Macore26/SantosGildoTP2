#ifndef _UTYPES_H_
#define _UTYPES_H_

/** @defgroup TiposUsais Tipos-Usais
 * @{
 *
 * Tipos-Usais para ajudar, facilitar a vida aos programadores
 */

typedef unsigned char uchar;   ///< uchar é a abreviatura para unsigned char
typedef unsigned short ushort; ///< ushort é a abreviatura para unsigned short
typedef unsigned int uint;     ///< uint é a abreviatura para unsigned int
typedef unsigned long ulong;   ///< ulong é a abreviatura para unsigned long

typedef unsigned char Byte;    ///< 8 bits, só no i386
typedef unsigned short Word;   ///< 16 bits, só no i386

/**
 * Definição de várias cores
 */
#define BLACK 0
#define WHITE 0xF
#define GREEN 2
#define RED 4
#define BLUE 1

/**
 * Definição do tipo boleano
 */
typedef enum {
  false = 0, 	///< valor falso
  true = 1 		///< valor verdadeiro
} Bool; 		///< definição do tipo Bool de boleano

/**@} final dos Tipos-Usais */

#endif

