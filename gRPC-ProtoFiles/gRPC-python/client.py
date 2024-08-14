# client.py
import grpc
import Actia_pb2
import Actia_pb2_grpc

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = Actia_pb2_grpc.CheckInStub(channel)
    
    # Create a Point message
    point = Actia_pb2.Point(id=1, nom="Test Point")
    
    # Call the GetFeature RPC method
    response = stub.GetFeature(point)
    
    print(f"Feature received: id={response.id}, nom={response.nom}")

if __name__ == '__main__':
    run()
