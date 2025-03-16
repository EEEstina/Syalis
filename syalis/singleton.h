#ifndef __SYALIS_SIGNLETON_H__
#define __SYALIS_SIGNLETON_H__

namespace syalis {

template <class T, class X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        static T v;
        return &v;
    }
};

template<class T, class X = void, int N = 0>
class SingletoinPtr {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v{new T};
        return v;
    }
};

}

#endif
