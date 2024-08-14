#include <grpcpp/grpcpp.h>
#include "Actia.pb.h"
#include "Actia.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Use the namespace defined in the proto file
namespace example {

class CheckInServiceImpl final : public CheckIn::Service {
    Status GetFeature(ServerContext* context, const point* request, feature* response) override {
        // Process the request and populate the response
        response->set_id(request->id());
        response->set_nom("Example Feature");
        return Status::OK;
    }
};

}  // namespace example

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    example::CheckInServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
