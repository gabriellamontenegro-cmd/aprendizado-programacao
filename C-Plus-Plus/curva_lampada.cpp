/*
 * Projeto: Caracterização de Lâmpada Incandescente - Física Experimental III
 * Objetivo: Medir a curva V x I, calcular a Potência Dissipada e a 
 * Temperatura Estimada do Filamento.
 */

float Vcc = 5000.0;    // Tensão da fonte em mV
float V0 = 0;          // Tensão no ponto A0 (mV)
float V1 = 0;          // Tensão no ponto A1 (mV)
float VRc = 0;         // Tensão no resistor de carga (auxiliar)
float Vlamp = 0;       // Tensão na lâmpada
float I = 0;           // Corrente (mA)
float Rc = 4.7;        // Resistência auxiliar (Ohms)
float R0 = 1.0;        // Resistência da lâmpada à temperatura ambiente (Ohms)
float Rlamp = 0;       // Resistência calculada da lâmpada
float T0 = 295.0;      // Temperatura ambiente em Kelvin (22°C)
float Pote = 0;        // Potência (Watts)
float Tfil = 0;        // Temperatura do filamento (Kelvin)

int botao;

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(5, INPUT); // Pino do botão

    Serial.println("CLEARSHEET"); 
    Serial.println("CLEARDATA"); 
    Serial.println("LABEL,Corrente I (mA),Tensao V (mV),Potencia (W),Temp (K)"); 
}

void loop() {
    do {
        botao = digitalRead(5);
        delay(100);
    } while (botao != HIGH);

    if (botao == HIGH) {
        // Conversão Analógica -> mV
        V0 = (float(analogRead(A0)) / 1024.0) * Vcc;
        V1 = (float(analogRead(A1)) / 1024.0) * Vcc;

        // --- CÁLCULOS FÍSICOS ---
        
        // 1. Corrente no circuito série (I = VRc / Rc)
        VRc = V1 - V0;
        I = VRc / Rc; // Corrente em mA

        // 2. Tensão na lâmpada
        Vlamp = V0;

        // 3. Potência Dissipada (P = V * I) 
        // Dividimos por 1.000.000 porque V está em mV e I em mA (mV * mA = microWatts)
        Pote = (Vlamp * I) / 1000000.0; 

        // 4. Estimativa de Temperatura do Filamento
        // Baseado na relação R = V / I e na variação da resistividade do Tungstênio
        if (I > 0) {
            Rlamp = Vlamp / I;
            // Fórmula simplificada: T = T0 * (Rlamp/R0)^(1/1.2) para Tungstênio
            Tfil = T0 * pow((Rlamp / R0), 0.833); 
        }

        // Envio para o Excel
        Serial.print("DATA,");
        Serial.print(I, 2);
        Serial.print(",");
        Serial.print(Vlamp, 2);
        Serial.print(",");
        Serial.print(Pote, 4);
        Serial.print(",");
        Serial.println(Tfil, 2);
    }

    delay(500);
}
