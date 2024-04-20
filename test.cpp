
#include "protocolstream.h"

#include <iostream>

void printData(const char* str, size_t len)
{
    printf("data(size: %lu): ", len);
    for (size_t i = 0; i < len; i++) {
        printf("%.2x ", *(str + i));
    }
    std::cout << std::endl;
}

int main(void)
{
    std::string outbuf;

    // test writer
    std::cout << "test writer" << std::endl;
    net::BinaryStreamWriter binaryWriter(&outbuf);
    // test CString
    binaryWriter << "abc";
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test String
    binaryWriter << std::string("def");
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test double
    binaryWriter << 3.14;
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test int32_t
    int32_t wI32 = 10;
    binaryWriter << wI32;
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test int64_t
    int64_t wI64 = 11;
    binaryWriter << wI64;
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test short
    short wShort = 6;
    binaryWriter << wShort;
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test char
    char wChar = 7;
    binaryWriter << wChar;
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test flush
    binaryWriter.Flush();
    printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // // test clear
    // binaryWriter.Clear();
    // printData(binaryWriter.GetData(), binaryWriter.GetSize());

    // test reader
    std::cout << "test reader" << std::endl;
    net::BinaryStreamReader binaryReader(binaryWriter.GetData());
    printData(binaryReader.GetData(), binaryReader.GetSize());

    // test CString
    char buf[4]{0};
    binaryReader.ReadCString(buf, 3);
    printf("test cstring: %s\n", buf);

    // test String
    std::string rStr;
    binaryReader.ReadString(rStr, 3);
    std::cout << "test string: " << rStr << std::endl;

    // test double
    double rDouble;
    binaryReader.ReadDouble(rDouble);
    std::cout << "test double: " << rDouble << std::endl;

    // test int32_t
    int32_t rI32;
    binaryReader.ReadInt32(rI32);
    std::cout << "test int32_t: " << rI32 << std::endl;

    // test int64_t
    int64_t rI64;
    binaryReader.ReadInt64(rI64);
    std::cout << "test int64_t: " << rI64 << std::endl;

    // test short
    short rShort;
    binaryReader.ReadShort(rShort);
    std::cout << "test short: " << rShort << std::endl;

    // test char
    char rChar;
    binaryReader.ReadChar(rChar);
    std::cout << "test char: " << static_cast<int32_t>(rChar) << std::endl;

    binaryReader.Clear();
    printData(binaryReader.GetData(), binaryReader.GetSize());

    return 0;
}