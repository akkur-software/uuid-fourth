#include "sources/Uuid4.h"
#include "CppUnitTest.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(UuidTests)
{
public:
		
	TEST_METHOD(GenerateNewUuid_Success)
	{
		// Arrange
		Uuid4 uuid;
		std::array<uint8_t, UUID_SIZE> uuidValue;
		std::string_view uuidString;

		// Act
		uuid = Uuid4();
		uuidValue = uuid.Value();
		uuidString = uuid.ToString();

		// Assert
		Assert::IsTrue(&uuid != nullptr);
		Assert::IsTrue(uuidValue.size() == UUID_SIZE);
		Assert::IsTrue(!std::all_of(uuidValue.begin(), uuidValue.end(), [](uint8_t byte) { return byte == 0; }));
	}

	TEST_METHOD(GenerateUuidFromSource_Success)
	{
		// Arrange
		Uuid4 source = Uuid4();
		Uuid4 target;

		// Act
		target = Uuid4(source);

		// Assert
		Assert::IsTrue(target.Value() == source.Value());
		Assert::AreEqual(source.ToString(), target.ToString());
	}

	TEST_METHOD(ParseUuid_Success)
	{
		// Arrange
		std::string_view raw = "3422b448-2460-4fd2-9183-8000de6f8343";
		Uuid4 uuid;
		std::array<uint8_t, UUID_SIZE> uuidValue;

		// Act
		uuid = Uuid4::Parse(raw);
		uuidValue = uuid.Value();

		// Assert
		Assert::IsTrue(&uuid != nullptr);
		Assert::IsTrue(uuid.Value().size() == UUID_SIZE);
		Assert::IsTrue(!std::all_of(uuidValue.begin(), uuidValue.end(), [](uint8_t byte) { return byte == 0; }));
		Assert::AreEqual(raw, uuid.ToString());
	}

	TEST_METHOD(ParseUuidWithoutNumber_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-246-4fd2-9183-8000de6f8343";
		Uuid4 uuid;
		auto func = [&]() { uuid = Uuid4::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}

	TEST_METHOD(ParseUuidWithoutDash_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-24604fd2-9183-8000de6f8343";
		Uuid4 uuid;
		auto func = [&]() {	uuid = Uuid4::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}

	TEST_METHOD(ParseUuidWithAdvancedDash_Fail)
	{
		// Arrange
		std::string_view raw = "3422b448-2460-4fd2-9183-8000de-6f8343";
		Uuid4 uuid;
		auto func = [&]() {	uuid = Uuid4::Parse(raw); };

		// Act & Assert
		Assert::ExpectException<std::invalid_argument>(func);
	}
};
