// #include <HTTPClient.h> // Biblioteca para realizar requisições HTTP
// #include "iot.h" // Certifique-se de que este arquivo gerencia a conexão Wi-Fi
// #include "json.h"
// #include "nfc_rfid.h"

// // URLs da API
// const char* serverName = "http://192.168.1.100/api.php"; // Endpoint para envio de dados
// const char* serverNameListar = "http://192.168.1.100/api.php?listar=true"; // Endpoint para listar dados

// // Função para enviar dados para a API
// void enviar_api() {
//      if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin(serverName);
//         http.addHeader("Content-Type", "application/json");

//         // Monta o JSON com o UID
//         String jsonPayload = "{\"uid\":" + String(numericUID) + "}";
//         Serial.println("Enviando JSON:");
//         Serial.println(jsonPayload);

//         int httpResponseCode = http.POST(jsonPayload);

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println("Resposta da API:");
//             Serial.println(response);
//         } else {
//             Serial.print("Erro na requisição: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("WiFi desconectado!");
//     }
// }

// // Função para receber dados da API
// void receber_api() {
//     // Verifica se o Wi-Fi está conectado
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http; // Cria um objeto HTTPClient
//         http.begin(serverNameListar); // Configura o endpoint para listar os dados

//         // Faz a requisição GET para obter os dados do servidor
//         int httpResponseCode = http.GET();

//         // Verifica a resposta do servidor
//         if (httpResponseCode > 0) {
//             String response = http.getString(); // Obtém os dados recebidos do servidor
//             Serial.println("Dados recebidos da API:");
//             Serial.println(response); // Imprime os dados recebidos no Serial Monitor
//         } else {
//             Serial.print("Erro na requisição HTTP: "); // Caso ocorra erro, imprime o código de erro
//             Serial.println(httpResponseCode);
//         }

//         http.end(); // Finaliza a conexão HTTP
//     } else {
//         Serial.println("WiFi desconectado"); // Mensagem de erro caso o Wi-Fi não esteja conectado
//     }
// }
