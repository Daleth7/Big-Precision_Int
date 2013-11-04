#include "Precision.h"
#include "Precision_Math.h"

#include <iostream>
#include <string>

#include <chrono>

using namespace std;

inline string pass(bool b)
    {return b ? "pass" : "fail";}

int main()
{
    cout
        << "Welcome to the Precision Type Sandbox."
        << " Below, the functionality of each type"
        << " will be tested."
    << '\n' << endl;

    using namespace Precision;


/********************Int********************************/
    Int subject0;
    cout << "\nPrecision::Int:\n";
    const string t(4, ' ');
        cout << t << "Constructors:\n";
            cout << t+t << "Int::Int(): "
                << subject0.str() << " : "
                << pass(subject0 == 0)
            << '\n';
    subject0 = Int(129834798);
            cout << t+t << "Int::Int(long long int): "
                << subject0.str() << " : "
                << pass(subject0 == 129834798)
            << '\n';
    subject0 = Int("-00012384712394871212129837562837642387");
            cout << t+t << "Int::Int(string, short): "
                << subject0.str() << " : "
                << pass(subject0.str() == "-12384712394871212129837562837642387")
            << '\n';
        cout << t << "Read-only functions:\n";
            cout << t+t << "Int::sign(): "
                << subject0.sign() << " : "
                << pass(subject0.sign() == -1)
            << '\n';
            cout << t+t << "Int::sci_note(): "
                << subject0.sci_note() << " : "
                << pass(subject0.sci_note() == "-1.23847E34")
            << '\n';
            cout << t+t << "Int::sci_note(size_t): "
                << subject0.sci_note(50) << " : "
                << pass(subject0.sci_note(50) == "-1.2384712394871212129837562837642387E34")
            << '\n';
            cout << t+t << "Int::sci_note_w_spaces(): "
                << subject0.sci_note_w_spaces() << " : "
                << pass(subject0.sci_note_w_spaces() == "- 1.23847 E 34")
            << '\n';
            cout << t+t << "Int::magnitude(): "
                << subject0.magnitude().str() << " : "
                << pass(subject0.magnitude().str() == "+12384712394871212129837562837642387")
            << '\n';
            cout << t+t << "Int::count_digits(): "
                << subject0.count_digits() << " : "
                << pass(subject0.count_digits() == 35)
            << '\n';
    Int subject1(70);
            cout << t+t << "Int::compare(const Int&): "
                << subject0.compare(subject1) << " : "
                << pass(subject0.compare(subject1) == -1)
            << '\n';
            cout << t+t << "Int::operator-(): "
                << (-subject0).str() << " : "
                << pass(-subject0 == subject0.magnitude())
            << '\n';
    subject0 = Int("789456123123456789");
    subject1 = Int("-4567891231230");
        cout << t << "Arithmetic operators:\n";
            cout << t+t << "Int::operator+=(const Int&): "
                << (subject1 + subject0).str() << " : "
                << pass((subject1 + subject0) == Int("789451555232225559"))
            << '\n';
            cout << t+t << "Int::operator-=(const Int&): "
                << (subject1 - subject0).str() << " : "
                << pass((subject1 - subject0) == Int("-789460691014688019"))
            << '\n';
            cout << t+t << "Int::operator*=(const Int&): "
                << (subject1 * subject0).str() << " : "
                << pass((subject1 * subject0) == Int("-3606149702256469505198912320470"))
            << '\n';

            cout << t+t << "Int::operator/=(const Int&): "
                << (subject0 / subject1).str() << " : "
                << pass((subject0 / subject1) == Int("-172827"))
            << '\n';
            cout << t+t << "Int::operator%=(const Int&): "
                << (subject0 % subject1).str() << " : "
                << pass((subject0 % subject1) == Int("1185303669579"))
            << '\n';
    const Int::lli bop1(123), bop2(15);
    subject0 = bop1;
    subject1 = bop2;
        cout << t << "Bitwise operators:\n";
            cout << t+t << "Int::operator&=(const Int&): "
                << (subject0 & subject1).str() << " : "
                << pass((subject0 & subject1) == (bop1 & bop2))
            << '\n';
            cout << t+t << "Int::operator|=(const Int&): "
                << (subject0 | subject1).str() << " : "
                << pass((subject0 | subject1) == (bop1 | bop2))
            << '\n';
            cout << t+t << "Int::operator^=(const Int&): "
                << (subject0 ^ subject1).str() << " : "
                << pass((subject0 ^ subject1) == (bop1 ^ bop2))
            << '\n';
            cout << t+t << "Int::operator>>=(const Int&): "
                << (subject0 >> subject1).str() << " : "
                << pass((subject0 >> subject1) == (bop1 >> bop2))
            << '\n';
            cout << t+t << "Int::operator<<=(const Int&): "
                << (subject0 << subject1).str() << " : "
                << pass((subject0 << subject1) == (bop1 << bop2))
            << '\n';
            cout << t+t << "Int::operator~(): "
                << (~subject0).str() << " : "
                << pass((~subject0) == (~bop1))
            << '\n';
    subject0 = "5601347890"_Precision_Int;
            cout << t+t << "operator\"\" _Precision_Int(char const *const,size_t): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+5601347890")
            << '\n';
    subject0 = "56012378"_Precision_Int_E;
            cout << t+t << "operator\"\" _Precision_Int_E(char const *const,size_t): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+56012378")
            << '\n';
    subject0 = "11.2387611E5"_Precision_Int_E;
            cout << t+t << "operator\"\" _Precision_Int_E(char const *const,size_t): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+1123876")
            << '\n';
    subject0 = "11.23E5"_Precision_Int_E;
            cout << t+t << "operator\"\" _Precision_Int_E(char const *const,size_t): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+1123000")
            << '\n';
    subject0 = "123E5"_Precision_Int_E;
            cout << t+t << "operator\"\" _Precision_Int_E(char const *const,size_t): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+12300000")
            << '\n';
    subject0 = 128374_Precision_Int;
            cout << t+t << "operator\"\" _Precision_Int(unsigned long long): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+128374")
            << '\n';


