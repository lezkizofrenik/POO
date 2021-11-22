#include "cadena.hpp"
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>
 
/**
 * @file cadena.cpp
 * @author Carmen del Mar Ruiz de Celis
 * @date 5 May 2019
 * @copyright 2019 Carmen del Mar Ruiz de Celis
 */


// ###### destructor #######
Cadena::~Cadena() {
    delete[] s_; 
}

/* ###### CONSTUCTORES ##### */


Cadena::Cadena(size_t tam, const char c): s_(new char[tam +1]), tam_(tam){
    std::memset(s_, c, tam_);
    s_[tam_] = '\0';
    
}

// Constructor de copia
Cadena::Cadena(const Cadena& c): s_(new char[c.tam_ +1]), tam_(c.tam_){
    std::strcpy(s_, c.s_);
}

//Constructor a partir de una cadena de caracteres de bajo nivel

Cadena::Cadena(const char* c): s_(new char[std::strlen(c) +1]), tam_(std::strlen(c)){
    std::strcpy(s_, c);
}

//Constructor de movimiento
Cadena::Cadena(Cadena &&c): s_(c.s_), tam_(c.tam_){
    c.s_ = nullptr;
    c.tam_ = 0;
}

Cadena Cadena::substr(size_t begindex, size_t len) const {
  if (begindex >= tam_ || begindex + len > tam_ || begindex + len < begindex)
    throw std::out_of_range("Error de rango");

  Cadena aux(len);
  std::strncpy(aux.s_, s_ + begindex, len);
  aux.s_[len] = '\0';
  return aux;
}

Cadena Cadena::toupper(){
  Cadena aux(*this);
  for(int i = 0; i < aux.tam_; i++){
    if(aux.s_[i] >= 97 && aux.s_[i] <=122) aux.s_[i] -= 32;
  }
  return aux;
}


/* ###### OPERADORES ##### */

Cadena& Cadena::operator = (const Cadena& c){
   if(this != &c){
    tam_ = c.tam_;
    delete[] s_; 
    s_ = new char[tam_ + 1];
    std::strcpy(s_, c.s_);
   }
    return *this;
}


Cadena& Cadena::operator = (const char* c){
    tam_ = std::strlen(c);
    delete[] s_;
     s_ = new char[tam_ + 1];
     std::strcpy(s_, c);
     return *this;
}


Cadena& Cadena::operator = (Cadena &&c){
    if(this != &c){
        tam_ = c.tam_;
        delete[] s_;
        s_ = c.s_;

        c.tam_ = 0;
        c.s_ = nullptr;
    }
   
     return *this;
}


Cadena operator+(const Cadena &cad1, const Cadena &cad2) {
  return Cadena(cad1) += cad2;
}


Cadena& Cadena::operator +=(const Cadena& c){
    Cadena aux(*this);
    delete[] s_;
    tam_ = aux.tam_ + c.tam_;
    s_ = new char[tam_];
    std::strcpy(s_, aux.s_);
    std::strcat(s_, c.s_);
    return *this;
}

   
bool operator <(const Cadena& c1, const Cadena& c2){
     return std::strcmp(c1.c_str(), c2.c_str()) < 0;
}


bool operator >(const Cadena& c1, const Cadena& c2){
     return !(c1 <= c2);
}


bool operator == (const Cadena& c1, const Cadena& c2){
    return std::strcmp(c1.c_str(), c2.c_str()) == 0;
}


bool operator != (const Cadena& c1, const Cadena& c2){
    return ! (c1 == c2);
}


bool operator <= (const Cadena& c1, const Cadena& c2){
    return (c1 < c2) || (c1 == c2);
}


bool operator >= (const Cadena& c1, const Cadena& c2){
    return (c1 > c2) || (c1 == c2);
}

// ###### ACCESO ######


const char Cadena::at(size_t i) const {
    if(i < 0 || i >= tam_) throw std::out_of_range("Error: Índice fuera de rango");
    return s_[i];
}


char& Cadena::at(size_t i){
    if(i < 0 || i >= tam_) throw std::out_of_range("Error: Índice fuera de rango");
    return s_[i];
}


const char Cadena:: operator [](size_t i) const noexcept{ return s_[i]; }


char& Cadena:: operator[](size_t i) noexcept{ return s_[i]; }



/* OPERADORES DE FLUJO */

std::ostream &operator<<(std::ostream &os, const Cadena &cad) noexcept {
  os << cad.c_str();
  return os;
}

std::istream &operator>>(std::istream &is, Cadena &cad) noexcept {
  char *tmp = new char[33];
  int i = 0;
  char aux;
  while (isspace(is.get()) && is.good()) {}
  is.unget();
  while (i < 32 && !isspace(is.peek()) && is.good() && is.peek() != '\n' &&
         is.peek() != '\0') {
    aux = is.get();
    if (is.good()) tmp[i++] = aux;
  }
  tmp[i] = '\0';
  cad = tmp;
  delete[] tmp;
  return is;
}
