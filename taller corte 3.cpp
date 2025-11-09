#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena; 
    string direccion;
    string metodoDePago;
};

struct CarritoDeCompras {
    int idCarrito;
    string nombreUsuario;     
    vector<int> productosIds;
    double subtotal;
    double impuestos;
};

struct OrdenDeCompra {
    int idOrden;
    vector<int> productosIds;
    long subtotal;
    double impuestos;
    double envio;
    double total;
};

struct Categoria {
    int idCategoria;
    string nombre;
};

struct Comentario {             
    int idComentario;
    string nombreProducto;
    string nombreUsuario;
    string comentario;
    string fecha;
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentario> comentarios;        
vector<CarritoDeCompras> carritos;     
vector<OrdenDeCompra> ordenes;         
vector<Categoria> categorias;

// =====================================================
// FUNCIÓN: limpiarString() - NUEVA
// Elimina espacios en blanco al inicio y final
// =====================================================
string limpiarString(string str) {
    // Eliminar espacios al inicio
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    
    // Eliminar espacios al final
    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

// =====================================================
// FUNCIÓN: dividirLinea() - NUEVA
// Divide una línea CSV en campos
// =====================================================
vector<string> dividirLinea(string linea) {
    vector<string> campos;
    stringstream ss(linea);
    string campo;
    
    while (getline(ss, campo, ',')) {
        campos.push_back(limpiarString(campo));
    }
    
    return campos;
}

// =====================================================
// FUNCIÓN: cargarUsuarios() - NUEVA
// Carga usuarios desde archivo Usuarios.txt
// =====================================================
bool cargarUsuarios() {
    ifstream archivo("Usuarios.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Usuarios.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 6) {
            Usuario u;
            u.idUsuario = atoi(campos[0].c_str());
            u.nombre = campos[1];
            u.correoElectronico = campos[2];
            u.contrasena = campos[3];
            u.direccion = campos[4];
            u.metodoDePago = campos[5];
            
            usuarios.push_back(u);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: cargarProductos() - NUEVA
// Carga productos desde archivo Productos.txt
// =====================================================
bool cargarProductos() {
    ifstream archivo("Productos.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Productos.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 5) {
            Producto p;
            p.idProducto = atoi(campos[0].c_str());
            p.nombre = campos[1];
            p.descripcion = campos[2];
            p.precio = atof(campos[3].c_str());
            p.stock = atoi(campos[4].c_str());
            
            productos.push_back(p);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: cargarComentarios() - NUEVA
// Carga comentarios desde archivo Comentarios.txt
// =====================================================
bool cargarComentarios() {
    ifstream archivo("Comentarios.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Comentarios.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 5) {
            Comentario c;
            c.idComentario = atoi(campos[0].c_str());
            c.nombreProducto = campos[1];
            c.nombreUsuario = campos[2];
            c.comentario = campos[3];
            c.fecha = campos[4];
            
            comentarios.push_back(c);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: guardarProductos() - NUEVA
// Guarda productos actualizados en archivo
// =====================================================
bool guardarProductos() {
    ofstream archivo("Productos.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo escribir en Productos.txt\n";
        return false;
    }
    
    // Escribir encabezado
    archivo << "idProducto,nombre,descripcion,precio,stock\n";
    
    // Escribir productos
    for (int i = 0; i < productos.size(); i++) {
        archivo << productos[i].idProducto << ","
                << productos[i].nombre << ","
                << productos[i].descripcion << ","
                << productos[i].precio << ","
                << productos[i].stock << "\n";
    }
    
    archivo.close();
    return true;
}

