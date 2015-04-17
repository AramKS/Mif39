#ifndef SERV_UTIL_HPP
#define SERV_UTILL_HPP
#include "Assets/structures.hpp"

namespace TypeRequest
{
     typedef enum
     {
          simple,   // 0
          coords ,  // 1
          image     // 2
     }TypeRequest;
}

void loadAllObj(){
    DIR *pDIR;
    struct dirent *entry;
    if( pDIR=opendir("./obj") ){
            while(entry = readdir(pDIR)){
                    if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                        QString path = "./obj/";
                        path.append(entry->d_name);
                        std::cout << path.toStdString() << "\n";
                        FileDescriptor file (path);
                        SharedResourceList ress = ResourceHolder::Load(file);
                    }
            }
            closedir(pDIR);
    }
}

ByteBuffer simpleRequest(const ByteBuffer &request){
    int requestNb = ((request.getData()[0]) - '0');

    QList <QUuid> l = ResourceHolder::AllKeys();
    SharedResourcePtr p = ResourceHolder::GetByUUID(l.at(requestNb));
    ByteBuffer mess = ResourceHolder::ToBuffer(p);

    return mess;
}

ByteBuffer imageRequest(const ByteBuffer &request){
    QString path = "./test.jpg";
    FileDescriptor file (path);
    SharedResourceList ress = ResourceHolder::Load(file);
    SharedResourcePtr ptr = ress [0];
    ByteBuffer message = ResourceHolder::ToBuffer(ptr);

    return message;
}

Vector3d loadCoords(const ByteBuffer &request){
    Vector3d res;
    float ftemp[3];
    int j=0;
    int k =0;
    char nb[1000];
    int ecart = 0;
    bool boucle = true;
    while(boucle)
    {
        if(request.getData()[j] == ' ')
        {
            char nbfin[j-ecart];
            for(int i=0;i<j-ecart;i++)
                nbfin[i] = nb[i];
            ecart = j+1;
            ftemp[k] = atof(nbfin);
            k++;
        }
        if(request.getData()[j] == '\0'){
            char nbfin[j-ecart];
            for(int i=0;i<j-ecart;i++)
                nbfin[i] = nb[i];
            ecart = j+1;

            ftemp[k] = atof(nbfin);
            k++;
            boucle = false;
        }
        else{
            nb[j - ecart] = request.getData()[j];
        }
        j++;
    }

    res.x = ftemp[0];
    res.y = ftemp[1];
    res.z = ftemp[2];

    std::cout<<res.x<<std::endl;
    std::cout<<res.y<<std::endl;
    std::cout<<res.z<<std::endl;
    return res;
}

#endif
