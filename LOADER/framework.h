#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <timeapi.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sysinfoapi.h>
#include <filesystem>
#include <WinInet.h>
#include <urlmon.h>
#include <strsafe.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Wininet.lib")

#pragma comment(lib, "manualmap - x64.lib")

#include "../MAPPER/main.h"

#pragma comment(lib, "mmap")

#include "xorstr.hpp"

#define Exit() 0

