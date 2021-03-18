#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/stat.h>


int g_is_pb_pressed = 0;

struct leds
{
    struct gpiohandle_request request;
    struct gpiohandle_data data;
};

typedef struct leds LEDs;

struct push_button
{
    struct gpioevent_request request;
    struct gpioevent_data event;
};

typedef struct push_button PushButton;

struct listen_pb_args
{
    LEDs ryg_leds;
    PushButton pb;
};

LEDs init_leds(int fd)
{
    LEDs ryg_leds;

    ryg_leds.request.lines = 3;
    ryg_leds.request.lineoffsets[0] = 27; // pin 27 - Red LED
    ryg_leds.request.lineoffsets[1] = 4; // pin 4 - Green LED
    ryg_leds.request.lineoffsets[2] = 17; // pin 17 - Yellow LED
    ryg_leds.request.flags = GPIOHANDLE_REQUEST_OUTPUT;

    ryg_leds.data.values[0] = 0; // Red LED is off initially
    ryg_leds.data.values[1] = 1; // Green LED is on initially
    ryg_leds.data.values[2] = 0; // Yellow LED is off initially

    ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &(ryg_leds.request));

    return ryg_leds;
}

PushButton init_push_button(int fd)
{
    PushButton pb;

    pb.request.lineoffset = 11; // pin 11 - Push Button
    pb.request.handleflags = GPIOHANDLE_REQUEST_INPUT;
    pb.request.eventflags = GPIOEVENT_EVENT_RISING_EDGE;

    strcpy(pb.request.consumer_label, "Push Button event");

    ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &(pb.request));

    return pb;
}

void* toggle_yellow_green_leds(void* args)
{
    LEDs* ryg_leds = (LEDs*) args;

    while(1)
    {
        usleep(1000000); // sleep for 1 second

        if(g_is_pb_pressed)
            ryg_leds->data.values[0] = !ryg_leds->data.values[0];

        ryg_leds->data.values[1] = !ryg_leds->data.values[1];
        ryg_leds->data.values[2] = !ryg_leds->data.values[2];

        ioctl(ryg_leds->request.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &(ryg_leds->data));
    }
}

void* listen_push_button(void* args)
{
    struct listen_pb_args* actual_args = (struct listen_pb_args*) args;

    LEDs ryg_leds = actual_args->ryg_leds;
    PushButton pb = actual_args->pb;

    int read_result;

    while(1)
    {
        read_result = read(pb.request.fd, &(pb.event), sizeof(pb.event));

        if(read_result == -1)
        {
            perror("error reading push button");
        }
        else if(read_result == 0)
        {
            fprintf(stdout, "button released\n");
            g_is_pb_pressed = 0;
        }
        else
        {
            fprintf(stdout, "button pressed\n");
            g_is_pb_pressed = 1;
        }
    }
}

int main(int argc, char* argv[])
{
    int fd0 = open("/dev/gpiochip0", O_RDWR);

    struct gpiochip_info c_info;

    ioctl(fd0, GPIO_GET_CHIPINFO_IOCTL, &c_info);
    fprintf(stdout, "GPIO chip 0: %s, \"%s\", %u lines\n", c_info.name, c_info.label, c_info.lines);

    LEDs ryg_leds = init_leds(fd0);
    ioctl(ryg_leds.request.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &(ryg_leds.data));

    PushButton pb = init_push_button(fd0);

    pthread_t yg_thread, pb_thread;

    pthread_create(&yg_thread, NULL, toggle_yellow_green_leds, (void*) &ryg_leds);

    struct listen_pb_args args;
    args.ryg_leds = ryg_leds;
    args.pb = pb;
    pthread_create(&pb_thread, NULL, listen_push_button, (void*) &args);

    pthread_join(yg_thread, NULL);
    pthread_join(pb_thread, NULL);

    // release lines
    close(pb.request.fd);
    close(ryg_leds.request.fd);

    close(fd0); // close fd for GPIO chip 0

    exit(EXIT_SUCCESS);
}