#ifndef TARJETA_HPP
#define TARJETA_HPP
#include <ostream>
#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
 
class Usuario;

struct EsDigito : public std::unary_function<char, bool>{
    bool operator()(char c) const { return isdigit(c); }
};

struct EsBlanco : public std::unary_function<char, bool>{
    bool operator()(char c) const { return isspace(c); }
};

class Numero{
    public:

        Numero(const Cadena& );
        enum Razon{LONGITUD, DIGITOS, NO_VALIDO}; 

        operator const char *() const;
        friend bool operator<(const Numero& , const Numero& );

        class Incorrecto{
            public:
                Incorrecto(Razon r) : r_(r) {}
                const Razon& razon() const { return r_; }

            private:
                Razon r_;
        };

    private:
        Cadena num_;
};

class Tarjeta{

    public:

        Tarjeta(Numero, Usuario& , Fecha);
        Tarjeta(const Tarjeta& ) = delete;
        Tarjeta& operator=(const Tarjeta& ) = delete;

        enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        Tipo tipo() const;
        Numero numero() const;
        const Usuario *titular() const;
        Cadena titular_facial() const;
        Fecha caducidad() const;
        bool activa() const { return estado_; }
        bool activa(bool est = true);
        void anula_titular();

        class Caducada{
            public:
                Caducada(const Fecha& f) : f_(f) {}
                Fecha cuando() const { return f_; }

            private:
                Fecha f_;
        };

        class Num_duplicado{
            public:
                explicit Num_duplicado(const Numero& n) : n_(n) {}
                Numero que() const { return n_; }

            private:
                Numero n_;
        };

        class Desactivada{
            public: 
            private:     
        };


    ~Tarjeta();

private:

    Tipo t_;
    Numero num_;
    const Usuario *user_;
    Fecha caducidad_;
    bool estado_;

};

std::ostream& operator<<(std::ostream&, const Tarjeta&);
std::ostream& operator<<(std::ostream&, const Tarjeta::Tipo&);
bool operator<(const Tarjeta&, const Tarjeta&);

#endif
