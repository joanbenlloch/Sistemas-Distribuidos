//Joan Benlloch   Pedro Morales
#include "multMatrix_imp.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "utils.h"

#define PORT 30001

void threadClient(int clientId){

    multMatrix_imp* mmi = new multMatrix_imp(clientId);
    mmi->recvOp();
    delete mmi;
}

int main(int argc, char** argv)
{
    int serverId = initServer(PORT);

    while(1){//bucle de escucha esperando una conexión

        if(checkNewConnections()){
            int clientId = getNewConnection();
            std::thread*th= new std::thread(threadClient, clientId);
            //th->detach();
        }
        //trabajo útil
        usleep(100);

    }
	
    close(serverId);
    return 0;

}