
#include "protocolstream.h"

#include <arpa/inet.h>
#include <cstring>

namespace
{
uint64_t htonll(uint64_t value)
{
    if (htonl(1) == 1) {
        return ((uint64_t)htonl(value & 0xFFFFFFFF) << 32) | htonl(value >> 32);
    } else {
        return value;
    }
}

uint64_t ntohll(uint64_t value)
{
    if (htonl(1) == 1) {
        return ((uint64_t)ntohl(value & 0xFFFFFFFF) << 32) | ntohl(value >> 32);
    } else {
        return value;
    }
}
} // namespace

namespace net
{
BinaryStreamWriter::BinaryStreamWriter(std::string *data) : m_data(data)
{
    m_data->clear();
    char str[BINARY_PACKLEN_LEN];
    m_data->append(str, sizeof(str));
}

const char *BinaryStreamWriter::GetData() const
{
    return m_data->c_str();
}

size_t BinaryStreamWriter::GetSize() const
{
    return m_data->size();
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(const char *str)
{
    m_data->append(str);
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(const std::string &str)
{
    m_data->append(str);
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(double value)
{
    auto v = reinterpret_cast<uint64_t *>(&value);
    auto v1 = ::htonll(*v);
    m_data->append((char *)&v1, sizeof(v1));
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(int64_t value)
{
    auto v = ::htonll(value);
    m_data->append((char *)&v, sizeof(v));
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(int32_t value)
{
    auto v = htonl(value);
    m_data->append((char *)&v, sizeof(v));
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(short value)
{
    auto v = htons(value);
    m_data->append((char *)&v, sizeof(v));
    return *this;
}

BinaryStreamWriter &BinaryStreamWriter::operator<<(char value)
{
    m_data->append(&value, sizeof(value));
    return *this;
}

void BinaryStreamWriter::Flush()
{
    char *ptr = &(*m_data)[0];
    unsigned int ulen = htonl(m_data->length());
    memcpy(ptr, &ulen, sizeof(ulen));
}

void BinaryStreamWriter::Clear()
{
    m_data->clear();
    char str[BINARY_PACKLEN_LEN];
    m_data->append(str, sizeof(str));
}

BinaryStreamReader::BinaryStreamReader(const char *data) : m_pos(BINARY_PACKLEN_LEN)
{
    auto len = ntohl(*reinterpret_cast<const uint32_t *>(data));
    m_data.append(data, len);
}

const char *BinaryStreamReader::GetData() const
{
    return m_data.c_str();
}

size_t BinaryStreamReader::GetSize() const
{
    return m_data.size();
}

bool BinaryStreamReader::IsEmpty() const
{
    return m_data.empty();
}

BinaryStreamReader &BinaryStreamReader::ReadCString(char *data, int len)
{
    memcpy(data, &m_data[m_pos], len);
    m_pos += len;
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadString(std::string &str, int len)
{
    str = m_data.substr(m_pos, len);
    m_pos += len;
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadDouble(double &value)
{
    auto v = ::ntohll(*reinterpret_cast<int64_t *>(&(m_data[m_pos])));
    value = *(reinterpret_cast<double *>(&v));
    m_pos += sizeof(value);
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadInt64(int64_t &value)
{
    value = ::ntohll(*reinterpret_cast<int64_t *>(&(m_data[m_pos])));
    m_pos += sizeof(value);
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadInt32(int32_t &value)
{
    value = ntohl(*reinterpret_cast<int32_t *>(&(m_data[m_pos])));
    m_pos += sizeof(value);
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadShort(short &value)
{
    value = ntohs(*reinterpret_cast<short *>(&(m_data[m_pos])));
    m_pos += sizeof(value);
    return *this;
}

BinaryStreamReader &BinaryStreamReader::ReadChar(char &value)
{
    value = m_data[m_pos];
    m_pos += sizeof(value);
    return *this;
}

void BinaryStreamReader::Clear()
{
    m_data.clear();
    m_pos = BINARY_PACKLEN_LEN;
}

} // namespace net
