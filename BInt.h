#ifndef BINT_H_INCLUDED
#define BINT_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <string>

class BInt {
public:
    typedef std::vector<uint32_t> data_type;
    BInt() { create(0); }
    BInt(int n) { create(n); }
    BInt(const data_type& dt) { create(dt); }
    BInt(const BInt& bi) { create(bi); }
    BInt(const std::string& si) { create(si); }
    BInt(const char* ci) { create(std::string(ci)); }
    explicit BInt(int n, int e) { create(n); pow(e); }
    explicit BInt(char *) {};
    ~BInt() {};

    const data_type& get_data() const { return data; }
    int get_sign() const { return sign; }
    void add_fast(const BInt& integer);

//    std::string toString();
    BInt operator+(const BInt& integer) const ;
    BInt operator-(const BInt& integer) const ;
//    BInt operator=(const BInt& integer);
//    friend ostream& operator<<(ostream& in, BInt& integer);
    void multiply(int n);
    void pow(int n);

    void print() const;
private:
    std::vector<uint32_t> data;
    int sign;
    void create(int n);
    void create(const data_type&);
    void create(const BInt&);
    void create(const std::string&);
    void destroy();
    BInt add(const data_type& t, const data_type& b) const;
    BInt sub(const data_type& t, const data_type& b) const;
};

void BInt::create(int n) {
    sign = 1;
    if(n < 0) {
        sign = -1;
        n = n * -1;
    }
    if(n >= 1000000000) {
        std::cerr << "Error: Number " << n << " is too large\n";
        exit(1);
    }
    data.push_back(n);
}

void BInt::create(const data_type& dt) {
    data = dt;
    return;
}

void BInt::create(const BInt& bi) {
    data = bi.data;
    sign = bi.sign;
    return;
}

void BInt::create(const std::string& si) {
    create(0);
    std::cout << "In string\n";
}

void BInt::destroy() {
}

void BInt::print() const {
    if(sign == -1) {
        printf("-");
    }
    printf("%lu", (long)data[data.size()-1]);
    for(int i = data.size() - 1; i; i--) {
        printf("%.9lu", (long)data[i-1]);
    }
    //putchar('\n');
    return;
}

/* Subtract operator override */
BInt BInt::operator-(const BInt& integer) const {
    int iSign = integer.get_sign();
    bool topIsBigger;
    BInt ret;

    // One num is negative, one is positive
    if((iSign < 0 && sign > 0) || (iSign > 0 && sign < 0)) {
        // Do a normal add here;
        ret = add(data, integer.get_data());
        ret.sign = sign;
    }
    // Both numbers are negative or positive
    else {
        data_type iData = integer.get_data();
        if(data.size() > iData.size()) {
            topIsBigger = true;
        }
        else if(data.size() < iData.size()) {
            topIsBigger = false;
        }
        else {
            topIsBigger = true; // Assume top is larger
            for(int x = data.size() - 1; x != -1; --x) {
                if(data[x] != iData[x]) {
                    topIsBigger = data[x] > iData[x];
                    break;
                }
            }
        }
        /* We now know what number is larger */
        if(topIsBigger) {
            ret = sub(data, integer.get_data());
            ret.sign = sign;
        }
        else {
            ret = sub(integer.get_data(), data);
            ret.sign = -iSign;
        }
    }
    return ret;
}

/* Addition operator override */
BInt BInt::operator+(const BInt& integer) const {
    int iSign = integer.get_sign();
    bool topIsBigger;
    BInt ret;

    /* Both numbers are positive or negative */
    if((iSign > 0 && sign > 0) || (iSign < 0 && sign < 0)) {
        // Do a normal add here;
        ret = add(data, integer.get_data());
        ret.sign = sign;
    }
    /* One number is positive, other is negative */
    else {
        data_type iData = integer.get_data();
        if(data.size() > iData.size()) {
            topIsBigger = true;
        }
        else if(data.size() < iData.size()) {
            topIsBigger = false;
        }
        else {
            topIsBigger = true; // Assume top is true
            for(int x = data.size() - 1; x != -1; --x) {
                if(data[x] != iData[x]) {
                    topIsBigger = data[x] > iData[x];
                    break;
                }
            }
        }
        /* We now know what number is larger */
        if(topIsBigger) {
            ret = sub(data, integer.get_data());
            if(sign < 0) {
                ret.sign = -1;
            }
            else {
                ret.sign = 1;
            }
        }
        else {
            ret = sub(integer.get_data(), data);
            if(iSign < 0) {
                ret.sign = -1;
            }
            else {
                ret.sign = 1;
            }
        }
    }
    return ret;
}

