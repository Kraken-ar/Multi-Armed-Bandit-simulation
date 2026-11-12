#include "config/ConfigReader.hpp"
#include <fstream>
#include <iostream>
#include<string>

ConfigReader::ConfigReader(const std::string &configFilePath) : configFilePath(configFilePath)
{
    std::ifstream configFile(configFilePath);
    ;
    if (!configFile.is_open())
    {
        throw std::runtime_error("Failed to open config file: " + configFilePath);
    }

    std::string ConfigContent;
    std::string line;
    while (std::getline(configFile, line))
    {
        ConfigContent += line;
        ConfigContent += "\n";
    }

    this->parseConfigFile(ConfigContent);
}

void ConfigReader::parseConfigFile(const std::string &configContent)
{

    document.Parse(configContent.c_str());
    if (document.HasParseError())
    {
        throw std::runtime_error("Failed to parse config file: " + configFilePath);
    }
}

bool ConfigReader::hasValue(const rapidjson::Value &value, const std::string &key)
{
    return value.HasMember(key.c_str());
}

bool ConfigReader::validateValueType(const rapidjson::Value &value, const std::string &key, ValidationType expectedType)
{
    if (!hasValue(value, key))
    {
        return false;
    }

    const rapidjson::Value &memberValue = value[key.c_str()];

    switch (expectedType)
    {
    case ValidationType::BOOL:
        return memberValue.IsBool();
    case ValidationType::INT:
        return memberValue.IsInt();
    case ValidationType::NUMBER:
        return memberValue.IsNumber();
    case ValidationType::DOUBLE:
        return memberValue.IsDouble();
    case ValidationType::STRING:
        return memberValue.IsString();
    case ValidationType::ARRAY:
        return memberValue.IsArray();
    case ValidationType::OBJECT:
        return memberValue.IsObject();
    default:
        return false;
    }
}


bool ConfigReader::existsAndValid(const rapidjson::Value& value, const std::string& key, ValidationType expectedType)
{
   
    return hasValue(value, key) && validateValueType(value, key, expectedType);
}

void ConfigReader::throwErrorIfMissingOrInvalid(const rapidjson::Value& value, const std::string& key, ValidationType expectedType){
    if (!existsAndValid(value, key, expectedType))
    {   
        if (!hasValue(value, key))
        {
            // then its missing
            throw std::runtime_error("Missing '" + key + "' in config file: " + configFilePath);
        }else{
                
                // then its invalid
                throw std::runtime_error("Invalid '" + key + "' in config file: " + configFilePath);
        }
        
        // throw std::runtime_error("Missing or invalid '" + key + "' in config file: " + configFilePath);
    }
    
}


AgentConfig ConfigReader::parseAgentConfig()
{
    // if (!hasValue(document,"steps") || !validateValueType(document, "steps", ValidationType::INT))
    // {
    //      throw std::runtime_error("Missing or invalid 'steps' in config file: " + configFilePath);
    // }
    if (!hasValue(document, "epsilon") || !validateValueType(document, "epsilon", ValidationType::DOUBLE))
    {
        throw std::runtime_error("Missing or invalid 'epsilon' in config file: " + configFilePath);
    }
    if (!hasValue(document, "alpha") || !validateValueType(document, "alpha", ValidationType::DOUBLE))
    {
        throw std::runtime_error("Missing or invalid 'alpha' in config file: " + configFilePath);
    }

    AgentConfig agentConfig;
    agentConfig.epslon = document["epsilon"].GetDouble();
    agentConfig.alpha = document["alpha"].GetDouble();

    return agentConfig;
}

