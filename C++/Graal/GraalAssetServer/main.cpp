#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"

#include "TcpNetworking/simpletcpstartpoint.hpp"

int nb_Client_connect;

void connection_Client (QUuid client, SimpleTcpStartPoint *server){
    while ( true ) {
        ByteBuffer message;
        server->receive(client,message); std::cout<<client.toString().toStdString()<<std::endl;//std::cout << "Recv : " << message.getLength() << " bytes" << std::endl;
        server->send(client,message); std::cout << "Sent : " << message.getLength() << " bytes" << std::endl;
    }
}

int main ( int argc, char** argv ) {
    nb_Client_connect = 0;
    std::thread th_client[10];
    std::thread th_listen;

    QUuid fake;
    SimpleTcpStartPoint::Options options;
    options.connectionPort = 3000;
    options.maximumConnectedClients = 2;
    SimpleTcpStartPoint server ( options );
    server.start();
    QUuid client;

    while ( true ) {
        client = server.listen();
        bool insert = true;
        if (client != fake){
            th_client[nb_Client_connect] = std::thread (connection_Client, client, &server/**/);
            nb_Client_connect++;
            std::cout<<"Client "<<nb_Client_connect<<" est connecté"<<endl;
        }
    }
    server.stop ();
    return 0;
}
