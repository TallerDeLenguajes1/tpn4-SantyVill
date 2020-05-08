#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int tareaID,duracion;
    char *descripcion;
} tarea;

typedef struct Nodo
{
    tarea T;
    Nodo *sig;
}Nodo;


//=========================FUNCIONES=========================
Nodo* busquedaPorPalabra(Nodo *tareasP,Nodo *tareasR);
bool buscar(char *frase,char *palabra);
Nodo* buscquedaPorId(Nodo *tareasP,Nodo *tareasR);
void mostrarTareas(Nodo *tareas);
void cargarTareas(Nodo **tareas,int n);
void realizarTareas(Nodo **tareasP, Nodo **tareasR);
//===========================MIAN===========================

int main(){
    srand (time(NULL));
    int n,i,opc;
    Nodo *paux;
    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d",&n);
    getchar();
    Nodo *tareasPendientes=(Nodo *)malloc(sizeof(Nodo));
    Nodo *tareasRealizadas=(Nodo *)malloc(sizeof(Nodo));
    tareasPendientes=NULL;
    tareasRealizadas=NULL;
    cargarTareas(&tareasPendientes,n);
    realizarTareas(&tareasPendientes,&tareasRealizadas);
    printf("\n\nTareas Realizadas: ");
    mostrarTareas(tareasRealizadas);
    printf("\n\nTareas Pendientes: ");
    mostrarTareas(tareasPendientes);

    paux=busquedaPorPalabra(tareasPendientes,tareasRealizadas);
    if (paux!=NULL)
    {
        printf("\nID de tarea: %d",paux->T.tareaID);
        printf("\nDescripcion: %s",paux->T.descripcion);
        printf("\nDuracion: %d",paux->T.duracion);
    } else
    {
        printf("No se encontro tarea.");
    }

    paux=buscquedaPorId(tareasPendientes,tareasRealizadas);
    if (paux!=NULL)
    {
        printf("\nID de tarea: %d",paux->T.tareaID);
        printf("\nDescripcion: %s",paux->T.descripcion);
        printf("\nDuracion: %d",paux->T.duracion);
    } else
    {
        printf("No se encontro tarea.");
    }
    
    
    getchar();
    getchar();
    free (tareasRealizadas);
    free (tareasPendientes);
    return 0;
}

//========================FUNCIONES========================

Nodo* busquedaPorPalabra(Nodo *tareasP,Nodo *tareasR){
    int i;
    char palabra[15];
    Nodo *aux;
    getchar();
    printf("\n\nIngrese la palabra con la que quiere buscar la tarea: ");
    gets(palabra);
    aux=tareasP;
    while(aux!=NULL)
    {
            if (buscar(aux->T.descripcion,palabra))
            {
                printf("\nTarea pendiente:");
                return aux;
            }
        aux=aux->sig;
    }
    aux=tareasR;
    while(aux!=NULL)
    {
        if (buscar(aux->T.descripcion,palabra))
        {
            printf("\nTarea realizada:");
            return aux;
        }
        aux=aux->sig;
    }
    return NULL;
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

Nodo* buscquedaPorId(Nodo *tareasP,Nodo *tareasR){
    int id,i;
    Nodo *aux;
    printf("\nIngrese el id de la tarea que desea buscar: ");
    scanf("%d",&id);
    aux=tareasR;
    while(aux!=NULL)
    {
        if (aux->T.tareaID==id)
        {
            return aux;
        }
        aux=aux->sig;
    }
    aux=tareasP;
    while (aux!=NULL)
    {
        if (aux->T.tareaID==id)
        {
            return (aux);
        }
        aux=aux->sig;
    }
}

void mostrarTareas(Nodo *tareas){
    while(tareas!=NULL)
    {
        printf("\n\nTarea numero %d",tareas->T.tareaID);
        printf("\nDescripcion: %s",tareas->T.descripcion);
        printf("\nDuracion: %d",tareas->T.duracion);
        tareas=tareas->sig;
    }
}

void cargarTareas(Nodo **tareas,int n){
    int i;
    char descr[60];
    Nodo *nuevoNodo;
    for ( i = 0; i < n; i++)
    {
        nuevoNodo =(Nodo *)malloc(sizeof(Nodo));
        nuevoNodo->T.tareaID=i+1;
        nuevoNodo->T.duracion=rand()%91+10;
        printf("\nIngrese la descripcion de la tarea %d: ",i+1);
        gets(descr);
        nuevoNodo->T.descripcion=(char *)malloc(sizeof(char)*strlen(descr));
        strcpy(nuevoNodo->T.descripcion,descr);
        nuevoNodo->sig=*tareas;
        *tareas=nuevoNodo;
    }
}

void realizarTareas(Nodo **tareasP, Nodo **tareasR){
    int opc=0,band=0;
    Nodo *nuevo,*aux=*tareasP,*auxant=*tareasP,*auxborrar;
    while (aux!=NULL)
    {
        printf("\nSe realizara la tarea %d?",aux->T.tareaID);
        printf("\nDescripcion: %s",aux->T.descripcion);
        printf("\nDuracion: %d",aux->T.duracion);
        do
        {
            printf("\nSI --> 1.\tNO --> 2.\n");
            scanf("%d",&opc);
        } while (opc!=1 && opc!=2);
        if (opc==1)
        {
            nuevo=(Nodo *) malloc(sizeof(Nodo));
            nuevo->T=aux->T;
            nuevo->sig=*tareasR;
            *tareasR=nuevo;

            auxborrar=aux;
            if (band==0)
            {
                *tareasP=(*tareasP)->sig;
                aux=aux->sig;
                free(auxborrar);
            } else
            {
                auxant->sig=aux->sig;
                aux=aux->sig;
                free(auxborrar);
            }
            
        } else
        {
            auxant=aux;
            aux=aux->sig;
        }
        band=1;
    }
}