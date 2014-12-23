SRC =  main.cpp L2_Receiver.cpp L2_Receiver.h DynBuffer.cpp DynBuffer.h Level2_Decoder_Demo.cpp Level2_Decoder_Demo.h

l2apidemo: ${SRC}
	g++ -o  l2apidemo  ${SRC} -L../lib/ -lfast_api -lpthread -I../include 
clean:
	rm -f l2apidemo
	
