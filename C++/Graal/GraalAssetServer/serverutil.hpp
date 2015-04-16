#ifndef SERV_UTIL_HPP
#define SERV_UTILL_HPP

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

#endif
