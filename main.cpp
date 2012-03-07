#include "bcv.h"
#include "Timer.h"

#include <algorithm>
#include <iostream>
#include <vector>

#define SIZE 1000000
#define BITS 5

int main(int argc, char* argv[])
{
        Timer t;
	BitCompressedVector<int> v(SIZE, BITS);
        vector<int> v2;

        long long res = 0;

	for(size_t i=0; i < SIZE; ++i)
	{
		v.set(i, i % (1 << BITS));
                v2.push_back(i % (1 << BITS));
	}

        t.start();
	for(size_t i=0; i < SIZE; ++i)	
	{
		res += v.get(i);
	}
        t.stop();
        std::cout << res << " time " << t.elapsed_time() << std::endl;

        res = 0;
        t.start();
        for(size_t i=0; i < SIZE; ++i)       
        {
                res += v2[i];
        }
        t.stop();
        std::cout << res << " time " << t.elapsed_time() << std::endl;
	
        if (argc > 1)
        {
                std::cout << "random access" << std::endl;
                std::vector<size_t> vPosList;
                for(size_t i=0; i < SIZE; ++i)
                        vPosList.push_back(i);

                std::random_shuffle(vPosList.begin(), vPosList.end());

                res = 0;
                t.start();
                for(size_t i=0; i < SIZE; ++i)       
                {
                        res += v.get(vPosList[i]);
                }
                t.stop();
                std::cout << res << " time " << t.elapsed_time() << std::endl;

                res = 0;
                t.start();
                for(size_t i=0; i < SIZE; ++i)       
                {
                        res += v2[vPosList[i]];
                }
                t.stop();
                std::cout << res << " time " << t.elapsed_time() << std::endl;
        }

	return 0;
}