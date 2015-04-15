#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"

#include "TcpNetworking/simpletcpstartpoint.hpp"



extern void __attach(void);
extern void __attachInterfaces(void);
extern void __attachGenerics(void);
extern void __attachAssets(void);
extern void __attachQImage(void);
extern void __attachWavefront(void);

int nb_Client_connect;

void connection_Client (QUuid client, SimpleTcpStartPoint *server, SharedResourcePtr ptr){

    ByteBuffer messageCube = ResourceHolder::ToBuffer(ptr);
    server->send(client,messageCube); std::cout << "Sent : " << messageCube.getLength() << " bytes" << std::endl;

}

int main ( int argc, char** argv ) {

    __attachQImage();
    __attachWavefront();


    FileDescriptor file ( argv[1]);
    SharedResourceList ress = ResourceHolder::Load(file);
    SharedResourcePtr ptr = ress [0];

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

            th_client[nb_Client_connect] = std::thread (connection_Client, client, &server, ptr);
            nb_Client_connect++;
            std::cout<<"Client "<<nb_Client_connect<<" est connecté"<<endl;
        }
    }
    server.stop ();
    return 0;
}
