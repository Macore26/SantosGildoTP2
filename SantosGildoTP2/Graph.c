#include <stdio.h>
#include "Graph.h"
#include <go32.h>
#include <sys/farptr.h>
#include <pc.h>
#include <sys/nearptr.h>
#include <pc.h>
#include <dpmi.h>

char *enter_graphics(int mode, __dpmi_meminfo map)
{

	__dpmi_regs regs;
	;					/*__dpmi_regs � uma estrutura que representa os registos do CPU */
	regs.x.ax = 0x4F02; /* registo AX do CPU com valor 0x4F02 */

	if (mode == 101)
		regs.x.bx = 0x4101;

	else if (mode == 103)
		regs.x.bx = 0x4103;

	else if (mode == 105)
		regs.x.bx = 0x4105;

	else
		regs.x.bx = 0x4107;

	__dpmi_int(0x10, &regs); /* gera interrup��o de software 0x10, activando o modo gr�fico */

	__djgpp_nearptr_enable();			   /* permite acesso � mem�ria f�sica usando apontadores */
	map.address = 0xC0000000;			   /* endere�o f�sico da mem�ria v�deo, usar o valor correcto */
	map.size = HRES * VRES;				   /* tamanho do bloco de mem�ria, usar apenas o necess�rio */
	__dpmi_physical_address_mapping(&map); /*Tamanho da tela escolhida HResxVRes*/

	return (char *)(map.address + __djgpp_conventional_base);
}

void leave_graphics(__dpmi_meminfo map)
{
	__dpmi_regs regs;
	;											/*__dpmi_regs é uma estrutura que representa os registos do CPU */
	__dpmi_free_physical_address_mapping(&map); /* liberta mapeamento */
	__djgpp_nearptr_disable();
	regs.x.ax = 0x0003;		 /* registo AX do CPU com valor 0x03 */
	__dpmi_int(0x10, &regs); /* gera interrupção software 0x10, entrando no modo texto */
}

void set_pixel(int x, int y, int color, char *base)
{
	int i;
	i = y * HRES + x;
	*(base + i) = color;
}

int get_pixel(int x, int y, char *base)
{

	int i;
	i = y * HRES + x;
	i = *(base + i);

	return i;
}

void clear_screen(int color, char *base)
{
	int i;
	for (i = 0; i < VRES * HRES; i++)
	{
		*(base + i) = color;
	}
}

void draw_line(int xi, int yi, int xf, int yf, int color, char *base)
{

	int x, y, aux_x = 0, aux_y = 0, i;
	float porp_cresc;
	if (xi > xf)
	{
		aux_x = xi;
		xi = xf;
		xf = aux_x;
		aux_x = -1;
	}
	if (yi > yf)
	{
		aux_y = yi;
		yi = yf;
		yf = aux_y;
		aux_y = -1;
	}
	x = xf - xi;
	y = yf - yi;
	if (y > x)
	{
		porp_cresc = (float)x / (float)y;
		if ((aux_y == 0 && aux_x == 0) || (aux_y == -1 && aux_x == -1))
		{
			for (i = 0; i < y; i++)
			{
				aux_x = porp_cresc * i + xi;
				aux_y = yi + i;
				set_pixel(aux_x, aux_y, color, base);
			}
		}
		else
		{
			for (i = 0; i < y; i++)
			{
				aux_x = porp_cresc * i + xi;
				aux_y = yf - i;
				set_pixel(aux_x, aux_y, color, base);
			}
		}
	}
	else
	{
		porp_cresc = (float)y / (float)x;
		if ((aux_y == 0 && aux_x == 0) || (aux_y == -1 && aux_x == -1))
		{
			for (i = 0; i < x; i++)
			{
				aux_y = porp_cresc * i + yi;
				aux_x = xi + i;
				set_pixel(aux_x, aux_y, color, base);
			}
		}
		else
		{
			for (i = 0; i < x; i++){
				aux_y = yf - porp_cresc * i;
				aux_x = xi + i;
				set_pixel(aux_x, aux_y, color, base);
			}
		}
	}
}