/*******************UInt********************************/
    UInt subject2;
    cout << "\nPrecision::UInt:\n";
        cout << t << "Constructors:\n";
            cout << t+t << "UInt::UInt(): "
                << subject2.str() << " : "
                << pass(subject2 == 0)
            << '\n';
    subject2 = UInt(129834798);
            cout << t+t << "UInt::UInt(long long int): "
                << subject2.str() << " : "
                << pass(subject2 == 129834798)
            << '\n';
    subject2 = UInt("00012384712394871212129837562837642387");
            cout << t+t << "UInt::UInt(string): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+12384712394871212129837562837642387")
            << '\n';
        cout << t << "Read-only functions:\n";
            cout << t+t << "UInt::sci_note(): "
                << subject2.sci_note() << " : "
                << pass(subject2.sci_note() == "+1.23847E34")
            << '\n';
            cout << t+t << "UInt::sci_note(size_t): "
                << subject2.sci_note(50) << " : "
                << pass(subject2.sci_note(50) == "+1.2384712394871212129837562837642387E34")
            << '\n';
            cout << t+t << "UInt::sci_note_w_spaces(): "
                << subject2.sci_note_w_spaces() << " : "
                << pass(subject2.sci_note_w_spaces() == "+ 1.23847 E 34")
            << '\n';
            cout << t+t << "UInt::count_digits(): "
                << subject2.count_digits() << " : "
                << pass(subject2.count_digits() == 35)
            << '\n';
    UInt subject3(70);
            cout << t+t << "UInt::compare(const UInt&): "
                << subject2.compare(subject3) << " : "
                << pass(subject2.compare(subject3) == 1)
            << '\n';
            cout << t+t << "Int::operator-(): "
                << (-subject2).str() << " : "
                << pass(-subject2 == Int("-12384712394871212129837562837642387"))
            << '\n';
    subject2 = UInt("789456123123456789");
    subject3 = UInt("4567891231230");
        cout << t << "Arithmetic operators:\n";
            cout << t+t << "UInt::operator+=(const UInt&): "
                << (subject3 + subject2).str() << " : "
                << pass((subject3 + subject2) == UInt("789460691014688019"))
            << '\n';
            cout << t+t << "UInt::operator-=(const UInt&): "
                << (subject3 - subject2).str() << " : "
                << pass((subject3 - subject2) == 0)
            << '\n';
            cout << t+t << "UInt::operator*=(const UInt&): "
                << (subject3 * subject2).str() << " : "
                << pass((subject3 * subject2) == UInt("3606149702256469505198912320470"))
            << '\n';
            cout << t+t << "UInt::operator/=(const UInt&): "
                << (subject2 / subject3).str() << " : "
                << pass((subject2 / subject3) == UInt("172827"))
            << '\n';
            cout << t+t << "UInt::operator%=(const UInt&): "
                << (subject2 % subject3).str() << " : "
                << pass((subject2 % subject3) == UInt("1185303669579"))
            << '\n';
    subject2 = bop1;
    subject3 = bop2;
        cout << t << "Bitwise operators:\n";
            cout << t+t << "UInt::operator&=(const UInt&): "
                << (subject2 & subject3).str() << " : "
                << pass((subject2 & subject3) == (bop1 & bop2))
            << '\n';
            cout << t+t << "UInt::operator|=(const UInt&): "
                << (subject2 | subject3).str() << " : "
                << pass((subject2 | subject3) == (bop1 | bop2))
            << '\n';
            cout << t+t << "UInt::operator^=(const UInt&): "
                << (subject2 ^ subject3).str() << " : "
                << pass((subject2 ^ subject3) == (bop1 ^ bop2))
            << '\n';
            cout << t+t << "UInt::operator>>=(const UInt&): "
                << (subject2 >> subject3).str() << " : "
                << pass((subject2 >> subject3) == (bop1 >> bop2))
            << '\n';
            cout << t+t << "UInt::operator<<=(const UInt&): "
                << (subject2 << subject3).str() << " : "
                << pass((subject2 << subject3) == (bop1 << bop2))
            << '\n';
    subject2 = bop1 * bop2;
            cout << t+t << "UInt::operator~(): "
                << (~subject2).str() << " : "
                << pass((~subject2) == (~(bop1*bop2)))
            << '\n';
    subject2 = "560347890"_Precision_UInt;
            cout << t+t << "operator\"\" _Precision_UInt(char const *const,size_t): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+560347890")
            << '\n';
    subject2 = "5601238"_Precision_UInt_E;
            cout << t+t << "operator\"\" _Precision_UInt_E(char const *const,size_t): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+5601238")
            << '\n';
    subject2 = "11.2387611E5"_Precision_UInt_E;
            cout << t+t << "operator\"\" _Precision_UInt_E(char const *const,size_t): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+1123876")
            << '\n';
    subject2 = "11.23E5"_Precision_UInt_E;
            cout << t+t << "operator\"\" _Precision_UInt_E(char const *const,size_t): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+1123000")
            << '\n';
    subject2 = "123E3"_Precision_UInt_E;
            cout << t+t << "operator\"\" _Precision_UInt_E(char const *const,size_t): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+123000")
            << '\n';
    subject2 = 128374_Precision_UInt;
            cout << t+t << "operator\"\" _Precision_UInt(unsigned long long): "
                << subject2.str() << " : "
                << pass(subject2.str() == "+128374")
            << '\n';


