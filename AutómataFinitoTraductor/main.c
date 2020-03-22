#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

int imprimirMenu();//Donde se elige el apartado a probar.

void borrarConsola();//Despeja la consola.

void aperturaFichero(int opcion);//Saca el AFDT del .txt y lo mete en un array struct.

void vaciar(char temp[],int tam);//Rellena un vector de nulos

void asignarMemoriaTransTraduDest(int n,int i);//Asignar el tamaño a los diferentes vectores dinamicos del struct AFDT, tras saber el numero de transiciones.

void rellenarVectores(char temp[],int i,int n);//rellena los vectores dinamicos con la informacion pertinente

void meterCharAlPrincpio(char aux,char temp[]);//mete un char al princpio de temp sin borrar nada

int tieneTransicion(char c,int estadoActual);//Busca para un simbolo si hay transicion en un estado

enum Boolean//Los boleanos no existen en C tienes que crearlos.
{
	FALSE, TRUE
};

typedef struct
{
    int tamTraduccion;//Cantidad de simbolos de la traduccion
    char *traduccion;//cadena de caracteres con la traduccion
}traducciones;

typedef struct
{
     int numeroEstadosAFDT;//Nº de estados del automata elegido.
     int numeroTransiciones;//Nº de transiciones de un estado=traducciones=destinos.
     enum Boolean esFinal;//TRUE es final, FALSE no es final.
     int nombreEstado;//Identificador del estado.
     char *transiciones;//Guarda las transiciones que salen del estado.
     traducciones *cad;//Guarda las traducciones respectivas a las transiciones.
     int *destinos;//Guarda el destino de cada transicion respectivamente.
}AFDT;

AFDT *traductor;//Vector dinamico de tipo AFDT cada posicion es un estado.


