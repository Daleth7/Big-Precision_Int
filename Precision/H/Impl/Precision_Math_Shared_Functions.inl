namespace Precision{
    template <typename Number_Type>
    Number_Type sqrt(const Number_Type& base, size_t precision){
        if(base.sign() < 0) return -1;
        else if(base == 0 || base == 1) return base;
    //Uses Babylonian method:
    //  http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    //      #Babylonian_method
        Number_Type toreturn(base/2);
        while(precision-- > 0)
            toreturn = (toreturn + base/toreturn)/2;
        return toreturn;
    }

    template <typename Integer_Type>
    Integer_Type factorial_range(const Integer_Type& f, const Integer_Type& s){
        if(s == f)
            return s;
        else if(s < f)
            return 1;
        else if(f+1 == s)
            return f*s;
        else
            return factorial_range(f, (f+s)/2) * factorial_range((f+s)/2+1, s);
    }

    template <typename Integer_Type>
    Integer_Type factorial(const Integer_Type& start){
        if(start < 2)   return 1;
        return factorial_range(Integer_Type(2), start);
    }

    template <typename Floating_Type>
    Floating_Type nlog(Floating_Type f, size_t precision){
        if(f <= 0)      return 0;
        else if(f == 1) return 0;
        Floating_Type toreturn(0);

        if(f > 1){  //Taylor series of ln(y) where y = x/(x-1)
            Floating_Type _x(f/(f-1));
            for(long long int i(1); i < precision; ++i)
                toreturn += (i*exponentiate(_x, i)).inverse();
        }else{  //Taylor series of ln(a-1)
            for(long long int i(1); i < precision; ++i)
                toreturn += (i%2 == 0 ? -1 : 1)*exponentiate(f-1, i)/i;
        }

        return toreturn;
    }

    template <typename Floating_Type>
    Floating_Type log(const Floating_Type& b, size_t precision)
        {return nlog(b, precision)/nlog(10, precision);}

    template <typename Floating_Type>
    Floating_Type log(
        const Floating_Type& x,
        const Floating_Type& base,
        size_t precision
    ){return nlog(x, precision)/nlog(base, precision);}

    template <typename Floating_Type>
    Floating_Type pow_e(const Floating_Type& e, size_t precision){
        typename Floating_Type::Integer n = precision*1e15;
        return exponentiate((1+e/n), n);
    }

    template <typename Number_Type, typename Integer_Type>
    Number_Type exponentiate(const Number_Type& base, Integer_Type exp){
        if(exp == Integer_Type(0))       return 1;
        else if(exp == Integer_Type(1))  return base;
        else if(exp == Integer_Type(-1)) return Number_Type(1) / base;
        Number_Type operand(base);
        if(exp < Integer_Type(0))
            operand = Number_Type(1)/operand, exp *= -1;
            //Exponentiation by squaring
        if(exp % Integer_Type(2) == Integer_Type(0))
            return exponentiate( (operand * operand), (exp/Integer_Type(2)) );
        else
            return operand * exponentiate( operand, (exp - Integer_Type(1)) );
    }

    template <typename Number_Type>
    Number_Type exponentiate(
        const Number_Type& base,
        const Number_Type& exp,
        size_t precision
    ){
        if(exp == 0)                return 1;
        else if(exp == 1)           return base;
        else if(exp == -1)          return 1 / base;
        else if(exp.is_integer())   return exponentiate(base, exp.integer());

        return pow_e(
            nlog(exp.sign() > 0 ? base : base.inverse(), precision)
            * exp.magnitude(), precision);
    }

    template <typename Number_Type>
    Number_Type gcd(const Number_Type& a, const Number_Type& b){
//Euclid's Algorithm:
//http://en.wikipedia.org/wiki/Greatest_common_divisor#Using_Euclid.27s_algorithm
        Number_Type toreturn(a), prev(b);
        while(prev != 0){
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