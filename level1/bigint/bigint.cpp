// #include "bigint.hpp"

// bigint::bigint():val("0"){}

// bigint::bigint(unsigned int i) {
//     std::ostringstream oss;
//     oss << i;
//     val = oss.str();
//     std::reverse(val.begin(), val.end());
// }

// // bigint::bigint(const std::string&val2) {
// //     bool isdigit = true;
// //     for(std::string::const_iterator it = val2.begin(); it < val2.end(); ++it)
// //     {
// //         if(!::isdigit(*it))
// //             isdigit = false;
// //         if (val2.empty() || isdigit == false)
// //             val = "0";
// //         else {
// //             val = val2;
// //             std::reverse(val.begin(), val.end());
// //             removezero();
// //         }
// //     }
// // }
// bigint::bigint(const std::string& val2) {
//     if (val2.empty()) {           // boş string
//         val = "0";
//         return;
//     }

//     for (size_t i = 0; i < val2.size(); i++) {
//         if (!isdigit(val2[i])) {  // geçersiz karakter
//             val = "0";
//             return;
//         }
//     }

//     val = val2;
//     std::reverse(val.begin(), val.end()); // ters sakla
//     removezero();
// }

// bigint::bigint(const bigint& other):val(other.val){

// }

// bigint& bigint::operator=(const bigint& other) {
//     if(this != &other)
//     val = other.val;
//     return *this;
// }

// bigint::~bigint() {}

// void bigint::removezero() {
//     while (!val.empty() && val.back() == '0')
//         val.pop_back();
// }

// // std::string bigint::addstring(const std::string s1, const std::string s2) {
// //     std::string final;
// //     size_t result = 0;
// //     size_t rest = 0;
// //     size_t len = 0;
// //     len = (s1.size() > s2.size() ? s1.size() : s2.size());
// //     for (size_t i = 0; i < len; i++)
// //     {
// //         int s1_r = (i < s1.size() ? s1[i] - '0' : 0);
// //         int s2_r = (i < s2.size() ? s2[i] - '0' : 0);
// //         result = s1_r + s2_r + rest;
// //         final.push_back((result % 10) + '0');
// //         rest = result / 10;
// //     }
// //     if (rest)
// //     final.push_back(rest + '0');
// //     return final;
// // }

// // addstring fonksiyonu (val ters saklanıyor)

// // bigint bigint::operator+(const bigint& b) {
// //     bigint res(addstring(val, b.val));
// //     return res;
// // }

// // bigint& bigint::operator+=(const bigint& b) {
// //     val = addstring(val, b.val);
// //     return *this;
// // }

// bigint bigint::operator++(int) {
//     bigint res(*this);
//     val = addstring(val, "1");
//     return res;
// }

// bigint& bigint::operator++() {
//     val = addstring(val, "1");
//     return *this;
// }


// bool bigint::operator==(const bigint& b) const {
//     return ( val == b.val);
// }

// bool bigint::operator!=(const bigint& b) const {
//     return ( val != b.val);
// }

// bool bigint::operator<=(const bigint& b) const {
//     if (val.size() < b.val.size() || val == b.val)
//         return true;
//     else if(val.size() > b.val.size())
//         return false;
//     else {
//         for (int i = val.size() - 1; i >= 0; i--)
//         {
//             if(val[i] < b.val[i])
//                 return true;
//             else if (val[i] > b.val[i])
//                 return false;
//             else
//                 continue;
//         }
//     }
//     return false;
// }
// bool bigint::operator>=(const bigint& b) const {
//     if (val.size() > b.val.size() || val == b.val)
//         return true;
//     else if(val.size() < b.val.size())
//         return false;
//     else {
//         for (int i = val.size() - 1; i >= 0; i--)
//         {
//             if(val[i] > b.val[i])
//                 return true;
//             else if (val[i] < b.val[i])
//                 return false;
//             else
//                 continue;
//         }
//     }
//     return false;
// }

