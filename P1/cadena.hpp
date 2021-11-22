#ifndef _CADENA_
#define _CADENA_
#include <iostream>
#include <ctime>
 

class Cadena{

    public:

        Cadena(size_t tam = 0, const char c = ' ');
        Cadena(const Cadena& c);
        Cadena(Cadena &&c);
        Cadena(const char* c);
        ~Cadena();
        

        const char at(size_t i) const;
        char& at(size_t i);
        const char operator [](size_t i) const noexcept;
        char& operator[](size_t i) noexcept;
        size_t length() const noexcept { return tam_; }
        const char *c_str() const noexcept { return s_; }
        Cadena substr(size_t, size_t) const;
        Cadena toupper();
        Cadena& operator += (const Cadena&)  ;
        Cadena& operator=(const Cadena&) ; 
	      Cadena& operator=(const char*) ; 
        Cadena& operator=(Cadena &&) ;  

        /* ITERADORES */
  using iterator = char *;
  using const_iterator = char const *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin() noexcept { return s_; }
  const_iterator begin() const noexcept { return s_; }
  const_iterator cbegin() const noexcept { return s_; }
  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  iterator end() noexcept { return s_ + tam_; }
  const_iterator end() const noexcept { return s_ + tam_; }
  const_iterator cend() const noexcept { return s_ + tam_; }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  } 
    private:

    char* s_;
    size_t tam_;

  
};

Cadena operator +(const Cadena& c1, const Cadena& c2);

bool operator <(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator == (const Cadena& c1, const Cadena& c2);
bool operator <= (const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);

/* OPERADORES DE FLUJO */
std::ostream &operator<<(std::ostream &os, const Cadena &cad) noexcept;
std::istream &operator>>(std::istream &is, Cadena &cad) noexcept;
/* HASH */
namespace std {
template <>
struct hash<Cadena> {
  size_t operator()(const Cadena &cad) const {
    return hash<std::string>{}(cad.c_str());
  }
};
}


#endif 
