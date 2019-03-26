/*
** fecha.hpp
*/

#ifndef _FECHA_HPP_ //Si no está definida la macro, la define. Evita que la procese dos veces si hay dos archivos
#define _FECHA_HPP_

class Fecha(){
    public:
        Fecha();
        explicit Fecha(int d); //no se permite la conversión explícita
        Fecha(int d, int m);
        Fecha(int d, int m, int y);
        Fecha(const char*); //constructor de conversión
        Fecha(const Fecha);
        Fecha(const String);
        Fecha operator =(const Fecha&);
        Fecha operator ++();
        Fecha operator --();
        Fecha operator +(int i);
        Fecha operator -(int i);
        Fecha operator +=(int i);
        //Fecha operator -=(int i);
        Fecha operator ==(const Fecha&);
        //Fecha operator !=(const Fecha&);
        Fecha operator <(const Fecha&);
        Fecha operator >(const Fecha&);
        void stringCorrecto(String f);
        bool comprobacion(int, int, int );
        void fecha_sis(int, int, int);
        void asignacion(int, int, int);
        String diaSemana();
        String toString();

        inline void set_d(int d){_d=d;}
        inline void set_m(int m){_m=m;}
        inline void set_y(int y){_y=y;}

        inline int dia(){ return _d; }
        inline int mes(){ return _m; }
        inline int anno(){ return _y; }

        const int AnnoMinimo=1902, AnnoMaximo=2037;
        const String mes[12] = {"enero", "febrero", "marzo", "abril", "mayo", "julio",
        "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

  
    private:

};

#endif
