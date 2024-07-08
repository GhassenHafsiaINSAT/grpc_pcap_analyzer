make : 
	protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` learning_example.proto    
	protoc -I . --cpp_out=. learning_example.proto

clean : 
	rm -r *.pb.*