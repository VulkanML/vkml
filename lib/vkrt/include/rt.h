#include <kompute/Kompute.hpp>
#include <memory>


namespace vkrt{
    class rt{
        kp::Manager _global_mgr;

        static std::shared_ptr<rt> instance;
        rt() : _global_mgr(){
            
        }
        ~rt(){
            _global_mgr.destroy();
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