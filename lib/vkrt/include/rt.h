#include <kompute/Kompute.hpp>
#include <memory>


namespace vkrt{
    class rt{
        kp::Manager mgr;

        static std::shared_ptr<rt> instance;
        rt() : mgr(){
            
        }
        ~rt(){
            mgr.destroy();
        }
    public:
        static std::shared_ptr<rt> get_instance(){
            if(instance == nullptr){
                instance = std::make_shared<rt>();
            }
            return instance;
        }
    };
}; // namespace vkrt