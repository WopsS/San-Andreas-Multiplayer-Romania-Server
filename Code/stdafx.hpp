#pragma once

#include <algorithm>
#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <mutex>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <format.h>
#include <mysql.h>
#include <Colors.hpp>
#include <Base/Types.hpp>
#include <Base/Any.hpp>
#include <Base/Data.hpp>
#include <Base/Map.hpp>
#include <Base/Point.hpp>
#include <Base/Singleton.hpp>
#include <Log/Log.hpp>

#include <MySQL/Parameter.hpp>
#include <MySQL/Query.hpp>
#include <MySQL/Result.hpp>
#include <MySQL/Connection.hpp>
#include <MySQL/ConnectionPool.hpp>
#include <MySQL/MySQL.hpp>

#define SAMPGDK_CPP_WRAPPERS

#include <sampgdk/a_objects.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/a_vehicles.h>
#include <sampgdk/core.h>
#include <sampgdk/interop.h>
#include <sampgdk/sdk.h>

#include <Streamer/MapIcon.hpp>
#include <Streamer/Object.hpp>
#include <Streamer/Pickup.hpp>
#include <Streamer/TextLabel.hpp>

#include <Utilities/Encryption.hpp>
#include <Utilities/SHA256.hpp>
#include <Utilities/Time.hpp>
#include <Utilities/Utils.hpp>

#define MYSQL_VERSION "1.0 alpha"
#define SERVER_VERSION "0.3.0 alpha"