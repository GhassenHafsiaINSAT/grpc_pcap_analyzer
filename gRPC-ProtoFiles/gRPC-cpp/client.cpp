#include <grpcpp/grpcpp.h>
#include "Actia.grpc.pb.h"

void RunClient() {
    std::string target_str = "localhost:50051";
    auto channel = grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());
    std::unique_ptr<CheckIn::Stub> stub = CheckIn::NewStub(channel);

    point request;
    request.set_id(1);
    request.set_nom("SamplePoint");

    feature response;
    grpc::ClientContext context;
    grpc::Status status = stub->GetFeature(&context, request, &response);

    if (status.ok()) {
        std::cout << "Feature ID: " << response.id() << std::endl;
        std::cout << "Feature Name: " << response.nom() << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
    }
}

int main(int argc, char** argv) {
    RunClient();
    return 0;
}
