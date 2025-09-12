#include "bigint.hpp"

bigint::bigint(): val("0"){}

bigint::bigint(unsigned int i){
    std::ostringstream oss;
    oss << i;
    val = oss.str();
}

bigint::bigint(const std::string& val2){
    bool valid = !val2.empty();

    // Sadece rakamları kabul et
    for(char c: val2){
        if(!isdigit(c))
            valid = false;
    }

    if(!valid)
        val = "0";
    else{
        val = val2;
        removezero(); // Leading zero'ları kaldır
    }
}

bigint::bigint(const bigint& o){
    val = o.val;
}

bigint& bigint::operator=(const bigint& o){
    if(this != &o)
    val = o.val;

    return *this;
}

void bigint::removezero(){
    size_t nonzero = val.find_first_not_of('0');
    if(nonzero == std::string::npos)
        val = "0";
    else
    val = val.substr(nonzero);
}

std::string bigint::addstring(const std::string& a, const std::string& b){
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    std::string final;
    while(i>= 0 || j>= 0 || carry){
        int d1 = (i>= 0) ? a[i] - '0' : 0;
        int d2 = (j>= 0) ? b[j] - '0' : 0;
        int sum = d1 + d2 + carry;
        final.push_back(sum % 10 + '0' );
        carry = sum / 10;
        i--;
        j--;
    }
    std::reverse(final.begin(), final.end());
    
    // Leading zero'ları kaldır
    size_t nonzero = final.find_first_not_of('0');
    if(nonzero == std::string::npos)
        return "0";
    else
        return final.substr(nonzero);
}

bool bigint::operator<(const bigint& b)const{
    if(val.size() != b.val.size())
        return val.size() < b.val.size();
    return val < b.val;
}

bool bigint::operator>(const bigint& b)const{
    return b < *this;
}

bool bigint::operator<=(const bigint& b)const{
    return !(b < *this);
}

bool bigint::operator>=(const bigint& b)const{
    return !(*this < b);
}


bigint bigint::operator<<(unsigned int i){ 
    return bigint(val + std::string(i, '0'));
}

bigint bigint::operator>>(unsigned int i){
    if(val.size() <= i)
        return bigint("0");
    std::string result = val.substr(0, val.size() - i);
    return bigint(result);  // Constructor removezero'yu çağıracak
}

bigint& bigint::operator>>=(unsigned int i){
    *this = *this >>i;
    return *this;
}

bigint& bigint::operator<<=(unsigned int i){
    *this = *this << i;
    return *this;
}

bigint bigint::operator<<(const bigint& b){ 
    // Güvenli conversion - overflow kontrolü
    try {
        size_t i = std::stoul(b.val);
        // Makul limit kontrolü (örnek: max 1000000)
        if(i > 1000000) i = 1000000;
        return bigint(val + std::string(i, '0'));
    } catch(...) {
        // Overflow durumunda çok büyük shift, makul bir değer döndür
        return bigint(val + std::string(1000000, '0'));
    }
}

bigint& bigint::operator<<=(const bigint& b){
    *this = *this < b;
    return *this;
}

bigint bigint::operator>>(const bigint& b){
    // Güvenli conversion
    try {
        size_t i = std::stoul(b.val);
        if(val.size() <= i)
            return bigint("0");
        return bigint(val.substr(0, val.size() - i));
    } catch(...) {
        // Overflow durumunda sıfır döndür
        return bigint("0");
    }
}

bigint& bigint::operator>>=(const bigint& b){
    *this = *this >> b;
    return *this;
}



bigint bigint::operator++(int){
    bigint temp = *this;
    *this = bigint(addstring(val, "1"));
    return temp;
}
bigint& bigint::operator++(){
    *this = bigint(addstring(val, "1"));
    return *this;
}

void bigint::print(std::ostream& out)const{
    out << val;
}

std::ostream& operator<<(std::ostream& out, const bigint& b){
    b.print(out);
    return out;
}

bigint bigint::operator+(const bigint& b){
    return bigint(addstring(val, b.val));
}

bigint& bigint::operator+=(const bigint& b){
   val = addstring(val, b.val);
    return *this;
}

bool bigint::operator==(const bigint& o)const{
    return val == o.val;
}

bool bigint::operator!=(const bigint& o)const{
    return val != o.val;
}
