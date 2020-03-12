#include <stdio.h>
#include <stdlib.h>

int imprimirMenu();//Donde se elige el apartado a probar.

void borrarConsola();//Despeja la consola.

void aperturaFichero(char fichero[MaxL][MaxC],int opcion);//Saca el AFDT del .txt y lo mete en un array struct.

void vaciar(char temp[]);//Rellena un vector de nulos

void asignarMemoriaTransTraduDest(int n,int i);//Asignar el tamaño a los diferentes vectores dinamicos del struct AFDT, tras saber el numero de transiciones.

void rellenarVectores(char aux,char temp[],int i,int n);//rellena los vectores dinamicos con la informacion pertinente

enum Boolean//Los boleanos no existen en C tienes que crearlos.
{
	FALSE, TRUE
};

typedef struct
{
    char *traduccion;//cadena de caracteres con la traduccion
}traducciones;

typedef struct
{
     enum Boolean esFinal;
     int nombreEstado;
     char *transiciones;//Guarda las transiciones que salen del estado
     traducciones *cad;//Guarda las traducciones respectivas a las transiciones
     int *destinos;//Guarda el destino de cada transicion respectivamente
}AFDT;

AFDT *traductor;//Vector dinamico de tipo AFDT cada posicion es un estado


//###################################################################################################################################################
//################################################################################# MAIN ############################################################
//###################################################################################################################################################
int main()
{
    char fichero[MaxL][MaxC];//La matriz fichero es donde se guardaran los automatasb.txt
    borrarConsola();

    aperturaFichero(fichero,imprimirMenu());
    return 0;
}

//##################################################################################################################################################
//################################################################################ FUNCIONES OBLIGATORIAS ##########################################
//##################################################################################################################################################

int imprimirMenu()//######################### IMPRIMIR MENU #################################################################
{
 int opcion;

 printf("\tMENU PRINCIPAL\n\n");
 printf("\t(1) Apartado 'A'\n\n");
 printf("\t(2) Apartado 'B'\n\n");
 printf("\t(3) Apartado 'C'\n\n");
 printf("\t(0) Salir\n\n");//Por si el usuario queria finalizar pero se equivoca y elige volver al menu principal.
 printf("\nElija el apartado que quiera probar mediante '1', '2', '3', o '0' para salir: ");
 scanf("%d",&opcion);
 while(opcion>3 || opcion<0)
  {
   printf("\nHa introducido una opcion que no esta en el menu, porfavor introduzca una viable: ");
   fflush( stdin );
   scanf("%d",&opcion);
  }
return opcion;
}

void borrarConsola()//#### BORRAR CONSOLA #######################################################################################
{
  system("cls");
}

