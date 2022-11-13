#include "BigInt.h"
#include <iostream>
#include <cstring>
#include <string>

const int MODULO = 1000000000;

void do_swap(char* buff, int size) {
    for (int i = 0, j = size - 1; i < size / 2; ++i, --j)
        std::swap(buff[i], buff[j]);
}

BigInt::BigInt() : size{ 0 }, big_int{ nullptr }, is_positive{ true } {} // a standard constructor

BigInt::BigInt(long long number) { // parsing the integer number into digits

    long long tmp = number;

    size = (number == 0) ? 1 : 0;

    // initializing the "size"
    while (tmp) {
        tmp /= MODULO;
        size++;
    }

    big_int = new int[size];

    // initializing the "is_positive"
    if (number < 0) {
        number = -number;
        is_positive = false;
    }
    else if (number == 0) {
        is_positive = true;
        big_int[0] = 0;
    }
    else
        is_positive = true;

    // initializing the "big_int"
    int next = 0;
    while (number) {
        big_int[next++] = static_cast<int>(number % MODULO);
        number /= MODULO;
    }
}

BigInt::BigInt(const std::string& str_number) { // parsing the string into digits

    if (str_number.length() == 0) throw std::invalid_argument{ "Empty string" };

    size_t len = (str_number[0] != '-') ? str_number.length() : str_number.length() - 1;

    size = static_cast<int>((len % 9 == 0) ? len / 9 : (len / 9) + 1);
    big_int = new int[size];
    is_positive = true;

    const int BUFFSIZE = 9;

    int stop = 0; // in case we have a negative number

    if (str_number[0] == '-') {
        is_positive = false;
        stop++;
    }
    else if (str_number[0] > '9' || str_number[0] < '0')
        throw std::invalid_argument{ "Invalid argument" };

    char* buff = new char[BUFFSIZE];
    std::fill(buff, buff + BUFFSIZE, '\0');

    int index = 0, next = 0;

    for (auto i = static_cast<long long>(len - ((str_number[0] != '-') ? 1 : 0)); i >= stop; i--) {
        if (str_number[i] <= '9' && str_number[i] >= '0') {
            buff[index++] = str_number[i];
            if (index == BUFFSIZE) {
                index = 0;
                do_swap(buff, BUFFSIZE);
                big_int[next++] = strtol(buff, nullptr, 0);
                std::fill(buff, buff + BUFFSIZE, '\0');
            }
        }
        else
            throw std::invalid_argument{ "Invalid argument" };
    }

    if (index) {
        buff[index] = '\0';
        do_swap(buff, index);
        big_int[next] = strtol(buff, nullptr, 0);
    }

    delete[] buff;
}

BigInt::BigInt(const BigInt& other) :
        size{ other.size },
        big_int{ new int[size] },
        is_positive{ other.is_positive } { // copying the "other" number to the "this" number
    memcpy(big_int, other.big_int, size * sizeof(int));
}

BigInt::BigInt(BigInt&& other) noexcept :
        size{ other.size },
        big_int{ other.big_int },
        is_positive{ other.is_positive } { // copying the "other" number to the "this" number and deleting "other"
    other.big_int = nullptr;
}

BigInt::~BigInt() { delete[] big_int; } // destructor

int BigInt::checkSize() const { return size; }

int BigInt::checkBigInt(int i) { return big_int[i]; }

bool BigInt::checkIsPositive() const { return is_positive; }

