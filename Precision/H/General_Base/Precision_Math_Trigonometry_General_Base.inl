#include "Precision_Math_Shared_Functions.h"
#include "Precision_Tags.h"

#include <type_traits>

namespace Precision{
    namespace General_Base{
        template <typename Number_Type>
        Number_Type sin(const Number_Type& angle, const Number_Type& pi_val){
            Number_Type toreturn(
                angle
                - (
                    angle > pi_val
                    ? 0
                    : Number_Type((angle/(Number_Type(2)*pi_val))
                        . integer())*pi_val
                )
            );
            if(toreturn == Number_Type(0) || toreturn.magnitude() == pi_val)
                return Number_Type(0);
            else if(toreturn*Number_Type(2) == pi_val)
                return Number_Type(angle.sign());
            Number_Type _x(toreturn), fact(1);
            const Number_Type _x_2(toreturn*toreturn);
            typename Number_Type::size_type i(1);
            while(true){
                const Number_Type old(toreturn);    _x.negate();    i += 2;
                toreturn += (_x *= _x_2)/(fact *= Number_Type(i * (i-1)));
                if(old == toreturn)
                    return toreturn;
            }
        }

        template <typename Number_Type>
        Number_Type cos(const Number_Type& angle, const Number_Type& pi_val)
            {return sin(angle + pi_val/Number_Type(2), pi_val);}

        template <typename Number_Type>
        Number_Type tan(const Number_Type& angle, const Number_Type& pi_val)
            {return sin(angle, pi_val)/cos(angle, pi_val);}

        template <typename Number_Type>
        Number_Type csc(const Number_Type& angle, const Number_Type& pi_val)
            {return Number_Type(1)/sin(angle, pi_val);}

        template <typename Number_Type>
        Number_Type sec(const Number_Type& angle, const Number_Type& pi_val)
            {return Number_Type(1)/cos(angle, pi_val);}

        template <typename Number_Type>
        Number_Type cot(const Number_Type& angle, const Number_Type& pi_val)
            {return cos(angle, pi_val)/sin(angle, pi_val);}

        template <typename Number_Type>
        Number_Type arcsin(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Number_Type(2) - arccos(result, pi_val);}

        template <typename Number_Type>
        Number_Type arccos(const Number_Type& result, const Number_Type& pi_val)
            {return arcsec(Number_Type(1)/result, pi_val);}

        template <typename Number_Type>
        Number_Type arctan(const Number_Type& result, const Number_Type& pi_val){
            const short comp(result.magnitude().compare(1));
            if(comp == 0)       return Number_Type(0);
            else if(comp == 1)  return result.sign()*pi_val/Number_Type(4);

            Number_Type toreturn(result), _x(result), old(0);
            const Number_Type _x_2(result*result);
            typename Number_Type::size_type N(1);
            while(toreturn != old){
                old = toreturn;
                _x.negate();
                toreturn += (_x *= _x_2)/Number_Type(N += 2);
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccsc(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Number_Type(2) - arcsec(result, pi_val);}

        template <typename Number_Type>
        Number_Type arcsec(const Number_Type& result, const Number_Type& pi_val){
            const short comp(result.magnitude().compare(1));
            if(comp == 0)       return result.sign()*pi_val/Number_Type(2);
            else if(comp == 1)  return Number_Type(0);

            Number_Type
                toreturn(result), _x(result), old(0),
                _odds(1), _evens(1)
            ;
            const Number_Type _x_2(result*result);
            typename Number_Type::size_type N(0), i(1);
            while(toreturn != old){
                old = toreturn;
                ++N;
                toreturn += (
                    (_odds *= Number_Type(N*(N-1)))
                    / (_evens *= Number_type(2*N))
                    / (_x *= _x_2)
                    / Number_Type(i += 2)
                );
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccot(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Number_Type(2) - arctan(result, pi_val);}



        template <typename Number_Type>
        Number_Type sinh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){
            Number_Type toreturn(angle), _x(angle), old(0), D(1);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(old != toreturn){
                old = toreturn;
                N += 2;
                toreturn += (_x *= _x_2)/(D *= Number_Type(N*(N-1)));
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type cosh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return exp(angle) - sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type tanh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return sinh(angle, pi_val)/cosh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type csch(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return Number_Type(1)/sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type sech(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return Number_Type(1)/cosh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type coth(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return cosh(angle, pi_val)/sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type arcsinh(const Number_Type& angle){
            Number_Type toreturn(angle), _x(angle), old(0);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(old != toreturn){
                old = toreturn;
                _x.negate();
                Number_Type fact_sq(factorial(Number_Type(++N)));
                toreturn
                    = (_x *= _x_2)
                    * factorial(Number_Type(2*N))
                    / Number_Type(2*N+1)
                    / exponentiate(Number_Type(2), 2*N)
                    / (fact_sq * fact_sq)
                ;
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccosh(const Number_Type& angle){
            Number_Type e(Number_Type(2)*arctanh(angle));
            return e * (
                Number_Type(1)
                - angle
                - exp(-e) * (Number_Type(1) + sqrt(++(angle*angle)))
            );
        }

        template <typename Number_Type>
        Number_Type arctanh(const Number_Type& angle){
            Number_Type toreturn(angle), _x(angle), old(0);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(old != toreturn){
                old = toreturn;
                toreturn = (_x *= _x_2)/Number_Type(N += 2);
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccsch(const Number_Type& angle)
            {return arcsinh(Number_Type(1)/angle);}

        template <typename Number_Type>
        Number_Type arcsech(const Number_Type& angle)
            {return arccosh(Number_Type(1)/angle);}

        template <typename Number_Type>
        Number_Type arccoth(const Number_Type& angle)
            {return arctanh(Number_Type(1)/angle);}
    }
}