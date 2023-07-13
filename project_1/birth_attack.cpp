#include <iostream>
#include "cryptlib.h"
#include  "hex.h"
#include "sm3.h"
#include "filters.h"
#include "randpool.h"
#include "osrng.h"
#include "files.h"
#include <windows.h>

using namespace std;
using namespace CryptoPP;

void collisionAttack( int hashSize)
{
    SM3 sm3;
    AutoSeededRandomPool prng;

    byte* msg1 = new byte[hashSize];
    byte* msg2 = new byte[hashSize];
    int i = 0;
    while (true) {
        i++;
        // 生成随机消息
        cout << "探索" << i << endl;
        prng.GenerateBlock(msg1, hashSize);
        prng.GenerateBlock(msg2, hashSize);

        // 计算哈希值
        byte hash1[32], hash2[32];
        sm3.CalculateDigest(hash1, msg1, hashSize);
        sm3.CalculateDigest(hash2, msg2, hashSize);

        // 检查哈希碰撞
        if (memcmp(hash1, hash2, hashSize) == 0){
            break;
        }
    }

    // 输出碰撞结果
    std::cout << "Message 1: ";
    StringSource(msg1, hashSize, true, new HexEncoder(new FileSink(std::cout)));
    std::cout << std::endl;

    std::cout << "Message 2: ";
    StringSource(msg2, hashSize, true, new HexEncoder(new FileSink(std::cout)));
    std::cout << std::endl;

    delete[] msg1;
    delete[] msg2;
}

int main()
{
    int hashSize = 1; // 设置哈希值大小
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    collisionAttack(hashSize);
    QueryPerformanceCounter(&t2);
    double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    printf("%fs", time);

    return 0;
}
