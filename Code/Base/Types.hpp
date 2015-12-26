#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

class CCommandParameters;
class CPlayer;

enum class DialogResponse : uint16_t;

typedef std::function<void(std::shared_ptr<CPlayer>, DialogResponse, size_t, std::string)> dialogfunction_t;
typedef std::function<void(std::shared_ptr<CPlayer>)> keyfunction_t;