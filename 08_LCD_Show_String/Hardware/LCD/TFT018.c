/*

                         \\\|///
                       \\  - -  //
                        (  @ @  )
+---------------------oOOo-(_)-oOOo-------------------------+
|                 智林STM32开发板试验程序                   |
|                   1.8‘ TFT LCD Driver                     |
|                 刘笑然 by Xiaoran Liu                     |
|                        2008.4.16                          |
|                                                           |
|           智林测控技术研究所 ZERO research group          |
|                      www.the0.net                         |
|                             Oooo                          |
+-----------------------oooO--(   )-------------------------+
                       (   )   ) /
                        \ (   (_/
                         \_)     

*/
/*----------------------------------------------------------*\
 |  引入相关芯片的头文件                                    |
\*----------------------------------------------------------*/
#include <stm32f10x.h>    // STM32F10x Library Definitions
#include "MyType.h"
#include "TFT018.h"
/*----------------------------------------------------------*\
 | HARDWARE DEFINITIONS                                     |
\*----------------------------------------------------------*/
/* PINS: 
   - DB0 = PC0
   - DB1 = PC1
   - DB2 = PC2
   - DB3 = PC3
   - DB4 = PC4
   - DB5 = PC5
   - DB6 = PC6
   - DB7 = PC7
   - RD  = PC8
   - RW  = PC9
   - RS  = PC10
   - RST = PC11
   - CS  = PC12                                             */

#define PIN_CS               (   1 << 12)
#define PIN_RST              (   1 << 11)
#define PIN_RS               (   1 << 10)
#define PIN_RW               (   1 <<  9)
#define PIN_RD               (   1 <<  8)
#define PINS_CTRL            (0x1F <<  8)
#define PINS_DATA            (0xFF <<  0)
#define PINS_ALL             (PINS_CTRL | PINS_DATA)

/* Enable Clock for peripheral driving LCD pins                               */
#define LCD_CLOCK_EN         (RCC->APB2ENR |= (1 << 4)); // enable clock for GPIOC

/* pin CS  setting to 0 or 1                                                  */
#define LCD_CS(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_CS) | (x ? PIN_CS : 0);
/* pin RST setting to 0 or 1                                                   */
#define LCD_RST(x)            GPIOC->ODR = (GPIOC->ODR & ~PIN_RST) | (x ? PIN_RST : 0);
/* pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RS) | (x ? PIN_RS : 0);
/* pin RW setting to 0 or 1                                                   */
#define LCD_RW(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RW) | (x ? PIN_RW : 0);
/* pin RD setting to 0 or 1                                                   */
#define LCD_RD(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RD) | (x ? PIN_RD : 0);

/* Reading DATA pins                                                          */
#define LCD_DATA_IN           (((GPIOC->IDR & PINS_DATA) >> 0) & 0xFF)
/* Writing value to DATA pins                                                 */
#define LCD_DATA_OUT(x)       GPIOC->ODR = (GPIOC->ODR & ~PINS_DATA) | (x << 0);

/* Setting all pins to output mode                                            */
#define LCD_ALL_DIR_OUT       GPIOC->CRL = (GPIOC->CRL & 0x00000000) | 0x33333333; \
                              GPIOC->CRH = (GPIOC->CRH & 0xFFF00000) | 0x00033333;
 
/* Setting DATA pins to input mode                                            */
#define LCD_DATA_DIR_IN       GPIOC->CRL = (GPIOC->CRL & 0x00000000) | 0x44444444;

/* Setting DATA pins to output mode                                           */
#define LCD_DATA_DIR_OUT      GPIOC->CRL = (GPIOC->CRL & 0x00000000) | 0x33333333;

/*----------------------------------------------------------*\
 | SOFTWARE DEFINITIONS                                     |
\*----------------------------------------------------------*/
/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be 
   increased by factor 2^N by this constant                                   */
#define DELAY_2N     0

volatile U8 Font=0;

/*----------------------------------------------------------*\
 | Delay in while loop cycles                               |
 | cnt:    number of while cycles to delay                  |
\*----------------------------------------------------------*/
static void delay (int cnt) {
  cnt <<= DELAY_2N;

  while (cnt--);
  }
/*----------------------------------------------------------*\
 | LOW LEVEL OPERATE : BUS simulate                         |
\*----------------------------------------------------------*/
void LCD_Bus_Initial( void ) {
  LCD_CLOCK_EN                          /* Enable clock for peripheral        */

  /* Set all pins for LCD as outputs                                          */
  LCD_ALL_DIR_OUT

  LCD_RST(0);
  delay( 15000 );
  LCD_CS(1);
  LCD_RW(1);
  LCD_RD(1);
  LCD_RS(1);
  LCD_RST(1);
  }
void LCD_Bus_Write_Byte( unsigned char Data ) {
  LCD_DATA_OUT( Data );
  LCD_RW(0);
  delay( 1 );
  LCD_RW(1);
  }
void LCD_Bus_Write_Data( unsigned short Data ) {
  LCD_Bus_Write_Byte( Data>>8 );
  LCD_Bus_Write_Byte( Data );
  }
unsigned int LCD_Bus_Read_Byte( void ) {
  unsigned int BusData;

  LCD_DATA_DIR_IN;
  LCD_RD(0);
  BusData = LCD_DATA_IN;
  delay( 1 );
  LCD_RD(1);

  return BusData>>8;
  }
