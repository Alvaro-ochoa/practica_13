// Materia: Programación I, Paralelo 1
// Autor: Alvaro Alejandro Ochoa Segales.
// Fecha creación: 11/12/2024
// Número de ejercicio: 1
// Problema planteado: un programa que permita al usuario ingresar alumnos, eliminarlos y mostrar sus reportes en un archivo
#include <bits/stdc++.h> //la libreria mencionada es un comprimido de todas las funciones básicas de c++
using namespace std;

struct Estudiante {
    char ci[10];
    char nombre[30];
    char apellidos[30];
};

struct Notas
{
    char ci[10];
    char materia[30];
    int nota;
};
//en este caso los dos nombres de los archivos son binarios
const char* NombreArchivo = "Estudiantes.bin";
const char* NombreArchivoNotas = "Notas.bin";
//en este caso, se tienen las funciones, algunas son vectores, como son los leer archivo
vector<Estudiante> leerArchivo ();
void escribirArchivo (Estudiante);
void IngresarNuevo (vector<Estudiante>);
void menu ();
vector<Notas> leerArchivoNotas ();
void escribirArchivoNotas (Notas);
void ingresarNotas (vector<Estudiante>);
void mostrarReporte(vector<Estudiante>, vector<Notas>);

int main ()
{
    menu ();
}

void menu () 
{
    
    bool bandera = true;
    while(bandera){
        vector<Estudiante> estudiantes = leerArchivo();
        vector<Notas> notas = leerArchivoNotas();
        int opcion;
        cout << "1. Ingresar nuevo estudiante "<< endl;
        cout << "2. Ingresar Materias y notas "<< endl;
        cout << "3. Mostrar Reporte " << endl;
        cout << "4. Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            IngresarNuevo(estudiantes);
            break;
        case 2:
            ingresarNotas(estudiantes);
            break;
        case 3:
            mostrarReporte(estudiantes, notas);
            break;
        case 4:
            cout << "Saliendo del sistema" << endl;
            bandera = false;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    }
}


vector<Estudiante> leerArchivo (){
    ifstream leer (NombreArchivo, ios::binary);
    vector<Estudiante> estudiantes;
    Estudiante es;
    while(leer.read((char*)&es, sizeof(Estudiante))){
        estudiantes.push_back(es);
    }
    leer.close();
    return estudiantes;
}

void escribirArchivo (Estudiante es){
    ofstream escribir (NombreArchivo, ios::binary | ios::app);
    escribir.write((char*)&es, sizeof(Estudiante));
    escribir.close();
    cout << "Se ha registrado al estudiante" << endl;
}

void IngresarNuevo (vector<Estudiante> estudiantes){
    Estudiante es;
    cout << "Ingrese su CI:" << endl;
    cin.ignore();
    cin.getline(es.ci, 10);
    for(Estudiante e: estudiantes){
        if(strcmp(es.ci, e.ci) == 0){
            cout << "Este carnet ya esta registrado"<<endl;
            return;
        }
    }

    cout << "Ingrese el nombre:" << endl;
    cin.getline(es.nombre, 30);
    cout << "Ingrese el apellido:" << endl;
    cin.getline(es.apellidos, 30);

    escribirArchivo(es);
}

vector<Notas> leerArchivoNotas (){
    ifstream leer (NombreArchivoNotas, ios::binary);
    vector<Notas> notas;
    Notas no;
    while(leer.read((char*)&no, sizeof(Notas))){
        notas.push_back(no);
    }
    leer.close();
    return notas;
}

void escribirArchivoNotas (Notas no){
    ofstream escribir (NombreArchivoNotas, ios::binary | ios::app);
    escribir.write((char*)&no, sizeof(Notas));
    escribir.close();
    cout << "Se ha registrado las notas del estudiante" << endl;
}

void ingresarNotas (vector<Estudiante> es){
    Notas no;
    cout << "Ingrese el CI:" << endl;
    cin.ignore();
    cin.getline(no.ci, 10);
    for(Estudiante e: es){
        if(strcmp(no.ci, e.ci) == 0){
            cout << "Ingrese la materia: " << endl;
            cin.getline(no.materia, 30);
            cout << "Ingrese la nota: " << endl;
            cin >> no.nota;
            escribirArchivoNotas(no);
            return;
        }
    }
}

void mostrarReporte(vector<Estudiante> estudiantes, vector<Notas> notas){
    for(Estudiante es : estudiantes){
        cout << "CI: " << es.ci << endl;
        cout << "Nombre: " << es.nombre << endl;
        cout << "Apellido: " << es.apellidos << endl;
        cout << "\tNotas: " << endl;
        for(Notas no : notas){
            if(strcmp(es.ci, no.ci) == 0){
                cout << "\tMateria: " << no.materia << endl;
                cout << "\tNota: " << no.nota << endl;
                cout << "===========================" << endl;
            }
        }
        cout << "==================" << endl;
    }
}