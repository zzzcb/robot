/*
#include <iostream>
#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

class GreeterImpl final :public helloworld::Greeter::Service
{
	grpc::Status SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response) override
	{
		std::string prefix("Hello ");
		response->set_message(prefix + request->name());
		return grpc::Status::OK;
	}
};


int main()
{
	std::string server_address("0.0.0.0:50051");

	GreeterImpl service;
	grpc::ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
	server->Wait();

	return 0;
}
*/