#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "greet.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using greet::Greeter;
using greet::HelloReply;
using greet::HelloRequest;

class GreeterClient
{
public:
    GreeterClient(std::shared_ptr<Channel> channel) : m_stub(Greeter::NewStub(channel)) {}
    std::string SayHello(const std::string& user)
    {
        HelloRequest request;
        request.set_name(user);

        HelloReply reply;
        ClientContext context;

        Status status = m_stub->SayHello(&context, request, &reply);

        if(status.ok())
        {
            return reply.message();
        }
        else
        {
            std::cerr << "gRPC call failed: " << status.error_message() << std::endl;
            return "gRPC call failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> m_stub;
};

int main(int argc, char** argv)
{
    std::string target_address = "localhost:50051";
    GreeterClient client(grpc::CreateChannel(target_address, grpc::InsecureChannelCredentials()));
    std::string user;
    if(argc>1) user = std::string(argv[1]);
    std::cout << "Client received: " << client.SayHello(user) << std::endl;

    return 0;
}