// bool bigint::operator<(const bigint& b) const {
//     if (val.size() < b.val.size())
//         return true;
//     else if(val.size() > b.val.size())
//         return false;
//     else {
//         for (int i = val.size() - 1; i >= 0; i--)
//         {
//             if(val[i] < b.val[i])
//                 return true;
//             else if (val[i] > b.val[i])
//                 return false;
//             else
//                 continue;
//         }
//     }
//     return false;
// }

// bool bigint::operator>(const bigint& b) const {
//     if (val.size() > b.val.size())
//         return true;
//     else if(val.size() < b.val.size())
//         return false;
//     else {
//         for (int i = val.size() - 1; i >= 0; i--)
//         {
//             if(val[i] > b.val[i])
//                 return true;
//             else if (val[i] < b.val[i])
//                 return false;
//             else
//                 continue;
//         }
//     }
//     return false;
// }


// bigint bigint::operator>>(unsigned int n)
// {
// 	std::string str = val;
// 	std::reverse(str.begin(), str.end());
// 	for (int i = 0; i < n ; i++)
// 	{
// 		if (str.empty())
// 		{
// 			str = "0";
// 			return (bigint(str));
// 		}
// 		str.pop_back();
// 	}
// 	return (bigint(str));
// }

// bigint bigint::operator<<(unsigned int n)
// {
// 	std::string str = val;
// 	std::reverse(str.begin(), str.end());
// 	for (int i = 0; i < n; i++)
// 		str.push_back('0');
// 	return bigint(str);
// }

// bigint bigint::operator>>(const bigint &b)
// {
// 	std::stringstream ss;
// 	std::string str = val;
// 	std::reverse(str.begin(), str.end());
// 	bigint res(str);
// 	int shift;
// 	ss << b.val;
// 	ss >> shift;
// 	res = *this >> shift;
// 	return res;
// }

// bigint bigint::operator<<(const bigint &b)
// {
// 	std::stringstream ss;
// 	std::string str = val;
// 	std::reverse(str.begin(), str.end());
// 	bigint res(str);
// 	int shift;
// 	ss << b.val;
// 	ss >> shift;
// 	res = *this << shift;
// 	return res;
// }

// // bigint bigint::operator<<(const bigint& b) const {
// //     size_t dix = 1;
// //     std::string res = val;
// //     std::reverse(res.begin(), res.end());
// //     for(size_t i = 0; i < b.val.size(); i++)
// //     {
// //         for(size_t y = 0; y < (size_t)((b.val[i] - '0') * dix); y++ )
// //         {
// //             res.append("0");
// //         }
// //         dix *= 10;
// //     }
// //     bigint result(res);
// //     return result;
// // }


// // bigint bigint::operator<<(unsigned int i) const {
// //     std::string res = val;
// //     std::reverse(res.begin(), res.end());
// //     for(size_t y = 0; y < i; y++)
// //      res.append("0");
// //     bigint result(res);
// //     return result;
// // }


// // bigint bigint::operator>>(unsigned int i) const {
// //     std::string res = val;
// //     std::reverse(res.begin(), res.end());
// //     for (size_t y = 0; y < i && !res.empty(); y++)
// //         res.erase(res.size() - 1);
// //     bigint result(res);
// //     return result;
// // }

// // bigint bigint::operator>>(const bigint& b) const {
// //     size_t dix = 1;
// //     std::string res = val;
// //     std::reverse(res.begin(), res.end());
// //     for (size_t i = 0; i < b.val.size(); i++)
// //     {
// //         if (res.empty())
// //             break;
// //         for (size_t y = 0; (size_t)((b.val[i] - '0') * dix); y++)
// //         {
// //             res.erase(res.size() - 1);
// //             if (res.empty())
// //             break;
// //         }
// //         dix *= 10;
// //     }
// //     bigint result(res);
// //     return result;
// // }

// bigint& bigint::operator<<=(unsigned int i){
//     *this = *this << i;
//     return *this;
// }

// bigint& bigint::operator>>=(unsigned int i){
//     *this = *this >> i;
//     return *this;
// }

// bigint& bigint::operator<<=(const bigint& b){
//     *this = *this << b;
//     return *this;
// }

// bigint& bigint::operator>>=(const bigint& b){
//     *this = *this >> b;
//     return *this;
// }