/********************Float********************************/
    Float subject4;
    cout << "\nPrecision::Float:\n";
        cout << t << "Constructors:\n";
            cout << t+t << "Float::Float(): "
                << subject4.str() << " : "
                << pass(subject4 == 0)
            << '\n';
    subject4 = Float(12983.4798);
            cout << t+t << "Float::Float(long double): "
                << subject4.str() << " : "
                << pass(subject4 == 12983.4798)
            << '\n';
    subject4 = Float("-0001238471239487121212983.7562837642387");
            cout << t+t << "Float::Float(string, short): "
                << subject4.str() << " : "
                << pass(subject4.str() == "-1238471239487121212983.7562837642387")
            << '\n';
        cout << t << "Read-only functions:\n";
            cout << t+t << "Float::sign(): "
                << subject4.sign() << " : "
                << pass(subject4.sign() == -1)
            << '\n';
            cout << t+t << "Float::sci_note(): "
                << subject4.sci_note() << " : "
                << pass(subject4.sci_note() == "-1.23847E21")
            << '\n';
            cout << t+t << "Float::sci_note(size_t): "
                << subject4.sci_note(15) << " : "
                << pass(subject4.sci_note(15) == "-1.238471239487121E21")
            << '\n';
            cout << t+t << "Float::sci_note_w_spaces(): "
                << subject4.sci_note_w_spaces() << " : "
                << pass(subject4.sci_note_w_spaces() == "- 1.23847 E 21")
            << '\n';
            cout << t+t << "Float::magnitude(): "
                << subject4.magnitude().str() << " : "
                << pass(subject4.magnitude().str() == "+1238471239487121212983.7562837642387")
            << '\n';
            cout << t+t << "Float::count_digits(): "
                << subject4.count_digits() << " : "
                << pass(subject4.count_digits() == 35)
            << '\n';
            cout << t+t << "Float::count_left_digits(): "
                << subject4.count_left_digits() << " : "
                << pass(subject4.count_left_digits() == 22)
            << '\n';
            cout << t+t << "Float::count_right_digits(): "
                << subject4.count_right_digits() << " : "
                << pass(subject4.count_right_digits() == 13)
            << '\n';
            cout << t+t << "Float::precision(): "
                << subject4.precision() << " : "
                << pass(subject4.precision() == 100)
            << '\n';
    Float subject5(70);
            cout << t+t << "Float::compare(const Float&): "
                << subject4.compare(subject5) << " : "
                << pass(subject4.compare(subject5) == -1)
            << '\n';
            cout << t+t << "Float::integer(): "
                << subject4.integer().str() << " : "
                << pass(subject4.integer() == Int("-1238471239487121212983"))
            << '\n';
    subject4.show_full(true);
            cout << t+t << "Float::show_full(): "
                << subject4.str()
            << '\n';
    subject4.show_full(false);
            cout << t+t << "Float::remainder(): "
                << subject4.remainder(subject5).str(10) << " : "
                << pass(subject4.remainder(subject5) == subject4 % subject5)
            << '\n';
            cout << t+t << "Float::operator-(): "
                << (-subject4).str() << " : "
                << pass(-subject4 == subject4.magnitude())
            << '\n';
    subject4 = Float("-789456123.123456789");
    subject5 = Float("456789.1231230");
        cout << t << "Arithmetic operators:\n";
            cout << t+t << "Float::operator+=(const Float&): "
                << (subject5 + subject4).str() << " : "
                << pass((subject5 + subject4) == Float("-788999334.000333789"))
            << '\n';
            cout << t+t << "Float::operator-=(const Float&): "
                << (subject5 - subject4).str() << " : "
                << pass((subject5 - subject4) == Float("+789912912.246579789"))
            << '\n';
            cout << t+t << "Float::operator*=(const Float&): "
                << (subject5 * subject4).str() << " : "
                << pass((subject5 * subject4) == Float("-360614970225646.9505198912320470"))
            << '\n';
            cout << t+t << "Float::operator/=(const Float&): "
                << (subject4 / subject5).str(9) << " : "
                << pass(Float(subject4 / subject5).str(9) == "-1728.272594859")
            << '\n';
    subject4 = 2.5;
    subject5 = 7.0;
            cout << t+t << "Float::operator%=(const Float&): "
                << (subject4 % subject5).str(10) << " : "
                << pass(Float(subject4 % subject5).str(10) == "+.3571428571")
            << '\n';
    subject5 = 7.6;
            cout << t+t << "Float::operator^=(const Int&): "
                << (subject4 ^ Int(7)).str() << " : "
                << pass(Float(subject4 ^ Int(7)).str() == "+610.3515625")
            << '\n';

            cout << t+t << "Float::operator^=(const Float&): "
                << (subject4 ^ subject5).str(10) << " : "
                << pass(Float(subject4 ^ subject5).str(10) == "+1057.6550951464")
            << '\n';

    subject4 = "56034.7890"_Precision_Float;
            cout << t+t << "operator\"\" _Precision_Float(char const *const,size_t): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+56034.789")
            << '\n';
    subject4 = "56012.38"_Precision_Float_E;
            cout << t+t << "operator\"\" _Precision_Float_E(char const *const,size_t): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+56012.38")
            << '\n';
    subject4 = "11.2387611E-5"_Precision_Float_E;
            cout << t+t << "operator\"\" _Precision_Float_E(char const *const,size_t): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+.000112387611")
            << '\n';
    subject4 = "11.23E5"_Precision_Float_E;
            cout << t+t << "operator\"\" _Precision_Float_E(char const *const,size_t): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+1123000.0")
            << '\n';
    subject4 = "123E3"_Precision_Float_E;
            cout << t+t << "operator\"\" _Precision_Float_E(char const *const,size_t): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+123000.0")
            << '\n';
    subject4 = 128.374_Precision_Float;
            cout << t+t << "operator\"\" _Precision_Float(unsigned long long): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+128.374")
            << '\n';
    subject4 = 128374_Precision_Float;
            cout << t+t << "operator\"\" _Precision_Float(unsigned long long): "
                << subject4.str() << " : "
                << pass(subject4.str() == "+128374.0")
            << '\n';


