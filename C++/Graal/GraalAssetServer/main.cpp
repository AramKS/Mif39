#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"

#include "TcpNetworking/simpletcpstartpoint.hpp"


void prin(){
    std::cout<<"Test thread !! "<<std::endl;
}

int main ( int argc, char** argv ) {
    std::cout<<"lol"<<std::endl;
    QUuid fake;
    SimpleTcpStartPoint::Options options;
    options.connectionPort = 3000;
    options.maximumConnectedClients = 1;
    SimpleTcpStartPoint server ( options );
    server.start();
    QUuid client;
    std::thread first(prin);
    std::cout<<first.get_id()<<std::endl;
    while ( client == fake ) {
        client = server.listen();
    }
    while ( true ) {
        ByteBuffer message;
        server.receive(client,message);// std::cout << "Recv : " << message.getLength() << " bytes" << std::endl;
        server.send(client,message); //std::cout << "Sent : " << message.getLength() << " bytes" << std::endl;
    }
    server.stop ();
    return 0;
}
