#include <iostream>

const int MODULO = 1000000000;

class BigInt {
    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend std::ostream& operator<<(std::ostream& os, const BigInt& i);
    //friend BigInt operator/(const BigInt&, const BigInt&);
    //friend BigInt operator^(const BigInt&, const BigInt&);
    //friend BigInt operator%(const BigInt&, const BigInt&);
    //friend BigInt operator&(const BigInt&, const BigInt&);
    //friend BigInt operator|(const BigInt&, const BigInt&);
private:
    int size;
    int* big_int;
    bool is_positive;
public:
    BigInt();
    BigInt(long long number);
    BigInt(const std::string);
    BigInt(const BigInt&);
    BigInt(BigInt&&) noexcept;
    ~BigInt();

    // methods for tests
    int checkSize() const;
    int checkBigInt(int i);
    bool checkIsPositive() const;
    // end of methods

    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&) noexcept;

    //BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int);

    BigInt operator+() const;
    BigInt operator-() const;

    BigInt& operator-=(const BigInt&);
    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);

    //BigInt& operator/=(const BigInt&);
    //BigInt& operator^=(const BigInt&);
    //BigInt& operator%=(const BigInt&);
    //BigInt& operator&=(const BigInt&);
    //BigInt& operator|=(const BigInt&);

    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    //size_t size() const;  // size in bytes
};