void aperturaFichero(char fichero[MaxL][MaxC],int opcion)//################## APERTURA DE FICHERO ###############################
{
  int i,j,n,cont=0;//Cuenta el numero de lineas(estados) del .txt
  char aux,temp[50];
  FILE *F;
  switch( opcion )
   {
    case 1: F = fopen ("Apartado1.txt","r");
          break;

    case 2: F = fopen ("Apartado2.txt","r");
          break;

    case 3: F = fopen ("Apartado.txt","r");
          break;

    case 0: exit(0);//Comando para terminar la ejecucion entera del programa
          break;
   }
 if (F==NULL)
  {
    printf("\n\t\tERROR:el fichero no se ha abierto correctamente\n");
    exit (EXIT_FAILURE);
  }
 //el fichero se ha abierto correctamente
 while(!feof(F))
  {
   fgets(temp,50,F);//Lee una linea hasta encontrar'\n' o llegar a 50 en este caso y deja el puntero al inicio de la siguiente
   cont++;//Cada aumento es una linea/estado más.
   //Cada ciclo del while sobreescribe temp añadiendo al final un nulo.
  }
 rewind(F);//Devuelve el puntero F al principio del fichero

 //Como ya conocemos el numero de estados del AFDT,asignamos al vector traductor el tamaño justo.
 traductor=(AFDT*)malloc(cont*sizeof(AFDT));
 if(traductor==NULL)//Comprobamos que se reservo la memoria correctamente
  {
    printf("No se ha podido reservar la memoria.\n");
    exit (1);
  }
  for(i=0; !feof(F); i++)
   {
      vaciar(temp);//Primeros debemos vaciar temp.
      traductor[i].nombreEstado=i;
      aux=fgetc(F);//Leemos el primer caracter de una linea y el cursor se queda tras ella, en este caso nos indica si esta linea/estado es final o no.
      if(aux=='n') traductor[i].esFinal=FALSE;
      else if('f') traductor[i].esFinal=TRUE;
      aux=fgetc(F);//Leemos el segundo caracter de una linea y el cursor se queda tras ella, en este caso nos indica si esta linea/estado tiene transiciones o no.
      if(aux=='-')//Esta linea/estado si tiene transiciones.
      {
         aux=fgetc(F);//Leemos el tercer caracter de una linea y el cursor se queda tras ella, en este caso nos indica cuantas transiciones tiene esta linea estado.
         for(j=0;aux>='0'&&aux<='9';j++)//Ya que pueden existir mas de 9 transiciones
          {
             temp[j]=aux;
             aux=fgetc(F);//Lee siguiente caracter
          }
          n=atoi(temp);
          asignarMemoriaTransTraduDest(n,i);//Como ya sabemos el numero de transiciones de esta linea/estado (mediante atoi que pasa '123'char a 123 int ya podemos asignar el tamaño a los diferentes vectores dinamicos.
          //Tras salir de while tenemos en aux va el simbolo de la primera transicion.
          vaciar(temp);//reseteamos temp.
          fgets(temp,50,F);//Lee toda la linea y deja el cursor al inicio de la siguiente o EOF
          rellenarVectores(aux,temp,i,n);




      }
      //else if(aux='*')
   }
}

void vaciar(char c[])
{
    int i;
    for(i=0;i<0;i++)
     {
        c[i]='\0';
     }
}

void asignarMemoriaTransTraduDest(int n,int i)
{
    traductor[i].transiciones = (char*)malloc(n*sizeof(char));
    if(traductor[i].transiciones==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
    traductor[i].cad = (traducciones*)malloc(n*sizeof(traducciones));
    if(traductor[i].cad==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
    traductor[i].destinos = (int*)malloc(n*sizeof(int));
    if(traductor[i].destinos==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria.\n");
        exit (1);
     }
}

void rellenarVectores(char aux,char temp[],int i,int n)
{
 int j,k,m,t=0,num;
 char numTraduccion[3];//Para guardar el numero de simbolos de una traduccion para depues transformarlo a int.
 for(j=0;j<n;j++)//for de numero de transiciones del estado 'i'
  {
     if(j==0)//Caso particular pues temp empieza por el primer '/' y no por el simbolo de la 1º transicion
      {
        traductor[i].transiciones[j]=aux;//metemos el primer simbolo de la primera transicion
        for(k=1;temp[k]!=','&&'\0';k++)//for para recorrer temp que empieza con '/'
         {
             if(temp[k-1]=='/')
              {
                if(temp[k]=='!') traductor[i].cad[j].traduccion = (char*)malloc(0*sizeof(char));//Asignamos cero memoria ya que no hay traduccion para esta transicion
                else if(temp[k]!='!')//La transicion si tiene traduccion, temp[k] tiene el primer simbolo del numero de simbolos de la traduccion
                 {
                    vaciar(numTraduccion);
                    for(m=k;temp[m]>='0'&&temp[m]<='9';m++)//Ya que pueden existir mas de 9 simbolos de traduccion
                     {
                       numTraduccion[t]=temp[m];
                       t++;
                     }
                    t=0;
                    num=atoi(numTraduccion);
                    traductor[i].cad[j].traduccion = (char*)malloc(num*sizeof(char));//Asignamos memoria ya que sabemos el numero de simbolos de traduccion para esta transicion
                    for(m=k;temp[m]!=':',m++)
                     {
                         if(temp[m+1]==':')
                     }
                 }

              }
         }
      }
     else
      {
        if(temp[j-1]=='/')
         {
            //if(temp[j]=='!')
         }
      }
  }
}

