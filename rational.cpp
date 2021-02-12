#include <iostream>
#include <string>

using namespace std;

class Rational {
// 1. Private attributes
private:
    int numerator;
    int denominator;
public:
	// 2. Two constructors, one with 2 parameters and one with none
    Rational(int numerator, int denominator);
	Rational() : numerator(), denominator(1) {};
	// 3. Two getters and setters function, with implementation below
    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int num);
    void SetDenominator(int num);
	// 4. Print function with implementation below
    void Print();
    void Reduce();
	Rational& operator +=(const Rational& rhs);
};

Rational::Rational(int num, int deno) : numerator(num), denominator(deno) {
}

int Rational::GetNumerator() const {
	return numerator;
}

int Rational::GetDenominator() const {
	return denominator;
}

void Rational::SetNumerator(int num) {
	numerator = num;
}

void Rational::SetDenominator(int num) {
	if (num > 0) denominator = num;
}

void Rational::Print() {
	cout << numerator << "/" << denominator << endl;
}

// Find the greatest common devisor using Euclidean's Algorithm
int GCD(int a, int b) {
	while (b != 0) {
		int temp = a;
		a = b;
		b = temp % b;
	}
	return a;
}

// 5. This function will reduce the fraction to its simplest form.
void Rational::Reduce() {
	if (denominator != 0) {
		int greatestCommonDivisor = GCD(numerator, denominator);
		numerator /= greatestCommonDivisor;
		denominator /= greatestCommonDivisor;
	}
}

// Find the like term of denominator to do arithmetic between fractions
int findSameDenominator(int a, int b) {
	if (a == b) return a;
	if (b % a == 0) return b;
	if (a % b == 0) return a;
	return a * b;
}

// 6. Operator overload function which will add the rhs to the lhs.
Rational& Rational:: operator +=(const Rational& rhs) {
	int temp = findSameDenominator(denominator, rhs.GetDenominator());
	int lhsNum = numerator * (temp / denominator);
	int rhsNum = rhs.GetNumerator() * (temp / rhs.GetDenominator());
	numerator = lhsNum + rhsNum;
	denominator = temp;
	return *this;
}

// 7. Operator overload function which will multiply the lhs and rhs fraction.
Rational operator *(const Rational& lhs, const Rational& rhs) {
	int productNumerator = lhs.GetNumerator() * rhs.GetNumerator();
	int productDenominator = lhs.GetDenominator() * rhs.GetDenominator();
	Rational newRationalNum(productNumerator, productDenominator);
	return newRationalNum;
}

// 8. Returns a new Rational that is the sum of the two fractions passed in.
Rational operator +(const Rational& lhs, const Rational& rhs) {
	int newDenominator  = findSameDenominator(lhs.GetDenominator(), rhs.GetDenominator());
	int lhsNum = lhs.GetNumerator() * (newDenominator / lhs.GetDenominator());	
	int rhsNum = rhs.GetNumerator() * (newDenominator / rhs.GetDenominator());
	int newNumerator = lhsNum + rhsNum;
	Rational newRationalNum(newNumerator, newDenominator);
	return newRationalNum;
}

// 9. Returns true if lhs == rhs, false if not.
bool operator ==(const Rational& lhs, const Rational& rhs) {
	Rational leftCopy = lhs;
	Rational rightCopy = rhs;
	leftCopy.Reduce();
	rightCopy.Reduce();
	if (leftCopy.GetNumerator() == rightCopy.GetNumerator()
		&& leftCopy.GetDenominator() == rightCopy.GetDenominator()) {
		return true;
	}
	return false;
}


int main() {
    Rational r1;
	Rational r2(12,36);

	r1.Print(); // 0/1
	r2.Print();	// 12/36

	r1.Reduce(); // 0/1
    r2.Reduce(); // 1/3
  
    r1.Print();
    r2.Print();

    Rational r3(1,2);
    Rational r4(2,3);
    r4 += r3;
    r4.Print();
	cout << "If equals to 7/6 then pass" << endl;
  	
	// Another test case
	Rational r11(2,5);
	Rational r12(7,6);
	r11 += r12;
	r11.Print();
	cout << "If equals to 47/30 then pass" << endl;

    Rational r5(3,8);
    Rational r6(2,5);
    Rational r7;
    r7 = r5 + r6;
    r7.Print();
  
    r7.Reduce();
    r7.Print();

    Rational r8;
    r8 = r5 * r6;
    r8.Print();

    r8.Reduce();
    r8.Print();
  
    Rational r9(36, 12);
    Rational r10(12, 4);
	Rational r13(1,2);
	Rational r14(3,4);
	
	if (r9 == r10) {
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    } 
    return 0;
}
/*
Results
0/1
12/36
0/1
1/3
7/6
31/40
31/40
6/40
3/20
equal
*/

  
