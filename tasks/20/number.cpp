#include "number.h"
#include <memory.h>


Number::Number()
{
    sign = '+';
    digits.push_back(0);
}

Number::~Number()
{
}


istream& operator>>(istream& stream, Number& number)
{
    string tmp;
    getline(stream, tmp ,'\n');
    if (tmp[0] == '+' || tmp[0] == '-')
    {
        number.sign = tmp[0];
        tmp.erase(tmp.begin());
    }
    number.digits.resize(tmp.size());

    for (size_t i = 0; i < tmp.size(); i++)
        number.digits[i] = tmp[tmp.size() - i - 1] - '0';
    return stream;
}

ostream& operator<<(ostream& stream, const Number& number)
{
    if (number.sign == '-')
        stream.put('-');
    for (int i = number.length() - 1; i >= 0; i--)
        stream.put(number.digits[i] + '0');
    return stream;
}

Number& Number::zero()
{
    static Number z;
    return z;
}

signed char& Number::operator[](unsigned int index)
{
    if (index >= length())
        digits.resize(index + 1);
    return digits[index];
}


Number Number::absAdd(const Number &operand) const
{
    Number result;
    result.digits.resize(max(length(), operand.length()));

    int carry = 0;
    for (size_t i = 0; i < result.length(); i++)
    {
        // add current digits
        if (length() < i)
            result.digits[i] =  operand.digits[i] + carry;
        else if (operand.length() < i)
            result.digits[i] = digits[i] + carry;
        else
            result.digits[i] = operand.digits[i] + carry + digits[i];

        // calculate carry
        carry = result.digits[i] / 10;
        result.digits[i] %= 10;
    }

    if (carry > 0)
        result.digits.push_back(carry);

    return result;
}


Number Number::absSub(const Number &operand) const
{
    Number result;
    result.digits.resize(length());

    int borrow = 0;

    for (size_t i = 0; i < length(); i++)
    {
        // substruct current digits
        result.digits[i] = digits[i] - borrow;
        if (operand.length() > i)
            result.digits[i] -= operand.digits[i];

        //calculate borrow
        borrow = 0;
        if (result.digits[i] < 0)
        {
            borrow = -result.digits[i]/10 + 1;
            result.digits[i] += borrow*10;
        }
    }

    // remove zeros
    int i = result.length() - 1;
    while (i > 0 && result[i] == 0)
        i--;

    result.digits.resize(i + 1);

    return result;
}


signed char Number::absCompare(const Number &operand) const
{
    if (length() > operand.length())
        return 1;
    if (length() < operand.length())
        return -1;

    // lengths are equal
    for (size_t i = 0; i < length(); i++)
    {
        if (digits[i] < operand.digits[i])
            return -1;

        if (digits[i] > operand.digits[i])
            return 1;
    }

    return 0;
}


signed char Number::compare(const Number &operand)
{
    if (sign == '+' && operand.sign == '+')
          return absCompare(operand);
    if (sign == '+' && operand.sign == '-')
      return 1;
    if (sign == '-' && operand.sign == '+')
      return -1;
    // sign= '-', operand.sign='-'
    return -absCompare(operand);
}


Number Number::operator+(const Number &operand)
{
    Number result;
    if (sign == operand.sign)
    {
        result = absAdd(operand);
        result.sign = sign;
        return result;
    }

    if (sign == '+') // operand.sign = '-'
    {
        if (absCompare(operand) >= 0)
            result = absSub(operand);
        else
        {
            result = operand.absSub(*this);
            result.sign = '-';
        }
        return result;
    }

    // sign = '-', operand.sign = '+'
    if (absCompare(operand) >= 0)
    {
        result = absSub(operand);
        result.sign = '-';
    }
    else
        result = operand.absSub(*this);

    return result;
}

Number Number::operator-(const Number &operand)
{
    Number result;
    if (sign != operand.sign)
    {
        result = absAdd(operand);
        result.sign = sign;
        return result;
    }

    if (sign == '-') // operand.sign = '-'
    {
        if (absCompare(operand) >= 0)
            result = absSub(operand);
        else
        {
            result = operand.absSub(*this);
            result.sign = '-';
        }
        return result;
    }

    // sign = '-', operand.sign = '+'
    if (absCompare(operand) >= 0)
    {
        result = absSub(operand);
        result.sign = '-';
    }
    else
        result = operand.absSub(*this);

    return result;
}

Number Number::operator*(const Number &operand)
{
    Number result;
    if (sign == operand.sign)
        result.sign = '+';
    else
        result.sign = '-';

    int carry = 0;
    //each digit of the first multiply with each one of the second
    for (size_t i = 0; i < length(); i++)
        for (size_t j = 0; j < operand.length(); j++)
        {
            carry += digits[i]*operand.digits[j];
            result[i+j] += carry % 10;
            carry /= 10;
        }

    while (carry > 0)
    {
        result.digits.push_back(carry%10);
        carry /= 10;
    }

    return result;
}

Number Number::operator/(const Number &operand)
{
    Number result;
    Number rest;

    result.digits.clear();

    for (int i = length() - 1; i >= 0; i--)
    {
        // add next digit to the rest
        if (rest != zero())
            rest.digits.insert(rest.digits.begin(), 1, digits[i]);
        else
            rest[0] = digits[i];

        int count = 0;
        // count how many times we can substract operand from the rest
        while (rest.absCompare(operand) >= 0)
        {
            rest = rest.absSub(operand);
            count++;
        }

        // add this number to the result
        result.digits.insert(result.digits.begin(), 1, count);
    }

    // remove zeros
    int i = result.length() - 1;
    while (i > 0 && result[i] == 0)
        i--;
    result.digits.resize(i + 1);

    if (sign == operand.sign || result == zero())
        result.sign = '+';
    else
        result.sign = '-';


    return result;
}


unsigned int Number::length() const
{
    return digits.size();
}

bool Number::operator !=(const Number &operand)
{
    return compare(operand) != 0;
}

bool Number::operator ==(const Number &operand)
{
    return compare(operand) == 0;
}

bool Number::operator <(const Number &operand)
{
    return compare(operand) < 0;
}

bool Number::operator <=(const Number &operand)
{
    return compare(operand) <= 0;
}

bool Number::operator >(const Number &operand)
{
    return compare(operand) > 0;
}

bool Number::operator >=(const Number &operand)
{
    return compare(operand) >= 0;
}
