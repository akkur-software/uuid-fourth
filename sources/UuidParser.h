#pragma once
#include <array>
#include <string_view>
#include <stdint.h>

/// <summary>
/// Размер UUID (в байтах)
/// </summary>
constexpr size_t UUID_SIZE = 16;

/// <summary>
/// Размер строкового представления UUID
/// </summary>
constexpr size_t UUID_STRING_SIZE = 36;

/// <summary>
/// Символ разделителя UUID (дефис)
/// </summary>
constexpr char DASH_CHAR = '-';

/// <summary>
/// Символ, определяющий версию UUID
/// </summary>
constexpr char VERSION_CHAR = '4';

/// <summary>
/// Позиции разделителей в UUID
/// </summary>
constexpr std::array<size_t, 4> UUID_DASH_POSITIONS({ 8, 13, 18, 23 });

/// <summary>
/// Набор значений для конвертации байтов в строковое hex-представление
/// </summary>
constexpr std::array<char, 16> HEX_VALUES({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' });
    
/// <summary>
/// Класс для парсинга UUID в массив байтов
/// </summary>
class UuidParser final 
{
public:
    static std::array<uint8_t, 16> Parse(std::string_view uuidString);
    static bool IsValid(std::string_view uuidString);
};
