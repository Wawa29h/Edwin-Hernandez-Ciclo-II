// Biblioteca digital
#include <iostream>
#include <string>
#include <vector>
// areglar duplicados
class Libro {
    public:
    std::string titulo;            
    std::string autor;
    int aniodepublicacion;
    bool disponible = true;

    void MostrarDetalles() const{
    std::cout << "---------------------------" << std::endl;
    std::cout << "Título: " << titulo << std::endl;
    std::cout << "Autor: " << autor << std::endl;
    std::cout << "Año de publicación: " << aniodepublicacion << std::endl;
    std::cout << "Disponibilidad: " << (disponible ? "Sí" : "No") << std::endl;

    }
};



class Usuario {
public:
    std::string nombre;
    std::vector<std::string> libros; //libros guardados

    Usuario() = default;
    explicit Usuario(const std::string& n) : nombre(n) {}
};

// solo permitir numeros en anios
int leerAnio() {
    std::string entrada;
    int anio;
    while (true) { //para que se ejectue hasta q de el resultado que quiero
        std::cout << "Anio (numero): ";
        std::getline(std::cin, entrada);

        bool esNumero = true;
        for (char c : entrada) { //si cumple los requisitos pasa de un solo 
            if (!isdigit(c)) { // si algun caracter no es dígito
                esNumero = false;
                break;
            }
        }

        if (esNumero && !entrada.empty()) {
            anio = std::stoi(entrada); // convertir string a int
            return anio;
        } else {
            std::cout << "Error: debe ingresar solo numeros.\n";
        }
    }
}



class Biblioteca {
  private:
    std::vector<Libro> coleccion;
    std::vector<Usuario> usuarios; 

    bool existetitulo(const std::string& titulo) const {
        for (const auto& l : coleccion) {
            if (l.titulo == titulo) return true;  
        }
        return false;
    }

    Usuario* buscarUsuario(const std::string& nombre) {
        for (auto& u : usuarios) {               
            if (u.nombre == nombre) return &u;
        }
        return nullptr;
    }

    Libro* buscarLibro(const std::string& titulo) {
        for (auto& l : coleccion) {
            if (l.titulo == titulo) return &l;
        }
        return nullptr;
    }
//const me ayuda a q no se podra modificar  el dato
    public:
         void agregarlibro(const Libro& libro) {
        if (existetitulo(libro.titulo)) {
            std::cout << "Ya existe un libro con ese titulo"<< std::endl;
            return;
        }
        coleccion.push_back(libro);
        std::cout << "Agregando libro: " << libro.titulo << "\n";
    }
        void mostrarbiblioteca() {
            std::cout << "Nuestros libros:" << std::endl;
            for (const auto& libro : coleccion) {
                libro.MostrarDetalles();
            }
        }

        //chat gpt
bool prestarLibro(const std::string& titulo) {
    for (auto& libro : coleccion) {
        if (libro.titulo == titulo) {
            if (!libro.disponible) {
                std::cout << "El libro ya está prestado.\n";
                return false;
            }
            libro.disponible = false;
            std::cout << "Préstamo realizado: " << libro.titulo << "\n";
            return true;
        }
    }
    std::cout << "No se encontró el libro.\n";
    return false;
}

bool devolverLibro(const std::string& titulo) {
    for (auto& libro : coleccion) {
        if (libro.titulo == titulo) {
            if (libro.disponible) {
                std::cout << "El libro ya estaba disponible.\n";
                return false;
            }
            libro.disponible = true;
            std::cout << "Devolución realizada: " << libro.titulo << "\n";
            return true;
        }
    }
    std::cout << "No se encontró el libro.\n";
    return false;
}


void registrarUsuario(const std::string& nombre) {
    if (buscarUsuario(nombre)) { 
        std::cout << "El usuario ya existe.\n"; 
        return; 
    }
    usuarios.push_back(Usuario{nombre});
    std::cout << "Usuario registrado: " << nombre << "\n";
}

void mostrarUsuarios() const {
    if (usuarios.empty()) { 
        std::cout << "No hay usuarios.\n"; 
        return; 
    }
    for (const auto& u : usuarios) {
        std::cout << "Usuario: " << u.nombre 
                  << " (tiene " << u.libros.size() << " libros)\n";
    }
}

void prestar(const std::string& titulo, const std::string& nombreUsuario) {
    Libro* l = buscarLibro(titulo);
    if (!l) { std::cout << "No se encontró el libro.\n"; return; }
    if (!l->disponible) { std::cout << "El libro ya está prestado.\n"; return; }

    Usuario* u = buscarUsuario(nombreUsuario);
    if (!u) { std::cout << "No se encontró el usuario.\n"; return; }

    l->disponible = false;
    u->libros.push_back(titulo);
    std::cout << "Prestado \"" << titulo << "\" a " << nombreUsuario << "\n";
}

void devolver(const std::string& titulo, const std::string& nombreUsuario) {
    Libro* l = buscarLibro(titulo);
    if (!l) { std::cout << "No se encontró el libro.\n"; return; }

    Usuario* u = buscarUsuario(nombreUsuario);
    if (!u) { std::cout << "No se encontró el usuario.\n"; return; }

    for (size_t i = 0; i < u->libros.size(); ++i) {
        if (u->libros[i] == titulo) {
            u->libros.erase(u->libros.begin() + static_cast<long>(i));
            l->disponible = true;
            std::cout << "Devuelto \"" << titulo 
                      << "\" por " << nombreUsuario << "\n";
            return;
        }
    }
    std::cout << "Ese usuario no tenía ese libro.\n";
}
};
 // por que cierra, creo q es por q cierra clase


