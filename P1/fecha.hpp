/*
** fecha.hpp
*/

#ifndef FECHA_HPP//Si no está definida la macro, la define. Evita que la procese dos veces si hay dos archivos
#define FECHA_HPP
#include <clocale>
#include <ctime>
#include <iostream>
 
class Fecha{
    public:

  
        explicit Fecha(int d = 0, int m = 0, int y = 0);
        Fecha(const char*); //constructor de conversión
        Fecha(const Fecha&)=default;
       

        int dia() const noexcept;
        int mes() const noexcept;
        int anno() const noexcept;

        Fecha &operator =(const Fecha&) = default;
        Fecha& operator ++();
        Fecha& operator --();
        Fecha operator ++(int);
        Fecha operator --(int );
        Fecha operator +(int i) const;
        Fecha operator -(int i) const;
        Fecha& operator +=(int i);
        Fecha& operator -=(int i);
      
        //operator const char*() const;

        const char* cadena() const;

        static const int AnnoMinimo=1902, AnnoMaximo=2037;
       
  
     ~Fecha() = default;
   

      class Invalida{
          public:
              explicit Invalida(const char *f): cad(f){}
              const char *por_que() const;
          private:
              const char *cad;
      };
  
    private:
    void comprobar();
      int _d, _m, _y;

};


  bool operator ==(const Fecha&, const Fecha&) noexcept;
  bool operator !=(const Fecha&, const Fecha&) noexcept;
  bool operator <(const Fecha&, const Fecha&) noexcept;
  bool operator >(const Fecha&, const Fecha&) noexcept;
  bool operator <=(const Fecha&, const Fecha&) noexcept;
  bool operator >=(const Fecha&, const Fecha&) noexcept;

 std::istream &operator>>(std::istream &is, Fecha &f);
 std::ostream &operator<<(std::ostream &os, const Fecha &f) noexcept;
#endif
