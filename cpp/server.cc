#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "common.hh"

int main(void) {

  printf("server is up and running\n");
  

  coap_context_t  *ctx = nullptr;
  coap_address_t dst;
  coap_resource_t *resource = nullptr;
  coap_endpoint_t *endpoint = nullptr;
  int result = EXIT_FAILURE;;
  coap_str_const_t *ruri = coap_make_str_const("hello");
  coap_startup();

  /* resolve destination address where server should be sent */
  if (resolve_address("localhost", "5683", &dst) < 0) {
    coap_log_crit("failed to resolve address\n");
    goto finish;
  }

  /* create CoAP context and a client session */
  ctx = coap_new_context(nullptr);

  if (!ctx || !(endpoint = coap_new_endpoint(ctx, &dst, COAP_PROTO_UDP))) {
    coap_log_emerg("cannot initialize context\n");
    goto finish;
  }

  resource = coap_resource_init(ruri, 0);
  coap_register_handler(resource, COAP_REQUEST_POST,
                        [](auto, auto,
                           const coap_pdu_t *request,
                           auto,
                           coap_pdu_t *response) {
                          unsigned char buf[3];
                          coap_show_pdu(COAP_LOG_WARN, request);
                          coap_pdu_set_code(response, COAP_RESPONSE_CODE_CONTENT);

                          // Get the payload from the request
                          const uint8_t *data;
                          size_t data_len;
                          coap_get_data(request, &data_len, &data);

                          // Print the received message to the terminal
                          printf("Received message from client: %.*s\n", (int)data_len, data);

                          // Set Content-Format to text/plain
                          coap_add_option(response, COAP_OPTION_CONTENT_FORMAT,
                                          coap_encode_var_safe(buf, sizeof(buf),
                                                               COAP_MEDIATYPE_TEXT_PLAIN),
                                          buf);

                          // Echo the message back to the client
                          coap_add_data(response, data_len, data);
                          coap_show_pdu(COAP_LOG_WARN, response);
                        });


  coap_add_resource(ctx, resource);

  while (true) { coap_io_process(ctx, COAP_IO_WAIT); }

  result = EXIT_SUCCESS;
 finish:

  coap_free_context(ctx);
  coap_cleanup();

  return result;
}
