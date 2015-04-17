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
const int nb_Client_Max = 100000000;
int th_active[nb_Client_Max];
QMap<QUuid, int> mapQUuid;

/** Prototypes */
void init_th_active ();
void Thread_Client (QUuid client, SimpleTcpStartPoint *server);
void connection_Client (QUuid client, SimpleTcpStartPoint *server);
void serverListen (SimpleTcpStartPoint *server);
/** ##################### */

int main ( int argc, char** argv ) {
    __attachQImage();
    __attachWavefront();

    nb_Client_connect = 0;
    init_th_active();
    std::thread th_listen;

    SimpleTcpStartPoint::Options options;
    options.connectionPort = 3000;
    options.maximumConnectedClients = 2;
    SimpleTcpStartPoint server ( options );
    server.start();

    loadAllObj();

    th_listen = std::thread (serverListen, &server);
    std::cout << "Serveur en ecoute..." << std::endl;

    while (true)
        std::this_thread::yield();

    server.stop ();
    return 0;
}

/** thread d'ecoute */
void serverListen (SimpleTcpStartPoint *server){
    QUuid fake;
    std::thread th_client[nb_Client_Max];

    while ( true ) {
        QUuid client;
        while (client == fake)
            client = server->listen();
        if (client != fake){
            bool insertQUuid = true;
            for (QMap<QUuid, int>::iterator it = mapQUuid.begin(); it != mapQUuid.end(); it++){
                if (it.key() == client){
                    insertQUuid = false;
                    th_active[mapQUuid[client]] =1;
                    std::cout<<"Client "<<mapQUuid.value(client)<<" est connecté"<<std::endl;
                }
            }
            if (insertQUuid){
                nb_Client_connect++;
                mapQUuid.insert(client, nb_Client_connect);
               th_client[nb_Client_connect] = std::thread (Thread_Client, client, server);
            }
            std::cout<<"Client "<<mapQUuid.value(client)<<" est connecté"<<std::endl;
        }
        std::this_thread::yield();
    }
}

/** Initialisation du tableau des threads actuves */
void init_th_active (){
    for (int i = 0; i < nb_Client_Max; i++){
        th_active[i] = 0;
    }
}

/** lancement du thread a la premiere connexion du client */
void Thread_Client (QUuid client, SimpleTcpStartPoint *server){
    //connection_Client (client, server);

        //while (th_active[mapQUuid[client]] == 0){}
        std::cout<<"connexion \t"<<std::endl;
        connection_Client (client, server);
        //th_active[mapQUuid[client]] = 0;

        std::this_thread::yield();

}

/** gestion d'une requete du client */
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
        case 2:
        {
            std::cout<<std::endl<<"IMAGE SENT "<<std::endl;
            while(request.getLength() == 0)
                server->receive(client,request);
            ByteBuffer mess = imageRequest(request);
            server->send(client, mess);
            break;
        }
    }
}

