// Materia: Programación I, Paralelo 1
// Autor: Alvaro Alejandro Ochoa Segales.
// Fecha creación: 11/12/2024
// Número de ejercicio: 3
// Problema planteado: crear un menu donde se deba añadir las pizzas, mostrar la lista de cuantas pedimos, eliminar un pedido, modificar tu precio y añadir ventas
#include <bits/stdc++.h>//la libreria comprime las librerias más usadas en c++
using namespace std;
struct Pizza
{
    int codigo;
    char nombre[30];
    char tipo[30];
    char tamanio[30];
    double precio;
    int cantidadVend;
};
struct Venta
{
    char ci[10];
    char tamanio_p[30];
    int codigo_p;
    int cantidad_v;
};
//se declaran como caracter los archivos tanto binario como de texto
const char* archivoProd="Producto.bin";
const char* archivoVentas="Ventas.txt";

void menu();
vector<Producto>leerArchvosProd();
void ingresarProd(vector<Pizza>);
void sobreescribirArchivo(vector<Pizza> );
void mostrarProd(vector<Pizza> );
void modificarProd(vector<Pizza>);
void eliminarProd(vector<Pizza>);
void ingresarVenta(vector<Pizza>);
int main()
{
    system("cls");
    menu();
    return 0;
}
void menu()
{
    bool bandera=true;
    int op;
    while(bandera)
    {
        cout<<"ingrese la opcion que desee: "<<endl;
        cout<<" 1. Adicionar Pizza" <<endl;
        cout<<"2. Listado de Pizzas "<<endl;
        cout<<"3. Modificar el precio" de la Pizza según el código <<endl;
        cout<<"4. Eliminar una Pizza" <<endl;
        cout<<"5. Adicionar Venta de Pizzas" <<endl;
        cout<<"0.salir"<<endl;
        vector<Pizza>pizzas=leerArchivosProd();
        switch(op)
        {
            case 0: cout<<"saliendo...";bandera=false;break;
            case 1: ingresarProd(pizzas);break;
            case 2: mostrarProd(pizzas);break;
            default: cout<<"usted no ha ingresado ninguna opcion..."<<endl;break;
        }
    }
}
vector<Pizza>leerArchvosProd()
{
    ifstream leer(archivoProd, ios::binary); 
    vector<Pizza>pizzas;
    PIzza pr;
    while(leer.read((char*)&pr, sizeof(Pizza)));
    {
        pizzas.push_back(pr);
    }
    leer.close();
    return pizzas;
}
void ingresarProd(vector<Pizza>pizzas)
{
    Pizza pr;
    cout<<"ingresar el codigo: ";
    cin>>pr.codigo;
    for(Pizza prod: pizzas)
    {
        if(pr.codigo==prod.codigo)
        {
            cout<<"no puede ingresar el mismp codigo para su nuevo producto..";
        }
    }
    cin.ignore();
    cout<<"ingrese el nombre de su pizza: ";
    cin.getline(pr.nombre,30);
    cout<<"ingrese el tamaño de su pizza: ";
    cin.getline(pr.tamanio,30);
    cout<<"ingrese el tipo de su pizza: ";
    cin.getline(pr.tipo, 30);
    cout<<"ingrese el precio de su pizza: ";
    cin>>pr.precio;
    pr.cantidadVend=0;
    if(pr.tipo=="especial")
    {
        pr.precio+=1.1;
    }
    sobreescribirArchivo(pr);
}
void sobreescribirArchivo(vector<Pizza> pr)
{
    ofstream escribir(archivoProd, ios::binary); 
    vector<Pizza>pizzas;
    for(Pizza pr: pizzas)
    {
    while(escribir.write((char*)&pr, sizeof(Pizza)));
    {
        pizzas.push_back(pr);
    }
    }
    escribir.close();
    cout<<"se han guardado los cambios..";
}
void mostrarProd(vector<Pizza>pr)
{
    for(Pizza p: pr)
    {
        cout<<p.codigo<<"\t"<<p.nombre<<"\t"<<p.tipo<<"\t"<<p.tamanio<<"\t"<<p.precio<<"\t"<<p.cantidadVend<<"\t"<<p.cantidadVend*p.precio<<endl;
    }
}
void modificarProd(vector<Pizza> prod)
{
    int codigo;
    cout<<"ingrese el código de su pizza: ";
    cin>>codigo;
    int posicion=0
    bool encontrado=false;
    for(int i=0; i<prod.size(); i++)
    {
        if(prod[i].size()==codigo)
        {
            encontrado=true;
            posicion=i;
        }
    }
    if(!encontrado)
    {
        cout<<"el codigo no se ha encontrado";
        return;
    }
    Pizza pr;
    cout<<"ingrese el nuevo precio de la pizza: ";
    cin>>pr.precio;
    pr.cantidadVend=0
    prod[posicion]=ps;
    sobreescribirProd(prod);
}
void eliminarProd(vector<Pizza>prod)
{
    int codigo;
    bool encontrado=true;
    cout<<"ingrese el codigo de la pizza: ";
    cin>>codigo;
    for(Pizza pr:prod)
    {
        if(pr.codigo==codigo)
        {
            encontrado=true;
        }
    }
    if(!encontrado)
    {
        cout<<"el codigo ingresado no fue encontrado..."
        return;
    }
    vector<Pizza>nuevo;
    for(Pizza p: prod)
    {
        if(p.codigo!=codigo)
        {
            nuevo.push_back(p);
        }
    }
    sobreescribirProd(nuevo);
}
void ingresarVenta (vector<PIzza> prod){
    Venta ve;
    cout << "Ingrese el codigo del producto: " << endl;
    cin >> ve.codigo_p;
    for(int i = 0; i < prod.size(); i++){
        if(prod[i].codigo == ve.codigo_p){
            cout << "Ingrese el CI" << endl;
            cin.ignore();
            cin.getline(ve.ci,10);
            cout << "Ingrese el tamaño de su pizza" << endl;
            cin.getline(ve.tamanio_p, 30);
            cout << "Ingrese la cantidad " << endl;
            cin >> ve.cantidad_v;
            prod[i].cantidadVend += ve.cantidad_v;
            sobreescribirProducto(prod);
            escribirArchivoVenta(ve);
            return;
        }
    }

    cout << "Producto no encontrado" << endl;
}