#include "sources/Uuid.h"
#include "sources/UuidParser.h"
#include "CppUnitTest.h"
#include <algorithm>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(UuidTests)
{
public:
		
	TEST_METHOD(GenerateNewUuid_Success)
	{
		// Arrange
		Uuid uuid;
		std::array<uint8_t, UUID_SIZE> uuidValue;
		std::string_view uuidString;

		// Act
		uuid = Uuid();
		uuidValue = uuid.Value();
		uuidString = uuid.ToString();

		// Assert
		Assert::IsTrue(&uuid != nullptr);
		Assert::IsTrue(uuidValue.size() == UUID_SIZE);
		Assert::IsTrue(!std::all_of(uuidValue.begin(), uuidValue.end(), [](uint8_t byte) { return byte == 0; }));
		Assert::IsTrue(uuid.IsValid());
	}

	TEST_METHOD(GenerateUuidFromSource_Success)
	{
		// Arrange
		Uuid source = Uuid();
		Uuid target;

		// Act
		target = Uuid(source);

		// Assert
		Assert::IsTrue(source.IsValid());
		Assert::IsTrue(target.IsValid());
		Assert::IsTrue(target.Value() == source.Value());
		Assert::AreEqual(source.ToString(), target.ToString());
	}

	TEST_METHOD(ParseUuid_Success)
	{
		// Arrange
		std::string_view raw = "3422b448-2460-4fd2-9183-8000de6f8343";
		Uuid uuid;
		std::array<uint8_t, UUID_SIZE> uuidValue;

		// Act
		uuid = Uuid::Parse(raw);
		uuidValue = uuid.Value();

		// Assert
		Assert::IsTrue(&uuid != nullptr);
		Assert::IsTrue(uuid.Value().size() == UUID_SIZE);
		Assert::IsTrue(!std::all_of(uuidValue.begin(), uuidValue.end(), [](uint8_t byte) { return byte == 0; }));
		Assert::IsTrue(uuid.IsValid());
		Assert::AreEqual(raw, uuid.ToString());
	}

	TEST_METHOD(ParseUuidWithoutNumber_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-246-4fd2-9183-8000de6f8343";
		Uuid uuid;
		auto func = [&]() { uuid = Uuid::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}

	TEST_METHOD(ParseUuidWithoutDash_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-24604fd2-9183-8000de6f8343";
		Uuid uuid;
		auto func = [&]() {	uuid = Uuid::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}

	TEST_METHOD(ParseUuidWithAdvancedDash_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-2460-4fd2-9183-8000de-6f8343";
		Uuid uuid;
		auto func = [&]() {	uuid = Uuid::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}

	TEST_METHOD(Parse_50000_Uuids_Success)
	{
		auto m_uuid_strings = std::vector<std::string>();

		for (size_t i = 0; i < 50000; ++i)
		{
			auto uuid = Uuid();
			m_uuid_strings.emplace_back(uuid.ToString().data());
		}

		bool allValid = true;
		
		for (auto uuidString : m_uuid_strings)
		{
			auto uuid = Uuid::Parse(uuidString);
			allValid &= uuid.IsValid();
		}

		Assert::IsTrue(allValid);
	}
};
