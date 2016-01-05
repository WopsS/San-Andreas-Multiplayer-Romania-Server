#pragma once

class Player;

enum class DialogResponse : uint16_t;

typedef std::function<void(std::shared_ptr<Player>, DialogResponse, size_t, std::string)> dialogfunction_t;
typedef std::function<void(std::shared_ptr<Player>)> keyfunction_t;