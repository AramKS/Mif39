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

   /* std::cout<<ptr2->getName().toStdString()<<std::endl;*/


    client.close ();

    return 0;
}
