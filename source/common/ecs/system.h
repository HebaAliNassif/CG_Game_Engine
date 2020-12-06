#pragma once
#ifndef COMPUTER
#define COMPUTER

namespace CGEngine {

    class System {
    protected:

    public:
        bool enabled = true;
        Scene * scene = nullptr;

        virtual void start() {}
        virtual void onAdded() {}
        virtual void update(double delta_time) {}
        virtual void onExit() {}

        int priority = 10;
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
