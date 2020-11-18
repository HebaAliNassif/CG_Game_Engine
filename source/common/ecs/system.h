#ifndef COMPUTER
#define COMPUTER

namespace CGEngine {

    class System {
    public:
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
