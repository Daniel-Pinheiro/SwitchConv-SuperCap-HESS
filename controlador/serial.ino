#define showMeasures
#define showVref

void loop() /*Rotina executada várias vezes*/
{
    while (Serial.available()) //Verifica se existe algum caractere não-lida
    {                          // no buffer da porta serial USB
      Vref = (Serial.parseInt()*1022)>>4; /*Lê sequência de chars numéricos e converte p/ int
      Serial.read();  /*Limpa último caractere nulo do buffer*/
    }
    delay(80);  /*Força intervalos regulares >80ms*/
    #ifdef showVref    
    Serial.print("Vref,");
    #endif
    #ifdef showMeasures
    Serial.println("Volt,Iboost");  /*Envia identificadores para gráfico*/
    #endif
    #ifdef showVref    
    Serial.print(Vref/63.88); /*Mostra Vref atual*/
    Serial.print(",");
    #endif
    #ifdef showMeasures
    Serial.print(Volt/63.88);     /*Tensão do barramento, de int p/ volts*/
    Serial.print(",");
    Serial.println(Iboost/37.88); /*Corrente do módulo SC, de int p/ ampères*/
    #endif
}
