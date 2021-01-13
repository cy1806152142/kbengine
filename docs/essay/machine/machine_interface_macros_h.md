```c++
#undef DEFINE_IN_INTERFACE
#undef MACHINE

#include "network/interface_defs.h"

namespace KBEngine{
    #define MACHINE_MESSAGE_DECLARE_STREAM(NAME, MSG_LENGTH)						\
	class NAME##MachineMessagehandler_stream : public Network::MessageHandler	\
	{																			\
	public:																		\
		virtual void handle(Network::Channel* pChannel,							\
							KBEngine::MemoryStream& s);							\
	};	                                                                        \
	                                                                            \
	extern const NAME##MachineMessagehandler_stream& NAME;                      \
	                                                                            \
	class NAME##Args_stream : public Network::MessageArgs			\
	{																\
	public:															\
		NAME##Args_stream():Network::MessageArgs(){}				\
		~NAME##Args_stream(){}										\
																	\
		virtual int32 dataSize(void)								\
		{															\
			return NETWORK_VARIABLE_MESSAGE;						\
		}															\
		virtual MessageArgs::MESSAGE_ARGS_TYPE type(void)			\
		{															\
			return MESSAGE_ARGS_TYPE_VARIABLE;						\
		}															\
		virtual void addToStream(MemoryStream& s)					\
		{															\
		}															\
		virtual void createFromStream(MemoryStream& s)				\
		{															\
		}															\
	};                                                              \
	
	
    #define MACHINE_MESSAGE_DECLARE_ARGS0(NAME, MSG_LENGTH)							\
    class NAME##MachineMessagehandler0 : public Network::MessageHandler			\
	{																			\
	public:																		\
		virtual void handle(Network::Channel* pChannel,							\
							KBEngine::MemoryStream& s);							\
	};																			\
	extern const NAME##MachineMessagehandler0& NAME;                            \
																				\
    class NAME##Args0 : public Network::MessageArgs					\
	{																\
	public:															\
		NAME##Args0():Network::MessageArgs(){}						\
		~NAME##Args0(){}											\
																	\
		static void staticAddToBundle(Network::Bundle& s)			\
		{															\
		}															\
		static void staticAddToStream(MemoryStream& s)				\
		{															\
		}															\
		virtual int32 dataSize(void)								\
		{															\
			return 0;												\
		}															\
		virtual void addToStream(MemoryStream& s)					\
		{															\
		}															\
		virtual void createFromStream(MemoryStream& s)				\
		{															\
		}															\
	};  
    
    #define MACHINE_MESSAGE_DECLARE_ARGS1(NAME, MSG_LENGTH, ARG_TYPE1, ARG_NAME1)	\
    class NAME##MachineMessagehandler1 : public Network::MessageHandler			\
	{																			\
	public:																		\
		virtual void handle(Network::Channel* pChannel,							\
							KBEngine::MemoryStream& s);							\
	};																			\
	extern const NAME##MachineMessagehandler1& NAME;                            \
																				\
	class NAME##Args1 : public Network::MessageArgs					\
	{																\
	public:															\
		ARG_TYPE1 ARG_NAME1;										\
	public:															\
		NAME##Args1():Network::MessageArgs(){						\
		strArgsTypes.push_back(#ARG_TYPE1);}						\
		NAME##Args1(ARG_TYPE1 init_##ARG_NAME1):					\
		Network::MessageArgs(),										\
		ARG_NAME1(init_##ARG_NAME1)									\
		{strArgsTypes.push_back(#ARG_TYPE1);}						\
		~NAME##Args1(){}											\
																	\
		static void staticAddToBundle(Network::Bundle& s,			\
								ARG_TYPE1 init_##ARG_NAME1)			\
		{															\
			s << init_##ARG_NAME1;									\
		}															\
		static void staticAddToStream(MemoryStream& s,				\
								ARG_TYPE1 init_##ARG_NAME1)			\
		{															\
			s << init_##ARG_NAME1;									\
		}															\
		virtual int32 dataSize(void)								\
		{															\
			return sizeof(ARG_TYPE1);								\
		}															\
		virtual void addToStream(MemoryStream& s)					\
		{															\
			s << ARG_NAME1;											\
		}															\
		virtual void createFromStream(MemoryStream& s)				\
		{															\
			s >> ARG_NAME1;											\
		}															\
	};
}
```



```c++
#define DEFINE_IN_INTERFACE
#define MACHINE

#include "network/interface_defs.h"

namespace KBEngine{
    #define MACHINE_MESSAGE_DECLARE_STREAM(NAME, MSG_LENGTH)						\
    void NAME##MachineMessagehandler_stream::handle(Network::Channel* pChannel,	\
													KBEngine::MemoryStream& s)	\
	{																			\
			KBEngine::Machine::getSingleton().NAME(pChannel, s);				\
	}																			\
	
	NAME##MachineMessagehandler_stream* p##NAME =                                \
	    				    static_cast<NAME##MachineMessagehandler_stream*>	\
    						(messageHandlers.add("Machine::"#NAME,               \                                    new NAME##Args_stream, MSG_LENGTH,             \
    						 new NAME##MachineMessagehandler_stream));	    \
    																		\
    const NAME##MachineMessagehandler_stream& NAME = *p##NAME;	
	
    #define MACHINE_MESSAGE_DECLARE_ARGS0(NAME, MSG_LENGTH)						\
    void NAME##MachineMessagehandler0::handle(Network::Channel* pChannel,	\
													KBEngine::MemoryStream& s)	\
	{																			\
			KBEngine::Machine::getSingleton().NAME(pChannel);				\
	}																			\
	                                                                       \
	NAME##MachineMessagehandler0* p##NAME =                                \
	    				    static_cast<NAME##MachineMessagehandler0*>			 \
    						(messageHandlers.add("Machine::"#NAME,               \                                    new NAME##Args0, MSG_LENGTH,             \
    						 new NAME##MachineMessagehandler0));	    \
    																	\
    const NAME##MachineMessagehandler0& NAME = *p##NAME;	
    
    #define MACHINE_MESSAGE_DECLARE_ARGS1(NAME, MSG_LENGTH, ARG_TYPE1, ARG_NAME1)	\
    void NAME##MachineMessagehandler1::handle(Network::Channel* pChannel,		\
												KBEngine::MemoryStream& s)		\
	{																			\
			ARG_TYPE1 ARG_NAME1;												\
			s >> ARG_NAME1;														\
			KBEngine::Machine::getSingleton().NAME(pChannel, ARG_NAME1);		\
	}																				\
	                                                                          \
	NAME##MachineMessagehandler1* p##NAME =                                \
	    				    static_cast<NAME##MachineMessagehandler1*>			 \
    						(messageHandlers.add("Machine::"#NAME,               \                                    new NAME##Args1, MSG_LENGTH,             \
    						 new NAME##MachineMessagehandler1));	    \
    																	\
    const NAME##MachineMessagehandler1& NAME = *p##NAME;	
    
    
}
```

