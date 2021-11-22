#ifndef PED_AR_HPP_
#define PED_AR_HPP_
 
#include <iostream>
#include <map>
#include <utility>
#include "pedido.hpp"
#include "articulo.hpp"

class LineaPedido;
class Pedido;

struct OrdenaPedidos: public std::binary_function <Pedido*,Pedido*,bool>{
	bool operator()(const Pedido* p1, const Pedido* p2) const { return p1->numero() < p2->numero() ;};
};

struct OrdenaArticulos: public std::binary_function<Articulo*,Articulo*,bool>{
	bool operator()(const Articulo* a1, const Articulo* a2) const { return a1->referencia() < a2->referencia() ;};
};


class Pedido_Articulo{
	public:
		typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;

		void pedir(Pedido&, Articulo&, double, unsigned c = 1);
		void pedir(Articulo&, Pedido&, double, unsigned c = 1);

		ItemsPedido& detalle(Pedido&); 
		Pedidos ventas(Articulo&); 
		
		std::ostream& mostrarDetallePedidos(std::ostream&);
		std::ostream& mostrarVentasArticulos(std::ostream&);


	private:
		std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedart_;
		std::map<Articulo*, Pedidos, OrdenaArticulos> artped_;
};

class LineaPedido{

	public:
		explicit LineaPedido(double, unsigned int c = 1);
		double precio_venta() const {return p_vnt_;}
		size_t cantidad() const {return cant_vnt_;}

	private:
		double p_vnt_;
		unsigned cant_vnt_;
};

std::ostream& operator <<(std::ostream&, const LineaPedido&);
std::ostream& operator <<(std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator <<(std::ostream&, const Pedido_Articulo::Pedidos&);


#endif
