#include "header.hpp"
namespace obliczenia {
    wymierna::wymierna(int l, int m) {
        if (m == 0) throw new dzielenie_przez_0();
        licz = l;
        mian = m;
        if (std::gcd(l, m) > 1) skroc();
    }

    int wymierna::getLicz() const noexcept {
        return licz;
    }

    int wymierna::getMian() const noexcept {
        return mian;
    }

    void wymierna::setLicz(int l) noexcept {
        licz = l;
    }

    void wymierna::setMian(int m) {
        if (m == 0) throw new dzielenie_przez_0();
        mian = m;
    }

    void wymierna::skroc() noexcept {
        int nwd = std::gcd(licz, mian);
        setLicz(licz / nwd);
        setMian(mian / nwd);
    }

    void wymierna::prettyPrint() noexcept {
        std::cout << licz << std::endl << "-" << std::endl << mian << std::endl;
    }

    wymierna operator+(const wymierna &wymierna1, const wymierna &wymierna2) noexcept {
        int nww = std::lcm(wymierna1.getMian(),wymierna2.getMian());
        int skalar = nww/wymierna1.getMian();
        int skalar2 = nww/wymierna2.getMian();
        return wymierna((wymierna1.getLicz() * skalar) + (wymierna2.getLicz() * skalar2), nww);
    }

    wymierna operator-(const wymierna &wymierna1, const wymierna &wymierna2) noexcept {
        int nww = std::lcm(wymierna1.getMian(),wymierna2.getMian());
        int skalar = nww/wymierna1.getMian();
        int skalar2 = nww/wymierna2.getMian();
        return wymierna((wymierna1.getLicz() * skalar) - (wymierna2.getLicz() * skalar2), nww);
    }

    wymierna operator*(const wymierna &wymierna1, const wymierna &wymierna2) noexcept {
        return wymierna(wymierna1.getLicz() * wymierna1.getLicz(), wymierna1.getMian() * wymierna1.getMian());
    }

    wymierna operator/(const wymierna &wymierna1, const wymierna &wymierna2) {
        if (wymierna1.getLicz() * wymierna1.getMian() == 0) throw new dzielenie_przez_0();
        return wymierna(wymierna1.getLicz() * wymierna1.getMian(), wymierna1.getMian() * wymierna1.getLicz());
    }

    wymierna operator!(const wymierna &wymierna1) {
        if (wymierna1.getLicz() == 0) throw new dzielenie_przez_0;
        return wymierna(wymierna1.getMian(), wymierna1.getLicz());
    }

    wymierna operator-(const wymierna &wymierna1) noexcept {
        return wymierna(-wymierna1.getLicz(), wymierna1.getMian());
    }

    wymierna::operator double() const {
        return ((double)licz/mian);
    }

    wymierna::operator int() const {
        return std::round(licz / mian);
    }

    std::ostream &operator<<(std::ostream &wyj, const wymierna &w) {
        std::string dec;
        std::map<int, int> mp;
        mp.clear();
        int l = abs(w.getLicz());
        int rem = l % w.getMian();
        int whole = l / w.getMian();
        std::string whole_output = std::to_string(whole);
        if(w.getLicz()<0){
            whole_output = "-" + whole_output;
        }
        while ((rem != 0)) {
            if ((mp.find(rem) != mp.end())){
                break;
            }
            mp[rem] = dec.length();
            rem = rem * 10;
            int res_part = rem / w.getMian();
            dec += std::to_string(res_part);
            rem = rem % w.getMian();
        }
        if (rem == 0) {
            return wyj << whole_output <<  "." << dec << "0";
        } else {
            return wyj << whole_output << "." << dec.substr(0, mp[rem]) << "(" << dec.substr(mp[rem]) << ")";
        }
    }

    wymierna wymierna::operator+=(const wymierna &wymierna2) noexcept {
        return *this = (*this + wymierna2);
    }

    wymierna wymierna::operator-=(const wymierna &wymierna2) noexcept {
        return *this = (*this - wymierna2);
    }

    wymierna wymierna::operator*=(const wymierna &wymierna2) noexcept {
        return *this = (*this * wymierna2);
    }

    wymierna wymierna::operator/=(const wymierna &wymierna2) {
        return *this = (*this / wymierna2);
    }
}