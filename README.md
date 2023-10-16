
#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#include <dpmi.h>
#include <go32.h>
#include <sys/farptr.h> 
#include <pc.h>
#include <sys/nearptr.h>
#include "Utypes.h"


int HRES;
int VRES;
__dpmi_meminfo map;
char *memoria;

void verifica_cordenadas(int *x ,int *y);
void escrever_pixel();
void entrar_modo_grafico(int modo);
int verifica_modo(int modo);
void menu_modo();
void verifica_cor(int *color);
void limpar_tela();
void desenhaBandeira();
void desenha_linha();
int menu();


int main()
{

  
    do{
		  int escolha = menu();
		
		switch(escolha){
			case 1:  escrever_pixel(); break;//
			case 2:  desenha_linha(); break;
			case 3:  limpar_tela();break;
			case 4:  desenhaBandeira();break;
            case 0: {
                    char sair[2];

                     system("cls");
                    printf("\ntem certeza que quer sair? [S/N]: ");
                    scanf("%s", sair);

                    if(sair[0] == 'S' || sair[0] == 's') {
                        exit(0);
                    }
            } break;
			default: printf("Opcao invalida");
            exit(0);
		}
    }while(true);

}

int menu(){
    
    int select;

    system("cls");
    printf("    Seja bem vindo   \n\n");
    printf("    1: para escrever pixel  \n");
    printf("    2: para escrever lina   \n");
    printf("    3: para limpar TELA\n");
    printf("    4: para desenhar bandeira   \n");
    printf("    0: para sair do sistema\n");

    printf("Selecione uma opcao: "); 
    scanf("%d", &select);

    if( select <1 && select > 5 ) {
        system("cls");
        printf("\nA opção  é inválida.\n\n");
        select = menu();
    }

    return select;

}

     /*DESENHAR BANDEIRA*/
	void desenhaBandeira()
	{

		int modo;
			
		printf("\n\nESTA FUNCAO DESENHA BANDEIRA DE Namibia\n\n");
		menu_modo();
		
		modo=verifica_modo(modo);
		
		entrar_modo_grafico(modo);

		BandeiraDeNamibia(memoria);
		scanf("%d", &modo);
		
		leave_graphics(map);
        getchar();		
	}
//---------------------------------------------------------------------------------------------------------------------------------
void escrever_pixel()
{
    int x, y,color,modo;
    system("cls");
    printf("\nESTA FUNCAO ESCREVE UM pixel NO MODO GrAFICO \n\n");
    
    modo=verifica_modo(modo);
    
    printf("introduza a cor que deseja que o pixel tenha: ");
    scanf("%d",&color);
	verifica_cor(&color);
    
    printf("introduza x a cordenada que deseja desenhar:  ");
    scanf("%d", &x);
    
    printf("introduza y a cordenada que deseja desenhar:  ");
    scanf("%d", &y);

    verifica_cordenadas(&x,&y);
	

    entrar_modo_grafico(modo);
    set_pixel(x,y,color,memoria);
	scanf("%d", &y);
	leave_graphics(map);
    getchar();
}
//---------------------------------------------------------------------------------------------------------------------------------
void entrar_modo_grafico(int modo)
{

    memoria=enter_graphics(modo,map);
}
//---------------------------------------------------------------------------------------------------------------------------------

void limpar_tela()
{

    int color,modo;

    system("cls");
    printf("\nESTA FUNCAO LIMPA A TELA COM UMA COR \n\n");
    modo=verifica_modo(modo);
    
    printf("introduza a cor que deseja que o pixel tenha: ");
    scanf("%d",&color);
    
    verifica_cor(&color);

    entrar_modo_grafico(modo);
    clear_screen(color,memoria);
	scanf("%d", &modo);
	leave_graphics(map);
    getchar();	
}
//---------------------------------------------------------------------------------------------------------------------------------

int verifica_modo(int modo)
{
    
    printf("insira o modo pelo qual deseja entrar: ");
    scanf("%d",&modo);
    
    switch(modo){
        case 101:  HRES=640; VRES=480; break;
        case 103:  HRES=800; VRES=600; break;
        case 105:  HRES=1024; VRES=786; break;
        case 107:  HRES=1280; VRES=1024;break;
        default: system("cls");menu_modo();return verifica_modo(modo); 
    }
    return modo;
    getchar();	
}

//---------------------------------------------------------------------------------------------------------------------------------
void menu_modo()
{
    
   
    printf("    101: para resulucao 640x480\n");
    printf("    103: para resulucao 800x600\n");
    printf("    105: para resulucao 1024x786\n");
    printf("    107: para resulucao 1280x1024\n");
}
//---------------------------------------------------------------------------------------------------------------------------------

void verifica_cor(int *color)
{

    while(*color<1 || *color>256){
        system("cls");
        printf("  A COR INTRODUZIDA NAO EXISTE: \n");
        printf("escolha uma no intervalo de 1-256:      ");
        scanf("%d",color);
    }
}

 void desenha_linha()
 {
	  
	int xi, yi,xf,yf,color,modo;
    system("cls");
    printf("\nESTA FUNCAO ESCREVE UM pixel NO MODO GrAFICO \n\n");

   
	menu_modo();
	modo=verifica_modo(modo);
	entrar_modo_grafico(modo);
  
	
    
    
    printf("introduza a cor que deseja que o pixel tenha: 1-256");
    scanf("%d",&color);
	verifica_cor(&color);
    
    printf("introduza xi a cordenada que deseja desenhar:  ");
    scanf("%d", &xi);
	

    printf("introduza yi a cordenada que deseja desenhar:  ");
    scanf("%d", &yi);
	
    verifica_cordenadas(&xi,&yi);

	printf("introduza xf a cordenada que deseja desenhar:  ");
    scanf("%d", &xf);
	
    printf("introduza yf a cordenada que deseja desenhar:  ");
    scanf("%d", &yf);

	verifica_cordenadas(&xf,&yf);
	
	scanf("%d", &modo);

	draw_line(xi, yi, xf, yf, color, memoria);
	scanf("%d", &yi);
	leave_graphics(map);
 }

void verifica_cordenadas(int *x ,int *y)
{

    while(*x>=HRES || *x<0){
        system("cls");
        printf("  A CORDENADA X ESTA FORA DOS LIMITES DO MODO ESCOLHIDO \n");
        printf("   escolha uma no intervalo de 0 - %d :      ",HRES-1);
        scanf("%d", x);
    }

    while(*y>=VRES || *y<0){
        system("cls");
        printf("  A CORDENADA Y ESTA FORA DOS LIMITES DO MODO ESCOLHIDO \n");
        printf("   escolha uma no intervalo de 0 - %d :      ",VRES-1);
        scanf("%d", y);
    }

}
# SantosGildoTP2
TP2
