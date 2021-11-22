#include "usuario.hpp"
#include <cstring>
extern "C"
{
#include <unistd.h>
}
#include <iomanip>
#include <random>
#define CHARS "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA9876543210/."

Clave::Clave(const char *cad){
    if (std::strlen(cad) < 5)
        throw Incorrecta(Clave::CORTA);
 
    static std::random_device rd;
    static std::uniform_int_distribution<std::size_t> dis(0, 63);
    static const char *const cv = CHARS; // CHARS en linea 16
    const char salt[] = {cv[dis(rd)], cv[dis(rd)]};
    if (const char *const encrypt = crypt(cad, salt))
        passwd_ = encrypt;
    else
        throw Incorrecta(Razon::ERROR_CRYPT);
}

const Cadena& Clave::clave() const{
    return passwd_;
}

bool Clave::verifica(const char *cad) const{
    if (const char *const pw = crypt(cad, passwd_.c_str()))
        return pw == passwd_;
    throw Incorrecta(Razon::ERROR_CRYPT);
}

Usuario::Usuarios Usuario::users_;

Usuario::Usuario(const Cadena& id, const Cadena& nomb, const Cadena& apell, const Cadena& dir, const Clave& clv) : 
id_(id), nom_(nomb), apell_(apell), dir_(dir), passwd_(clv){
    if (!users_.insert(id).second)
        throw Id_duplicado(id_);
}

void Usuario::es_titular_de(Tarjeta& t){
    if (this == t.titular()){
        tarjetas_.insert(std::make_pair(t.numero(),& t));
    }
}

void Usuario::no_es_titular_de(Tarjeta& t){
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

void Usuario::compra(Articulo& art, unsigned cant){
    if (cant == 0)
        articulos_.erase(&art);
    else
        articulos_[&art] = cant;
}


Usuario::~Usuario(){
    for (auto &[numero, tarjeta] : tarjetas_)
        tarjeta->anula_titular();
    users_.erase(id_);
}

std::ostream& operator<<(std::ostream& os, const Usuario& user){
    os << user.id_ << "[" << user.passwd_.clave().c_str() << "]"
       << user.nom_ << user.apell_ << std::endl
       << user.dir_ << std::endl
       << "Tarjetas:" << std::endl;
    for (const auto &[numero, tarjeta] : user.tarjetas())
        os << *tarjeta << std::endl;
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user){
    os << "Carrito de compra de " << user.id() << " [Artículos: "
       << user.n_articulos() << "]\n Cant. Artículo\n"
       << Cadena(95, '=') + "\n";
    for (const auto &[articulo, cantidad] : user.compra()){
        os << std::setw(4) << cantidad << "   "
           << "[" << articulo->referencia() << "] \"" << articulo->titulo()
           << "\", " << articulo->f_publi().anno() << ". " << std::fixed
           << std::setprecision(2) << articulo->precio() << " €\n";
    }
    return os;
}


