#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
 
int Pedido::ultped_ = 0;

Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& user,
               const Tarjeta& t, const Fecha& f)
    : num_(ultped_ + 1), tarjeta_(&t), fecha_(f), total_(0) {
  if (user.n_articulos() == 0) throw Vacio(user);
  if (t.titular() != &user) throw Impostor(user);
  if (t.caducidad() < f) throw Tarjeta::Caducada(t.caducidad());
  if (!t.activa()) throw Tarjeta::Desactivada();

  Usuario::Articulos carrito = user.compra();
  bool pedido_final_vacio = true;

  for (auto c : carrito) {
    Articulo* pa = c.first;
    unsigned int cantidad = c.second;
    if (ArticuloAlmacenable* const aa =
            dynamic_cast<ArticuloAlmacenable* const>(pa)) {
      if (aa->stock() < cantidad) {
        const_cast<Usuario::Articulos&>(user.compra()).clear();
        throw SinStock(*c.first);

      } else {
        double precio = aa->precio();
        aa->stock() -= cantidad;
        pe_art.pedir(*this, *aa, precio, cantidad);
        total_ += precio * cantidad;
        pedido_final_vacio = false;
      }

    } else {
      if (LibroDigital* const ld = dynamic_cast<LibroDigital* const>(pa)) {
        if (ld->f_expir() > f) {
          total_ += ld->precio() * cantidad;
          pe_art.pedir(*this, *ld, ld->precio(), cantidad);
          pedido_final_vacio = false;
        }
      } else
        throw std::logic_error(
            "Pedido::Pedido error, tipo de Articulo desconocido");
    }

    user.compra(*(c.first), 0);
  }  // for

  if (pedido_final_vacio) throw Vacio(user);
  us_pe.asocia(user, *this);
  ++ultped_;
}

std::ostream& operator<<(std::ostream& os, const Pedido& p) {
  os << "Núm. pedido: " << p.numero() << "\n";
  os << "Fecha:       " << std::setfill(' ') << std::setw(6) << p.fecha()
     << "\n";
  os << "Pagado con:  " << p.tarjeta()->tipo()
     << " n.º: " << p.tarjeta()->numero() << "\n";
  os << "Importe:" << std::setfill(' ') << std::setw(4) << p.total() << " €";
  return os;
}