BigInt& BigInt::operator=(const BigInt& other) { // implementation of the assignment operator
    delete[] big_int;

    size = other.size;

    big_int = new int[size];
    memcpy(big_int, other.big_int, size * sizeof(int));

    is_positive = other.is_positive;

    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept { // implementation of the assignment operator
    delete[] big_int;

    size = other.size;
    big_int = other.big_int;
    is_positive = other.is_positive;

    other.big_int = nullptr;

    return *this;
}

BigInt& BigInt::operator++() { return (*this += (1)); } // right increment

const BigInt BigInt::operator++(int) { // left increment
    const BigInt new_object = *this;
    *this += (1);
    return new_object;
}

BigInt& BigInt::operator--() { return (*this -= (1)); } // right decrement

const BigInt BigInt::operator--(int) { // left decrement
    const BigInt new_object = *this;
    *this -= (1);
    return new_object;
}

BigInt BigInt::operator+() const { // unary +
    return *this;
}

BigInt BigInt::operator-() const { // unary -
    BigInt result = *this;
    result.is_positive = !is_positive;
    return *this;
}

BigInt& BigInt::operator+=(const BigInt& other) { // adding "other" to "this"

    if ((is_positive && other.is_positive) || (!is_positive && !other.is_positive)) {

        int carry = 0;

        int max = std::max(size, other.size);
        int* buff = new int[max + 1]; // additional array
        std::fill(buff, buff + (max + 1), '\0');

        int stop = (other.size > size) ? size : other.size;
        int i = 0;

        for (; i < stop; i++) {
            long tmp = carry + big_int[i] + other.big_int[i];
            buff[i] = tmp % MODULO;
            carry = tmp / MODULO;
        }

        while (i != max) {
            long tmp = carry + ((other.size > size) ? other.big_int[i] : big_int[i]);
            buff[i] = tmp % MODULO;
            carry = tmp / MODULO;
            i++;
        }

        if (carry)
            buff[i] = carry;

        if (buff[i] != 0)
            size = max + 1;
        else
            size = max;

        delete[] big_int;
        this->big_int = new int[size];
        memcpy(big_int, buff, size * sizeof(int));
    }
    else if (!is_positive && other.is_positive) {
        BigInt tmp = other;
        is_positive = true;
        tmp -= *this;
        *this = tmp;
    }
    else {
        BigInt tmp = other;
        tmp.is_positive = true;
        *this -= tmp;
    }

    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) { // subtracting from "this" "other"
    bool is_this_first = true; // 1 : this - other; 0 : other - this

    if (!is_positive && other.is_positive) {
        is_positive = true;
        *this += other;
        is_positive = false;
        return *this;
    }
    else if (is_positive && !other.is_positive) {
        is_positive = false;
        *this += other;
        is_positive = true;
        return *this;
    }
    else if (!is_positive && !other.is_positive) {
        if (*this > other) {
            is_positive = true;
            is_this_first = false;
        }
        else if (*this == other) {
            is_positive = true;
            is_this_first = true;
        }
    }
    else {
        if (*this < other) {
            is_positive = false;
            is_this_first = false;
        }
        else if (*this == other) {
            is_positive = true;
            is_this_first = true;
        }
    }

    int carry = 0;

    int max = std::max(size, other.size);
    int* buff = new int[max]; // additional array
    std::fill(buff, buff + max, '\0');

    int stop = (other.size > size) ? size : other.size;
    int i = 0;

    if (is_this_first)
        for (; i < stop; i++) {
            long tmp = (MODULO + big_int[i]) - (carry + other.big_int[i]);
            buff[i] = tmp % MODULO;
            carry = (tmp >= MODULO) ? 0 : 1;
        }
    else
        for (; i < stop; i++) {
            long tmp = (MODULO + other.big_int[i]) - (carry + big_int[i]);
            buff[i] = tmp % MODULO;
            carry = (tmp >= MODULO) ? 0 : 1;
        }

    while (i != max) {
        long tmp = MODULO  + ((other.size > size) ? other.big_int[i] : big_int[i]) - carry;
        buff[i++] = tmp % MODULO;
        carry = (tmp >= MODULO) ? 0 : 1;
    }
    i--;

    while (buff[i] == 0 && i > 0) i--;

    size = static_cast<int>(i + 1);

    delete[] big_int;
    this->big_int = new int[size];
    memcpy(big_int, buff, size * sizeof(int));

    return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    int carry = 0;
    int i = 0;
    unsigned long long cur;

    int* buff = new int[(size * other.size) + 1]; // additional array
    std::fill(buff, buff + ((size * other.size) + 1), '\0');

    while (i < size) {
        int j = 0;
        while (j < other.size || carry) {
            if (j < other.size)
                cur = static_cast<long long>(buff[i + j])
                      + static_cast<long long>(big_int[i]) * static_cast<long long>(other.big_int[j])
                      + static_cast<long long>(carry);
            else
                cur = static_cast<long long>(buff[i + j])
                      + static_cast<long long>(carry);
            buff[i + j] = static_cast<int>(cur % MODULO);
            carry = static_cast<int>(cur / MODULO);
            j++;
        }
        i++;
    }

    if ((!is_positive && !other.is_positive)
        || (other.size == 1 && other.big_int[0] == 0))
        is_positive = true;
    else if (is_positive && !other.is_positive)
        is_positive = false;


    i = size * other.size;

    while (buff[i] == 0 && i > 0) i--;

    size = i + 1;

    delete[] big_int;
    this->big_int = new int[size];
    memcpy(big_int, buff, size * sizeof(int));

    delete[] buff;

    return *this;
}


//BigInt& operator/=(const BigInt&);

//BigInt& operator^=(const BigInt&);

//BigInt& operator%=(const BigInt&);

//BigInt& operator&=(const BigInt&);

//BigInt& operator|=(const BigInt&);

bool BigInt::operator==(const BigInt& other) const { // comparing two number for equality
    if (is_positive == other.is_positive) {
        if (other.size > size || other.size < size)
            return false;
        else
            for (int i = 0; i < size; i++)
                if (big_int[i] != other.big_int[i])
                    return false;
        return true;
    }
    else
        return false;
}

bool BigInt::operator!=(const BigInt& other) const { // comparing two number for inequality
    if (operator==(other))
        return false;
    return true;
}

bool BigInt::operator<(const BigInt& other) const { // checking if the "other" is greater than the "this"
    if ((!is_positive && other.is_positive)
        || (is_positive && other.is_positive && other.size > size)
        || (!is_positive && !other.is_positive && other.size < size))
        return true;
    else if ((is_positive && !other.is_positive)
             || (operator==(other))
             || (is_positive && other.is_positive && other.size < size)
             || (!is_positive && !other.is_positive && other.size > size))
        return false;
    else
        for (int i = size - 1; i >= 0; i--) {
            if ((big_int[i] > other.big_int[i] && is_positive && other.is_positive)
                || (big_int[i] < other.big_int[i] && !is_positive && !other.is_positive))
                return false;
            else if ((big_int[i] < other.big_int[i] && is_positive && other.is_positive)
                     || (big_int[i] > other.big_int[i] && !is_positive && !other.is_positive))
                return true;
            else
                continue;
        }
    return false;
}

bool BigInt::operator>(const BigInt& other) const { // checking if the "other" is less than the "this"
    if (!(*this == other) && !(*this < other))
        return true;
    return false;
}

bool BigInt::operator>=(const BigInt& other) const { // checking if the "other" is greater than or equal to the "this"
    if (*this == other || !(*this < other))
        return true;
    return false;
}

bool BigInt::operator<=(const BigInt& other) const { // checking if the "other" is less than or equal to the "this"
    if (*this == other || !(*this > other))
        return true;
    return false;
}

BigInt::operator int() const {
    return big_int[0];
}

BigInt::operator std::string() const {

    int tmp = big_int[size - 1];
    int count = (big_int[size - 1] == 0) ? 1 : 0;
    while (tmp > 0) {
        tmp = tmp / 10;
        count++;
    }

    std::string buff((size - 1) * 9 + count, '\0');

    int start = 0; // for the second cycle

    std::string str_num;

    for (int i = 0; i < size; i++) {

        if (i != 0) {
            for (int g = 10; g <= MODULO; g *= 10)
                if (big_int[size - i - 1] < g) {

                    str_num = "000000000";
                    int l = static_cast<int>(str_num.length()) - 1;

                    std::string help = std::to_string(big_int[size - i - 1]);
                    int j = static_cast<int>(help.length()) - 1;

                    for (; j >= 0; j--, l--)
                        str_num[l] = help[j];

                    break;
                }
        }
        else
            str_num = std::to_string(big_int[size - i - 1]);

        int length = static_cast<int>(str_num.length());
        for (int j = start, k = 0; j < length + start; j++, k++)
            buff[j] = str_num[k];

        start += static_cast<int>(str_num.length());
    }
    if (!is_positive)
        buff.insert(0, "-");
    return buff;
}

//size_t size() const;  // size in bytes

BigInt operator+(const BigInt& first, const BigInt& second) { // first + second
    BigInt tmp = first;
    return (tmp += second);
}

BigInt operator-(const BigInt& first, const BigInt& second) { // first - second
    BigInt tmp = first;
    return (tmp -= second);
}

BigInt operator*(const BigInt& first, const BigInt& second) { // first * second
    BigInt tmp = first;
    return (tmp *= second);
}

//BigInt operator/(const BigInt& first, const BigInt& second) {
//	BigInt tmp = first;
//	return (tmp /= second);
//}
//
//BigInt operator^(const BigInt& first, const BigInt& second) {
//	BigInt tmp = first;
//	return (tmp ^= second);
//}
//
//BigInt operator%(const BigInt& first, const BigInt& second) {
//	BigInt tmp = first;
//	return (tmp %= second);
//}
//
//BigInt operator&(const BigInt& first, const BigInt& second) {
//	BigInt tmp = first;
//	return (tmp &= second);
//}
//
//BigInt operator|(const BigInt& first, const BigInt& second) {
//	BigInt tmp = first;
//	return (tmp |= second);
//
//BigInt BigInt:: operator~() const {}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
    return o << i.operator std::string();
}
