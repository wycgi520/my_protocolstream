
#ifndef __PROTOCOL_STREAM_H__
#define __PROTOCOL_STREAM_H__

#include <string>

namespace net
{
enum {
    BINARY_PACKLEN_LEN = 4
};

class BinaryStreamWriter final
{
public:
    BinaryStreamWriter(std::string *data);
    ~BinaryStreamWriter() = default;

    const char *GetData() const;
    size_t GetSize() const;
    BinaryStreamWriter &operator<<(const char *str);
    BinaryStreamWriter &operator<<(const std::string &str);
    BinaryStreamWriter &operator<<(double value);
    BinaryStreamWriter &operator<<(int64_t value);
    BinaryStreamWriter &operator<<(int32_t value);
    BinaryStreamWriter &operator<<(short value);
    BinaryStreamWriter &operator<<(char value);
    size_t GetCurrentPos() const { return m_data->length(); }
    void Flush();
    void Clear();

private:
    BinaryStreamWriter(const BinaryStreamWriter &) = delete;
    BinaryStreamWriter &operator=(const BinaryStreamWriter &) = delete;

private:
    std::string *m_data;
};

class BinaryStreamReader final
{
public:
    BinaryStreamReader(const char *data);
    ~BinaryStreamReader() = default;

    const char *GetData() const;
    size_t GetSize() const;
    bool IsEmpty() const;
    BinaryStreamReader &ReadCString(char *data, int len);
    BinaryStreamReader &ReadString(std::string &str, int len);
    BinaryStreamReader &ReadDouble(double &value);
    BinaryStreamReader &ReadInt64(int64_t &value);
    BinaryStreamReader &ReadInt32(int32_t &value);
    BinaryStreamReader &ReadShort(short &value);
    BinaryStreamReader &ReadChar(char &value);
    size_t GetCurrentPos() const { return m_pos; }
    void Clear();

private:
    BinaryStreamReader(const BinaryStreamReader &) = delete;
    BinaryStreamReader &operator=(const BinaryStreamReader &) = delete;

private:
    std::string m_data;
    uint32_t m_pos;
};

} // namespace net

#endif // __PROTOCOL_STREAM_H__