/********************UFloat********************************/
    UFloat subject6;
    cout << "\nPrecision::UFloat:\n";
        cout << t << "Constructors:\n";
            cout << t+t << "UFloat::UFloat(): "
                << subject6.str() << " : "
                << pass(subject6 == 0)
            << '\n';
    subject6 = UFloat(12983.4798);
            cout << t+t << "UFloat::UFloat(long double): "
                << subject6.str() << " : "
                << pass(subject6 == 12983.4798)
            << '\n';
    subject6 = UFloat("-0001238471239487121212983.7562837642387");
            cout << t+t << "UFloat::UFloat(string, short): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+1238471239487121212983.7562837642387")
            << '\n';
        cout << t << "Read-only functions:\n";
            cout << t+t << "UFloat::sci_note(): "
                << subject6.sci_note() << " : "
                << pass(subject6.sci_note() == "+1.23847E21")
            << '\n';
            cout << t+t << "UFloat::sci_note(size_t): "
                << subject6.sci_note(15) << " : "
                << pass(subject6.sci_note(15) == "+1.238471239487121E21")
            << '\n';
            cout << t+t << "UFloat::sci_note_w_spaces(): "
                << subject6.sci_note_w_spaces() << " : "
                << pass(subject6.sci_note_w_spaces() == "+ 1.23847 E 21")
            << '\n';
            cout << t+t << "UFloat::count_digits(): "
                << subject6.count_digits() << " : "
                << pass(subject6.count_digits() == 35)
            << '\n';
            cout << t+t << "UFloat::count_left_digits(): "
                << subject6.count_left_digits() << " : "
                << pass(subject6.count_left_digits() == 22)
            << '\n';
            cout << t+t << "UFloat::count_right_digits(): "
                << subject6.count_right_digits() << " : "
                << pass(subject6.count_right_digits() == 13)
            << '\n';
            cout << t+t << "UFloat::precision(): "
                << subject6.precision() << " : "
                << pass(subject6.precision() == 100)
            << '\n';
    UFloat subject7(70);
            cout << t+t << "UFloat::compare(const UFloat&): "
                << subject6.compare(subject7) << " : "
                << pass(subject6.compare(subject7) == 1)
            << '\n';
            cout << t+t << "UFloat::integer(): "
                << subject6.integer().str() << " : "
                << pass(subject6.integer() == Int("+1238471239487121212983"))
            << '\n';
    subject6.show_full(true);
            cout << t+t << "UFloat::show_full(): "
                << subject6.str()
            << '\n';
    subject6.show_full(false);
            cout << t+t << "UFloat::remainder(): "
                << subject6.remainder(subject7).str(10) << " : "
                << pass(subject6.remainder(subject7) == subject6 % subject7)
            << '\n';
            cout << t+t << "UFloat::operator-(): "
                << (-subject6).str() << " : "
                << pass((-subject6).str() == "-1238471239487121212983.7562837642387")
            << '\n';
    subject6 = UFloat("-789456123.123456789");
    subject7 = UFloat("456789.1231230");
        cout << t << "Arithmetic operators:\n";
            cout << t+t << "UFloat::operator+=(const UFloat&): "
                << (subject7 + subject6).str() << " : "
                << pass((subject7 + subject6) == UFloat("+789912912.246579789"))
            << '\n';
            cout << t+t << "UFloat::operator-=(const UFloat&): "
                << (subject7 - subject6).str() << " : "
                << pass((subject7 - subject6) == UFloat("0"))
            << '\n';
            cout << t+t << "UFloat::operator*=(const UFloat&): "
                << (subject7 * subject6).str() << " : "
                << pass((subject7 * subject6) == UFloat("+360614970225646.9505198912320470"))
            << '\n';
            cout << t+t << "UFloat::operator/=(const UFloat&): "
                << (subject6 / subject7).str(9) << " : "
                << pass(UFloat(subject6 / subject7).str(9) == "+1728.272594859")
            << '\n';
    subject6 = 2.5;
    subject7 = 7.0;
            cout << t+t << "UFloat::operator%=(const UFloat&): "
                << (subject6 % subject7).str(10) << " : "
                << pass(UFloat(subject6 % subject7).str(10) == "+.3571428571")
            << '\n';
    subject7 = 7.6;
            cout << t+t << "UFloat::operator^=(const Int&): "
                << (subject6 ^ Int(7)).str() << " : "
                << pass(UFloat(subject6 ^ Int(7)).str() == "+610.3515625")
            << '\n';
