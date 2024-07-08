make : 
	protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` Actia.proto    
	protoc -I . --cpp_out=. Actia.proto

clean : 
	rm -r *.pb.*