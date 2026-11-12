#pragma once

#include <vector>
#include <string>
#include "Enviroment.hpp"
#include "document.h"
#include "reward/StaticRewardModel.hpp"
#include "reward/GaussianRewardModel.hpp"


#define STATIC_REWARD "static"
#define GAUSSIAN_REWARD "gaussian"


using AgentConfig = struct AgentConfig
{
    double epslon;
    double alpha;
};


enum class RewardModelType
{
    STATIC,
    GAUSSIAN
};

enum class ValidationType{
    BOOL,
    INT,
    NUMBER,
    DOUBLE,
    STRING,
    ARRAY,
    OBJECT
};

struct ArmConfig
{
    RewardModelType rewardModelType;
    double rewardValue;
    bool isNoisy;
    bool drift;
    double noiseMean;
    double noiseStd;
};



using EnviromentConfig = struct EnviromentConfig
{
    
    std::vector<ArmConfig> armsConfig;
    bool exportRewardHistoryToFile;
    bool exportArmsEstimatedHistoryToFile;
    bool drawRewardHistoryPlot;
    bool drawArmsEstimatedHistoryPlot;
    bool exportRewardHistoryPlotToImage;
    bool exportArmsEstimatedHistoryPlotToImage;


};

class ConfigReader
{
private:
    rapidjson::Document document;
    std::string configFilePath;
    std::string readConfigFile(const std::string& filePath);
    void parseConfigFile(const std::string& configContent);
    // bool isValidConfig();
    bool hasValue(const rapidjson::Value& value, const std::string& key);
    bool validateValueType(const rapidjson::Value& value, const std::string& key, ValidationType expectedType);
    AgentConfig parseAgentConfig();
    EnviromentConfig parseEnviromentConfig();
    std::vector<ArmConfig> parseArmsConfig(const rapidjson::Value& armsArray);
    std::vector<ArmConfig> parseArmConfig(const rapidjson::Value& arm);
    bool existsAndValid(const rapidjson::Value& value, const std::string& key, ValidationType expectedType);
    // bool throwErrorIfexistsAndValid(const rapidjson::Value& value, const std::string& key, ValidationType expectedType);
    void throwErrorIfMissingOrInvalid(const rapidjson::Value& value, const std::string& key, ValidationType expectedType);
public:
    ConfigReader(const std::string& configFilePath);
    ~ConfigReader();
    Agent* getAgent();
    Enviroment* getEnviroment();

   
    
};

