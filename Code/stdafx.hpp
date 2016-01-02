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
#include <xmemory>

#include <format.h>
#include <mysql.h>
#include <Colors.hpp>
#include <Base/CAny.hpp>
#include <Base/CData.hpp>
#include <Base/CMap.hpp>
#include <Base/CPoint.hpp>
#include <Base/CSingleton.hpp>
#include <Base/Types.hpp>
#include <Log/CLog.hpp>

#include <MySQL/CParameter.hpp>
#include <MySQL/CQuery.hpp>
#include <MySQL/CResult.hpp>
#include <MySQL/CConnection.hpp>
#include <MySQL/CConnectionPool.hpp>
#include <MySQL/CMySQL.hpp>

#define SAMPGDK_CPP_WRAPPERS

#include <sampgdk/a_objects.h>
#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/a_vehicles.h>
#include <sampgdk/core.h>
#include <sampgdk/interop.h>
#include <sampgdk/sdk.h>

#define MYSQL_VERSION "1.0 alpha"
#define SERVER_VERSION "0.3.0 alpha"