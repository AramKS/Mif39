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


    int type = argv[1][0] - '0';
    int randomRequest = rand() % 6 + 1;
    randomRequest -=1;
    unsigned char ch = randomRequest + '0';
    unsigned char c = type +'0';
    unsigned char coords[100] = "0.25264 1.26145 10.0";

    //Type request
    ByteBuffer requestType (&c,1);

    if ( client.open() == false ) exit ( -1 );

    //Type request
    client.send(requestType);

    //Request
    switch (type)
    {
        case 0:
        {
            ByteBuffer request(&ch, 1);
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
                if(t[i].m_hasNormals)
                    std::cout<<"Normales ok"<<std::endl;
                if(t[i].m_hasTexcoords)
                    std::cout<<"Textures ok"<<std::endl;

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
            break;
        }
        case 1:
        {
            ByteBuffer request(coords, 20);
            client.send(request);
            break;
        }

        case 2 :
        {
            ByteBuffer request(&ch, 1);
            client.send(request);
            while(message.getLength()==0)
                client.receive(message); std::cout << "Recv : " << message.getLength() << " bytes" << std::endl;
            unsigned long long d = 0;

            SharedResourcePtr ptr = ResourceHolder::FromBuffer(message,d);

            std::cout<<ptr->getUUID().toString().toStdString()<<std::endl;

            ptr->Usage();

            unsigned int w = ptr->get <unsigned int> ("Width");
            unsigned int h = ptr->get <unsigned int> ("Height");
            unsigned int dep = ptr->get <unsigned int> ("Depth");
            unsigned int n = ptr->get <unsigned int> ("nChannels");

            std::cout<<"Width : "<<w<<std::endl;
            std::cout<<"Height : "<<h<<std::endl;
            std::cout<<"Depth : "<<dep<<std::endl;
            std::cout<<"nChannels : "<<n<<std::endl;

            /*unsigned char * data = ptr->get <unsigned char*> ("Data");
            for(int i=0;i< w*h*dep ; i++)
                std::cout<<data[i];
            std::cout<<std::endl;*/


        }
    }
    client.close ();

    return 0;
}
