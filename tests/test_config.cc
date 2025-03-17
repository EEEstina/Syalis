#include "../syalis/log.h"
#include "../syalis/config.h"

syalis::ConfigVar<int>::ptr g_int_value_config = syalis::Config::Lookup("system.port", (int)8080, "system port");

syalis::ConfigVar<float>::ptr g_float_value_config = syalis::Config::Lookup("system.value", (float)10.2f, "system value");

int main(int argc, char** argv) {
    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << g_int_value_config->getValue();
    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << g_float_value_config->toString();
    return 0;
}