// --- Función Principal con el Menú ---
int main() {
    Biblioteca mibiblioteca;
   

    // Libro 1
    Libro l1;
    l1.titulo = "El Hobbit";
    l1.autor = "J.R.R. Tolkien";
    l1.aniodepublicacion = 1937;
    l1.disponible = true;
    mibiblioteca.agregarlibro(l1);

    // Libro 2
    Libro l2;
    l2.titulo = "Cien Anos de Soledad";
    l2.autor = "Gabriel Garcia Marquez";
    l2.aniodepublicacion = 1967;
    l2.disponible = true;
    mibiblioteca.agregarlibro(l2);

    // Libro 3
    Libro l3;
    l3.titulo = "El Principito";
    l3.autor = "Antoine de Saint-Exupery";
    l3.aniodepublicacion = 1943;
    l3.disponible = true;
    mibiblioteca.agregarlibro(l3);

    // Libro 4
    Libro l4;
    l4.titulo = "1984";
    l4.autor = "George Orwell";
    l4.aniodepublicacion = 1949;
    l4.disponible = true;
    mibiblioteca.agregarlibro(l4);

    // Libro 5
    Libro l5;
    l5.titulo = "Don Quijote de la Mancha";
    l5.autor = "Miguel de Cervantes";
    l5.aniodepublicacion = 1605;
    l5.disponible = true;
    mibiblioteca.agregarlibro(l5);

    // Libro 6
    Libro l6;
    l6.titulo = "La Odisea";
    l6.autor = "Homero";
    l6.aniodepublicacion = -800;  
    l6.disponible = true;
    mibiblioteca.agregarlibro(l6);
    int opcion = 0;

    
   while (opcion != 7) {
    std::cout << "Mi biblioteca" << std::endl;
        std::cout << "1. Añadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Registrar usuario" << std::endl;
        std::cout << "4. Mostrar usuarios" << std::endl;
        std::cout << "5. Prestar libro a usuario" << std::endl;
        std::cout << "6. Devolver libro de usuario" << std::endl;
        std::cout << "7. Salir" << std::endl;
    
    if (!(std::cin >> opcion)) {
    std::cout << "Error: ingrese un número válido." << std::endl;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    continue;
}
        
if (opcion == 1) {
    Libro nuevo;
    std::cout << "Titulo: ";
    std::getline(std::cin >> std::ws, nuevo.titulo); //wa para borrar espacios en blanco
    std::cout << "Autor: ";
    std::getline(std::cin >> std::ws, nuevo.autor);
    nuevo.aniodepublicacion = leerAnio();
    nuevo.disponible = true;
    mibiblioteca.agregarlibro(nuevo);
    std::cout << "Libro agregado.\n";
}
else if (opcion == 2) {
    mibiblioteca.mostrarbiblioteca();
}
else if (opcion == 3) { // Registrar usuario
    std::string nombre;
    std::cout << "Nombre de usuario: ";
    std::getline(std::cin >> std::ws, nombre);
    mibiblioteca.registrarUsuario(nombre);
}
else if (opcion == 4) { // Mostrar usuarios
    mibiblioteca.mostrarUsuarios();
}
else if (opcion == 5) { // Prestar libro a usuario
    std::string usuario, titulo;
    std::cout << "Usuario: ";
    std::getline(std::cin >> std::ws, usuario);
    std::cout << "Titulo a prestar: ";
    std::getline(std::cin >> std::ws, titulo);
    mibiblioteca.prestar(titulo, usuario);
}
else if (opcion == 6) { // Devolver libro de usuario
    std::string usuario, titulo;
    std::cout << "Usuario: ";
    std::getline(std::cin >> std::ws, usuario);
    std::cout << "Titulo a devolver: ";
    std::getline(std::cin >> std::ws, titulo);
    mibiblioteca.devolver(titulo, usuario);
}
else if (opcion == 7) {
    std::cout << "Saliendo..." << std::endl;
}
else {
    std::cout << "Opcion invalida." << std::endl;
}
}

return 0;
}