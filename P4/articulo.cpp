#include <iostream>
#include <iomanip>
#include "articulo.hpp"

using namespace std;
 
Autor::Autor(const Cadena& nom, const Cadena& ape, const Cadena& dir) noexcept
    : nom_(nom),
      apell_(ape),
      dir_(dir) {}

Articulo::Articulo(const Autores& a,
                   const Cadena& ref,
                   const Cadena& t,
                   const Fecha& pub,
                   double pre)
    : ref_(ref), titulo_(t), publi_(pub), precio_(pre), autores_(a) {
  if (a.size() == 0)
    throw Autores_vacios();
}

Libro::Libro(const Autores& a,
             const Cadena& ref,
             const Cadena& t,
             const Fecha& pub,
             double pre,
             unsigned npags,
             unsigned stock)
    : ArticuloAlmacenable(a, ref, t, pub, pre, stock), n_pag_(npags) {}

std::ostream& operator<<(std::ostream& os, const Articulo& A) {
  auto i = A.autores().begin();
  os << "[" << A.referencia() << "] \"" << A.titulo() << "\", de ";
  os << (*i)->apellidos();

  for (++i; i != A.autores().end(); i++)
    os << ", " << (*i)->apellidos();

  os << ". ";
  os << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
     << A.precio() << " €"
     << "\n\t";

  A.impresion_especifica(os);

  return os;
}

Cederron::Cederron(const Autores& a,
                   const Cadena& ref,
                   const Cadena& t,
                   const Fecha& pub,
                   double pre,
                   unsigned tam,
                   unsigned stock)
    : ArticuloAlmacenable(a, ref, t, pub, pre, stock), tam_(tam) {}

LibroDigital::LibroDigital(const Autores& a,
                           const Cadena& ref,
                           const Cadena& t,
                           const Fecha& pub,
                           double pre,
                           const Fecha& f_expir)
    : Articulo(a, ref, t, pub, pre), f_expir_(f_expir) {}

void LibroDigital::impresion_especifica(std::ostream& os) const {
  os << "A la venta hasta el " << f_expir_ << ".";
}

void Libro::impresion_especifica(std::ostream& os) const {
  os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const {
  os << tam_ << " MB, " << stock_ << " unidades.";
}
