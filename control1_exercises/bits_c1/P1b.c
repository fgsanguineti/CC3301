unsigned repBits(unsigned x, int i, int k, unsigned val){
    unsigned wea = ~((-1)<< k);

    unsigned mask = (val & wea) << i;


    unsigned wea2 = ~(wea<< i);

    unsigned pre_resultado = wea2 & x;
    return pre_resultado | mask;
}