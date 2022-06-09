#include <iostream>
#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

int main()
{
	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	std::unique_ptr<helloworld::Greeter::Stub> stub = helloworld::Greeter::NewStub(channel);


	helloworld::HelloRequest request;
	request.set_name("ZCB");

	helloworld::HelloReply reply;
	grpc::ClientContext context;
	grpc::Status status = stub->SayHello(&context, request, &reply);

	if (status.ok())
	{
		std::cout << "reply is " << reply.message();
		std::cout << std::endl;
	}
	else
	{
		std::cout << status.error_code() << ": " << status.error_message()<< std::endl;
		std::cout << "RPC failed." << std::endl;
	}
	
	std::cout << "Please input ENTER." << std::endl;
	getchar();

	return 0;
}