void draw_rect(int xi, int yi, int widith, int height, int color, char *base)
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		draw_line(xi, yi + i, xi + widith, yi + i, color, base);
	}
}


void BandeiraDeNamibia(char *base){

	//===============tornar a area Branca================
	int r, i, y = 390;
	
	draw_rect(10, 50, 600, 360, 15, base);

	//===============tornar a area Azul================
	for (i = 525; i > 10; i--)
	{

		//	draw_line(10, i+2, 10, i+8, 2, base);
		draw_line(10, 350, i, 48, 1, base);
	}

	//===============tornar a area vermelha================
	for (i = 550; i < 585; i++)
	{
		if (y > 370){

			y--;
		}
		draw_line(10, 370, i, 50, 4, base);
		draw_line(10, 390, i, 50, 4, base);
		draw_line(10, y, 558, 50, 4, base);
	}
	//===============tornar a area vermelha================
		for(i=580; i < 610 ; i++){
		int c, j=410;

			if (j > 390){
				j--;
			}
			for( r=390; r < 410; r++)
			draw_line(10, r, i , 50, 4, base);
			draw_line(10, 410, i , 50, 4, base);

		}

	//===============tornar a area vermelha================
	for(i = 10; i <= 50; i++){
		
		int j=1;
		for(j=100; j >49; j--){
			
			draw_line(60-i, 408, 610 , j, 4, base);
			draw_line(90-i, 408, 610 , j, 4, base);

		}
			draw_line(i, 409, 605 , 100, 4, base);

			//===============tornar a area verde================
			int d;
			for(d=120; d < 415; d++){
				 draw_line(115, 409, 610 , d, 2, base);
			}

			
	
	}


	//fill_between(10, 50, 11, 200, 10, 200, 170, 50, 5, base);
	// int i,color;
	//===============tornar a area branca================
	// for(i=0;i<360;i++){
	// 	draw_line(50, i, 600, i,15,base);
	// }

	// for(i=0;i<360;i++){
	// 	draw_line(50, i, 70, i,15,base);
	// }

	// // // 	// ===============pinta as baras horizontais==========
	// 	for(i=0;i<360;i++){
	// 		if(i<120) color=4;
	// 		if(i>120 && i<140) color=15;
	// 		if(i>140 && i<220) color=2;
	// 		if(i>220 && i<240) color=15;
	// 		if(i>240 && i<360) color=1;

	// 		//draw_line(1, i, 600, i,color,base);

	// 	}

	// //=================pinta preto no meio========================
	// for(i=70;i<290;i++){
	// 	draw_line(0, i, 150,i,0,base);

	// }
	// //======================diagonais amarelos======================
	// for(i=50;i<70;i++){
	// 	draw_line(0, i, 150,(i+140),14,base);
	// }
	// for(i=309;i>289;i--){
	// 	draw_line(0, i, 150,(i-140),14,base);
	// }

	// //=================================diagonal superior branca=============
	// for(i=0;i<25;i++){
	// 	draw_line(70, i, 200,(i+120),15,base);

	// }
	// //===========================superior verde=====================
	// for(i=0;i<80;i++){
	// 	draw_line(50, i, 200,(i+140),2,base);
	// }

	// for(i=0;i<50;i++){
	// 	draw_line(0, i, 150,(i+140),2,base);
	// }

	// //=============================inferior branca===================
	// for(i=359;i>334;i--){
	// 	draw_line(70, i, 200,(i-120),15,base);

	// }
	// for(i=359;i>279;i--){
	// 	draw_line(50, i, 200,(i-140),2,base);
	// }

	// for(i=359;i>309;i--){
	// 	draw_line(0, i, 150,(i-140),2,base);
	// }
}
