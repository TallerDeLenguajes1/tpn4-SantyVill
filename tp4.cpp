#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int tareaID,duracion;
    char *descripcion;
} tarea;

//=========================FUNCIONES=========================
void cargarTareas(tarea *tareas,int n);
int realizarTareas(tarea *tareasP, tarea *tareasR,int n);
void mostrarTareas(tarea *tareas,int n);
tarea* buscarTarea(tarea *tareasP,tarea *tareasR,int n,int c);
bool buscar(char *frase,char *palabra);

//===========================MIAN===========================

int main(){
    srand (time(NULL));
    int n,i,opc,c=0;
    tarea *paux;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&n);
    getchar();
    tarea *tareasPendientes=(tarea *)malloc(sizeof(tarea)*n);
    tarea *tareasRealizadas=(tarea *)malloc(sizeof(tarea)*n);
    cargarTareas(tareasPendientes, n);
    c=realizarTareas(tareasPendientes,tareasRealizadas,n);
    printf("\n\nTareas Realizadas: ");
    mostrarTareas(tareasRealizadas,c);
    printf("\n\nTareas Pendientes: ");
    mostrarTareas(tareasPendientes,n);

    paux=buscarTarea(tareasPendientes,tareasRealizadas,n,c);
    printf("\nID de tarea: %d",paux->tareaID);
    printf("\nDescripcion: %s",paux->descripcion);
    printf("\nDuracion: %d",paux->duracion);
    
    getchar();
    getchar();
    free (tareasRealizadas);
    free (tareasPendientes);
    return 0;
}

//========================FUNCIONES========================

tarea* buscarTarea(tarea *tareasP,tarea *tareasR,int n,int c){
    int i,j,cont,h;
    char palabra[15];
    tarea *aux;
    getchar();
    printf("\n\nIngrese la palabra con la que quiere buscar la tarea: ");
    gets(palabra);
    aux=tareasP;
    for(h=0;h<n;h++){
        if (aux->descripcion!=NULL)
        {
            if (buscar(aux->descripcion,palabra))
            {
                printf("\nTarea pendiente:");
                return aux;
            }
        }
        aux++;
    }
    aux=tareasR;
    for(h=0;h<c;h++){
        if (aux->descripcion!=NULL)
        {
            if (buscar(aux->descripcion,palabra))
            {
                printf("\nTarea realizada:");
                return aux;
            }
        }
        aux++;
    }
}

bool buscar(char *frase,char *palabra){
    int i,j,c=0;
    for (i = 0; i <= strlen(frase)-strlen(palabra); i++)
    {
        c=0;
        for ( j = 0; j < strlen(palabra); j++)
        {
            if (*(frase+j+i)!=*(palabra+j))
            {
                j=strlen(palabra);
            } else {
                c++;
                if (c==strlen(palabra))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void mostrarTareas(tarea *tareas,int n){
    int i;
    for (i = 0; i < n; i++)
    {
        if ((tareas+i)->descripcion!=NULL)
        {
            printf("\n\nTarea numero %d",(tareas+i)->tareaID);
            printf("\nDescripcion: %s",(tareas+i)->descripcion);
            printf("\nDuracion: %d",(tareas+i)->duracion);
        }
    }
    
}

void cargarTareas(tarea *tareas,int n){
    int i;
    char descr[60];
    for ( i = 0; i < n; i++)
    {
        (tareas+i)->tareaID=i+1;
        (tareas+i)->duracion=rand()%91+10;
        printf("\nIngrese la descripcion de la tarea %d: ",i+1);
        gets(descr);
        (tareas+i)->descripcion=(char *)malloc(sizeof(char)*strlen(descr));
        strcpy((tareas+i)->descripcion,descr);
    }
}

int realizarTareas(tarea *tareasP, tarea *tareasR,int n){
    int opc=0,i,c=0;
    for (i = 0; i < n; i++)
    {
        printf("\nSe realizara la tarea %d?",i+1);
        printf("\nDescripcion: %s",(tareasP+i)->descripcion);
        printf("\nDuracion: %d",(tareasP+i)->duracion);
        do
        {
            printf("\nSI --> 1.\tNO --> 2.");
            scanf("%d",&opc);
        } while (opc!=1 && opc!=2);
        if (opc==1)
        {
            *(tareasR+c)=*(tareasP+i);
            (tareasP+i)->descripcion=NULL;
            (tareasP+i)->tareaID=NULL;
            (tareasP+i)->duracion=NULL;
            c++;
        }
    }
    return c;
}