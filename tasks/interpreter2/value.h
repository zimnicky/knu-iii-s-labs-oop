#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <iostream>
#include <limits>

using namespace std;

namespace interpreter
{

enum ValueType {valUndefined, valNumber, valString, valError};
class Value {
protected:
    ValueType type;
    string str_val;
    double numb_val;
public:
    Value(ValueType t) {
        type = t;
        numb_val = 0;
    }
    Value(double val) {
        type = valNumber;
        numb_val = val;
    }
    Value(string val) {
        type = valString;
        str_val = val;
    }
    Value(const char *val) {
        type = valString;
        str_val = val;
    }
    Value() {
        type = valUndefined;
    }
    Value static error(string msg) {
        Value t(valError);
        t.str_val = msg;
        return t;
    }
    ValueType getType(){ return type;}
    Value operator -();
    Value operator !();
    Value operator +(Value b);
    Value operator -(Value b);
    Value operator *(Value b);
    Value operator /(Value b);
    Value operator >(Value b);
    Value operator >=(Value b);
    Value operator <(Value b);
    Value operator <=(Value b);
    Value operator ==(Value b);
    Value operator !=(Value b);
    double toDouble();
    int toInt();
    string toString();
    friend istream& operator>>(istream& stream, Value &val) {
        int t;
        stream >> t;
        switch (t) {
        case valNumber:
            stream >> val.numb_val;
            break;
        case valString:
        case valError:
            getline(stream, val.str_val,'\n');
            break;
        default:
            break;
        }
        val.type = ValueType(t);
        return stream;
    }
    friend ostream& operator<<(ostream& stream, Value &val) {
        stream << int(val.type) << " ";
        switch (val.type) {
        case valNumber:
            stream << val.numb_val;
            break;
        case valString:
        case valError:
            stream << val.str_val;
            break;
        default:
            break;
        }
        return stream;
    }
};

};

#endif // VALUE_H
