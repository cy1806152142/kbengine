```c++
#undef DEFINE_IN_INTERFACE
#undef MACHINE

// common include
#include "common/common.h"
#include "common/smartpointer.h"
#include "network/common.h"
#include "network/message_handler.h"
#include "network/bundle.h"
#include "network/channel.h"

namespace KBEngine{
namespace Network
{
    #define NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, HANDLER_TYPE, MSG_LENGTH, ARG_N) \
    	extern const HANDLER_TYPE& NAME;	
    
    #define NETWORK_MESSAGE_EXPOSED(DOMAIN, NAME)	                               \
    
    #define NETWORK_INTERFACE_DECLARE_BEGIN(INAME) 						\
    namespace INAME                                                     \
    {                                                                   \
        extern Network::MessageHandlers messageHandlers;			    \
    	
    #define NETWORK_INTERFACE_DECLARE_END()                             \
    }
    
    #define MESSAGE_STREAM(NAME)										\
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
	};
    
    #define NETWORK_MESSAGE_DECLARE_STREAM(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH) \
		NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, _stream) \
		MESSAGE_STREAM(NAME)	
    
    /**---------------------------------------------------------------------
    /		零个参数的消息
    -----------------------------------------------------------------------*/
    #define MESSAGE_ARGS0(NAME)											\
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
    
    /**---------------------------------------------------------------------
    /		1个参数的消息
    -----------------------------------------------------------------------*/
    #define MESSAGE_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)					\
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
	};																\
		
    
    #define NETWORK_MESSAGE_DECLARE_ARGS0(DOMAIN, NAME, MSGHANDLER,		\
											MSG_LENGTH)				\
	NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, 0)\
	MESSAGE_ARGS0(NAME)	
    
    
    #define NETWORK_MESSAGE_DECLARE_ARGS1(DOMAIN, NAME, MSGHANDLER,		\
											MSG_LENGTH,				\
											ARG_TYPE1, ARG_NAME1)	\
	NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, 1)\
	MESSAGE_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)						\
    
}
}
```



```c++
#define DEFINE_IN_INTERFACE
#define MACHINE

namespace KBEngine{
namespace Network
{
	#define NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, HANDLER_TYPE, MSG_LENGTH, ARG_N)		\
	HANDLER_TYPE* p##NAME = static_cast<HANDLER_TYPE*>			                        \                              (messageHandlers.add(#DOMAIN"::"#NAME,                     \
						      new NAME##Args##ARG_N, MSG_LENGTH, new HANDLER_TYPE));	\
    const HANDLER_TYPE& NAME = *p##NAME;											
			
	#define NETWORK_MESSAGE_EXPOSED(DOMAIN, NAME);									    \
	bool p##DOMAIN##NAME##_exposed =  messageHandlers.pushExposedMessage            \			                                  (#DOMAIN"::"#NAME);
    
    #define NETWORK_INTERFACE_DECLARE_BEGIN(INAME) 						\
	namespace INAME													\
	{																	\
		Network::MessageHandlers messageHandlers(#INAME);			\
			
    #define NETWORK_INTERFACE_DECLARE_END()                         \
    }
    
    #define MESSAGE_STREAM(NAME)
    
    #define NETWORK_MESSAGE_DECLARE_STREAM(DOMAIN, NAME, MSGHANDLER,MSG_LENGTH)	\
	NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, _stream)	    \
	MESSAGE_STREAM(NAME)											\
	
	#define MESSAGE_ARGS0(NAME)
    
    #define MESSAGE_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)
    
	#define NETWORK_MESSAGE_DECLARE_ARGS0(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH)	  \
    NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, 0)\
	MESSAGE_ARGS0(NAME)												\
	
	#define NETWORK_MESSAGE_DECLARE_ARGS1(DOMAIN, NAME, MSGHANDLER,		\
											MSG_LENGTH,				\
											ARG_TYPE1, ARG_NAME1)	\
	NETWORK_MESSAGE_HANDLER(DOMAIN, NAME, MSGHANDLER, MSG_LENGTH, 1)\
	MESSAGE_ARGS1(NAME, ARG_TYPE1, ARG_NAME1)						\
}
}
```

