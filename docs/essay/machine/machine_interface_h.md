```c++
#undef DEFINE_IN_INTERFACE
#undef MACHINE

#include "machine_interface_macros.h"
#include "network/interface_defs.h"

namespace KBEngine{
    namespace MachineInterface
    {
        extern Network::MessageHandlers messageHandlers;
        
        // 某个app请求查看该app负载状态
        //MACHINE_MESSAGE_DECLARE_ARGS0(queryLoad, NETWORK_FIXED_MESSAGE)
        class queryLoadMachineMessageHandler0 : public Network::MessageHandler
        {
            public:
            virtual void handle(Network::Channel* pChannel,	KBEngine::MemoryStream& s);
        };
        
        extern const queryLoadMachineMessageHandler0& queryLoad;
        
        class queryLoadArgs0 : public Network::MessageArgs
        {
            public:
            queryLoadArgs0():Network::MessageArgs(){}
            ~queryLoadArgs0(){}
            
            static void staticAddToBundle(Network::Bundle& s)
            {
            }
            static void staticAddToStream(MemoryStream& s)
            {
            }
            virtual int32 dataSize(void)
            {
                return 0;
            }
            virtual void addToStream(MemoryStream& s)
            {    
            }
            virtual void createFromStream(MemoryStream& s)
            {               
            }
        };
        
        // 启动服务器
	    //MACHINE_MESSAGE_DECLARE_STREAM(startserver, NETWORK_VARIABLE_MESSAGE)
        class startserverMachineMessagehandler_stream : public Network::MessageHandler
        {
            public:
            virtual void handle(Network::Channel* pChannel,	KBEngine::MemoryStream& s);
        };
        
        extern const startserverMachineMessagehandler_stream& startserver;
        
        class startserverArgs_stream : public Network::MessageArgs
        {
           public:
            startserverArgs_stream():Network::MessageArgs(){}
            ~startserverArgs_stream(){}
           
            virtual int32 dataSize(void)
            {
                return NETWORK_VARIABLE_MESSAGE;
            }
            virtual MessageArgs::MESSAGE_ARGS_TYPE type(void)
            {    
                return MESSAGE_ARGS_TYPE_VARIABLE;
            }
            virtual void addToStream(MemoryStream& s)
            {               
            }
            virtual void createFromStream(MemoryStream& s)
            {               
            } 
        };  
    }
}
```



```c++
#define DEFINE_IN_INTERFACE
#define MACHINE

#include "machine_interface_macros.h"
#include "network/interface_defs.h"

namespace KBEngine{
    namespace MachineInterface
    {
        Network::MessageHandlers messageHandlers("MachineInterface");
        
        // 某个app请求查看该app负载状态
        //MACHINE_MESSAGE_DECLARE_ARGS0(queryLoad, NETWORK_FIXED_MESSAGE)
		void queryLoadMachineMessagehandler0::handle(Network::Channel* pChannel,
                                                  KBEngine::MemoryStream& s)
        {
            KBEngine::Machine::getSingleton().queryLoad(pChannel);
        }
        
        queryLoadMachineMessagehandler0* pqueryLoad = 
            static_cast<queryLoadMachineMessagehandler0*>(messageHandlers.add(
            "Machine::queryLoad", new queryLoadArgs0, NETWORK_FIXED_MESSAGE,
            new queryLoadMachineMessagehandler0));
        
        extern const queryLoadMachineMessageHandler0& queryLoad = *pqueryLoad;
    }
}
                                                  
```

