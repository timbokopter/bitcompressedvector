#include "bcv.h"
#include "decompress2.h"
#include "test.h"
#include "Timer.h"
#include "PapiTracer.h"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>

#include <emmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>

template<int BITS>
void performance(size_t size)
{
    BitCompressedVector<int, BITS> v(size);
    std::vector<int> v2(size);

    fill<BitCompressedVector<int, BITS>, BITS>(v, size);
    fill<std::vector<int>, BITS>(v2, size);

    double a,b,c,d,e;

    Timer t;
    long long res = 0;
    std::cout << "# BITS res get res get[] res mget res vector" << std::endl;
    ///////////////////////////////////////////////////////////////////////////
    t.start();
    for(size_t i=0; i < size; i+=1)  
    {
        res += v.get(i);                
    }
    t.stop();
    std::cout << BITS << " " << res << " " << (a = t.elapsed_time());

    ///////////////////////////////////////////////////////////////////////////
    res = 0;
    t.start();
    for(size_t i=0; i < size; i+=1)  
    {
        res += v[i];                
    }
    t.stop();
    std::cout << " " << res << " " << (b = t.elapsed_time()) << " ";


    ///////////////////////////////////////////////////////////////////////////
    res = 0;
    size_t alloca = 1000;
    int *tmp = (int*) malloc(sizeof(int) * alloca);

    size_t actual;
    t.start();
    for(size_t i=0; i < size; )       
    {
        actual = 0;
        v.mget(i, tmp, &actual);
        //for(size_t j=0; j < actual & i < size; ++j)
        res += tmp[0];
        i += actual;

        v.mget(i, tmp, &actual);
        //for(size_t j=0; j < actual & i < size; ++j)
        res += tmp[0];
        i += actual;

        v.mget(i, tmp, &actual);
        //for(size_t j=0; j < actual & i < size; ++j)
        res += tmp[0];
        i += actual;

        v.mget(i, tmp, &actual);
        //for(size_t j=0; j < actual & i < size; ++j)
        res += tmp[0];
        i += actual;

    }
    t.stop();
    std::cout << res << " " << (c = t.elapsed_time()) << " ";
    //std::cout << papi.first << " " << papi.second << std::endl;
    free(tmp);

    ///////////////////////////////////////////////////////////////////////////
    // VErtical
    res = 0;
    alloca = 100000;
    tmp = (int*) malloc(sizeof(int) * alloca);

    __m128i *data = reinterpret_cast<__m128i*>(v.getData()); 
    t.start();
    for(size_t i=0; i < size; )       
    {
        actual = 0;
        
        VerticalBitCompression<BITS>::decompress(data, tmp, &actual);
        res += tmp[0];
        i += actual;        
        ++data;

        VerticalBitCompression<BITS>::decompress(data, tmp, &actual);
        res += tmp[0];
        i += actual;        
        ++data;

        VerticalBitCompression<BITS>::decompress(data, tmp, &actual);
        res += tmp[0];
        i += actual;        
        ++data;

        VerticalBitCompression<BITS>::decompress(data, tmp, &actual);
        res += tmp[0];
        i += actual;        
        ++data;

    }
    t.stop();
    std::cout << res << " " << (c = t.elapsed_time()) << " ";
    //std::cout << papi.first << " " << papi.second << std::endl;
    free(tmp);

    
    ///////////////////////////////////////////////////////////////////////////
    res = 0;
    t.start();
    for(size_t i=0; i < size; i+=16)  
    {
        res += v2[i];
        res += v2[i+1];
        res += v2[i+2];
        res += v2[i+3];
        res += v2[i+4];
        res += v2[i+5];
        res += v2[i+6];
        res += v2[i+7];
        res += v2[i+8];
        res += v2[i+9];
        res += v2[i+10];
        res += v2[i+11];
        res += v2[i+12];
        res += v2[i+13];
        res += v2[i+14];
        res += v2[i+15];
    }
    t.stop();
    std::cout << res << " " << (e = t.elapsed_time()) << std::endl;
}


int main(int argc, char* argv[])
{
    // Setting size
    long SIZE = atol(argv[1]);

    //pshufb_test(SIZE);
    #ifndef NDEBUG
    runTests();
    #endif

    // performance<1>(SIZE);
    // std::cout << "#---" << std::endl;
    performance<2>(SIZE);
    std::cout << "#---" << std::endl;
    // performance<3>(SIZE);
    // std::cout << "#---" << std::endl;
    performance<4>(SIZE);
    std::cout << "#---" << std::endl;
    // performance<5>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<6>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<7>(SIZE);
    // std::cout << "#---" << std::endl;
    performance<8>(SIZE);
    std::cout << "#---" << std::endl;
    // performance<9>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<10>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<11>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<12>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<13>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<14>(SIZE);
    // std::cout << "#---" << std::endl;
    // performance<15>(SIZE);
    // std::cout << "#---" << std::endl;
    performance<16>(SIZE);
    std::cout << "#---" << std::endl;

	return 0;
}
