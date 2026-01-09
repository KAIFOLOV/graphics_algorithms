#ifndef NODECONTEXT_H
#define NODECONTEXT_H

#include <typeindex>
#include <unordered_map>

class NodeContext
{
public:
    template<typename T> void set(T *device)
    {
        devices[typeid(T)] = device;
    }

    template<typename T> T *get() const
    {
        auto it = devices.find(typeid(T));
        if (it == devices.end())
            return nullptr;
        return static_cast<T *>(it->second);
    }

private:
    std::unordered_map<std::type_index, void *> devices;
};

#endif // NODECONTEXT_H
