TO		  = o
EXES		= libfast_api
CC		  = g++

OBJS = tinystr.$(TO) tinyxml.$(TO) tinyxmlerror.$(TO) tinyxmlparser.$(TO) \
       Decoder_Factory_Impl.$(TO) Fast_Decoder_Impl.$(TO) Fast_Define.$(TO) \
       Fast_Message_Impl.$(TO) Fast_Record_Impl.$(TO)
       
all : clean $(EXES)       

TINYXML_PATH = ./TinyXML
CPP_PATH     = ./
tinystr.$(TO): $(TINYXML_PATH)/tinystr.cpp
	$(CC) -fpic -c $(TINYXML_PATH)/tinystr.cpp
tinyxml.$(TO): $(TINYXML_PATH)/tinyxml.cpp
	$(CC) -fpic -c $(TINYXML_PATH)/tinyxml.cpp
tinyxmlerror.$(TO): $(TINYXML_PATH)/tinyxmlerror.cpp
	$(CC) -fpic -c $(TINYXML_PATH)/tinyxmlerror.cpp
tinyxmlparser.$(TO): $(TINYXML_PATH)/tinyxmlerror.cpp
	$(CC) -fpic -c $(TINYXML_PATH)/tinyxmlparser.cpp
  
Decoder_Factory_Impl.$(TO): $(CPP_PATH)/Decoder_Factory_Impl.cpp
	$(CC) -fpic -c $(CPP_PATH)/Decoder_Factory_Impl.cpp 
Fast_Decoder_Impl.$(TO): $(CPP_PATH)/Fast_Decoder_Impl.cpp
	$(CC) -fpic -c $(CPP_PATH)/Fast_Decoder_Impl.cpp  
Fast_Define.$(TO): $(CPP_PATH)/Fast_Define.cpp
	$(CC) -fpic -c $(CPP_PATH)/Fast_Define.cpp  
Fast_Message_Impl.$(TO): $(CPP_PATH)/Fast_Message_Impl.cpp
	$(CC) -fpic -c $(CPP_PATH)/Fast_Message_Impl.cpp
Fast_Record_Impl.$(TO): $(CPP_PATH)/Fast_Record_Impl.cpp
	$(CC) -fpic -c $(CPP_PATH)/Fast_Record_Impl.cpp
  
clean: 
	rm -f *.o
$(EXES):$(OBJS)
	$(CC) -shared $(OBJS) -o libfast_api.so
#	$(ARCHIVE) $(OUTDIR)/$(EXES) $(OBJS)
