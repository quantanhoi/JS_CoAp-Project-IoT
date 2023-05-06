#include <iostream>
#include <SDL.h>
#include<sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>


#include "common.hh"


int send_payload_to_server(coap_session_t *session, const char *payload) {
  coap_pdu_t *pdu = coap_pdu_init(COAP_MESSAGE_CON,
                                  COAP_REQUEST_CODE_POST,
                                  coap_new_message_id(session),
                                  coap_session_max_pdu_size(session));
  if (!pdu) {
    coap_log_emerg("cannot create PDU\n");
    return -1;
  }

  /* add a Uri-Path option */
  coap_add_option(pdu, COAP_OPTION_URI_PATH, 5,
                  reinterpret_cast<const uint8_t *>("hello"));

  coap_add_data(pdu, strlen(payload), reinterpret_cast<const uint8_t *>(payload));

  coap_show_pdu(COAP_LOG_WARN, pdu);

  if (coap_send(session, pdu) == COAP_INVALID_MID) {
    coap_log_err("cannot send CoAP pdu\n");
    return -1;
  }

  return 0;
}



static int have_response = 0;
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    int num_joysticks = SDL_NumJoysticks();
    if (num_joysticks < 1) {
        std::cerr << "No joysticks connected" << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (!joystick) {
        std::cerr << "Failed to open joystick: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;






    //test COAP client
    coap_context_t *ctx = nullptr;
    coap_session_t *session = nullptr;
    coap_address_t dst;
    coap_pdu_t *pdu = nullptr;
    int result = EXIT_FAILURE;

    coap_startup();

    /* Set logging level */
    coap_set_log_level(COAP_LOG_WARN);
    const char *payload = "Hello, bruh";
    /* resolve destination address where server should be sent */
    if (resolve_address("localhost", "5683", &dst) < 0) {
        coap_log_crit("failed to resolve address\n");
        goto finish;
    }

    /* create CoAP context and a client session */
    if (!(ctx = coap_new_context(nullptr))) {
        coap_log_emerg("cannot create libcoap context\n");
        goto finish;
    }
    
    /* Support large responses */
    coap_context_set_block_mode(ctx,
                    COAP_BLOCK_USE_LIBCOAP | COAP_BLOCK_SINGLE_BODY);

    if (!(session = coap_new_client_session(ctx, nullptr, &dst,
                                                    COAP_PROTO_UDP))) {
        coap_log_emerg("cannot create client session\n");
        goto finish;
    }

    /* coap_register_response_handler(ctx, response_handler); */
    coap_register_response_handler(ctx, [](auto, auto,
                                            const coap_pdu_t *received,
                                            auto) {
                                            have_response = 1;
                                            coap_show_pdu(COAP_LOG_WARN, received);
                                            return COAP_RESPONSE_OK;
                                        });
    /* construct CoAP message */
    pdu = coap_pdu_init(COAP_MESSAGE_CON,
                        COAP_REQUEST_CODE_POST, // Change this line from COAP_REQUEST_CODE_GET
                        coap_new_message_id(session),
                        coap_session_max_pdu_size(session));
    if (!pdu) {
        coap_log_emerg("cannot create PDU\n" );
        goto finish;
    }

    /* add a Uri-Path option */
    coap_add_option(pdu, COAP_OPTION_URI_PATH, 5,
                    reinterpret_cast<const uint8_t *>("hello"));

    coap_add_data(pdu, strlen(payload), reinterpret_cast<const uint8_t *>(payload));

    coap_show_pdu(COAP_LOG_WARN, pdu);
    /* and send the PDU */
    if (coap_send(session, pdu) == COAP_INVALID_MID) {
        coap_log_err("cannot send CoAP pdu\n");
        goto finish;
    }

    while (have_response == 0)
        coap_io_process(ctx, COAP_IO_WAIT);

    result = EXIT_SUCCESS;




//   end coap 


    while (running) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_JOYBUTTONDOWN ) {
            std::ostringstream message;
            message << "Button: " << static_cast<int>(e.jbutton.button) << ", " << "State:" << static_cast<int>(e.jbutton.state);
            std::string tempString = message.str(); // Store the message string in a temporary variable
            payload = tempString.c_str(); // Get the const char* from the temporary string
            std::cout << payload << std::endl;
            send_payload_to_server(session, payload);
            have_response = 0; // Reset have_response
            while (have_response == 0) {
                coap_io_process(ctx, COAP_IO_WAIT);
            }
        }
        // ...
    }
}


    SDL_JoystickClose(joystick);
    SDL_Quit();



finish:
    coap_session_release(session);
    coap_free_context(ctx);
    coap_cleanup();

    return result;
    return 0;
}