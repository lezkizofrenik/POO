#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdexcept>
 
Fecha::Fecha(int d, int m, int y) : _d(d), _m(m), _y(y) {
  std::time_t t_c = std::time(nullptr);
  std::tm* t_d = std::localtime(&t_c);

  if (_d == 0) _d = t_d->tm_mday;
  if (_m == 0) _m = t_d->tm_mon + 1;
  if (_y == 0) _y = t_d->tm_year + 1900;
  comprobar();
}

Fecha::Fecha(const char* f) : _d(20), _m(20), _y(20) {
  int conta, contd, contm;

  int cad = sscanf(f, "%d/%d/%d", &contd, &contm, &conta);

  if (cad != 3) throw Invalida("Error formato dd/mm/aaaa ");
  else {
    Fecha a(contd, contm, conta);

    _d = a._d;
    _m = a._m;
    _y = a._y;
  }
}

const char* Fecha::Invalida::por_que() const {
  return cad;
}

void Fecha::comprobar() {
  int bisiesto =
      static_cast<int>(_y % 4 == 0 && (_y % 400 == 0 || _y % 100 != 0));
  int diam[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  diam[2] += bisiesto;

  if (_y < Fecha::AnnoMinimo || _y > Fecha::AnnoMaximo) throw Invalida("Año inválido");
  if (_m < 1 || _m > 12) throw Invalida("Mes inválido");
  if (_d < 1 || _d > diam[_m]) throw Invalida("Día inválido");
}

Fecha Fecha::operator++(int) {
  Fecha aux(*this);
  *this += 1;
  return aux;
}

Fecha& Fecha::operator++() {
  return * this += 1;
}

Fecha Fecha::operator--(int) {
  Fecha aux(*this);
  *this += -1;
  return aux;
}

Fecha& Fecha::operator--() {
  return * this += -1;
}

Fecha Fecha::operator+(int i) const {
  Fecha aux(*this);
  aux += i;
  return aux;
}

Fecha Fecha::operator-(int i) const {
  Fecha res(*this);
  res += -i;
  return res;
}

Fecha& Fecha::operator-=(int i) {
  return (*this += -i);
}

Fecha& Fecha::operator+=(int i) {
  if (i != 0) {
    tm f = {0};
    f.tm_mday = _d + i;
    f.tm_mon = _m - 1;
    f.tm_year = _y - 1900;
    mktime(&f);

    _d = f.tm_mday;
    _m = f.tm_mon + 1;
    _y = f.tm_year + 1900;

    comprobar();
  }

  return *this;
}

bool operator==(const Fecha& f1, const Fecha& f2) noexcept {
  return (f1.dia() == f2.dia() && f1.mes() == f2.mes() &&
          f1.anno() == f2.anno());
}

bool operator!=(const Fecha& f1, const Fecha& f2) noexcept {
  return !(f1 == f2);
}

bool operator<(const Fecha& f, const Fecha& f2) noexcept {
  if (f.anno() < f2.anno())
    return true;
  else if (f.anno() > f2.anno())
    return false;
  else if (f.mes() < f2.mes())
    return true;
  else if (f.mes() > f2.mes())
    return false;
  else
    return f.dia() < f2.dia();
}

bool operator>(const Fecha& f1, const Fecha& f2) noexcept {
  return (f2 < f1);
}

bool operator<=(const Fecha& f1, const Fecha& f2) noexcept {
  return (f1 < f2 || f1 == f2);
}

bool operator>=(const Fecha& f1, const Fecha& f2) noexcept {
  return (f2 < f1 || f1 == f2);
}

const char* Fecha::cadena() const {
  static char f[40];
  const char* DIASEM[] = {"domingo", "lunes",   "martes", "miércoles",
                          "jueves",  "viernes", "sábado"};
  const char* MES[] = {"enero",      "febrero", "marzo",     "abril",
                       "mayo",       "junio",   "julio",     "agosto",
                       "septiembre", "octubre", "noviembre", "diciembre"};

  tm fecha = {0};

  fecha.tm_year = anno() - 1900;
  fecha.tm_mon = mes() - 1;
  fecha.tm_mday = dia();

  mktime(&fecha);

  sprintf(f, "%s %d de %s de %d", DIASEM[fecha.tm_wday], fecha.tm_mday,
          MES[fecha.tm_mon], fecha.tm_year + 1900);

  return f;
}

inline int Fecha::dia() const noexcept {
  return _d;
}
inline int Fecha::mes() const noexcept {
  return _m;
}
inline int Fecha::anno() const noexcept {
  return _y;
}

std::istream& operator>>(std::istream& is, Fecha& f1) {
  char* fecha = new char[11];
  is.getline(fecha, 11);

  try {
    f1 = Fecha(fecha);
    delete[] fecha;

  } catch (Fecha::Invalida& e) {
    is.setstate(std::ios_base::failbit);
    throw e;
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, const Fecha& fecha) noexcept {
  os << fecha.cadena();
  return os;
}
