#pragma once

namespace Encryption
{
	const std::string Encrypt(const std::string& Data, const std::string& Salt);

	const std::string GenerateSalt(size_t Length);
}