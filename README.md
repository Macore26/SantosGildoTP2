
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
Aqui está uma breve descrição do que cada função faz:

verifica_cordenadas(int *x, int *y): Esta função verifica se as coordenadas x e y estão dentro dos limites do modo gráfico escolhido (definido anteriormente em HRES e VRES). Se estiverem fora dos limites, solicita que o usuário insira novas coordenadas até que estejam dentro dos limites.

escrever_pixel(): Esta função permite ao usuário especificar uma cor, coordenadas x e y, entra no modo gráfico selecionado e desenha um pixel na tela com a cor especificada nas coordenadas fornecidas.

entrar_modo_grafico(int modo): Entra no modo gráfico especificado e aloca memória para desenhar gráficos.

limpar_tela(): Permite ao usuário escolher uma cor, entra no modo gráfico selecionado e preenche toda a tela com a cor escolhida.

verifica_modo(int modo): Solicita que o usuário insira o modo gráfico desejado (101, 103, 105 ou 107) e verifica se a entrada está dentro das opções válidas. Define a resolução do modo gráfico com base na escolha.

menu_modo(): Apresenta as opções de modos gráficos disponíveis para o usuário.

verifica_cor(int *color): Verifica se a cor fornecida pelo usuário está dentro do intervalo válido (1-256) e solicita que o usuário insira novamente, se não estiver.

desenha_linha(): Permite ao usuário especificar uma cor, coordenadas de início (xi e yi) e coordenadas de fim (xf e yf) para desenhar uma linha no modo gráfico selecionado.

menu(): Apresenta um menu para o usuário escolher entre várias opções, como escrever pixel, desenhar uma linha, limpar a tela, desenhar a bandeira da Namíbia ou sair do programa. Verifica se a escolha é válida (1-4) e retorna a opção selecionada.

main(): A função principal que executa um loop onde o usuário pode escolher várias opções de ações gráficas. O loop é repetido até que o usuário escolha a opção para sair (0).
