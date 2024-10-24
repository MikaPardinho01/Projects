const char *ssid = "MQTT";
const char *password = "info@134";
const char *AWS_IOT_ENDPOINT = "a3q1cz4vj5wfqi-ats.iot.us-east-1.amazonaws.com"; // adicionar o endpoint AWS
const int mqtt_port = 8883; //porta do Broker MQTT

#include <pgmspace.h>
#define THINGNAME "esp32_projeto"

//AWS IOT core Creditionals
//TLS1.2
//Amazon ROOT CA1
static const char AWS_CERT_CA[] PROGMEM = 
R"EOF(-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----)EOF";

//Dispositivos.pem
static const char AWS_CERT_CRT[] PROGMEM =
R"KEY(-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVANg4PGcN7LJGcMc1CMFFinYt+2h/MA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDEwMjIxNzM3
MTBaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDmW5ujwZBlvNtTG/2C
rKVd7a7krIVrT6p3p0SKYKwOZ5peGSUy6cASeo4K7HDeLXI6YKG4hQE2SepWgwx7
xyUPO2SU2pn306FUkZC+YN/2YlMur9MWQkozdq0a1383RTrUmZ1IL7zvPjg+6t+x
1G6RDx+ueIxkYpZtP6ieW710sk6n2O6DiQvxKJI1utzs6BTJ0bzHonbCSJUvCTYc
mQshk3cs2qTQ6+pnfFOnWsNRTE1dQqnkJHQikQrmIjSZtKzBKSLAV40B9S1oTzXD
NL6Y8pdZmrNUGN7DzffSE/fYl3Ow8jF4RSK99U8l1vpsBuZv/TlTtu4U4LKS9XMP
LVJJAgMBAAGjYDBeMB8GA1UdIwQYMBaAFC8KE2QXG/Rb2or0j/vwdzCdu+AeMB0G
A1UdDgQWBBRv1XmMBMKKV0e6f2cJZT8XdZ2KWzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEARx5lTGyPmoaoDAC3EHuNfniW
OyNtK31Y8kdljZeNVtmKQj7GLJNQszTLYJX6lcvLLUmFv8LuAQPc6GSJ5y8js4Gt
LioVuuWthFgGCTCx/7H7Tys3D4LYajQJoj8sNk0E029tR0yu6fJC/laXDghOv/4G
HVLUU2I3ljmIoGqUEuwlwYH1vE7IHGrt1s8vKmaRjgWIcBTUEszuHXLTKosocKFB
QBbepO5AeGkPW65ZzGi2x+qUkNYtMfUgWnBFZJe/5xGRd1NTeYb9UeQEJhQgFCek
hLU7xo1yl3dPR4Vtegl9ruWjETSGmMjeo9qCRBBE/f/99PeHP9ngswvKfHOuEQ==
-----END CERTIFICATE-----)KEY";

//PRIVADA.KEY
static const char AWS_CERT_PRIVATE[] PROGMEM = 
R"KEY(-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA5lubo8GQZbzbUxv9gqylXe2u5KyFa0+qd6dEimCsDmeaXhkl
MunAEnqOCuxw3i1yOmChuIUBNknqVoMMe8clDztklNqZ99OhVJGQvmDf9mJTLq/T
FkJKM3atGtd/N0U61JmdSC+87z44PurfsdRukQ8frniMZGKWbT+onlu9dLJOp9ju
g4kL8SiSNbrc7OgUydG8x6J2wkiVLwk2HJkLIZN3LNqk0OvqZ3xTp1rDUUxNXUKp
5CR0IpEK5iI0mbSswSkiwFeNAfUtaE81wzS+mPKXWZqzVBjew8330hP32JdzsPIx
eEUivfVPJdb6bAbmb/05U7buFOCykvVzDy1SSQIDAQABAoIBAD21RJg1fg0C7m3x
DZQ304S56yPu4z6/9JZhBIddJjolnsCeU8yzuXQ5yFs8w2+BFRx2TlwzpQN6AYBz
UqDF1DOkYWlOtfghhRI2fGPDZ7uE02uqRg2sbFwk6nJKUBXqQbw5+lwgDai5LjAM
kyf8FDJfrsj6GgG6NznE19K0GKhtqUnvdN0krljk0jSNrHJxyDyzaZfwGw+MGBkN
dt3WHAAaZXBLvtiM+XKlXuG0bxTZ//p/EU1+hD9u6B+6gZxOa3z8FQ821yWn0mbR
hAjWJL3uxUxQhu7f1a2UmHbeakXiPtLjaNp+6oQn9gW5+vDG+LCvs8mEozvBEN1G
HWPwDAECgYEA/u8QY+WH7R99Q8xFSF4mWKLQ+JHmb3yB+WQK2r0Mg/wJME9TrY9U
m4VGLePJKyZ8D3NErP4wIAOyqwuYLHy6VZ0fMTKoVCX/On4Ly6kiqC10cEINt2Hg
9qXE1r2bTjVOsKIDPcV5nw5haclSjVLTd3rh6Jk527DBYZa8b4ZeBOkCgYEA51I7
hdNaBOYJop30uE+OMUvfBQV5Bkk6vnstuFuRhG5qLJQiPxyOPPuK/fCMoAXRZXPz
bvqa4w2dsg6lTztdu9KtlMOygylRdtBPCdOyHZfUMnquW8mGDsSWE8oA103ToTY2
st5efDvC4FITnFyoecDH9U+vOP+PpXfGiT/wBmECgYADD7XfrTrzowQrE0Hlu5O0
Tsg5o+7jedhJuWTT+Z8z2ov1s44qsGTwtSoBlRGuXfjxao3xkd/cEo9LtIjwR9Mp
AgkE2zngQNCO0EKuAGr1IA6c5n4prJg5/gWeGorJ5qP6RQfK7xslyNNspMlD/zGg
5q3d0DE8rSO1W00J/dAVOQKBgCSpiNuOAt9x4icO5+FqYnv3rXIrSuIvKwtTlIx6
ntahdVx5YfAkw3pw17elr3QRV/2/Yd6+A1xnJQ46egLTwuho3LAOUDWvj8TIAS7q
iXldPfl+LjJH/2JJ0At04as+H4OWhxbUXZ9NDXbmK0uF+AHMByUfKwNapdaw5BuO
sakhAoGBAL0pr+HxVIMzhNB5Eb604eZ42YIRcE7aT4eJvtqifWd6K47PScxMVe/a
pteFLvYWYjcTIHYjq+uzlvGM8Jmt1aLgvbMu+1e8vEjjwuF3jiHmPzm4e5qBJqtX
ZEPk5lN5NJN9EsBA8ZaLMK5H8BlsJg3MjQoJLI9gPCFZUx1I2mQC
-----END RSA PRIVATE KEY-----)KEY";
