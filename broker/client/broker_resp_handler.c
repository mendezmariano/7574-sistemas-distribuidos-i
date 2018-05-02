//
// Created by gaston on 22/04/18.
//


#include <stdlib.h>
#include <unistd.h>
#include "../common/log/log.h"
#include "../common/ipc/msg_queue.h"
#include "broker_handler.h"
#include "../common/ipc/shm.h"
#include "../common/message.h"
#include "../common/ipc/semaphore.h"

int get_msg_req_queue();

msg_t* get_msg_shm() {
    int msg_shm = getshm(INCOMING_MSG_SHM);
    if (msg_shm < 0) {
        log_error("Error getting msg shm.");
        exit(-1);
    }
    return map(msg_shm);
}

int* get_msg_count_shm() {
    int msg_count_shm = getshm(INCOMING_MSG_COUNT_SHM);
    if (msg_count_shm < 0) {
        log_error("Error getting msg count shm.");
        exit(-1);
    }
    return map(msg_count_shm);
}

int get_incoming_msg_sem() {
    int incoming_msgs_sem = getsem(INCOMING_MSG_SEM);
    if (incoming_msgs_sem < 0) {
        log_error("Error getting msg sem.");
        exit(-1);
    }
    return incoming_msgs_sem;
}

int main(int argc, char* argv[]) {
    log_info("Starting local broker Response Handler.");

    if (argc < 2) {
        log_error("No socket parameter received.");
        exit(-1);
    }
    int socket_fd;
    sscanf(argv[1], "%d", &socket_fd);

    int resp_queue = get_msg_req_queue();
    msg_t* incoming_msgs = get_msg_shm();
    int* incoming_msg_count = get_msg_count_shm();
    int incoming_msgs_sem = get_incoming_msg_sem();


    incoming_msgs[0].type = CREATE;

    // TODO while(true) read from socket and send msg to resp_queue.

    unmap(incoming_msgs);
    unmap(incoming_msg_count);

    log_debug("Closing socket");
    close(socket_fd);


}

int get_msg_req_queue() {
    int resp_queue = getmsg(BROKER_RESP_MSG);
    if (resp_queue < 0) {
        log_error("Error getting resp message queue");
        exit(-1);
    }
    return resp_queue;

}