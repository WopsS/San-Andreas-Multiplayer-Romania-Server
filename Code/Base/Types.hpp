#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

class CCommandParameters;
class CPlayer;

enum class DialogResponse : uint16_t;

typedef std::function<void(std::shared_ptr<CPlayer>, std::shared_ptr<CCommandParameters>)> commandfunction_t;
typedef std::function<void(std::shared_ptr<CPlayer>, DialogResponse, size_t, std::string)> dialogfunction_t;