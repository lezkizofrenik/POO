#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"
 

// ########### AUTOR ###########

class Autor{
	public:

		Autor(const Cadena&, const Cadena&, const Cadena&)noexcept;

		Cadena nombre() const noexcept{return nom_;}
		Cadena apellidos() const noexcept{return apell_;}
		Cadena direccion() const noexcept{return dir_;}

	private:
		Cadena nom_, apell_, dir_;
};


// ########### ARTICULO ###########

class Articulo{

public:

	typedef std::set<Autor*> Autores;

	class Autores_vacios{};

	Articulo(const Autores&, const Cadena&, const Cadena&, const Fecha&, double);

	Cadena referencia() const { return ref_;}
	Cadena titulo() const { return titulo_;}
	Fecha f_publi() const { return publi_;}
	double precio() const { return precio_;}
	double& precio() { return precio_;}
	const Autores& autores() const {return autores_;};
	//stock
	virtual void impresion_especifica(std::ostream&) const = 0;
	virtual ~Articulo(){}
	
private:
	Cadena ref_, titulo_;	
	Fecha publi_; 	
	double precio_;

	const Autores autores_;
};

std::ostream& operator <<(std::ostream&, const Articulo&);


// ########### LIBRO DIGITAL ###########

class LibroDigital: public Articulo{
	public:
		LibroDigital(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);
		Fecha f_expir() const {return f_expir_;}
		void impresion_especifica(std::ostream&) const;

	private:
		const Fecha f_expir_;

};


// ########### ARTICULO ALMACENABLE ###########

class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& a, const Cadena& ref, const Cadena& t, const Fecha& pub, double pre, unsigned stk = 0): 
						Articulo(a, ref, t, pub, pre), stock_(stk){}
	unsigned stock() const {return stock_;};
	unsigned& stock() {return stock_;};

	virtual ~ArticuloAlmacenable(){}

protected:
	unsigned stock_;
	
};


// ########### LIBRO ###########

class Libro: public ArticuloAlmacenable{
	public:
		Libro(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned s = 0);
		const unsigned n_pag() const{return n_pag_ ;}
		void impresion_especifica(std::ostream&) const;

	protected:
		const unsigned n_pag_ ;
};


// ########### CEDERRON ###########

class Cederron: public ArticuloAlmacenable{
	public:
		Cederron(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned s = 0);
		const unsigned tam() const{ return tam_;}

		void impresion_especifica(std::ostream&) const;


	protected:
		const unsigned tam_;
};

#endif