std::vector<ArmConfig> ConfigReader::parseArmsConfig(const rapidjson::Value &armsArray)
{
    std::vector<ArmConfig> armsConfig = {};
    int armIndex = 0;
    for (rapidjson::Value::ConstValueIterator itr = armsArray.Begin(); itr != armsArray.End(); ++itr)
    {   
        std::cout<<"Parsing arm config for arm index: " << ++armIndex << std::endl;
        ArmConfig armConfig;

        this->throwErrorIfMissingOrInvalid(*itr, "type", ValidationType::STRING);

        armConfig.rewardModelType = strcmp("static",(*itr)["type"].GetString()) == 0 ? RewardModelType::STATIC : RewardModelType::GAUSSIAN;

        if (armConfig.rewardModelType == RewardModelType::GAUSSIAN)
        {   
            // std::cout<<"Parsing Gaussian arm config for arm index: " << armIndex << std::endl;
            this->throwErrorIfMissingOrInvalid(*itr, "mean", ValidationType::NUMBER);
            this->throwErrorIfMissingOrInvalid(*itr, "std", ValidationType::NUMBER);

            armConfig.noiseStd = (*itr)["std"].GetDouble();
            armConfig.noiseMean = (*itr)["mean"].GetDouble();

            armsConfig.push_back(armConfig);  
            
        }
        else
        {
            // std::cout<<"Parsing Static arm config for arm index: " << armIndex << std::endl;
            this->throwErrorIfMissingOrInvalid(*itr, "value", ValidationType::NUMBER);

            armConfig.rewardValue = (*itr)["value"].GetDouble();

           

            if (this->existsAndValid(*itr, "drift", ValidationType::OBJECT))
            {
                this->throwErrorIfMissingOrInvalid((*itr)["drift"], "mean", ValidationType::NUMBER);
                this->throwErrorIfMissingOrInvalid((*itr)["drift"], "std", ValidationType::NUMBER);

               
                armConfig.noiseMean = (*itr)["drift"]["mean"].GetDouble();
                armConfig.noiseStd = (*itr)["drift"]["std"].GetDouble();
            }else{
                    
                    armConfig.noiseMean = 0;
                    armConfig.noiseStd = 0;
            }

            armsConfig.push_back(armConfig);

        }

      
    }

    return armsConfig;
}

OutputPaths ConfigReader::parseOutputPaths()
{
    OutputPaths outputPaths;

    if (!hasValue(document, "output"))
    {
        return outputPaths;
    }

    this->throwErrorIfMissingOrInvalid(document, "output", ValidationType::OBJECT);
    const rapidjson::Value& output = document["output"];

    if (hasValue(output, "directory"))
    {
        this->throwErrorIfMissingOrInvalid(output, "directory", ValidationType::STRING);
        outputPaths.directory = output["directory"].GetString();
    }

    if (hasValue(output, "rewardHistoryFile"))
    {
        this->throwErrorIfMissingOrInvalid(output, "rewardHistoryFile", ValidationType::STRING);
        outputPaths.rewardHistoryFile = output["rewardHistoryFile"].GetString();
    }

    if (hasValue(output, "armsEstimateHistoryFile"))
    {
        this->throwErrorIfMissingOrInvalid(output, "armsEstimateHistoryFile", ValidationType::STRING);
        outputPaths.armsEstimateHistoryFile = output["armsEstimateHistoryFile"].GetString();
    }

    return outputPaths;
}

EnviromentConfig ConfigReader::parseEnviromentConfig()
{
    
    this->throwErrorIfMissingOrInvalid(document, "steps", ValidationType::INT);
    this->throwErrorIfMissingOrInvalid(document, "arms", ValidationType::ARRAY);
  

    rapidjson::Value &armsArray = document["arms"];
    if (armsArray.Size() == 0)
    {
        throw std::runtime_error("No arms defined in config file: " + configFilePath);
    }


    EnviromentConfig enviromentConfig;
    enviromentConfig.steps = document["steps"].GetInt();
    enviromentConfig.outputPaths = parseOutputPaths();
    enviromentConfig.armsConfig = parseArmsConfig(armsArray);

    return enviromentConfig;

}


Agent* ConfigReader::getAgent()
{
    AgentConfig agentConfig = parseAgentConfig();
    Agent* agent = new Agent(agentConfig.epslon, agentConfig.alpha);
    return agent;
}

Enviroment* ConfigReader::getEnviroment()
{
    EnviromentConfig enviromentConfig = parseEnviromentConfig();
    std::vector<Arm*> arms;
    for (const auto& armConfig : enviromentConfig.armsConfig)
    {
        if (armConfig.rewardModelType == RewardModelType::STATIC)
        {
            arms.push_back(new Arm(new StaticRewardModel(armConfig.rewardValue, true, armConfig.drift, armConfig.noiseMean, armConfig.noiseStd)));
        }
        else if (armConfig.rewardModelType == RewardModelType::GAUSSIAN)
        {
            arms.push_back(new Arm(new GaussianRewardModel(armConfig.noiseMean, armConfig.noiseStd)));
        }
    }

    Agent* agent = getAgent();
    Enviroment* enviroment = new Enviroment(agent, arms, enviromentConfig.steps, enviromentConfig.outputPaths);
    return enviroment;
}


ConfigReader::~ConfigReader()
{
}
