#ifndef _E1_
#define _E1_

#include <iostream>
#include <ctime>

using namespace std;

time_t t_c = time(nullprt);
tm* t_d = localtime(&t_c);




class Fecha{
    public:
    /*
    Fecha(int d, int m, int y): _d(d), _m(m), _y(y){}
    Fecha(int m, int y): _m(m), _y(y){}
    Fecha(int d): _d(d){}
    Fecha(){}
    Fecha(const Fecha f){
        _d=f->d;
        _m=f->m;
        _y=f->y;
    }
    */
   int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Fecha(int d, int m, int y){
      asignacion(d, m, y);
    }

    Fecha(int d, int m){
      asignacion(d, m, 0);
    }

    explicit Fecha(int d){
      asignacion(d, 0, 0);
    }

    Fecha(){
      asignacion(0, 0, 0);
    }

    Fecha(const Fecha& f){
          _d=f->get_d();
          _m=f->get_m();
          _y=f->get_y();
    }

    Fecha(const String f){
      stringCorrecto(f);
    }

    Fecha& operator =(const Fecha &f){

      _d = f->get_d();
      _m = f->get_m();
      _y = f->get_y();
    }

//corregir
    Fecha& operator ++(){
      int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
      if(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0)) v[1]++;

      if(_d == v[_m-1])
      {
        _d=1;
        if(_m == 12){
          _y++;
          _m=1;
        }
        else _m++;
      }
      else _d++;
    }

//corregir
    Fecha& operator --(){
      int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
      if(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0)) v[1]++;

      if(_d == 1)
      {
        _d=v[_m-2];
        if(_m == 1){
          _y--;
          _m=12;
        }
        else _m--;
      }
      else _d--;
    }

    Fecha& operator +(const Fecha &f, int i){
      Fecha res = f;
      int d = f->get_d(), m = f->get_m(), y = f->get_y();
      //int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
      if(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0)) res.v[1]++;

      if(d + i > res.v[_m-1])
      {
        res.set_d((d + i) - res.v[m-1]);
        if(m == 12){
          res.set_m(1);
          res.set_y(y+1);
        }
        else res.set_m(m+1);
      }
      else res.set_d(d += i);

      return res;
    }

    /*Fecha& operator -(int i){
      int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
      if(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0)) v[1]++;

      if(_d - i < 1)
      {

        if(_m == 1){
          _m=12;
          _y--;
        }
        else _m--;
        _d = (_d + v[m-1]) - i;
      }
      else _d -= i;
    }
    */

    Fecha& operator -(const Fecha &f, int i){
      Fecha res = f;
      int d = f->get_d(), m = f->get_m(), y = f->get_y();

      int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
      if(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0)) v[1]++;

      if(d - i < 1)
      {

        if(m == 1){
          res.set_m(12);
          res.set_y(y-1);
        }
        else res.set_m(m-1);
        res.set_d(d + res.v[m-1]) - i);
      }
      else _d -= i;
    }

    Fecha& operator +=(const Fecha &f, int i){
      Fecha aux = f;
      return aux + i;
    }

    /*Fecha& operator -=(int i){
      this.Fecha = this.Fecha - i;
    }*/

    bool operator ==(Fecha f){
      if(_y == f->get_y() && _m== f->get_m() && _d == d->get_d()) return true;
      else return false;
    }


    /*Fecha& operator !=(Fecha f){
      if(_y != f->get_y() || _m != f->get_m() || _d != d->get_d()) return true;
      else return false;
    }*/

    bool operator <(const Fecha &f){

      int y = f->get_y();
      int m = f->get_m();
      int d = f->get_d();

    if(this.Fecha == f) return false;
    else{
      if(_y < y) return true;
      else if(_y == y){
        if(_m < m) return true;
        else if(_m == m){
          if (_d < d) return true;
          else return false;
        }
        else return false;
      }
      else return false;
    }
}

bool operator >(const Fecha &f){

  int y = f->get_y();
  int m = f->get_m();
  int d = f->get_d();

if(this.Fecha == f) return false;
else{
  if(_y > y) return true;
  else if(_y == y){
    if(_m > m) return true;
    else if(_m == m){
      if (_d > d) return true;
      else return false;
    }
    else return false;
  }
  else return false;
}
}


      //Comprueba si el formato de la fecha es correcto
      void stringCorrecto(String f){

        int id, im, iy;
        string d, m, y
        size_t foud2, found = f.find('/');

        if (found != string::npos){  // Si encuentra el primer '/', busca el siguiente
          found2 = f.find('/', found+1);
          if (found2 != string::npos){ //Si lo encuentra, convierte el string en int

            for(int i=0; i<found; i++)  d += f[i];
            for(int i=found+1; i<found2; i++) m += f[i];
            for(int i= found 2; i<f.size(); i++) y += f[i];

            id= stroi(d);
            im= stroi(m);
            iy= stroi(y);

            if(comprobacion(id, im, iy)){ //Comprueba si los numeros introducidos son correctos
              asignacion(id, im, iy); // Comprueba si hay 0 y asigna los valores
            }
          }

        }
      }

      bool comprobacion(int d, int m, int y){
        bool aux = true;
        int v[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
        if(y<Fecha::AnnoMinimo || y>Fecha::AnnoMaximo){
          cout << "Año introducido incorrecto: " << y << endl;
          aux = false;
        }
        if(y % 4 == 0 && (y % 400 == 0 || y % 100 != 0)) v[1]++;
        if(m<0&&m>12){
          cout << "Mes introducido incorrecto: " << m << endl;
          aux = false;
        }
        else{
           if(d>0&&d<=v[_m-1]) _d=d;
           else{
             cout << "Dia introducido incorrecto: " << d << endl;
             aux = false;
           }
        }
        return aux;
      }


      void fecha_sis(int d, int m, int y){
        if(d==0) _d=t_d->tm_mday;
        if(m==0) _d=t_d->tm_mon+1;
        if(y==0) _d=t_d->tm_myear + 1900;
      }

      void asignacion(int d, int m, int y){
        if(comprobacion(d, m, y)) fecha_sis(d, m, y);
        else cout << "Error: \n" << endl;
      }



      String diaSemana(){
        const String DiaSemana[7] = {"lunes", "martes", "miércoles", "jueves", "viernes"
        "sábado", "domingo"};
        n = ((14 - Mes) \ 12)
        int y = (_y - n)
        int m = (_m + (12 * n) - 2)
        return DiaSemana(((_d + y + (y \ 4) - (y\ 100) + (y \ 400) + ((31 * m) \ 12)) % 7))

      }

      String toString(){
        cout << diaSemana() << "de" << mes[_m] << "de" << _y << endl;
      }



    private:
      int _d, _m, _y;
};

#endif _E1_
