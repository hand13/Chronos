#pragma once
#include <memory>
namespace Chronos {
template <typename T>
/**
 * @brief 跨moudule资源指针,任意一个指针释放，则指向所有相同数据的指针均释放
 *
 */
class InterModulePointer {
   private:
    std::shared_ptr<T*> value_ptr;

   public:
    InterModulePointer() { value_ptr = std::make_shared<T*>((T*)nullptr); }
    InterModulePointer(T* value) { value_ptr = std::make_shared<T*>(value); }

    InterModulePointer(const InterModulePointer<T>& other) {
        value_ptr = other.value_ptr;
    }

    InterModulePointer<T>& operator=(const InterModulePointer<T>& other) {
        value_ptr = other.value_ptr;
        return *this;
    }

    T* get() { return *value_ptr; }
    const T* get() const { return *value_ptr; }
    T& operator*() { return **value_ptr; }
    const T& operator*() const { return **value_ptr; }

    T* operator->() { return *value_ptr; }
    const T* operator->() const { return *value_ptr; }

    operator bool() const { return *value_ptr != nullptr; }

    ~InterModulePointer() {
        if (value_ptr && *value_ptr) {
            delete *value_ptr;
            *value_ptr = nullptr;
        }
    }
};
}  // namespace Chronos