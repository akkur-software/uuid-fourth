#include <string>
#include <exception>
#include <format>
#include <random>
#include <limits>
#include "UuidParser.h"
#include "Uuid.h"

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<uint64_t> uid(
    std::numeric_limits<std::uint64_t>::min(),
    std::numeric_limits<std::uint64_t>::max());

Uuid::Uuid() : m_value(std::array<uint8_t, 16>())        
{
    // Генерация 128-битного числа (uint128_t) и перевод его в массив из 16 байтов
    auto highWord = uid(mt);
    auto lowWord = uid(mt);
    auto highWordArray = toByteArray(highWord);
    auto lowWordArray = toByteArray(lowWord);

    m_value = mergeArrays(highWordArray, lowWordArray);

    // Модификация массива байтов с целью указания версии и варианта UUID (7-й и 9-й байты соответственно)
    m_value[6] = (m_value[6] & 0x0F) | 0x40;
    m_value[8] = (m_value[8] & 0x3F) | 0x80;

    // Формирование строкового значения
    m_stringValue = stringify(m_value);
}

Uuid::Uuid(const std::array<uint8_t, 16>& value) : m_value(value)
{
    m_stringValue = stringify(m_value);
}

Uuid::Uuid(const Uuid& uuid) : Uuid(uuid.Value()) { }

std::array<uint8_t, 16> Uuid::Value() const
{
    return m_value;
}

std::string_view Uuid::ToString() const
{
    return m_stringValue;
}

Uuid Uuid::Parse(std::string_view uuidString)
{
    auto value = UuidParser::Parse(uuidString);        
    return Uuid(value);
}

std::array<uint8_t, 8> Uuid::toByteArray(uint64_t value)
{
    const size_t BITS = 8;
    auto byteArray = std::array<uint8_t, 8>();
        
    for (size_t i = 0; i < byteArray.size(); ++i)
    {
        size_t offset = (7 - i) * BITS;
        uint8_t byte = (value >> offset) & 0xFF;
        byteArray[i] = byte;
    }
        
    return byteArray;
}

std::array<uint8_t, 16> Uuid::mergeArrays(const std::array<uint8_t, 8>& high, const std::array<uint8_t, 8>& low)
{
    return std::array<uint8_t, 16>(
        {
            high[0], high[1], high[2], high[3], high[4], high[5], high[6], high[7],
            low[0], low[1], low[2], low[3], low[4], low[5], low[6], low[7]
        });
}

std::string Uuid::stringify(const std::array<uint8_t, 16>& array)
{
    auto result = std::string();

    result += byteToHex(array[0]);
    result += byteToHex(array[1]);
    result += byteToHex(array[2]);
    result += byteToHex(array[3]);
    result += DASH_CHAR;
    result += byteToHex(array[4]);
    result += byteToHex(array[5]);
    result += DASH_CHAR;
    result += byteToHex(array[6]);
    result += byteToHex(array[7]);
    result += DASH_CHAR;
    result += byteToHex(array[8]);
    result += byteToHex(array[9]);
    result += DASH_CHAR;
    result += byteToHex(array[10]);
    result += byteToHex(array[11]);
    result += byteToHex(array[12]);
    result += byteToHex(array[13]);
    result += byteToHex(array[14]);
    result += byteToHex(array[15]);

    if (!UuidParser::IsValid(result.c_str()))
    {
        throw std::runtime_error(std::format("Invalid UUID string: {}", result.c_str()));
    }
    
    return result;
}

std::string Uuid::byteToHex(uint8_t byte)
{
    uint8_t highNibble = byte >> 4;
    uint8_t lowNibble = byte & 0x0F;

    std::string result = "";
    result += HEX_VALUES[highNibble];
    result += HEX_VALUES[lowNibble];

    return result;
}

bool operator==(const Uuid& lhs, const Uuid& rhs)
{
    if ((&lhs == nullptr) ^ (&rhs == nullptr))
    {
        return false;
    }
        
    if (&lhs == nullptr && &rhs == nullptr)
    {
        return true;
    }

    auto lhsValue = lhs.Value();
    auto rhsValue = rhs.Value();        
        
    return
        lhsValue[0]  == rhsValue[0] &&
        lhsValue[1]  == rhsValue[1] &&
        lhsValue[2]  == rhsValue[2] &&
        lhsValue[3]  == rhsValue[3] &&
        lhsValue[4]  == rhsValue[4] &&
        lhsValue[5]  == rhsValue[5] &&
        lhsValue[6]  == rhsValue[6] &&
        lhsValue[7]  == rhsValue[7] &&
        lhsValue[8]  == rhsValue[8] &&
        lhsValue[9]  == rhsValue[9] &&
        lhsValue[10] == rhsValue[10] &&
        lhsValue[11] == rhsValue[11] &&
        lhsValue[12] == rhsValue[12] &&
        lhsValue[13] == rhsValue[13] &&
        lhsValue[14] == rhsValue[14] &&
        lhsValue[15] == rhsValue[15];
}

bool operator!=(const Uuid& lhs, const Uuid& rhs)
{
    return !(lhs == rhs);
}