/* Add two vectors, don't worry about sign */
BInt BInt::add(const data_type& t, const data_type& b) const {
    uint32_t carry = 0;
    uint64_t val;
    size_t maxsize = std::max(t.size(), b.size());
    data_type num;

    for(size_t x = 0; x != maxsize; ++x) {
        int topNum = 0;
        int bottomNum = 0;
        if(x < t.size()) topNum = t[x];
        if(x < b.size()) bottomNum = b[x];

        val = topNum + bottomNum + carry;
        carry = val / 1000000000;
        val   = val % 1000000000;
        num.push_back(val);
    }
    if(carry > 0) {
        num.push_back(carry);
    }

    return BInt(num);
}

void BInt::add_fast(const BInt& integer) {
    uint32_t carry = 0;
    uint64_t val;
    size_t maxsize = std::max(data.size(), integer.data.size());
    //data_type num;

    for(size_t x = 0; x != maxsize; ++x) {
        int topNum = 0;
        int bottomNum = 0;
        if(x < data.size()) topNum = data[x];
        if(x < integer.data.size()) bottomNum = integer.data[x];

        val = topNum + bottomNum + carry;
        carry = val / 1000000000;
        val   = val % 1000000000;
        if(x >= data.size()) {
            data.push_back(val);
        }
        else {
            data[x] = val;
        }
    }
    if(carry > 0) {
        data.push_back(carry);
    }

    return;
}

/* Subtract two vectors, don't worry about sign, largest vector is */
/* always first */
BInt BInt::sub(const data_type& t, const data_type& b) const {
    uint32_t carry = 0;
    size_t maxsize = t.size();
    data_type num;

    for(size_t x = 0; x != maxsize; ++x) {
        int topNum = 0;
        int bottomNum = 0;
        topNum = t[x];
        if(x < b.size()) bottomNum = b[x];

        /* We had to borrow one from the next place */
        if(carry == 1) {
            /* Number is 0, we have to borrow again */
            if(topNum == 0) {
                carry = 1;
                topNum = 1000000000 - 1;
            }
            /* Number is more than zero, we are ok to borrow */
            else {
                carry = 0;
                --topNum;
            }
        }

        if(topNum >= bottomNum) {
            num.push_back(topNum - bottomNum);
        }
        else {
            carry = 1;
            topNum += 1000000000;
            num.push_back(topNum - bottomNum);
        }
    }
    for(size_t x = num.size() - 1; x >= 0; --x) {
        /* Remove leading zero elements */
        if(num[x] == 0) {
            num.pop_back();
        }
        else {
            break;
        }
    }
    if(num.size() == 0) {
        num.push_back(0);
    }

    return BInt(num);
}

/*
std::string BInt::toString() {
    std::string ret;
    if(sign == -1) {
        printf("-");
    }
    printf("%lu", (long)data[data.size()-1]);
    for(int i = data.size() - 1; i; i--)
        printf("%.9lu", (long)data[i-1]);
    putchar('\n');
}

ostream& operator<<(ostream& in, BInt& integer) {
in << integer.toString();

return in;
}
*/
void BInt::pow(int n) {
    int num = data[0];
    for(int x = 0; x != n - 1; ++x) {
        multiply(num);
    }
    return;
}

void BInt::multiply(int n) {
    uint32_t carry = 0;
    if(n >= 1000000000) {
        std::cout << "Num too large: " << n << "\n";
        exit(1);
    }
    for(std::vector<uint32_t>::size_type x = 0; x != data.size(); ++x) {
        uint64_t tmp = n * (uint64_t)data[x] + carry;
        data[x] = tmp % 1000000000;
        carry =   tmp / 1000000000;
    }
    if(carry) {
        data.push_back(carry);
    }
}

#endif
