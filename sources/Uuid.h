#pragma once
#include <string_view>
#include <array>

/// <summary>
/// Универсальный уникальный идентификатор (UUID) v4
/// </summary>
class Uuid final
{
public:
    /// <summary>
    /// Предоставляет новый экземпляр Uuid
    /// </summary>
    Uuid();

    /// <summary>
    /// Предоставляет новый экземпляр Uuid c указанным значением
    /// </summary>
    /// <param name="value">Значение Uuid в виде массива байтов</param>
    Uuid(const std::array<uint8_t, 16>& value);

    /// <summary>
    /// Предоставляет новый экземпляр Uuid, основанного на значении указанного
    /// </summary>
    /// <param name="uuid">Uuid, используемый в качестве исходного значения</param>
    Uuid(const Uuid& uuid);

    ~Uuid() = default;

    /// <summary>
    /// Значение идентификатора
    /// </summary>
    std::array<uint8_t, 16> Value() const;

    /// <summary>
    /// Валидный ли UUID
    /// </summary>
    bool IsValid() const;

    /// <summary>
    /// Строковое представление идентификатора
    /// </summary>
    std::string_view ToString() const;        

    /// <summary>
    /// Парсинг строки, содержащей UUID
    /// </summary>
    /// <param name="uuidString">Строка, являющаяся представлением UUID v4</param>
    /// <returns>Новый экземпляр Uuid</returns>
    static Uuid Parse(std::string_view uuidString);

    /// <summary>
    /// Равны ли указанные UUID
    /// </summary>
    friend bool operator==(const Uuid& lhs, const Uuid& rhs);

    /// <summary>
    /// Не равны ли указанные UUID
    /// </summary>
    friend bool operator!=(const Uuid& lhs, const Uuid& rhs);

private:
    std::array<uint8_t, 8> toByteArray(uint64_t value);
    std::array<uint8_t, 16> mergeArrays(const std::array<uint8_t, 8>& high, const std::array<uint8_t, 8>& low);
    std::string stringify(const std::array<uint8_t, 16>& array);
    std::string byteToHex(uint8_t byte);

private:
    std::array<uint8_t, 16> m_value;
    std::string m_stringValue;
    bool m_isValid;
};
