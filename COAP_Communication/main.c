
#include <stdio.h>
#include "msg.h"

#include "net/gcoap.h"
#include "shell.h"
#include "fmt.h"

#include "lpsxxx.h"
#include "lpsxxx_params.h"

#include "isl29020.h"
#include "isl29020_params.h"
#include "isl29020-internal.h"


/* Declaration lpsxxx_t sensor variable  */
static lpsxxx_t sensor;
/* Declaration isl29020 sensor variable  */
static isl29020_t isl29020;

static ssize_t _encode_link(const coap_resource_t *resource, char *buf,
                            size_t maxlen, coap_link_encoder_ctx_t *context);

static ssize_t _temperature_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);
static ssize_t _pressure_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);
static ssize_t _light_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);

static const coap_resource_t _resources[] = {
    { "/temperature", COAP_GET, _temperature_handler, NULL },
    { "/pressure", COAP_GET, _pressure_handler, NULL },
    { "/light", COAP_GET, _light_handler, NULL },

};


static ssize_t _temperature_handler(coap_pkt_t *pdu, uint8_t *buf, 
                                         size_t len, void *ctx)
{
    (void)ctx;

    /* Implementation the temperature GET handler */
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    char response[32];
    int16_t temp;
    lpsxxx_read_temp(&sensor, &temp);
    sprintf(response, "%i.%u°C",(temp / 100), (temp % 100));

    /* write the temperature value in the response buffer */
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

}

static ssize_t _pressure_handler(coap_pkt_t *pdu, uint8_t *buf, 
                                         size_t len, void *ctx)
{
    (void)ctx;

     /* Implementation the pressure GET handler */
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    char response[32];
    uint16_t pres;
    lpsxxx_read_pres(&sensor, &pres);
    sprintf(response,"%uhPa", pres);

    /* write the pressure value in the response buffer */
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

}

static ssize_t _light_handler(coap_pkt_t *pdu, uint8_t *buf, 
                                         size_t len, void *ctx)
{
    (void)ctx;

    /* Implementation the luminosity GET handler */
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    char response[32];
    int16_t light;
    light=isl29020_read(&isl29020);
    sprintf(response, "%i.%ulx",(light / 100), (light % 100));

    /* write the luminosity value in the response buffer */
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }

}


static gcoap_listener_t _listener = {
    &_resources[0],
    ARRAY_SIZE(_resources),
    _encode_link,
    NULL,
    NULL
};

/* Adds link format params to resource list */
static ssize_t _encode_link(const coap_resource_t *resource, char *buf,
                            size_t maxlen, coap_link_encoder_ctx_t *context) {
    ssize_t res = gcoap_encode_link(resource, buf, maxlen, context);

    return res;
}

void gcoap_cli_init(void)
{
    gcoap_register_listener(&_listener);
}


#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int gcoap_cli_cmd(int argc, char **argv);
extern void gcoap_cli_init(void);

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    isl29020_init (&isl29020, &isl29020_params[0]);

     if (lpsxxx_init(&sensor, &lpsxxx_params[0]) != LPSXXX_OK) {
        puts("LPS331AP initialization failed");
        return 1;
    }
    lpsxxx_enable(&sensor);
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    gcoap_cli_init();
    puts("gcoap example app");

    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
