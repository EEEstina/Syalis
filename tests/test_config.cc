#include "../syalis/log.h"
#include "../syalis/config.h"
#include <yaml-cpp/yaml.h>

syalis::ConfigVar<int>::ptr g_int_value_config = syalis::Config::Lookup("system.port", (int)8080, "system port");

syalis::ConfigVar<float>::ptr g_float_value_config = syalis::Config::Lookup("system.value", (float)10.2f, "system value");

syalis::ConfigVar<std::vector<int> >::ptr g_vec_int_value_config = syalis::Config::Lookup("system.vec_int", std::vector<int>{1, 2}, "system value");

void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << std::string(level * 4, ' ') << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << std::string(level * 4, ' ') << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin(); it != node.end(); ++it) {
            SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << std::string(level * 4, ' ') << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << std::string(level * 4, ' ') << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}

void test_yaml() {
    // 最好用绝对路径
    YAML::Node root = YAML::LoadFile("/mnt/c/Users/Estin/Documents/GitHub/Syalis/bin/conf/log.yaml");
    // YAML::Node root = YAML::LoadFile("../bin/conf/log.yaml");
    print_yaml(root, 0);

    //SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << root;
}

void test_config() {
    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "before: " << g_float_value_config->toString();
    auto v = g_vec_int_value_config->getValue();
    for(auto& i : v) {
        SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "before vec_int: " << i;
    }

    YAML::Node root = YAML::LoadFile("/mnt/c/Users/Estin/Documents/GitHub/Syalis/bin/conf/log.yaml");
    syalis::Config::LoadFileYaml(root);

    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
    SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "after: " << g_float_value_config->toString();

    v = g_vec_int_value_config->getValue();
    for(auto& i : v) {
        SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << "after vec_int: " << i;
    }


}

int main(int argc, char** argv) {
    // SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << g_int_value_config->getValue();
    // SYALIS_LOG_INFO(SYALIS_LOG_ROOT()) << g_float_value_config->toString();

    // test_yaml();
    test_config();

    return 0;
}
