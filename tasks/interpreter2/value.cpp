#include "value.h"

namespace interpreter
{

Value Value::operator -()
{
    Value res;
    if (type == valError)
        return *this;
    if (type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != valNumber) {
        res.str_val = "no operator '-' for this type";
        res.type = valError;
        return res;
    }
    return Value(-numb_val);
}
Value Value::operator !()
{
    Value res;
    if (type == valError)
        return *this;
    if (type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != valNumber) {
        res.str_val = "no operator '!' for this type";
        res.type = valError;
        return res;
    }
    return Value(!numb_val);
}
Value Value::operator +(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valString)
        return Value(this->str_val + b.str_val);
    if (type == valNumber)
        return Value(this->numb_val + b.numb_val);
    res.str_val = "no operator '+' for this type";
    res.type = valError;
    return res;
}
Value Value::operator -(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val - b.numb_val);
    res.str_val = "no operator '-' for this type";
    res.type = valError;
    return res;
}
Value Value::operator *(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val * b.numb_val);
    res.str_val = "no operator '*' for this type";
    res.type = valError;
    return res;
}
Value Value::operator /(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val / b.numb_val);
    res.str_val = "no operator '/' for this type";
    res.type = valError;
    return res;
}

Value Value::operator >(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val > b.numb_val);
    res.str_val = "no operator '>' for this type";
    res.type = valError;
    return res;
}
Value Value::operator >=(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val >= b.numb_val);
    res.str_val = "no operator '>=' for this type";
    res.type = valError;
    return res;
}

Value Value::operator <(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val < b.numb_val);
    res.str_val = "no operator '<' for this type";
    res.type = valError;
    return res;
}

Value Value::operator <=(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valNumber)
        return Value(this->numb_val <= b.numb_val);
    res.str_val = "no operator '<=' for this type";
    res.type = valError;
    return res;
}

Value Value::operator ==(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valString)
        return Value(this->str_val == b.str_val);
    if (type == valNumber)
        return Value(this->numb_val == b.numb_val);
    res.str_val = "no operator '==' for this type";
    res.type = valError;
    return res;
}

Value Value::operator !=(Value b)
{
    Value res;
    if (type == valError)
        return *this;
    if (b.type == valError)
        return b;
    if (type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (b.type == valUndefined) {
        res.str_val = "value is undefined";
        res.type = valError;
        return res;
    }
    if (type != b.type) {
        res.str_val = "type mismatch";
        res.type = valError;
        return res;
    }
    if (type == valString)
        return Value(this->str_val != b.str_val);
    if (type == valNumber)
        return Value(this->numb_val != b.numb_val);
    res.str_val = "no operator '!=' for this type";
    res.type = valError;
    return res;
}

double Value::toDouble()
{
    if (type != valNumber)
        return numeric_limits<double>::quiet_NaN();
    return numb_val;
}

int Value::toInt()
{
    if (type != valNumber)
        return numeric_limits<int>::quiet_NaN();
    return (int)numb_val;
}

string Value::toString()
{
    if (type != valString)
        return "";
    return str_val;
}

}
