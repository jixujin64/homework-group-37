#include <iostream>
#include <windows.h>
#include <string>
#include "sm3.h"
#include "filters.h"
#include "hex.h"

using namespace CryptoPP;

// 计算给定消息的SM3哈希值
std::string ComputeSM3Hash(const std::string& message) {

    CryptoPP::byte digest[CryptoPP::SM3::DIGESTSIZE];
    CryptoPP::SM3().CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(message.data()), message.size());
    CryptoPP::HexEncoder encoder;
    std::string encoded;
    encoder.Attach(new CryptoPP::StringSink(encoded));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();
    return encoded;
}

// 执行基于SM3哈希函数的rho碰撞算法
void RhoCollisionAlgorithm()
{
    std::string x = "0345678678";  // x的初始值
    std::string y="0345678678";//y的初始值
    char* tem1=new char[100];
    char* tem2=new char[100];
    x = ComputeSM3Hash(x);
    y = ComputeSM3Hash(y);
    y = ComputeSM3Hash(y);
    // 打印当前的x和y的值
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    strcpy(tem1, x.c_str());
    strcpy(tem2, y.c_str());
    while (memcmp(tem1,tem2,8))//比较前n个字节的大小，现在是1
    {
        // 计算x和y的哈希值
        x = ComputeSM3Hash(x);
        y = ComputeSM3Hash(y);
        y = ComputeSM3Hash(y);
        strcpy(tem1, x.c_str());
        strcpy(tem2, y.c_str());
        // 打印当前的x和y的值
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
    }

    // 打印找到的碰撞点
    std::cout << "找到碰撞点!" << std::endl;
}

int main()
{
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    RhoCollisionAlgorithm();

    QueryPerformanceCounter(&t2);
    double time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
    printf("%fs", time);
    return 0;
}
