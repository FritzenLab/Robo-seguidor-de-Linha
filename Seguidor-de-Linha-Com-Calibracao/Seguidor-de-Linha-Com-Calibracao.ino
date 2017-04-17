/* 
 *  Robô seguidor de linha com Arduino UNO (Fritzen UM) 
 *  - Controle ON-OFF dos dois motores CC  
 *  - Utilizando apenas um sensor infravermelho (segue sempre á esquerda da linha)
 *  
 *  Desenvolvido por Clóvis Fritzen em 16/04/2017, para o 
 *  blog FritzenLab .. http://FritzenLab.com.br
 *  
 *  Baseado no código "Controle 2 motores DC usando Ponte H L298N" 
do autor FILIPEFLOP

*/

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 3;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int valorReceptor = 0; 

long tempoAjustado = 100;
long tempoinicial = 0;
long tempoPassado = 0;
long meioDasLeituras = 0;
int leituraMaxima = 0;
int leituraMinima = 1023;
int leituraCalibracao = 0;


#define emissor 2 // LED infravermelho
#define led13 13 // LED vermelho pino 13 do Arduino
#define receptor A0 // Fotodiodo ou fototransistor receptor infravermelho

  
void setup()
{
  //Define os pinos como saida
 pinMode(emissor, OUTPUT);
 pinMode(led13, OUTPUT);
 digitalWrite(emissor, LOW);

 
delay(3000);  
// Calibracao:
analogWrite(IN1, 0); // LEFT wheel going front
analogWrite(IN2, 125);
tempoinicial = millis();
tempoAjustado = millis() + 100;

while ((tempoAjustado - tempoPassado) > 0.00) {

  leituraCalibracao= analogRead(receptor);
  if (leituraCalibracao >= leituraMaxima){
    leituraMaxima = leituraCalibracao;
  } 
  if (leituraCalibracao < leituraMinima){
    leituraMinima = leituraCalibracao;
  }
  

  tempoPassado = millis() - tempoinicial;
}

meioDasLeituras = (leituraMaxima + leituraMinima)/2;
tempoPassado = millis() - tempoinicial;
analogWrite(IN1, 125); // LEFT wheel going front
analogWrite(IN2, 0);
delay(tempoPassado);

analogWrite(IN1, 125);
analogWrite(IN2, 125);

 
}
  
void loop()
{

 valorReceptor = analogRead(receptor);

 if (valorReceptor <= meioDasLeituras){
  analogWrite(IN1, 125); // LEFT wheel going front
  analogWrite(IN2, 125);
  
  analogWrite(IN3,125); // RIGHT wheel stopped
  analogWrite(IN4, 0);
 } else {
    analogWrite(IN1, 0); // LEFT wheel going front
    analogWrite(IN2, 125);
    analogWrite(IN3, 125); // RIGHT wheel stopped
    analogWrite(IN4, 125);
 }
  
}
