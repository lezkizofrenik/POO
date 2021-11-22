#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <iostream>
#include <utility>
#include <iomanip>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
 

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
	public:

		Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& fp = Fecha());

		int numero() const { return num_;}
		const Tarjeta* tarjeta() const { return tarjeta_;}
		Fecha fecha() const { return fecha_;}
		double total() const { return total_;}
		static int n_total_pedidos() { return ultped_;}


		class Vacio{
			public:
				Vacio(Usuario& user): user_(&user){}
				Usuario& usuario() const {return *user_;}
			private:
				Usuario* user_;
		};

			

		class Impostor{
			public:
				Impostor(Usuario& user):user_(&user){}
				Usuario& usuario() const {return *user_;}
			private:
				Usuario* user_;
		};

			

		class SinStock{
			public:
				SinStock(Articulo& art):art_(&art){}
				Articulo& articulo() const {return *art_;}
			private:
				Articulo* art_;
		};



	private:
		
		int num_;
		const Tarjeta* tarjeta_;
		Fecha fecha_;
		double total_;
		static int ultped_;
};

std::ostream& operator <<(std::ostream&, const Pedido&);

#endif
