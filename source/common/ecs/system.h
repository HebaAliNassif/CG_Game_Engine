#pragma once
#ifndef COMPUTER
#define COMPUTER

namespace CGEngine {

    class System {
    protected:
        Scene * scene = nullptr;

    public:
        bool enabled = true;

        virtual void onAdded() {}
        virtual void start() {}
        virtual void update() {}
        virtual void postUpdate() {}

        int priority = 0;
        System(){};
        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }

        template<class T>
        T *As() {
            return dynamic_cast<T *>(this);
        }
    };
}

#endif //COMPUTER