void LCD_Inst(unsigned int Cmd) {
  LCD_CS(0);
  LCD_RD(1);
  LCD_RS(0);
  LCD_Bus_Write_Byte( Cmd );
  LCD_CS(1);
  }
void LCD_Data(unsigned int Data) {
  LCD_CS(0);
  LCD_RD(1);
  LCD_RS(1);
  LCD_Bus_Write_Byte( Data );
  LCD_CS(1);
  }
void LCD_Reg_Set(unsigned int Cmd,unsigned int Data) {
  LCD_CS(0);
  LCD_RD(1);
  LCD_RS(0);
  LCD_Bus_Write_Byte( Cmd );
  LCD_RS(1);
  LCD_Bus_Write_Byte( Data );
  LCD_CS(1);
  }
/*----------------------------------------------------------*\
 | HIGHLEVEL OPERATION                                      |
\*----------------------------------------------------------*/

void LCD_GPIO_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void LCD_Init( void ) {
	LCD_Bus_Initial();

	LCD_Reg_Set(0x01,0x02);
	LCD_Reg_Set(0x02,0x86);
	LCD_Reg_Set(0x03,0x00);
	LCD_Reg_Set(0x05,0x08);
	LCD_Reg_Set(0x07,0x7F);
	LCD_Reg_Set(0x08,0x17);
	// SRAM control
	LCD_Reg_Set(0x09,0x00);
	LCD_Reg_Set(0x10,0x00);
	LCD_Reg_Set(0x11,0x7F);
	LCD_Reg_Set(0x12,0x9F);
	LCD_Reg_Set(0x14,0x00);
	LCD_Reg_Set(0x16,0x9F);
	LCD_Reg_Set(0x17,0x01);
	LCD_Reg_Set(0x18,0x00);
	LCD_Reg_Set(0x19,0x00);
	// Gamma voltage adjustalbe level
	LCD_Reg_Set(0x21,0x88);
	LCD_Reg_Set(0x22,0x33);
	LCD_Reg_Set(0x23,0xCC);
	LCD_Reg_Set(0x24,0xCC);
	LCD_Reg_Set(0x25,0xBB);
	LCD_Reg_Set(0x26,0xBB);
	LCD_Reg_Set(0x27,0x77);
	LCD_Reg_Set(0x28,0x77);
	LCD_Reg_Set(0x29,0x77);

	LCD_Reg_Set(0x06,0xC7);
	}
void LCD_SetArea( U8 x0, U8 y0, U8 x1, U8 y1 ) {
	// SRAM control
	LCD_Reg_Set(0x09,y0);
	LCD_Reg_Set(0x10,x0);
	LCD_Reg_Set(0x11,y1);
	LCD_Reg_Set(0x12,x1);
							
	LCD_Reg_Set(0x18,y0);
	LCD_Reg_Set(0x19,x0);
	}
void LCD_Rectangle( unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned int Data ) {
	int x,y;

	LCD_SetArea(x0,y0,x1,y1);

	LCD_CS(0);
	LCD_RD(1);

	LCD_RS(1);
	for(x=0;x<=x1-x0;x++)
		for(y=0;y<=y1-y0;y++) {
			LCD_Bus_Write_Byte( Data>>8 );
			LCD_Bus_Write_Byte( Data );
			}

	LCD_CS(1);
	}
void LCD_Clear_Screen( unsigned int Data ) {
	LCD_Rectangle(0,0,159,128, Data );
	}
void LCD_SetPixel(unsigned short x, unsigned short y, unsigned short color) {
	LCD_SetArea(x,y,x,y);

	LCD_CS(0);
	LCD_RD(1);
	LCD_RS(1);
	LCD_Bus_Write_Byte( color>>8 );
	LCD_Bus_Write_Byte( color );
	LCD_CS(1);
	}
#include "8X16.h"

void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int f, unsigned int b) {
	register unsigned int i,j;

	LCD_SetArea(x,y,x+8-1,y+16-1);

	LCD_CS(0);
	LCD_RD(1);
	LCD_RS(1);

	for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				LCD_Bus_Write_Byte(f>>8);
				LCD_Bus_Write_Byte(f);
				}
			else {
				LCD_Bus_Write_Byte(b>>8);
				LCD_Bus_Write_Byte(b);
				}
			m<<=1;
			}
		}

	LCD_CS(1);
	}
#include "8X8h.h"

void LCD_PutChar8x8(unsigned short x, unsigned short y, char c, unsigned int f, unsigned int b) {
	register unsigned int i,j;

	LCD_SetArea(x,y,x+8-1,y+8-1);

	LCD_CS(0);
	LCD_RD(1);
	LCD_RS(1);

	for(i=0; i<8;i++) {
		unsigned char m=Font8x8[c][i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				LCD_Bus_Write_Byte(f>>8);
				LCD_Bus_Write_Byte(f);
				}
			else {
				LCD_Bus_Write_Byte(b>>8);
				LCD_Bus_Write_Byte(b);
				}
			m<<=1;
			}
		}

	LCD_CS(1);
	}

void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int f, unsigned int b) {
	if( Font )
		LCD_PutChar8x8( x, y, c, f, b );
	else
		LCD_PutChar8x16( x, y, c, f, b );
	}

void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int f, unsigned int b) {
	register unsigned char l=0;
	while(*s) {
		LCD_PutChar(x+l*8,y,*s,f,b);
		s++;l++;
		}
	}

/*----------------------------------------------------------*\
 | END OF FILE                                              |
\*----------------------------------------------------------*/
