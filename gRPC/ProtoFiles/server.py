# server.py
from concurrent import futures
import grpc
import Actia_pb2
import Actia_pb2_grpc

class CheckInServicer(Actia_pb2_grpc.CheckInServicer):
    def GetFeature(self, request, context):
        # Implement your logic here
        return Actia_pb2.Feature(id=request.id, nom=f"Feature {request.id}")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    Actia_pb2_grpc.add_CheckInServicer_to_server(CheckInServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server is running on port 50051.")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
