namespace Precision{
    namespace General_Base{
    //Read-only
        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::seed()const{return m_seed;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::max()const{return m_max;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::min()const{return m_min;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::and1()const{return m_and1;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::and2()const{return m_and2;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::and3()const{return m_and3;}

        template <typename Integer_Type>
        const Integer_Type& Random<Integer_Type>::and4()const{return m_and4;}

        template <typename Integer_Type>
        typename Integer_Type::lli Random<Integer_Type>::order_of_entropy()const
            {return m_order_of_entropy;}

        template <typename Integer_Type>
        size_t Random<Integer_Type>::push1()const{return m_push1;}

        template <typename Integer_Type>
        size_t Random<Integer_Type>::push2()const{return m_push2;}

        template <typename Integer_Type>
        size_t Random<Integer_Type>::push3()const{return m_push3;}

        template <typename Integer_Type>
        constexpr typename Integer_Type::digit_10_type
            Random<Integer_Type>::base()
        {return (type::base());}

    //Retrive and/or change state

        template <typename Integer_Type>
        Integer_Type Random<Integer_Type>::operator()(){
        //Algorithm is a modified form of the SFMT as described in this paper:
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/sfmt.pdf
            typename type::str_type image(m_seed.str());
            const size_t quad(image.size()/4);
            type
                word_1(image.substr(0, quad)),
                word_2(image.substr(quad+1, quad)),
                word_3(image.substr(2*quad+1, quad)),
                word_4(image.substr(3*quad+1))
            ;
            m_seed.shift(m_order_of_entropy);
            image =
                m_seed
                . logical_shift_left(m_push1)
                . logical_xor(m_seed)                                   //wA

                . logical_xor(type(
                    word_1
                        . logical_shift_right(m_push2)
                        . logical_and(m_and1)
                        . str()
                    + word_2
                        . logical_shift_right(m_push2)
                        . logical_and(m_and2)
                        . str()
                        . substr(1)
                    + word_3
                        . logical_shift_right(m_push2)
                        . logical_and(m_and3)
                        . str()
                        . substr(1)
                    + word_4
                        . logical_shift_right(m_push2)
                        . logical_and(m_and4)
                        . str()
                        . substr(1)
                    ))                                                  //wB
                . logical_xor(m_seed.logical_shift_right(m_push1))      //wC
                . logical_xor(m_seed.logical_shift_left(m_push3))       //wD
                . str()
                . substr(1)
            ;

            std::reverse(image.begin(), image.end());
            return m_seed = (type(image)%(m_max-m_min) + m_min);
        }

        template <typename Integer_Type>
        void Random<Integer_Type>::discard(){this->operator()();}
    //Change settings

        template <typename Integer_Type>
        void Random<Integer_Type>::seed(const type& new_seed)
            {m_seed = new_seed;}

        template <typename Integer_Type>
        void Random<Integer_Type>::max(const type& new_max)
            {m_max = new_max;}

        template <typename Integer_Type>
        void Random<Integer_Type>::min(const type& new_min)
            {m_min = new_min;}

        template <typename Integer_Type>
        void Random<Integer_Type>::and1(const type& a1){m_and1 = a1;}

        template <typename Integer_Type>
        void Random<Integer_Type>::and2(const type& a2){m_and1 = a2;}

        template <typename Integer_Type>
        void Random<Integer_Type>::and3(const type& a3){m_and1 = a3;}

        template <typename Integer_Type>
        void Random<Integer_Type>::and4(const type& a4){m_and1 = a4;}

        template <typename Integer_Type>
        void Random<Integer_Type>::order_of_entropy(typename type::lli ooe)
            {m_order_of_entropy = ooe;}

        template <typename Integer_Type>
        void Random<Integer_Type>::push1(size_t p1){m_push1 = p1;}

        template <typename Integer_Type>
        void Random<Integer_Type>::push2(size_t p2){m_push1 = p2;}

        template <typename Integer_Type>
        void Random<Integer_Type>::push3(size_t p3){m_push1 = p3;}

    //Constructor

        template <typename Integer_Type>
        Random<Integer_Type>::Random(
            const type& INseed,
            const type& INmax, const type& INmin,
            typename type::lli INorder_of_entropy,
            const type& INand1, const type& INand2,
            const type& INand3, const type& INand4,
            size_t INpush1, size_t INpush2, size_t INpush3,
            bool call_discard
        )
            : m_seed(INseed.positive() ? INseed : 1)
            , m_max(INmax), m_min(INmin)
            , m_and1(INand1), m_and2(INand2), m_and3(INand3), m_and4(INand4)
            , m_order_of_entropy(INorder_of_entropy)
            , m_push1(INpush1), m_push2(INpush2), m_push3(INpush3)
        {
            if(call_discard){
                size_t i(7);
                while(i-- > 0)
                    this->discard();
            }
        }
    }
}
