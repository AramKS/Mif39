#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"
#include "TcpNetworking/simpletcpstartpoint.hpp"

#include "serverutil.hpp"

extern void __attach(void);
extern void __attachInterfaces(void);
extern void __attachGenerics(void);
extern void __attachAssets(void);
extern void __attachQImage(void);
extern void __attachWavefront(void);

int nb_Client_connect;

void connection_Client (QUuid client, SimpleTcpStartPoint *server){

    ByteBuffer request;
    server->receive(client,request);
    std::cout<<"Request : "<<request.getData()<<std::endl;
    int requestNb = ((request.getData()[0]) - '0');

    QList <QUuid> l = ResourceHolder::AllKeys();
    SharedResourcePtr p = ResourceHolder::GetByUUID(l.at(requestNb));
    ByteBuffer mess = ResourceHolder::ToBuffer(p);
    server->send(client, mess);
}

void serverListen (SimpleTcpStartPoint *server){
    QUuid fake;
    std::thread th_client[10];

    while ( true ) {
        QUuid client;
        while (client == fake)
            client = server->listen();
        if (client != fake){
            th_client[nb_Client_connect] = std::thread (connection_Client, client, server);
            nb_Client_connect++;
            std::cout<<"Client "<<nb_Client_connect<<" est connecté"<<endl;
        }
        std::this_thread::yield();
    }
}

int main ( int argc, char** argv ) {
    __attachQImage();
    __attachWavefront();

    nb_Client_connect = 0;
    std::thread th_listen;

    SimpleTcpStartPoint::Options options;
    options.connectionPort = 3000;
    options.maximumConnectedClients = 2;
    SimpleTcpStartPoint server ( options );
    server.start();

    loadAllObj();

    th_listen = std::thread (serverListen, &server);

    while (true)
        std::this_thread::yield();

    server.stop ();
    return 0;
}