//###################################################################################################################################################
//################################################################################# MAIN ############################################################
//###################################################################################################################################################
int main()
{
    int i,j,m,respuesta=0,opcion,n,estadoActual,posT,posS,tamS;
    char *palabra,*salida;
    borrarConsola();
    do{//Ir cambiando de AFDT
        borrarConsola();
        opcion=imprimirMenu();
        aperturaFichero(opcion);
        do{//Mismo AFDT todo el rato
            borrarConsola();
            estadoActual=0;
            posS=0;
            tamS=0;
            printf("\n\t\tEL AFDT %d TIENE %d ESTADOS\n",opcion,traductor[0].numeroEstadosAFDT);
            printf("\nDESGLOSE DE ESTADOS:\n");
            for(i=0;i<traductor[0].numeroEstadosAFDT;i++)
             {
                printf("\t- Estado: %d ",i);
                if(traductor[i].esFinal==TRUE) printf("(ES FINAL)\n");
                else if (traductor[i].esFinal==FALSE) printf("(NO FINAL)\n");
                if(traductor[i].numeroTransiciones==0) printf("\t\t- NO tiene transiciones");
                else
                 {
                   for(j=0;j<traductor[i].numeroTransiciones;j++)
                    {
                      printf("\t\t- Transicion %d\n",j);
                      printf("\t\t\t- Mediante el simbolo '%c'\n",traductor[i].transiciones[j]);
                      printf("\t\t\t- Estado destino '%d'\n",traductor[i].destinos[j]);
                      printf("\t\t\t- Traduccion %c --> ",traductor[i].transiciones[j]);
                      if(traductor[i].cad[j].tamTraduccion!=0)
                       {
                         for(m=0;m<traductor[i].cad[j].tamTraduccion;m++)
                          {
                             printf("%c",traductor[i].cad[j].traduccion[m]);
                          }
                         printf("\n");
                       }
                      else printf("palabra vacia (Epsilon)\n");
                    }
                 }
             }
            printf("\n\nIntroduzca el numero de simbolos que va introducir (0 seria Epsilon):");
            scanf("%d", &n);
            palabra = (char*)malloc(n*sizeof(char));
            if(palabra==NULL)//Comprobamos que se reservo la memoria correctamente
             {
               printf("No se ha podido reservar la memoria para su palabra vuelva a intentarlo.\n");
               exit (1);
             }
            vaciar(palabra,n);
            if(n!=0)
             {
               printf("Introduce una palabra reconocida por el lenguaje L del apartado %d del enunciado con %d simbolos.\n",opcion,n);
               printf("NOTA: Si introduce menos simbolos de los guardados se consideraran Epsilon los restantes\n");
               scanf("%s", palabra);
             }
            if(n==0)
             {
              if(traductor[0].esFinal==TRUE) printf("TRADUCCION: Palabra vacia (Epsilon)\n");
              else printf("NO HAY TRADUCCION: La palabra vacia (Epsilon) no pertenece a L\n");
             }
            else
             {
              for(i=0;i<n;i++)//recorremos la palabra
               {
                 posT=tieneTransicion(palabra[i],estadoActual);
                 if(posT>=0)//Hay transiccion con el simbolo actual.
                   {

                     if(i==0)
                      {
                         salida = (char*)malloc(traductor[estadoActual].cad[posT].tamTraduccion*sizeof(char));//asignamos nueva memoria a la traduccion
                      }
                     else if (traductor[estadoActual].cad[posT].tamTraduccion!=0)
                      {
                         salida = (char*)realloc(salida,traductor[estadoActual].cad[posT].tamTraduccion*sizeof(char));
                      }
                     tamS=tamS+traductor[estadoActual].cad[posT].tamTraduccion;
                     if(palabra==NULL)//Comprobamos que se reservo la memoria correctamente
                      {
                        printf("No se ha podido reservar la memoria para la traduccion, vuelva a intentarlo.\n");
                        exit (1);
                      }
                     for(j=0;j<traductor[estadoActual].cad[posT].tamTraduccion;j++)//actualizamos la traduccion
                      {
                         salida[posS]=traductor[estadoActual].cad[posT].traduccion[j];
                         posS++;
                      }
                     estadoActual=traductor[estadoActual].destinos[posT];
                   }
                 else
                   {
                     if(palabra[i]=='\0')//Se han introducido menos simbolos a los dichos
                      {
                         i=n-1;
                      }
                     else//un simbolo no pertenece a L
                      {
                         n=-1;
                      }
                   }
               }
              if(i==n&&traductor[estadoActual].esFinal==TRUE)
               {
                 printf("TRADUCCION: ");
                 if(tamS==0) printf("Palabra vacia (Epsilon)\n\n");
                 else
                  {
                    for(m=0;m<tamS;m++)
                     {
                       printf("%c",salida[m]);
                     }
                    printf("\n");
                  }
               }
              else
               {
                 printf("No existe traduccion, la palabra dada no pertenece a L\n");
               }
             }
            free(palabra);//liberamos memoria
            free(salida);//liberamos memoria
            printf("%cQuiere otra seguir probando el mismo AFDT(1), o cambiar de AFDT(2) o finalizar(0)?: ",168);//168==¿, pero si pongo '¿' me imprime otro signo
            scanf("%d",&respuesta);
            while(respuesta>2 || respuesta<0)
             {
               printf("\nEsa opcion no existe, porfavor introduzca 1 o 2 o 0 si quiere probar el mismo AFDT, cambiar de AFDT\no finalizar, respectivamente: ");
               fflush( stdin );
               scanf("%d",&respuesta);
             }
          }while(respuesta==1);
        free(traductor);//liberamos memoria para ya que se ha elegido un automata diferente
      }while(respuesta==2);
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

void aperturaFichero(int opcion)//################## APERTURA DE FICHERO ###############################
{
  int i,j,n,cont=0;//Cuenta el numero de lineas(estados) del .txt
  char aux,temp[MAX];
  FILE *F;
  switch( opcion )
   {
    case 1: F = fopen ("Apartado1.txt","r");
          break;

    case 2: F = fopen ("Apartado2.txt","r");
          break;

    case 3: F = fopen ("Apartado3.txt","r");
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
 traductor[0].numeroEstadosAFDT=cont;//Guardamos el numero de estados de AFDT pra luego poder recorrerlo.
 for(i=0; !feof(F); i++)
   {
      vaciar(temp,MAX);//Primeros debemos vaciar temp.
      traductor[i].nombreEstado=i;
      aux=fgetc(F);//Leemos el primer caracter de una linea y el cursor se queda tras ella, en este caso nos indica si esta linea/estado es final o no.
      if(aux=='n') traductor[i].esFinal=FALSE;
      else if(aux=='f') traductor[i].esFinal=TRUE;
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
          //Tras salir del for tenemos en aux el simbolo de la primera transicion, de esta linea/estado.
          vaciar(temp,MAX);//reseteamos temp.
          fgets(temp,MAX,F);//Lee toda la linea y deja el cursor al inicio de la siguiente o EOF
          //fscanf(F,"%s",temp);
          meterCharAlPrincpio(aux,temp);
          rellenarVectores(temp,i,n);
       }
      else if(aux=='*')//Esta linea estado no tiene transiciones
       {
            asignarMemoriaTransTraduDest(0,i);
            aux=fgetc(F);//Para leer EOF.
       }
   }
 fclose(F);
}

void vaciar(char c[],int tam)
{
    int i;
    for(i=0;i<tam;i++)
     {
        c[i]='\0';
     }
}

void asignarMemoriaTransTraduDest(int n,int i)
{
    traductor[i].transiciones = (char*)malloc(n*sizeof(char));
    if(traductor[i].transiciones==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria para las transiciones del estado %d.\n",traductor[i].nombreEstado);
        exit (1);
     }
    traductor[i].cad = (traducciones*)malloc(n*sizeof(traducciones));
    if(traductor[i].cad==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria para las traducciones del estado %d.\n",traductor[i].nombreEstado);
        exit (1);
     }
    traductor[i].destinos = (int*)malloc(n*sizeof(int));
    if(traductor[i].destinos==NULL)//Comprobamos que se reservo la memoria correctamente
     {
        printf("No se ha podido reservar la memoria para los destinos del estado %d.\n",traductor[i].nombreEstado);
        exit (1);
     }
    traductor[i].numeroTransiciones=n;//Guardamos el numero de transiciones que sera = traducciones e = destinos.
}

void rellenarVectores(char temp[],int i,int n)
{
 int j,k=0,m,num,t=0,h,r;
 char numTraduccion[3];//Para guardar el numero de simbolos de una traduccion para depues transformarlo a int, y lo mismo para el caacter destino.
 for(j=0;j<n;j++)//for de numero de transiciones del estado 'i'
  {
        traductor[i].transiciones[j]=temp[k];//metemos el simbolo de la transicion
        for(k=k+1;temp[k]!=','&&temp[k]!='\0';k++)//for para recorrer una de las 'n' transiciones de temp que empieza con la '/' de transicion
         {
            if(temp[k]=='!')
             {
                traductor[i].cad[j].traduccion = (char*)malloc(0*sizeof(char));//Asignamos cero memoria ya que no hay traduccion para esta transicion
                if(traductor[i].cad[j].traduccion==NULL)//Comprobamos que se reservo la memoria correctamente
                 {
                    printf("No se ha podido reservar la memoria, para la traduccion de la transicion %d del estado %d.\n",j,traductor[i].nombreEstado);
                    exit (1);
                 }
                traductor[i].cad[j].tamTraduccion=0;
             }
            else if(temp[k]==':')//Ahora temp[k], esta en ':', tenemos que leer el destino que esta en k+1 y guardarlo en el struct, actualizamos k.
             {
                vaciar(numTraduccion,3);
                t=0;
                for(k=k+1;temp[k]!=','&&temp[k]!='\0';k++)
                 {
                     numTraduccion[t]=temp[k];
                     t++;
                 }
                t=0;
                num=atoi(numTraduccion);
                traductor[i].destinos[j]=num;
                //Ahora temp[k] esta en la posicion de ',' o '\0'; restamos 1 a 'k' asi ya que tras llegar a '}' el contador del for hara 'k++', y ya no se cumplira la condicion y saldra del for.
                k--;
             }
            else if(temp[k]!='!'&&temp[k]!='/')//La transicion si tiene traduccion, temp[k] tiene el primer simbolo del numero de simbolos de la traduccion
             {
                vaciar(numTraduccion,3);
                for(m=k;temp[m]>='0'&&temp[m]<='9';m++)//Ya que pueden existir mas de 9 simbolos de traduccion
                 {
                   numTraduccion[t]=temp[m];
                   t++;
                 }
                t=0;
                num=atoi(numTraduccion);
                traductor[i].cad[j].traduccion = (char*)malloc(num*sizeof(char));//Asignamos memoria ya que sabemos el numero de simbolos de traduccion para esta transicion
                if(traductor[i].cad[j].traduccion==NULL)//Comprobamos que se reservo la memoria correctamente
                 {
                    printf("No se ha podido reservar la memoria, para la traduccion de la transicion %d del estado %d.\n",j,traductor[i].nombreEstado);
                    exit (1);
                 }
                traductor[i].cad[j].tamTraduccion=num;//Guardamos el numero de simbolos de la traduccion de la transicion 'j', para luego poder recorrerla.
                //Ahora temp[m] esta en la posicion centinela '.', es decir lo proximo es analizar la traduccion, actualizamos el indice 'k' para pasar al primer simbolo de traduccion.
                m++;
                t=m+num;
                r=0;
                for(h=m;h<=t;h++)
                 {
                   traductor[i].cad[j].traduccion[r]=temp[h];
                   r++;
                 }
                t=0;
                k=m+num;
                //Ahora temp[k], esta en ':', tenemos que leer el destino que esta en k+1 y guardarlo en el struct, actualizamos k.
                t=0;
                vaciar(numTraduccion,3);
                for(k=k+1;temp[k]!=','&&temp[k]!='\0';k++)
                 {
                     numTraduccion[t]=temp[k];
                     t++;
                 }
                t=0;
                num=atoi(numTraduccion);
                traductor[i].destinos[j]=num;
                //Ahora temp[k] esta en la posicion  de ',' o '\0'; restamos 1 a 'k' asi ya que tras llegar a '}' el contador del for hara 'k++', y ya no se cumplira la condicion y saldra del for.
                k--;
             }
         }
        //Ahora temp[k] esta en la posicion de ',' o '\0'; si hay otra transicion ya que 'n'>1 queremos que temp[k] sea la posicion del simbolo de la siguiente transicion para que el for de 'k' se complete con normalidad.
        k++;
  }
}

void meterCharAlPrincpio(char aux,char temp[])
{
    char temp2;
    int i;
    for(i=0;i<MAX;i++)
     {
       temp2=temp[i];
       temp[i]=aux;
       aux=temp2;
     }
     printf("\n\n");
}

int tieneTransicion(char c,int estadoActual)
{
    int i;
    for(i=0;i<traductor[estadoActual].numeroTransiciones;i++)
     {
       if(c==traductor[estadoActual].transiciones[i]) return i;
     }
    return -1;
}


