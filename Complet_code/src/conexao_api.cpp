#include <HTTPClient.h> // Biblioteca para realizar requisições HTTP
#include "iot.h" // Certifique-se de que este arquivo gerencia a conexão Wi-Fi

// URLs da API
const char* serverName = "http://192.168.1.100/api.php"; // Endpoint para envio de dados
const char* serverNameListar = "http://192.168.1.100/api.php?listar=true"; // Endpoint para listar dados

// Função para enviar dados para a API
void enviar_api() {
    // Verifica se o Wi-Fi está conectado
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Cria um objeto HTTPClient
        http.begin(serverName); // Configura o endpoint para envio
        http.addHeader("Content-Type", "application/json"); // Adiciona o cabeçalho Content-Type para indicar o formato JSON

        // JSON de exemplo a ser enviado para o servidor
        String jsonPayload = "{\"uid\":\"123456\", \"descricao\":\"Produto Teste\", \"quantidade\":5}";

        // Faz a requisição POST para enviar os dados
        int httpResponseCode = http.POST(jsonPayload);

        // Verifica a resposta do servidor
        if (httpResponseCode > 0) {
            String response = http.getString(); // Obtém a resposta do servidor
            Serial.println("Resposta do servidor:");
            Serial.println(response); // Imprime a resposta no Serial Monitor
        } else {
            Serial.print("Erro na requisição HTTP: "); // Caso ocorra erro, imprime o código de erro
            Serial.println(httpResponseCode);
        }

        http.end(); // Finaliza a conexão HTTP
    } else {
        Serial.println("WiFi desconectado"); // Mensagem de erro caso o Wi-Fi não esteja conectado
    }
}

// Função para receber dados da API
void receber_api() {
    // Verifica se o Wi-Fi está conectado
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Cria um objeto HTTPClient
        http.begin(serverNameListar); // Configura o endpoint para listar os dados

        // Faz a requisição GET para obter os dados do servidor
        int httpResponseCode = http.GET();

        // Verifica a resposta do servidor
        if (httpResponseCode > 0) {
            String response = http.getString(); // Obtém os dados recebidos do servidor
            Serial.println("Dados recebidos da API:");
            Serial.println(response); // Imprime os dados recebidos no Serial Monitor
        } else {
            Serial.print("Erro na requisição HTTP: "); // Caso ocorra erro, imprime o código de erro
            Serial.println(httpResponseCode);
        }

        http.end(); // Finaliza a conexão HTTP
    } else {
        Serial.println("WiFi desconectado"); // Mensagem de erro caso o Wi-Fi não esteja conectado
    }
}
