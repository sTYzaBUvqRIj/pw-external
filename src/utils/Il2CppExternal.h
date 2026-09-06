#pragma once

#include "ProcessManager.hpp"

struct Il2CppExternal
{

    inline static constexpr size_t sizeof_Il2CppObject = 2 * sizeof(void*);
    template<typename T>
    struct Array
    {
        uintptr_t ptr = 0x0;
        inline size_t size() const
        {
            uintptr_t size = 0;
            ProcessMgr.ReadMemory(ptr + sizeof_Il2CppObject + sizeof(void*), size);
            return size;
        }
        inline T get(int index) const
        {
            T result {};
            if (ptr && index >= 0)
                ProcessMgr.ReadMemory(ptr + sizeof_Il2CppObject + 2 * sizeof(void*) + index * sizeof(T), result);
            return result;
        }

        inline void set(int index, const T& newval) const
        {
            if (ptr && index >= 0)
                ProcessMgr.WriteMemory(ptr + sizeof_Il2CppObject + 2 * sizeof(void*) + index * sizeof(T), newval);
        }

        inline std::vector<T> ToVector(size_t maxSize = 0) const
        {
            if (maxSize == 0)
                maxSize = size();
            std::vector<T> result;
            result.reserve(maxSize);
            T temp;
            for (size_t i = 0; i < maxSize; ++i) {
                if (!ProcessMgr.ReadMemory(ptr + sizeof_Il2CppObject + 2 * sizeof(void*) + i * sizeof(T), temp))
                    continue;
                result.push_back(temp);
            }
            return std::move(result);
        }
    };

    template<typename T>
    struct List
    {
        uintptr_t ptr = 0x0;
        inline size_t size() const
        {
            int size = 0;
            ProcessMgr.ReadMemory(ptr + sizeof_Il2CppObject + sizeof(void*), size);
            return size;
        }
        inline std::vector<T> ToVector() const
        {
            Array<T> array;
            ProcessMgr.ReadMemory(ptr + sizeof_Il2CppObject, array);
            if (!array.ptr)
                return {};
            return array.ToVector(size());
        }
    };
};

using IE = Il2CppExternal;