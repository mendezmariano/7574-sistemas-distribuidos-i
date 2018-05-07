//
// Created by gaston on 04/05/18.
//

#include <unistd.h>
#include "../common/log/log.h"
#include "broker.h"

int main(int argc, char* argv[]) {
    log_info("Starting test client.");
    int mom = creabrk();
    log_info("mom created: %d", mom);

    sleep(10);

    int res = subscribe(mom, "Avengers");
    log_info("Subscribed result %d.", res);

    sleep(10);

    res = subscribe(mom, "NBA");
    log_info("Subscribed result %d.", res);

    sleep(10);

    res = publish(mom, "Infinity war rules!", "Avengers");
    log_info("Published message result %d.", res);

    sleep(10);

    payload_t payload;
    res = receive(mom, &payload);
    log_info("Receive result %d.", res);
    log_info("Message received on topic '%s' : '%s'", payload.topic, payload.msg);

    sleep(10);

    res = delbrk(mom);
    log_info("Delete result %d.", res);

}