/*
            cout << t+t << "UFloat::operator^=(const UFloat&): "
                << (subject6 ^ subject7).str() << " : "
       //         << pass(UFloat(subject6 ^ subject7).str(8) == "+1057.65509515")
            << '\n';
*/
    subject6 = "56034.7890"_Precision_UFloat;
            cout << t+t << "operator\"\" _Precision_UFloat(char const *const,size_t): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+56034.789")
            << '\n';
    subject6 = "56012.38"_Precision_UFloat_E;
            cout << t+t << "operator\"\" _Precision_UFloat_E(char const *const,size_t): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+56012.38")
            << '\n';
    subject6 = "11.2387611E-5"_Precision_UFloat_E;
            cout << t+t << "operator\"\" _Precision_UFloat_E(char const *const,size_t): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+.000112387611")
            << '\n';
    subject6 = "11.23E5"_Precision_UFloat_E;
            cout << t+t << "operator\"\" _Precision_UFloat_E(char const *const,size_t): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+1123000.0")
            << '\n';
    subject6 = "123E3"_Precision_UFloat_E;
            cout << t+t << "operator\"\" _Precision_UFloat_E(char const *const,size_t): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+123000.0")
            << '\n';
    subject6 = 128.374_Precision_UFloat;
            cout << t+t << "operator\"\" _Precision_UFloat(unsigned long long): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+128.374")
            << '\n';
    subject6 = 128374_Precision_UFloat;
            cout << t+t << "operator\"\" _Precision_UFloat(unsigned long long): "
                << subject6.str() << " : "
                << pass(subject6.str() == "+128374.0")
            << '\n';
    cout << "Precision::Fract:\n";
        cout << t << "Constructors:\n";
    Fract subject8;
            cout << t+t << "Fract::Fract(): "
                << subject8.str() << " : "
                << pass(subject8.str() == "+0/1")
            << '\n';
    subject8 = Fract(18237.293845);
            cout << t+t << "Fract::Fract(long double): "
                << subject8.str() << " : "
                << pass(subject8.str() == "+3647458769/200000")
            << '\n';
    subject8 = Fract(Float("3.285714285714285714", 18));
            cout << t+t << "Fract::Check_Pattern(Str, Float): "
                << subject8.str() << " : "
                << pass(subject8.str() == "+23/7")
            << '\n';
    subject8 = Fract("-1928379182471235.2837098749648");
            cout << t+t << "Fract::Fract(Str): "
                << subject8.str() << " : "
                << pass(subject8.str() == "-1205236989044522052318671853/625000000000")
            << '\n';
    subject8 = Fract("237468237623432"_Precision_Int);
            cout << t+t << "Fract::Fract(Integer): "
                << subject8.str() << " : "
                << pass(subject8.str() == "+237468237623432/1")
            << '\n';
    subject8 = Fract("-127461249.023940298"_Precision_Float);
            cout << t+t << "Fract::Fract(Float): "
                << subject8.str() << " : "
                << pass(subject8.str() == "-63730624511970149/500000000")
            << '\n';
    subject8 = Fract("-183744729784326996655298477496546"_Precision_Int, "5052980069068992408020708131155015"_Precision_Int);
            cout << t+t << "Fract::Fract(Integer, Integer): "
                << subject8.str() << " : "
                << pass(subject8.str() == "-2/55")
            << '\n';
        cout << t << "Read-only functions:\n";
            cout << t+t << "Fract::sign(): "
                << subject8.sign() << " : "
                << pass(subject8.sign() == -1)
            << '\n';
            cout << t+t << "Fract::numerator(): "
                << subject8.numerator().str() << " : "
                << pass(subject8.numerator() == -2_Precision_Int)
            << '\n';
            cout << t+t << "Fract::denominator(): "
                << subject8.denominator().str() << " : "
                << pass(subject8.denominator() == 55_Precision_Int)
            << '\n';
    subject8 = Fract(Int(-1244), Int(56));
            cout << t+t << "Fract::mixed(): "
                << subject8.mixed() << " : "
                << pass(subject8.mixed() == "-22 3/14")
            << '\n';
            cout << t+t << "Fract::magnitude(): "
                << subject8.magnitude().str() << " : "
                << pass(subject8.magnitude().str() == "+311/14")
            << '\n';
            cout << t+t << "Fract::precision(): "
                << subject8.precision() << " : "
                << pass(subject8.precision() == 100)
            << '\n';
            cout << t+t << "Fract::whole(): "
                << subject8.whole().str() << " : "
                << pass(subject8.whole().str() == "-22")
            << '\n';
            cout << t+t << "Fract::decimal(): "
                << subject8.decimal().str(5) << " : "
                << pass(subject8.decimal().str(5) == "-22.21428")
            << '\n';
    Fract subject9(Int(6576321), Int(449519));
            cout << t+t << "Fract::gcd(Fract): "
                << subject8.gcd(subject9).str() << " : "
                << pass(subject8.gcd(subject9).str() == "+7")
            << '\n';
            cout << t+t << "Fract::remainder(Fract): "
                << subject8.remainder(subject9).str() << " : "
                << pass(subject8.remainder(subject9).str() == "-6818845/13152642")
            << '\n';
        cout << t << "Arithmetic Operators:\n";
            cout << t+t << "Fract::operator+=(Fract): "
                << (subject8 + subject9).str() << " : "
                << pass((subject8 + subject9).str() == "-6818845/899038")
            << '\n';
            cout << t+t << "Fract::operator-=(Fract): "
                << (subject8 - subject9).str() << " : "
                << pass((subject8 - subject9).str() == "-33124129/899038")
            << '\n';
            cout << t+t << "Fract::operator*=(Fract): "
                << (subject8 * subject9).str() << " : "
                << pass((subject8 * subject9).str() == "-2045235831/6293266")
            << '\n';
            cout << t+t << "Fract::operator/=(Fract): "
                << (subject8 / subject9).str() << " : "
                << pass((subject8 / subject9).str() == "-19971487/13152642")
            << '\n';
            cout << t+t << "Fract::operator-(): "
                << (-subject8).str() << " : "
                << pass((-subject8).str() == "+311/14")
            << '\n';
            cout << t+t << "Fract::operator~(): "
                << (~subject8).str() << " : "
                << pass((~subject8).str() == "-14/311")
            << '\n';
    subject0 = 80;
            cout << t+t << "Fract::operator^=(Int): "
                << (subject8 ^ subject0).str() << " : "
                << pass((subject8 ^ subject0).str()
                    == "+263530643282403693186533245135848"
                    "9727201635742670117039853698383417424"
                    "6787709309998651364251605086213452032"
                    "4039347027852710239986242482116202132"
                    "0092286412309674160891192907918036418"
                    "5975891637205660801/49005277664853092"
                    "6503925164706454801750793782124721438"
                    "88975139770441605011777683293445554176"
                )
            << '\n';



