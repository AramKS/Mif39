#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"

#include "TcpNetworking/simpletcpendpoint.hpp"

#include <iostream>
#include <fstream>

#include <time.h>


extern void __attach(void);
extern void __attachInterfaces(void);
extern void __attachGenerics(void);
extern void __attachAssets(void);
extern void __attachQImage(void);
extern void __attachWavefront(void);




int main ( int argc, char** argv ) {
    __attachQImage();
    __attachWavefront();

    /* initialize random seed: */
    srand (time(NULL));

    SimpleTcpEndPoint::Options options;
    options.serverIP = "127.0.0.1";
    options.connectionPort = 3000;
    SimpleTcpEndPoint client ( options );
    ByteBuffer message;
    int randomRequest = rand() % 6 + 1;
    randomRequest -=1;
    unsigned char ch = randomRequest + '0';

    std::cout << std::endl << randomRequest << std::endl << ch << std::endl;

    ByteBuffer request(&ch, 1);
    if ( client.open() == false ) exit ( -1 );

    client.send(request);


    while(message.getLength()==0)
        client.receive(message); std::cout << "Recv : " << message.getLength() << " bytes" << std::endl;

    unsigned long long d = 0;

    SharedResourcePtr ptr = ResourceHolder::FromBuffer(message,d);

    std::cout<<ptr->getUUID().toString().toStdString()<<std::endl;

    ptr->Usage();
    std::cout<<"Vertices : "<<std::endl;
    Vector3d * p = ptr->get < Vector3d* > ( "Vertices");
    for(int i=0;i<ptr->get < unsigned int > ( "#Vertices");i++){
        std::cout<<p[i].x<<" ";
        std::cout<<p[i].y<<" ";
        std::cout<<p[i].z<<std::endl;
    }

    std::cout<<"Triangles : "<<std::endl;
    Triangle * t = ptr->get < Triangle* > ( "Faces");
    for(int i=0;i<ptr->get < unsigned int > ( "#Faces");i++){
        std::cout<<t[i].m_vertexIndices[0]<<" // "<<t[i].m_normalIndices[0]<<"  ";
        std::cout<<t[i].m_vertexIndices[1]<<" // "<<t[i].m_normalIndices[1]<<"  ";
        std::cout<<t[i].m_vertexIndices[2]<<" // "<<t[i].m_normalIndices[2]<<std::endl;
    }

    std::cout<<"Normales : "<<std::endl;
    Vector3d * n = ptr->get < Vector3d* > ( "Normals");
    for(int i=0;i<ptr->get < unsigned int > ( "#Normals");i++){
        std::cout<<n[i].x<<" ";
        std::cout<<n[i].y<<" ";
        std::cout<<n[i].z<<std::endl;
    }

    std::cout<<"Textures : "<<std::endl;
    Vector2d * tex = ptr->get < Vector2d* > ( "TexVertices");
    for(int i=0;i<ptr->get < unsigned int > ( "#TexVertices");i++){
        std::cout<<tex[i].x<<" ";
        std::cout<<tex[i].y<<std::endl;
    }

    client.close ();

    return 0;
}
