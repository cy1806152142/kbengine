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
        
        // 查询所有machine进程
        /*
		MACHINE_MESSAGE_DECLARE_ARGS3(onQueryMachines, NETWORK_VARIABLE_MESSAGE,
									   int32,							uid, 
									   std::string,					    username,
									   uint16,							finderRecvPort)
		*/
        class onQueryMachinesMachineMessageHandler3 : public Network::MessageHandler
        {
            public:
            virtual void handle(Network::Channel* pChannel,	KBEngine::MemoryStream& s);
        };
        
        extern const onQueryMachinesMachineMessageHandler3& onQueryMachines; 
        
        class onQueryMachinesArgs3 : public Network::MessageArgs
        {
            public:
            	int32 uid;
            	std::string username;
            	uint16 finderRecvPort;
            
            public:
            	onQueryMachinesArgs3():Network::MessageArgs()
                {
                    strArgsTypes.push_back("int32");
                    strArgsTypes.push_back("std::string");
                    strArgsTypes.push_back("uint16");
                }
            
            	onQueryMachinesArgs3(int32 init_uid, 
                						std::string init_username,
                            			uint16 init_finderRecvPort):
            				Network::MessageArgs(),	
            				uid(init_uid),
            				username(init_username),
            				finderRecvPort(init_finderRecvPort)
                 {
                 	 strArgsTypes.push_back("int32");
                     strArgsTypes.push_back("std::string");
                     strArgsTypes.push_back("uint16");      
                 }
            				
            	 ~onQueryMachinesArgs3(){}
            	 
            	static void staticAddToBundle(Network::Bundle& s,
                                             	int32 init_uid,
                                             	std::string init_username,
                                                uint16 init_finderRecvPort)
                {
                    s << init_uid;
                    s << init_username;
                    s << init_finderRecvPort;
                }
            
                static void staticAddToStream(MemoryStream& s,
                                              	int32 init_uid,
                                             	std::string init_username,
                                                uint16 init_finderRecvPort)
                {
                    s << init_uid;
                    s << init_username;
                    s << init_finderRecvPort;
                }
            
                virtual int32 dataSize(void)
                {
                    return sizeof(int32) + 
                           sizeof(std::string) + 
                           sizeof(uint16);
                }
            
                virtual void addToStream(MemoryStream& s)
                {    
                    s << uid;
                    s << username;
                    s << finderRecvPort; 
                }
            
                virtual void createFromStream(MemoryStream& s)
                {
                    s >> uid;
                    s >> username;
                    s >> finderRecvPort; 
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

#include "machine.h"
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
        
        const queryLoadMachineMessageHandler0& queryLoad = *pqueryLoad;
        
        // 查询所有machine进程
        /*
		MACHINE_MESSAGE_DECLARE_ARGS3(onQueryMachines, NETWORK_VARIABLE_MESSAGE,
									   int32,							uid, 
									   std::string,					    username,
									   uint16,							finderRecvPort)
		*/
        void onQueryMachinesMachineMessageHandler3::handle(Network::Channel* pChannel,
                                                  KBEngine::MemoryStream& s)
        {
            int32 uid;
            s >> uid;
            std::string username;
            s >> username;
            uint16 uid;
            s >> uid;
            KBEngine::Machine::getSingleton().onQueryMachines(pChannel,
                                                             uid, username,
                                                             finderRecvPort);
        }
        
        onQueryMachinesMachineMessageHandler3* ponQueryMachines = 
            static_cast<onQueryMachinesMachineMessageHandler3*>(messageHandlers.add(
            "Machine::onQueryMachines", new onQueryMachinesArgs3, 									NETWORK_VARIABLE_MESSAGE,
            new onQueryMachinesMachineMessageHandler3));
        
        const onQueryMachinesMachineMessageHandler3& onQueryMachines = 
            									*onQueryMachinesMachineMessageHandler3;
        
        // 启动服务器
	    //MACHINE_MESSAGE_DECLARE_STREAM(startserver, NETWORK_VARIABLE_MESSAGE)
        void startserverMachineMessagehandler_stream::handle(Network::Channel* pChannel,
                                                  KBEngine::MemoryStream& s)
        {
            KBEngine::Machine::getSingleton().startserver(pChannel, s);
        }
        
        startserverMachineMessagehandler_stream* pstartserver = 
            static_cast<startserverMachineMessagehandler_stream*>(messageHandlers.add(
            "Machine::startserver", new startserverArgs_stream, NETWORK_VARIABLE_MESSAGE,
            new startserverMachineMessagehandler_stream));
        
        const startserverMachineMessagehandler_stream& startserver = *pstartserver;
    }
}
                                                  
```

