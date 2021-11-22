#include "pedido-articulo.hpp"
#include <iomanip>
 
LineaPedido::LineaPedido(double p, unsigned int c):p_vnt_(p), cant_vnt_(c){}

void Pedido_Articulo::pedir(Pedido& pe, Articulo& ar, double p, unsigned c){
	pedart_[&pe].insert(std::make_pair(&ar, LineaPedido(p, c)));
	artped_[&ar].insert(std::make_pair(&pe, LineaPedido(p, c)));
}

void Pedido_Articulo::pedir(Articulo& ar, Pedido& p, double pr, unsigned c){
	pedir(p,ar,pr,c);
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a){
	return artped_[&a];
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p){
	return pedart_[&p];
}


std::ostream& operator <<(std::ostream& os, const LineaPedido& lp){
	return os << std::fixed << std::setprecision(2) << lp.precio_venta() << ' ' << "€" << '\t' << lp.cantidad();	
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP){
	double total = 0;

	os << "PVP\tCantidad\t\tArticulo\n" << Cadena(80, '=') << "\n";
	for(auto c : IP){
		Articulo* pa = c.first;
		LineaPedido lp = c.second;

		total += pa->precio() * lp.cantidad();

		os << lp << "\t\t" << "[" << pa->referencia() << "] \"" << pa->titulo() << "\"\n";
	}

	os << Cadena(80, '=') << "\nTotal\t" << total << " €" << std::endl;

	return os;

}


std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pe){
	int total = 0;
	double p = 0;

	os << "[Pedidos: " << pe.size() << "]\n";
	os << "================================================================================\n";
	os << " PVP\tCantidad\tFecha de venta\n";
	os << "================================================================================\n";

	for(auto c : pe){
		Pedido* pp = c.first;
		LineaPedido lp = c.second;

		p += lp.precio_venta() * lp.cantidad();
		total += lp.cantidad(); 

		os << lp << "\t\t" << pp->fecha() << "\n";
	}

	os << "================================================================================\n";

	os << std::setprecision(2) << p << " €\t" << total << std::endl;

	return os;

}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
	
	double total = 0; 

	for(auto c: pedart_){
		Pedido* pe = c.first;
		ItemsPedido IP = c.second;

		if(pe->fecha() <= Fecha()){
			os << "Pedido núm." << pe->numero() << "\n";
			os << "Cliente: " << pe->tarjeta()->titular()->nombre() << "\t";
			os << "Fecha: " << pe->fecha() << "\n" << IP;
		}
		total += pe->total();

	}
	os <<  "TOTAL VENTAS\t "  << std::fixed << std::setprecision(2) << total << " €" << std::endl;

	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
	for(auto c: artped_){
		Articulo* pa = c.first;
		os << "Ventas de " << "[" << pa->referencia() << "] \"" << pa->titulo() << "\"\n" << c.second << "\n"; 
	}

	return os;
}
