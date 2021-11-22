#ifndef USUARIO_HPP
#define USUARIO_HPP
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "cadena.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

class Tarjeta;
class Numero;
 
class Clave{
    public:
        Clave(const char *);
        enum Razon{CORTA, ERROR_CRYPT};
        const Cadena& clave() const;
        bool verifica(const char *) const;
        
        class Incorrecta{
            public:
                Incorrecta(Razon r) : r_(r) {}
                Razon razon() const{ return r_; }

            private:
                Razon r_;
        };


    private:
        Cadena passwd_;
};

class Usuario{
    public:
        Usuario(const Cadena& , const Cadena& , const Cadena& , const Cadena& , 
                const Clave& );
        Usuario(const Usuario& ) = delete;
        Usuario& operator=(const Usuario& ) = delete;

        typedef std::map<Numero, Tarjeta *> Tarjetas;
        typedef std::unordered_map<Articulo *, unsigned> Articulos;
        typedef std::unordered_set<Cadena> Usuarios;
        
       
        Cadena id() const {return id_;}
        Cadena nombre() const {return nom_;}
        Cadena apellidos() const {return apell_;}
        Cadena direccion() const {return dir_;}
        const Tarjetas& tarjetas() const { return tarjetas_; }
        const Articulos& compra() const{return articulos_; }
        size_t n_articulos() const{ return articulos_.size();}

        void es_titular_de(Tarjeta&);
        void no_es_titular_de(Tarjeta&);
        void compra(Articulo&, unsigned cant = 1);
       
        friend std::ostream& operator << (std::ostream&, const Usuario&);

        class Id_duplicado{
            public:
                Id_duplicado(const Cadena& cad): cad_(cad) {}
                const Cadena idd() const{ return cad_;};

            private:
                Cadena cad_;
         };
    
    ~Usuario();

private:
    Cadena id_, nom_, apell_, dir_;
    Clave passwd_;
    static Usuarios users_ ;
    Tarjetas tarjetas_;
    Articulos articulos_;
};

std::ostream& mostrar_carro(std::ostream& , const Usuario& );

#endif
