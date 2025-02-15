#include "uart_cmd.h"


rf_status_t RF_status = RF_ON;



/**
 * Wybór aktualnego łącza komunikacyjnego. Komenda jako jedyna może zostać odebrana na dowolnym łączu, bez względu na to które obecnie obsługuje moduł Master.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Master_SetLink(uint8_t *data, uart_packet_link_t link_type) {
    //komenda zawsze mozliwa do odebrania, bez wzgledu na aktualnie wybrane lacze i lacze po ktorym ja wyslano
    //dodatkowo informacja zawsze wysylana na uart debugowy

    printf("[%s] Master SetLink: %d\r\n",
            (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
            data[0]);

    //TODO: more dynamic uart
    uart_packet_link_t new_link = LINK_RF_UART;
    if (data[0] == 0) {
        new_link = LINK_RF_UART;
    }
    else if (data[0] == 1) {
        new_link = LINK_AUTO_UART;
    }
    else if (data[0] == 2) {
        new_link = LINK_AUTO_UART;
    }

    //najpierw odsylana jest odpowiedz na poprzednie lacze, a potem nastepuje jego aktualizacja
    Cmd_UART_Master_SetLinkResponse(new_link);
    logic.link_type = new_link;

    Cmd_UART_BlinkLed(link_type);
}

/**
 * Zwracanie potwierdzenia zmiany łącza komunikacyjnego, po odebraniu komendy Cmd_Master_SetLink. Ramka zwracana jest jeszcze na poprzednim łączu (tzn. odsyłana jest przed zmianą).
 */
void Cmd_UART_Master_SetLinkResponse(uart_packet_link_t new_link) {
    uart_packet_t msg = {
        .cmd = UART_CMD_MASTER_SET_LINK_RESPONSE,
        .arg_count = UART_ARG_MASTER_SET_LINK_RESPONSE,
        .origin = logic.link_type,
        .args = {new_link}
    };

    Queues_SendUARTFrame(&msg);
}

//silent mode to limit interference
void Cmd_UART_SilentMode(uint8_t* data, uart_packet_link_t link_type) {
	RF_status = data[0];
}
