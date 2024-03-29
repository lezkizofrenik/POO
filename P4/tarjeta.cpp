#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>
#include "tarjeta.hpp"
#include "usuario.hpp"
 
bool luhn(const Cadena& cad);

static Cadena str_toupper(Cadena s){
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

bool operator<(const Numero& A, const Numero& B){
    return strcmp(A, B) < 0;
}

Numero::operator const char *() const{
    return num_.c_str();
}

Numero::Numero(const Cadena& cad){
    Cadena aux(cad);
    Cadena::iterator end = remove_if(aux.begin(), aux.end(), EsBlanco());
    if(end != aux.end()){
        *end = '\0';
        Cadena tmp(aux.c_str());
        num_ = tmp;
    }
    if (aux.length() < 13 || aux.length() > 19 || aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);

    num_ = aux.c_str();
 

    if (std::find_if(num_.begin(), num_.end(), std::not1(EsDigito())) != num_.end())
        throw Incorrecto(Razon::DIGITOS);
    if (!luhn(num_))
        throw Incorrecto(Razon::NO_VALIDO);
}

Tarjeta::Tarjeta(Numero num, Usuario& user, Fecha f) : num_(num), user_(&user), caducidad_(f), estado_(true){
    if (Fecha() > caducidad_)
        throw Caducada(caducidad_);
    user.es_titular_de(*this);
    switch (num[0])
    {
    case '3':
        switch (num[1])
        {
        case '4':
        case '7':
            t_ = JCB;
            break;
        default:
            t_ = AmericanExpress;
            break;
        }
        break;
    case '4':
        t_ = VISA;
        break;
    case '5':
        t_ = Mastercard;
        break;
    case '6':
        t_ = Maestro;
        break;
    default:
        t_ = Otro;
        break;
    }
}

inline Tarjeta::Tipo Tarjeta::tipo() const{
    return t_;
}

inline Numero Tarjeta::numero() const{
    return num_;
}

const Usuario *Tarjeta::titular() const{
    return user_;
}

inline Fecha Tarjeta::caducidad() const{
    return caducidad_;
}

bool Tarjeta::activa(bool est){
    estado_ = est;
    return estado_;
}

void Tarjeta::anula_titular()
{
    user_ = nullptr;
    estado_ = false;
}

Tarjeta::~Tarjeta()
{
    if (Usuario *usuar = const_cast<Usuario *>(user_))
        usuar->no_es_titular_de(*this);
}

Cadena Tarjeta::titular_facial() const
{
    return str_toupper(user_->nombre()) + " " + str_toupper(user_->apellidos());
}

std::ostream& operator<<(std::ostream& os, const Tarjeta& T)
{
    return os << T.tipo() << std::endl
              << T.numero() << std::endl
              << T.titular_facial() << std::endl
              << "Caduca: " << std::setfill('0') << std::setw(2)
              << T.caducidad().mes() << '/' << std::setw(2)
              << (T.caducidad().anno() % 100);
}

std::ostream& operator<<(std::ostream& os, const Tarjeta::Tipo& t)
{
    switch (t)
    {
    case Tarjeta::Tipo::VISA:
        os << "VISA";
        break;
    case Tarjeta::Tipo::Mastercard:
        os << "Mastercard";
        break;
    case Tarjeta::Tipo::Maestro:
        os << "Maestro";
        break;
    case Tarjeta::Tipo::JCB:
        os << "JCB";
        break;
    case Tarjeta::Tipo::AmericanExpress:
        os << "AmericanExpress";
        break;
    default:
        os << "Tipo indeterminado";
        break;
    }
    return os;
}

bool operator<(const Tarjeta& A, const Tarjeta& B)
{
    return A.numero() < B.numero();
}
