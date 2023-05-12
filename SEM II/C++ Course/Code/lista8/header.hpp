#ifndef UNIVERSITY_HEADER_HPP
#define UNIVERSITY_HEADER_HPP
// Piotr Stachowicz lista 8
#include <iostream>
#include <map>
#include <exception>
#include <cmath>
#include <numeric>
#include <vector>
namespace obliczenia {
    class wymierna {
    private:
        int licz, mian;
    public:
        wymierna(int l = 0, int m = 1);
        int getLicz() const noexcept;
        int getMian() const noexcept;
        void setLicz(int l) noexcept;
        void setMian(int m);
        void skroc() noexcept;
        wymierna operator+= (const wymierna &wymierna2) noexcept;
        wymierna operator-= (const wymierna &wymierna2) noexcept;
        wymierna operator*= (const wymierna &wymierna2) noexcept;
        wymierna operator/= (const wymierna &wymierna2);
        friend wymierna operator+(const wymierna &wymierna1, const wymierna &wymierna2) noexcept;
        friend wymierna operator-(const wymierna &wymierna1, const wymierna &wymierna2) noexcept;
        friend wymierna operator*(const wymierna &wymierna1, const wymierna &wymierna2) noexcept;
        friend wymierna operator/(const wymierna &wymierna1,  const wymierna &wymierna2);
        friend wymierna operator-(const wymierna &wymierna1) noexcept;
        friend wymierna operator!(const wymierna &wymierna1);
        operator double() const;
        operator int() const;
        void prettyPrint() noexcept;
        friend std::ostream &operator<<(std::ostream &wyj, const wymierna &w);
    };
    class wyjatek_wymierny : std::logic_error {
    public:
        wyjatek_wymierny(const std::string &what_arg) : std::logic_error(what_arg) {}
    };
    class przekroczenie_zakresu : wyjatek_wymierny {
    public:
        przekroczenie_zakresu() : wyjatek_wymierny("Przekroczenie zakresu!") {}
    };
    class dzielenie_przez_0 : wyjatek_wymierny {
    public:
        dzielenie_przez_0() : wyjatek_wymierny("Dzielenie przez 0!") {}
    };
}
#endif //UNIVERSITY_HEADER_HPP