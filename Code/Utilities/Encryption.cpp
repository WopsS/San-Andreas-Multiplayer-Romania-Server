#include <Utilities/Encryption.hpp>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <random>

#include <Utilities/SHA256.hpp>

const std::string Encryption::Encrypt(const std::string& Data, const std::string& Salt)
{
	size_t SaltLength = Salt.length(), Position = 8, Addition = 6;

	std::string Result(Salt);

	for (size_t i = 0; i < Data.length(); i++)
	{
		Result.insert(Position, 1, Data[i]);

		Position += Addition;

		if (Position + Addition > SaltLength)
		{
			Addition--;
			Position = Addition;

			if (Addition <= 0)
			{
				std::random_device RandomDevice;
				std::default_random_engine RandomEngine(RandomDevice());
				std::uniform_int_distribution<int> uniform_dist(5, 12);

				Addition = uniform_dist(RandomEngine);
			}
		}
	}

	for (uint16_t i = 0; i < 12; i++)
	{
		Result = sha256(Result);
	}

	return Result;
}

const std::string Encryption::GenerateSalt(size_t Length)
{
	srand(static_cast<size_t>(time(nullptr)) + rand());

	auto RandomCharacter = []() -> char
	{
		const char CharSet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		const size_t MaxIndex = sizeof(CharSet) - 1;
		return CharSet[rand() % MaxIndex];
	};

	std::string Result(Length, 0);
	std::generate_n(Result.begin(), Length, RandomCharacter);

	return Result;
}
