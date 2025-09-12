#include "bigint.hpp"

bigint::bigint()
{
	numbers = "0";
}

bigint::bigint(unsigned int n)
{
	stringstream s;
	s << n;
	numbers = s.str();
	reverse(numbers.begin(), numbers.end());
}

static bool control(const string &s)
{
	size_t i = -1;
	if (s.empty())
		return true;
	while (++i < s.size())
		if (!(s[i] >= '0' && s[i] <= '9'))
			return true;
	return false;
}

bigint::bigint(const string &n)
{
	if (control(n))
	{
		numbers = "0";
		return ;
	}
	numbers = n;
	reverse(numbers.begin(), numbers.end());
	zeroClear();
}

bigint::bigint(const bigint &other)
{
	numbers = other.numbers;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this->numbers != other.numbers)
		numbers = other.numbers;
	return *this;
}

bigint::~bigint() {}

string bigint::addNumbers(const string &s1, const string &s2) const
{
	size_t i = -1;
	size_t len = std::max(s1.size(), s2.size());
	int val = 0;
	int ret = 0;
	string result = "";
	if (s1.empty() || s2.empty())
		return result;
	while (++i < len)
	{
		val = i < s1.size() ? s1[i] - '0' : 0;
		val += i < s2.size() ? s2[i] - '0' : 0;
		val += ret;
		ret = val / 10;
		result.push_back(val % 10 + 48);
	}
	if (ret)
		result.push_back(ret + 48);
	return result;
}

void bigint::zeroClear()
{
	while (numbers.size() > 1 && numbers.back() == '0')
		numbers.pop_back();
}

string bigint::getNumbers() const
{
	return numbers;
}

bool bigint::operator==(const bigint &other)
{
	return this->numbers == other.numbers;
}

bool bigint::operator!=(const bigint &other)
{
	return !(*this == other);
}

bool bigint::operator<(const bigint &other)
{
	if (this->numbers.size() != other.numbers.size())
		return this->numbers.size() < other.numbers.size();
	return lexicographical_compare(this->numbers.rbegin(), this->numbers.rend(),
			other.numbers.rbegin(), other.numbers.rend());
}

bool bigint::operator>(const bigint &other)
{
	if (this->numbers.size() != other.numbers.size())
		return this->numbers.size() > other.numbers.size();
	return lexicographical_compare(other.numbers.rbegin(), other.numbers.rend(),
			this->numbers.rbegin(), this->numbers.rend());
}

bool bigint::operator<=(const bigint &other)
{
	return !(*this > other);
}

bool bigint::operator>=(const bigint &other)
{
	return !(*this < other);
}

bigint bigint::operator+(const bigint &other) const
{
	bigint result;
	result.numbers = addNumbers(this->numbers, other.numbers);
	return result;
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return *this;
}

bigint &bigint::operator++()
{
	this->numbers = addNumbers(this->numbers, "1");
	return *this;
}

bigint bigint::operator++(const int n)
{
	bigint result = *this;
	(void)n;
	this->numbers = addNumbers(this->numbers, "1");
	return *this;
}

bigint bigint::operator>>(const int n)
{
	string str = numbers;
	int i = -1;
	reverse(str.begin(), str.end());
	while (++i < n)
	{
		if (str.empty())
			return bigint("0");
		str.pop_back();
	}
	return bigint(str);
}

bigint bigint::operator<<(const int n)
{
	string str = numbers;
	int i = -1;
	reverse(str.begin(), str.end());
	while (++i < n)
		str.push_back('0');
	return bigint(str);
}

bigint bigint::operator<<(const bigint &other)
{
	string str = other.numbers;
	reverse(str.begin(), str.end());
	int num = std::stoi(str);
	return *this << num;
}

bigint bigint::operator>>(const bigint &other)
{
	string str = other.numbers;
	reverse(str.begin(), str.end());
	int num = std::stoi(str);
	return *this >> num;
}

bigint &bigint::operator<<=(const int n)
{
	*this = *this << n;
	return *this;
}

bigint &bigint::operator>>=(const int n)
{
	*this = *this >> n;
	return *this;
}

bigint &bigint::operator<<=(const bigint &other)
{
	*this = *this << other;
	return *this;
}

bigint &bigint::operator>>=(const bigint &other)
{
	*this = *this >> other;
	return *this;
}

ostream &operator<<(ostream &os, const bigint &other)
{
	string str = other.getNumbers();
	reverse(str.begin(), str.end());
	os << str;
	return os;
}