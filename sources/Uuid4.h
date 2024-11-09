#pragma once
#include <string>
#include <array>
#include <stdint.h>

/// <summary>
/// Размер UUID (в байтах)
/// </summary>
constexpr size_t UUID_SIZE = 16;

/// <summary>
/// Универсальный уникальный идентификатор (UUID) v4
/// </summary>
class Uuid4 final
{
public:
    ~Uuid4() = default;
    Uuid4(const Uuid4& other) = default;
    Uuid4& operator=(const Uuid4& other) = default;

    /// <summary>
    /// Предоставляет новый экземпляр Uuid4
    /// </summary>
    Uuid4();

    /// <summary>
    /// Предоставляет новый экземпляр Uuid4 c указанным значением
    /// </summary>
    /// <param name="value">Значение Uuid4 в виде массива байтов</param>
    Uuid4(const std::array<uint8_t, 16>& value);

    /// <summary>
    /// Предоставляет новый экземпляр Uuid4, основанный на значении указанного, 
    /// без дополнительного копирования и выделения памяти
    /// </summary>
    /// <param name="other">Uuid4, используемый в качестве исходного значения</param>
    Uuid4(Uuid4&& other) noexcept;

    /// <summary>
    /// Оператор присваивания перемещением
    /// </summary>
    /// <param name="other">Uuid4, используемый в качестве исходного значения</param>
    /// <returns>Текущий экземпляр Uuid4, содержащий перемещенные данные</returns>
    Uuid4& operator=(Uuid4&& other) noexcept;

    /// <summary>
    /// Предоставляет значение идентификатора
    /// </summary>
    /// <returns>Значение текущего экземпляра Uuid4 в виде массива байтов</returns>
    std::array<uint8_t, 16> Value() const;

    /// <summary>
    /// Возвращает cтроковое представление идентификатора
    /// </summary>
    /// <returns>Представление текущего экземпляра Uuid4 в виде <see cref="std::string_view"/></returns>
    std::string_view ToString() const;

    /// <summary>
    /// Определяет, равны ли указанные Uuid4
    /// </summary>
    /// <returns>
    /// Возвращает <see langword="true"/>, если сравниваемые Uuid4 равны,
    /// иначе возвращает <see langword="false"/>
    /// </returns>
    bool operator==(const Uuid4& other);

    /// <summary>
    /// Определяет, не равны ли указанные Uuid4
    /// </summary>
    /// <returns>
    /// Возвращает <see langword="true"/>, если сравниваемые Uuid4 не равны,
    /// иначе возвращает <see langword="false"/>
    /// </returns>
    bool operator!=(const Uuid4& other);

    /// <summary>
    /// Парсит строку, содержащую UUIDv4
    /// </summary>
    /// <param name="uuidString">Строка, являющаяся представлением UUID v4</param>
    /// <returns>Новый экземпляр Uuid4</returns>
    static Uuid4 Parse(std::string_view uuidString);

private:
    std::array<uint8_t, 8> toByteArray(uint64_t value);
    std::array<uint8_t, 16> mergeArrays(const std::array<uint8_t, 8>& high, const std::array<uint8_t, 8>& low);
    std::string stringify(const std::array<uint8_t, 16>& array);
    std::string byteToHex(uint8_t byte);

    static bool isValid(std::string_view uuidString);
    static std::array<uint8_t, 16> parse(std::string_view uuidString);

private:
    std::array<uint8_t, 16> m_value;
    std::string m_stringValue;
};
