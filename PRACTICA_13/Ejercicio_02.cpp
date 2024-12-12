// Materia: Programación I, Paralelo 1
// Autor: Alvaro Alejandro Ochoa Segales.
// Fecha creación: 11/12/2024
// Número de ejercicio: 2
// Problema planteado: un sistema que se encarga de los pedidos en la farmacia Chavez, donde ingresamos un producto, lo eliminamos o modificamos su precio y añadimos ventas
#include <bits/stdc++.h>//libreria que tiene las librerias base de c++
using namespace std;
//se declaran los nombres de losarchivos, los cuales seran un binario y un texto
const char* NombreArchivoProducto = "Productos.bin";
const char* NombreArchivoVentas = "Ventas.txt";

struct Producto
{
    int codigo;
    char nombre[30];
    int CantidadInicial;
    double precioUnitario;
    int cantidadVendida;
};

struct Ventas
{
    char ci[10];
    char nombre[30];
    int codigoProducto;
    int cantidad;
};

vector<Producto> leerArchivoProducto ();
void escribirArchivoProducto (Producto);
void ingrearProducto (vector<Producto>);
void sobreescribirProducto (vector<Producto>);
void eliminarProducto (vector<Producto>);
void modificarProducto (vector<Producto>);
void mostrarListado (vector<Producto>);
void escribirArchivoVenta (Ventas);
void ingresarVentaNueva (vector<Producto>);

int main (){
    bool bandera = true;
    while(bandera){
        cout << "1. Ingresar nuevo producto" << endl;
        cout << "2. Listar productos" << endl;
        cout << "3. Eliminar productos " << endl;
        cout << "4. Modificar un producto" << endl;
        cout << "5. Adicionar ventas" << endl;
        cout << "6. Salir" << endl;
        vector<Producto> productos = leerArchivoProducto();
        int opcion;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            ingrearProducto(productos);
            break;
        case 2:
            mostrarListado(productos);
            break;
        case 3:
            eliminarProducto(productos);
            break;
        case 4:
            modificarProducto(productos);
            break;
        case 5:
            ingresarVentaNueva(productos);
            break;
        case 6:
            cout << "Saliendo del sistema" << endl;
            bandera = false;
            break;
        default:
            break;
        }
    }
}

void ingresarVentaNueva (vector<Producto> prod){
    Ventas ve;
    cout << "Ingrese el codigo del producto: " << endl;
    cin >> ve.codigoProducto;
    for(int i = 0; i < prod.size(); i++){
        if(prod[i].codigo == ve.codigoProducto){
            cout << "Ingrese el CI" << endl;
            cin.ignore();
            cin.getline(ve.ci,10);
            cout << "Ingrese el nombre" << endl;
            cin.getline(ve.nombre, 30);
            cout << "Ingrese la cantidad " << endl;
            cin >> ve.cantidad;
            prod[i].cantidadVendida += ve.cantidad;
            sobreescribirProducto(prod);
            escribirArchivoVenta(ve);
            return;
        }
    }

    cout << "Producto no encontrado" << endl;
}

void escribirArchivoVenta (Ventas ve){
    ofstream escribir (NombreArchivoVentas, ios::app);
    escribir << ve.ci << ";" << ve.nombre << ";" << ve.codigoProducto << ";" << ve.cantidad << endl;
    escribir.close();
    cout << "Venta registrada" << endl;
}

vector<Producto> leerArchivoProducto (){
    ifstream leer (NombreArchivoProducto, ios::binary);
    vector<Producto> productos;
    Producto pr;
    while(leer.read((char*)&pr, sizeof(Producto))){
        productos.push_back(pr);
    }
    leer.close();
    return productos;
}

void escribirArchivoProducto (Producto pr){
    ofstream escribir (NombreArchivoProducto, ios::binary | ios::app);
    escribir.write((char*)&pr, sizeof(Producto));
    escribir.close();
    cout << "Se ha registrado el producto" << endl;
}

void ingresarProducto (vector<Producto> productos){
    Producto pr;
    cout << "Ingrese el codigo: " << endl;
    cin >> pr.codigo;
    for(Producto p : productos){
        if(p.codigo == pr.codigo){
            cout << "No se puede ingresar codigos repetidos!!" << endl;
            return;
        }
    }
    cout << "Ingrese el nombre: " << endl;
    cin.ignore();
    cin.getline(pr.nombre, 30);
    cout << "Ingrese la cantidad inicial: " << endl;
    cin >> pr.CantidadInicial;
    cout << "Ingrese el precio uitario: " << endl;
    cin >> pr.precioUnitario;
    pr.cantidadVendida = 0;
    escribirArchivo(pr);
}

void sobreescribirProducto (vector<Producto> prod){
    ofstream escribir (NombreArchivoProducto, ios::binary);
    for(Producto pr : prod){
        escribir.write((char*)&pr, sizeof(Producto));
    }
    escribir.close();
    cout << "Se ha registrado los cambios" << endl;
}

void eliminarProducto (vector<Producto> prod){
    int codigo;
    cout << "Ingrese el codigo del producto a eliminar: " << endl;
    cin >> codigo;
    bool encontrado =  false;
    for(Producto p : prod){
        if(p.codigo == codigo){
            encontrado = true;
        }
    }
    if(!encontrado){
        cout << "Producto no encontrado" << endl;
        return;
    }
    vector<Producto> nuevo;
    for(Producto p : prod){
        if(p.codigo != codigo){
            nuevo.push_back(p);
        }
    }
    sobreescribirProducto(nuevo);
}

void modificarProducto (vector<Producto> prod){
    int codigo;
    cout << "Ingrese el codigo del producto a modificar: " << endl;
    cin >> codigo;
    bool encontrado =  false;
    int posicion = 0;
    for(int i = 0; i < prod.size(); i++)
    {
        if(prod[i].codigo == codigo)
        {
            encontrado = true;
            posicion = i;
        }
    }
    if(!encontrado){
        cout << "Producto no encontrado" << endl;
        return;
    }
    Producto pr;
    pr.codigo = codigo;
    cout << "Ingrese el nuevo nombre: " << endl;
    cin.ignore();
    cin.getline(pr.nombre, 30);
    cout << "Ingrese la cantidad inicial: " << endl;
    cin >> pr.CantidadInicial;
    cout << "Ingrese el precio unitario: " << endl;
    cin >> pr.precioUnitario;
    pr.cantidadVendida = 0;
    prod[posicion] = pr;
    sobreescribirProducto(prod);
}

void mostrarListado (vector<Producto> prod){
    cout << "CODIGO\tNOMBRE PRODUCTO\tCANTIDAD INICAL\tPRECIO\tCANTIDAD VENDIDA\tTOTAL" << endl;
    for(Producto p : prod){
        cout << p.codigo << "\t" << p.nombre << "\t" << p.CantidadInicial << "\t" << p.precioUnitario << "\t" << p.cantidadVendida << "\t" << p.cantidadVendida * p.precioUnitario << endl;
    }
}