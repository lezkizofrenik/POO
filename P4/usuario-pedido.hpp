#ifndef USU_PED_HPP_
#define USU_PED_HPP_
 
#include <set>
#include <map>
#include <utility>
#include <iostream>
#include "usuario.hpp"
#include "pedido.hpp"


class Usuario_Pedido{
	public:
		typedef std::set<Pedido*> Pedidos;

		void asocia(Usuario& us, Pedido& pe);
		void asocia(Pedido& pe, Usuario& us);


		Pedidos pedidos(Usuario& us) const { return pedart_.at(&us);}
		Usuario* cliente(Pedido& pe) const { return artped_.find(&pe)->second;}
		

	private:
		std::map<Usuario*, Pedidos> pedart_;
		std::map<Pedido*, Usuario*> artped_;

};

inline void Usuario_Pedido::asocia(Usuario& us, Pedido& pe){
	pedart_[&us].insert(&pe);
	artped_[&pe] = &us;
}

inline void Usuario_Pedido::asocia(Pedido& pe, Usuario& us){
	asocia(us, pe);
}

#endif
