#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int tareaId;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} typedef Nodo;

void insertarNodo(Tarea nuevaTarea, Nodo **Start);
void cargarTarea(int *proximo, Nodo **nodoDestino);
void mostrarTareas(Nodo *nodoTarea);
void moverTarea(Nodo **Desde, Nodo **Hasta, int id);
void insertarNodoOrdenado(Tarea nuevaTarea, Nodo **Start);

int main()
{
    Nodo *Pendientes = NULL;
    Nodo *Realizadas = NULL;
    int proximo = 1000;
    int opcion;
    int id;

    do
    {
        printf(".......MODO TO-DO......\n");
        printf("1- Cargar Tarea\n");
        printf("2- Mostrar Tarea Pendiente\n");
        printf("3- Mostrar Tarea Realizada\n");
        printf("4- Mover Tarea a realizada\n");
        printf("0- Salir.\n");
        scanf("%d", &opcion);
        getchar();
        switch (opcion)
        {
        case 1:
            cargarTarea(&proximo, &Pendientes);
            break;
        case 2:
            mostrarTareas(Pendientes);
            break;
        case 3:
            mostrarTareas(Realizadas);
            break;
        case 4:
            printf("=== Tareas Pendientes ===\n");
            printf("ingrese id de la tarea a mover\n");
            scanf("%d", &id);
            getchar();
            moverTarea(&Pendientes, &Realizadas, id);
            break;
        default:
            break;
        }
    } while (opcion != 0);
}

void insertarNodoOrdenado(Tarea nuevaTarea, Nodo **Start)
{
    Nodo *nNuevo = (Nodo *)malloc(sizeof(Nodo));
    nNuevo->T = nuevaTarea;
    nNuevo->siguiente = NULL;

    // inserta al inicio si la lista esta vacia o si el id de la nueva tarea es menor que el del primer nodo
    if (*Start == NULL || (*Start)->T.tareaId > nNuevo->T.tareaId)
    {
        nNuevo->siguiente = *Start;
        *Start = nNuevo; 
    }else{
        Nodo *actual = *Start;
        // hace un recorrido bucando la ultima ubicacion del nodo
        while (actual->siguiente != NULL && actual->siguiente->T.tareaId < nuevaTarea.tareaId)
        {
            actual = actual->siguiente;
        }
        //inserta el nuevo nodo
        nNuevo->siguiente = actual->siguiente;//ajusta el puntero del nuevo nodo->siguiente que apunte al siguiente
        actual->siguiente = nNuevo;//ajusta el puntero del nodo-anterior asi apunteal nuevo puntero        
    }

    
}

void insertarNodo(Tarea nuevaTarea, Nodo **Start)
{
    Nodo *nPendiente = (Nodo *)malloc(sizeof(Nodo));
    nPendiente->T = nuevaTarea;
    nPendiente->siguiente = *Start;
    *Start = nPendiente;
}

void cargarTarea(int *proximo, Nodo **nodoDestino)
{
    int opcion;
    do
    {
        Tarea nuevaTarea;
        nuevaTarea.tareaId = (*proximo)++;
        nuevaTarea.Duracion = rand() % (100 - 10 + 1) + 10;
        char descTarea[50];
        printf("ingrese la tarea a realizar\n");
        fgets(descTarea, 50, stdin);
        descTarea[strcspn(descTarea, "\n")] = 0; // elimina el santo de linea
        nuevaTarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(descTarea) + 1));//reserva memoria para la descripcion de acuerdo al tamaño de la cadena de caracteres
        strcpy(nuevaTarea.Descripcion, descTarea);
        insertarNodoOrdenado(nuevaTarea, nodoDestino);//inserta la tarea en el nodo correspondiente
        printf("desea cargar otra tarea? \n 1-SI\n 0-NO\n");
        scanf("%d", &opcion);
        getchar();// recoge un solo caracter ingresado por teclado
    } while (opcion == 1);
}

void mostrarTareas(Nodo *nodoTarea)
{
    Nodo *aux;
    aux = nodoTarea;
    while (aux != NULL)
    {
        printf("Id: %d\tDescripcion: %s\t Duracion: %d\n", aux->T.tareaId, aux->T.Descripcion, aux->T.Duracion);
        aux = aux->siguiente;
    }
}

void moverTarea(Nodo **Desde, Nodo **Hasta, int id)
{
    Nodo *actual = *Desde;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.tareaId != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {
        printf("tarea no encontrada\n");
        return;
    }

    if (anterior == NULL)
    {
        *Desde = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
    }

    actual->siguiente == NULL;

    insertarNodoOrdenado(actual->T, Hasta);
}

