#include <ESP8266WiFi.h>

const char* nomeRede = "LIVE TIM_FFC6_2G";
const char* senhaRede = "33tcj8p3dr";

WiFiServer servidorEmbarcado(80);

void setup() {
  Serial.begin(9600);
  analogWrite(D1, 0);
  analogWrite(D2, 0);
  analogWrite(D3, 0);

  WiFi.begin(nomeRede, senhaRede);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado, IP: ");
  Serial.println(WiFi.localIP());

  servidorEmbarcado.begin();
}

void loop() {
  WiFiClient cliente = servidorEmbarcado.available();

  if(cliente) {
    String req = cliente.readStringUntil('\r');
    Serial.println(req);

    cliente.println("HTTP/1.1 200 OK");
    cliente.println("Content-type: text/html");
    cliente.println("Connection: close");
    cliente.println();

    if(req.indexOf("/dim") >= 0) {
      /*    GET /dim1=230- HTTP/1.1     */
      String dimmer = req.substring(req.indexOf("/") + 1, req.indexOf("="));
      String valor = req.substring(req.indexOf("=") + 1, req.indexOf("-"));

      // Serial.println("Dimmer {" + dimmer + "}");
      // Serial.println("Valor {" + valor + "}");

      if(dimmer == "dim1") {
        analogWrite(D1, valor.toInt());
        // Serial.println("Vai alterar o pino 1");
      } else if(dimmer == "dim2") {
        analogWrite(D2, valor.toInt());
        // Serial.println("Vai alterar o pino 2");
      } else if(dimmer == "dim3") {
        analogWrite(D3, valor.toInt());
        // Serial.println("Vai alterar o pino 3");
      }
    }

  }
}
