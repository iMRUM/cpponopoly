#pragma once
#include <unordered_map>
#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>

//IdType should have a constructor along incrementing, decrementing and (perhaps) assignment operators.
template<typename T, typename IdType, typename... SpecifyingTypes>
class IRepository {
private:
    std::map<IdType, std::shared_ptr<T> > repository;
    IdType current_id;

public:
    //will create and register the Object (SHOULD pass creation to factory)
    const IdType& createObject(SpecifyingTypes... specifyingTypes) {
        IdType object_id(current_id++);
        repository[object_id] = std::make_shared<T>(specifyingTypes...);
        return object_id;
    }

    const T& getObject(IdType object_id) const {
        return repository.at(object_id);
    }

    /*void updateObject(IdType, SpecifyingTypes... specifyingTypes) {
        SHOULD BE IMPLEMENTED WITHIN CONCRETE REPO
    }*/

    const T& removeObject(IdType object_id) {
        return repository.erase(object_id);
    }

    bool containsObject(IdType object_id) const {
        return repository.contains(object_id);
    }

    [[nodiscard]] size_t repoSize() const {
        return repository.size();
    }
};
