# server.py
from concurrent import futures  # way to create a pool of threads that execute function calls asynchronusly
import grpc                     # core library for creating gRPC clients and servers
import Actia_pb2                # contain classes for message types
import Actia_pb2_grpc           # contain classes and methodes for gRPC service 



class CheckInServer(Actia_pb2_grpc.CheckInServer): 
    def GetFeature(self,request): 
        return Actia_pb2.Feature(id=1, nom= "GHASSEN")

def serve():
    server = grpc.server(ThreadPoolExecutor(max_workers=10))
    Actia_pb2_grpc.add_CheckInServicer_to_server(CheckInServer,server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("server is listening on the port 50051")
    server.wait_for_termination()

if __name__ == __main__
    serve()
























c