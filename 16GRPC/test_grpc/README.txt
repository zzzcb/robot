## windows平台grpc测试

### 目录介绍
	.\
		\client   	  server工程代码
		\dependency   grpc依赖
		\exe          helloworld Demo 
		\proto        protobuffer文件以及 脚本bat 
		\server       server工程代码





### grpc 
	1,grpc 简介
		As in many RPC systems, gRPC is based around the idea of 【defining a service】, 【specifying the methods】 that can be called remotely with their parameters and return types.
		On the server side, the server implements this interface and runs a gRPC server to handle client calls.
		On the client side, the client has a stub (referred to as just a client in some languages) that provides the same methods as the server.
		
	2，protobuf 简介
		Protocol buffer data 【is structured as messages】, where 【each message is a small logical record】 of information containing 【a series of name-value】 pairs called fields.
		Then, once you’ve specified your data structures, you use the 【protocol buffer compiler protoc】 to generate data access classes in your preferred language(s) from your proto definition. 
		These provide 【simple accessors】 for each field, like name() and set_name(), as well as 【methods to serialize/parse】 the whole structure 【to/from raw bytes】.
		Starting from a service definition in a .proto file, gRPC provides protocol buffer compiler plugins that generate client-side and server-side code.
		【gRPC users】 typically 【call these APIs on the client side】and 【implement the corresponding API on the server side】.
		On the server side, the server implements the methods declared by the service and runs a gRPC server to handle client calls. The gRPC infrastructure 【decodes incoming requests】, 【executes service methods】, and 【encodes service responses】.
		On the client side, the client has a 【local object known as stub】 (for some languages, the preferred term is client) that implements the same methods as the service. The client can then just call those methods on the local object.






