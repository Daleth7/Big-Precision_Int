#include <type_traits>
#include "Precision_Tags.h"

namespace Precision{
    template <typename Number_Type>
    Number_Type sqrt(const Number_Type& base){
        if(base.sign() < 0)
            return -1;
        else if(base == Number_Type(0) || base == Number_Type(1))
            return base;
    //Uses Babylonian method:
    //  http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    //      #Babylonian_method
        Number_Type toreturn(base/Number_Type(2)), old(0);
        while(old != toreturn){
            old = toreturn;
            toreturn = (toreturn + base/toreturn)/Number_Type(2);
        }
        return toreturn;
    }
    

    template <typename Number_Type, typename Integer_Type>
    Number_Type root(const Number_Type& base, const Integer_Type& n){
        if(base.sign() < 0)
            return -1;
        else if(base == Number_Type(0) || base == Number_Type(1))
            return base;
    //Newton's method
        Number_Type toreturn(base/n), old(0);
        while(old != toreturn){
            old = toreturn;
            toreturn = ((n-1)*toreturn + base/exponentiate(toreturn, n))/n;
        }
        return toreturn;
    }

    template <typename Integer_Type>
    Integer_Type factorial_range(const Integer_Type& f, const Integer_Type& s){
        if(s == f)
            return s;
        else if(s < f)
            return 1;
        else if(f+Integer_Type(1) == s)
            return f*s;
        else
            return factorial_range(
                f
                , (f+s)/Integer_Type(2))
            * factorial_range(
                (f+s)/Integer_Type(2)+Integer_Type(1)
                , s
            );
    }

    template <typename Number_Type>
    Number_Type gamma_helper(const Number_Type& z, size_t start, size_t lim){
        //Used to help find the product of a sequence, or capital PI
        //  Use the divide and conquer technique to ease the multiplications
        if(lim < start)
            return z;
        else if(start == lim)
            return z+Number_Type(start);
        else if(lim - 1 == start)
            return (z+Number_Type(start))*(z+Number_Type(lim));
        else
            return gamma_helper(z, start, lim/2)*gamma_helper(z, lim/2+1, lim);
    }

    template <typename Number_Type>
    Number_Type factorial_gamma(const Number_Type& z, size_t lim){
        //Based on Euler's gamma function
        using int_type = typename Number_Type::Integer;
        return
            exponentiate(Number_Type(lim), z)
            * factorial_range(int_type(2), int_type(lim))
            / gamma_helper(z, 0, lim)
        ;
    }

    template <typename Integer_Type>
    Integer_Type factorial_sift(const Integer_Type& start, std::true_type){
        if(start < Integer_Type(2))   return 1;
        return factorial_range(Integer_Type(2), start);
    }

    template <typename Number_Type>
    Number_Type factorial_sift(const Number_Type& start, std::false_type){
        if(start.is_integer())
            return factorial_sift(start.integer(), std::true_type());
        else
            return factorial_gamma(start, start.precision());
    }

    template <typename Integer_Type>
    Integer_Type factorial(const Integer_Type& start){
        return factorial_sift(start
            , typename std::is_base_of<Tag::Integral, Integer_Type>::type());
    }

    template <typename Floating_Type>
    Floating_Type nlog(Floating_Type f){
        if(f <= Floating_Type(0) || f == Floating_Type(1))  return 0;

        long long int i(1);
        bool over(f > Floating_Type(1));
        if(over)
            f = (f/(f-Floating_Type(1)));
        Floating_Type toreturn(0), old(-1);
        while(old != toreturn){
            old = toreturn;
            toreturn
                += over
                    //Taylor series of ln(y) where y = x/(x-1)
                ? ( Floating_Type(1)/(i*exponentiate(f, i)) )
                    //Taylor series of ln(a-1)
                : ( (i%2 ? 1 : -1)*exponentiate(f-1, i)/i )
            ;
            ++i;
        }
        return toreturn;
    }

    template <typename Floating_Type>
    Floating_Type log(const Floating_Type& b)
        {return nlog(b)/nlog(10);}

    template <typename Floating_Type>
    Floating_Type log(
        const Floating_Type& x,
        const Floating_Type& base
    ){return nlog(x)/nlog(base);}

    template <typename Floating_Type>
    Floating_Type exp(const Floating_Type& e, size_t precision){
        typename Floating_Type::Integer n = precision;
        n.shift_left(10);
        return exponentiate((1+e/n), n);
    }

    template <typename Number_Type, typename Integer_Type>
    Number_Type exponentiate(const Number_Type& base, Integer_Type e){
        if(e == Integer_Type(0))       return 1;
        else if(e == Integer_Type(1))  return base;
        else if(e == Integer_Type(-1)) return Number_Type(1) / base;
        Number_Type operand(base);
        if(e < Integer_Type(0))
            operand = Number_Type(1)/operand, e *= -1;
            //Exponentiation by squaring
        if(e % Integer_Type(2) == Integer_Type(0))
            return exponentiate( (operand * operand), (e/Integer_Type(2)) );
        else
            return operand * exponentiate( operand, (e - Integer_Type(1)) );
    }

    template <typename Number_Type>
    Number_Type exponentiate(
        const Number_Type& base,
        const Number_Type& e,
        size_t precision
    ){
        if(e == Number_Type(0))                return 1;
        else if(e == Number_Type(1))           return base;
        else if(e == Number_Type(-1))          return Number_Type(1) / base;
        else if(e.is_integer())   return exponentiate(base, e.integer());

        return exp(
            nlog(e.sign().positive() ? base : (Number_Type(1) / base))
            * e.magnitude()
            , precision
        );
    }

    template <typename Number_Type>
    Number_Type gcd(const Number_Type& a, const Number_Type& b){
//Euclid's Algorithm:
//http://en.wikipedia.org/wiki/Greatest_common_divisor#Using_Euclid.27s_algorithm
        Number_Type toreturn(a), prev(b);
        while(prev != Number_Type(0)){
            toreturn %= prev;
            std::swap(toreturn, prev);
        }
        return toreturn;
    }

    template <typename Number_Type>
    Number_Type gcf(const Number_Type& a, const Number_Type& b)
        {return (a*b)/gcd(a, b);}

    template <typename Number_Type>
    Number_Type agm(const Number_Type& _1, const Number_Type& _2){
        if(_1.sign() != _2.sign()) return 0;
        Number_Type a(_1), g(_2);
        while(a.str(a.precision()/4) != g.str(a.precision()/4)){
            Number_Type hold(a);
            (a += g)/=2;
            g = sqrt(hold*g);
        }
        return a;
    }
}
