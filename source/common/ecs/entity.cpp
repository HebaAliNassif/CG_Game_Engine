#include <entity.h>

bool CGEngine::Entity::Deserialize(const rapidjson::Value &obj) {
    return true;
}

bool CGEngine::Entity::Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const {

    writer->String("name");
    writer->String((name).c_str());

    writer->String("components");
    writer->StartArray();
    std::cout<<ListOfComponents.size();

    for(auto &comp:ListOfComponents)
    {
        writer->StartObject();
        comp->Serialize(writer);
        writer->EndObject();
    }

    writer->EndArray();

    return true;
}