// // void bigint::print(std::ostream& os)const {
// //     std::string res = val;
// //     std::reverse(res.begin(), res.end());
// //     os << res <<  std::endl;
// // }

// void bigint::print(std::ostream& os) const {
//     std::string res = val;
//     std::reverse(res.begin(), res.end());

//     size_t first_non_zero = res.find_first_not_of('0');
//     if (first_non_zero == std::string::npos)
//         os << '0'; // tüm karakterler '0' ise
//     else
//         os << res.substr(first_non_zero);
// }


// std::ostream& operator<<(std::ostream& os, const bigint& b) {
//     b.print(os);
//     return os;
// }

#include "bigint.hpp"

// Constructors
bigint::bigint(): val("0") {}

bigint::bigint(unsigned int i) {
    std::ostringstream oss;
    oss << i;
    val = oss.str();
}

bigint::bigint(const std::string& val2) {
    bool valid = !val2.empty();
    for (char c : val2)
        if (!isdigit(c))
            valid = false;
    if (!valid)
        val = "0";
    else {
        val = val2;
        removezero();
    }
}

bigint::bigint(const bigint& other): val(other.val) {}

bigint& bigint::operator=(const bigint& other) {
    if (this != &other)
        val = other.val;
    return *this;
}

bigint::~bigint() {}

// Helper functions
void bigint::removezero() {
    size_t first_non_zero = val.find_first_not_of('0');
    if (first_non_zero == std::string::npos) {
        val = "0";
    } else {
        val = val.substr(first_non_zero);
    }
}

std::string bigint::addstring(const std::string& s1, const std::string& s2) {
    std::string final;
    int carry = 0;
    int n1 = s1.size(), n2 = s2.size();
    int i = n1 - 1, j = n2 - 1;
    while (i >= 0 || j >= 0 || carry) {
        int d1 = (i >= 0) ? s1[i] - '0' : 0;
        int d2 = (j >= 0) ? s2[j] - '0' : 0;
        int sum = d1 + d2 + carry;
        final.push_back((sum % 10) + '0');
        carry = sum / 10;
        i--; j--;
    }
    std::reverse(final.begin(), final.end());
    return final;
}

// Operators
bigint bigint::operator+(const bigint& b) {
    return bigint(addstring(val, b.val));
}

bigint& bigint::operator+=(const bigint& b) {
    val = addstring(val, b.val);
    return *this;
}

bigint bigint::operator++(int) {
    bigint res(*this);
    val = addstring(val, "1");
    return res;
}

bigint& bigint::operator++() {
    val = addstring(val, "1");
    return *this;
}

// Comparisons
bool bigint::operator==(const bigint& b) const { return val == b.val; }
bool bigint::operator!=(const bigint& b) const { return val != b.val; }
bool bigint::operator<(const bigint& b) const {
    if (val.size() != b.val.size()) return val.size() < b.val.size();
    return val < b.val;
}
bool bigint::operator>(const bigint& b) const { return b < *this; }
bool bigint::operator<=(const bigint& b) const { return !(b < *this); }
bool bigint::operator>=(const bigint& b) const { return !(*this < b); }

// Shifts
bigint bigint::operator<<(unsigned int n) {
    return bigint(val + std::string(n, '0'));
}

bigint bigint::operator>>(unsigned int n) {
    if (val.size() <= n) return bigint("0");
    return bigint(val.substr(0, val.size() - n));
}

bigint bigint::operator<<(const bigint& b) {
    unsigned int n = std::stoul(b.val);
    return *this << n;
}

bigint bigint::operator>>(const bigint& b) {
    unsigned int n = std::stoul(b.val);
    return *this >> n;
}

bigint& bigint::operator<<=(unsigned int i) { *this = *this << i; return *this; }
bigint& bigint::operator>>=(unsigned int i) { *this = *this >> i; return *this; }
bigint& bigint::operator<<=(const bigint& b) { *this = *this << b; return *this; }
bigint& bigint::operator>>=(const bigint& b) { *this = *this >> b; return *this; }

// Print
void bigint::print(std::ostream& os) const { os << val; }
std::ostream& operator<<(std::ostream& os, const bigint& b) { b.print(os); return os; }
