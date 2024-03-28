#include <string>
#include <exception>
#include <algorithm>
#include <format>
#include "UuidParser.h"


std::array<uint8_t, 16> UuidParser::Parse(std::string_view uuidString)
{
    if (!IsValid(uuidString))
    {
        throw std::invalid_argument(std::format("Invalid UUID string: {}", uuidString.data()));
    }

    auto solidUuid = std::string();
    std::copy_if(uuidString.begin(), uuidString.end(), std::back_inserter(solidUuid), [=](char ch)
        {
            return ch != DASH_CHAR;
        });

    if (solidUuid.size() != UUID_SIZE * 2)
    {
        throw std::invalid_argument(std::format("The UUID '{}' must be {} characters long without dashes", solidUuid.c_str(), UUID_SIZE));
    }

    auto value = std::array<uint8_t, UUID_SIZE>();

    for (size_t i = 0; i < value.size(); ++i)
    {
        size_t pos = i * 2;
        std::string hex = { solidUuid[pos], solidUuid[pos + 1] };
        value[i] = (uint8_t)(std::stoi(hex, nullptr, 16));
    }

    return value;
}

bool UuidParser::IsValid(std::string_view uuidString)
{
    return 
        uuidString.size() == UUID_STRING_SIZE &&
        uuidString[14] == VERSION_CHAR &&
        std::count(uuidString.begin(), uuidString.end(), DASH_CHAR) == UUID_DASH_POSITIONS.size() &&
        std::all_of(UUID_DASH_POSITIONS.begin(), UUID_DASH_POSITIONS.end(), [=](size_t index)
        {
            return uuidString[index] == DASH_CHAR;
        });
}
