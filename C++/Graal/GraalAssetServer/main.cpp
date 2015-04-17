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

    ByteBuffer typerequest;
    ByteBuffer request;
    while(typerequest.getLength() == 0)
        server->receive(client,typerequest);
    int type = ((typerequest.getData()[0]) - '0');

    switch (type)
    {
        case 0:
        {
            std::cout<<std::endl<<"SIMPLE REQUEST (MESH) "<<std::endl;
            while(request.getLength() == 0)
                server->receive(client,request);
            ByteBuffer mess = simpleRequest(request);
            server->send(client, mess);
            break;
        }
        case 1:
        {
            std::cout<<std::endl<<"COORDS SENT "<<std::endl;
            while(request.getLength() == 0)
                server->receive(client,request);
            Vector3d coord = loadCoords(request);
            break;
        }
    }
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
