from concurrent.futures import ThreadPoolExecutor  # Correct import
import grpc
import example_pb2
import example_pb2_grpc


class CheckInServer(example_pb2_grpc.CheckInServicer):  # Inherit from CheckInServicer
    def GetFeature(self, request, context):  # Add the context parameter
        return example_pb2.Feature(id=1, nom="GHASSEN")


def serve():
    server = grpc.server(ThreadPoolExecutor(max_workers=10))
    example_pb2_grpc.add_CheckInServicer_to_server(CheckInServer(), server)  # Instantiate the server
    server.add_insecure_port('[::]:80')
    server.start()
    print("Server is listening on port 80")
    server.wait_for_termination()


if __name__ == "__main__":  # Fix the __name__ check
    serve()
