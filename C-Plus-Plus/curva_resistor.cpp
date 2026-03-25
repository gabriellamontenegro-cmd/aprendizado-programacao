/*
 * Projeto: Caracterização de Elementos Passivos - Física Experimental III (USP)
 * Objetivo: Coleta automática de dados para curva característica (V x I) 
 * Integrando Arduino e Excel para análise de dados em tempo real.
 */

float Vcc = 5000;      // Tensão da fonte em mV
float V0 = 0;          // Tensão no ponto A0 (mV)
float V1 = 0;          // Tensão no ponto A1 (mV)
float VRa = 0;         // Diferença de potencial no resistor auxiliar
float Vel = 0;         // Tensão sobre o elemento de interesse
float I = 0;           // Corrente calculada (mA)
float Ra = 68.0;       // Resistência auxiliar em Ohms (medida com ohmímetro)

int botao;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    
    // Comandos para o software de integração com Excel (ex: PLX-DAQ)
    Serial.println("CLEARSHEET"); 
    Serial.println("CLEARDATA"); 
    Serial.println("LABEL,Corrente I (mA),Tensao Vel (mV)"); 
}

void loop() {
    // Aguarda o pressionamento do botão para iniciar a medida
    do {
        botao = digitalRead(5);
        delay(100);
    } while (botao != HIGH);

    if (botao == HIGH) {
        // Conversão dos valores analógicos para milivolts (mV)
        V0 = (float(analogRead(A0)) / 1024.0) * Vcc;
        V1 = (float(analogRead(A1)) / 1024.0) * Vcc;

        // --- CÁLCULOS FÍSICOS ---
        // A corrente I é a mesma no circuito série: I = VRa / Ra
        // VRa é a diferença de potencial sobre o resistor auxiliar (V1 - V0)
        VRa = V1 - V0; 
        I = (VRa / Ra); // I em mA (já que as tensões estão em mV)

        // Vel é a tensão sobre o elemento de interesse (conectado entre A0 e GND)
        Vel = V0;

        // Envio dos dados formatados para o Excel
        Serial.print("DATA,");
        Serial.print(I, 4); // Corrente com 4 casas decimais
        Serial.print(",");
        Serial.println(Vel, 2); // Tensão com 2 casas decimais
    }

    delay(500); // Intervalo de segurança entre medidas
}