/********************Precision Math********************************/
    cout << "\nPrecision Math:\n";
    subject0 = Sqrt(Int(50625));
            cout << t+t << "Sqrt(Int): "
                << subject0.str() << " : "
                << pass(subject0.str() == Int::Str("+225"))
            << '\n';
    subject4 = Float("872364872.2348172");
    subject4 = Sqrt(subject4, subject4.precision()/5);
            cout << t+t << "Sqrt(Float): "
                << subject4.str() << " : "
                << pass(subject4.str(10) == Float::Str("+29535.8235408260"))
            << '\n';
    subject0 = Pow(Int(123), Int(40));
            cout << t+t << "Pow(Int, Int): "
                << subject0.str() << " : "
                << pass(subject0.str() == Int::Str("+394643048784752"
                    "3963424972575073648786068041972683918764049885"
                    "52236061387660472578401")
                    )
            << '\n';
    subject0 = Factorial(400);
            cout << t+t << "Factorial(Int): "
                << subject0.sci_note(11) << " : "
                << pass(subject0.sci_note(11) == ("+6.40345228466E868"))
            << '\n';
    subject0 = GCF(Int("1083901458"), string("7650399054"));
            cout << t+t << "GCF(Int): "
                << subject0.str() << " : "
                << pass(subject0.str() == "+876234")
            << '\n';
            cout << t+t << "Num_to_Words(Int): "
                << Num_to_Words("10283479821734098625872648767283737"_Precision_Int)
            << '\n';
/*
    Rand(chrono::system_clock::now().time_since_epoch().count());
    cout << "Random:\n";
    Int seed(0);
    for(size_t i(0); i < 100; ++i)
        seed = Rand(), cout << "\t#" << i+1 << ": " << Rand(seed).str() << '\n';
*/
//cin.get();

    return 0;

}
