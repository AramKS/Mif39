#include "QImageLoader/qimageloader.hpp"
#include "Wavefront/wavefront.hpp"

#include "TcpNetworking/simpletcpendpoint.hpp"

#include <iostream>
#include <fstream>


extern void __attach(void);
extern void __attachInterfaces(void);
extern void __attachGenerics(void);
extern void __attachAssets(void);
extern void __attachQImage(void);
extern void __attachWavefront(void);




int main ( int argc, char** argv ) {
    __attachQImage();
    __attachWavefront();

/*
    std::cout<<"MAIN : "<<std::endl<<std::endl<<std::endl;
    for(int i=0;i<messageCube.getLength();i++)
        std::cout<<messageCube.getData()[i];

    std::cout<<endl;
*/


/*
    std::ofstream myfile;
    myfile.open("example.txt");
    for(int i=0;i<messageCube.getLength();i++)
        myfile<<messageCube.getData()[i];
*/

    SimpleTcpEndPoint::Options options;
    options.serverIP = "127.0.0.1";
    options.connectionPort = 3000;
    SimpleTcpEndPoint client ( options );
    ByteBuffer message;
    if ( client.open() == false ) exit ( -1 );

    while(message.getLength()==0)
        client.receive(message); std::cout << "Recv : " << message.getLength() << " bytes" << std::endl;



    unsigned long long d = 0;

    for(int i=0;i<message.getLength();i++)
        std::cout<<message.getData()[i];
    std::cout<<std::endl;

    SharedResourcePtr ptr = ResourceHolder::FromBuffer(message,d);

    std::cout<<ptr->getName().toStdString()<<std::endl;
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

    std::cout<<"textures : "<<std::endl;
    Vector2d * tex = ptr->get < Vector2d* > ( "TexVertices");
    for(int i=0;i<ptr->get < unsigned int > ( "#TexVertices");i++){
        std::cout<<tex[i].x<<" ";
        std::cout<<tex[i].y<<std::endl;
    }

    client.close ();

    return 0;
}
