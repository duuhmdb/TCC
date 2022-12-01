//Motor esquerdo
int IN1 = 9;
int IN2 = 8;
int MotorEsquerdo = 10;

//Motor direito
int IN3 = 6;
int IN4 = 7;
int MotorDireito = 5;

//Sensores
int sensorEsquerdo = A3;
int sensorEsquerdoCentral = A2;
int sensorDireitoCentral = A1;
int sensorDireito = A0;

//Velocidade
int velocidadeZero = 0;
int velocidadeMedia = 180;
int velocidadeAlta = 220;
  
//Tempo da volta na pista(Mili)
long tempoAtual = 0;
long tempoDaVolta = 22000;

//Taxa de leitura
int linha = 250;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(MotorEsquerdo, OUTPUT);
  pinMode(MotorDireito, OUTPUT);
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorEsquerdoCentral, INPUT);
  pinMode(sensorDireitoCentral, INPUT);
  pinMode(sensorDireito, INPUT);
  delay(5000);
}

void loop() {
  if (tempoAtual <= tempoDaVolta) {
    int taxaLeituraSensorEsquerdo = analogRead(sensorEsquerdo); //Obtem a leitura do sensor direito
    int taxaLeituraSensorEsquerdoCentral = analogRead(sensorEsquerdoCentral);  //Obtem a leitura do sensor central
    int taxaLeituraSensorDireitoCentral = analogRead(sensorDireitoCentral);  //Obtem a leitura do sensor esquerdo
    int taxaLeituraSensorDireito = analogRead(sensorDireito);  //Obtem a leitura do sensor esquerdo

    //Seta as rodas sentido Frente
    RotacionarFrente();

    Run(taxaLeituraSensorEsquerdo, taxaLeituraSensorEsquerdoCentral, taxaLeituraSensorDireitoCentral, taxaLeituraSensorDireito);

    tempoAtual = millis();
  }
  else {
    Parar();
    exit(0);
  }
}

void Run(int taxaLeituraSensorEsquerdo, int taxaLeituraSensorEsquerdoCentral, int taxaLeituraSensorDireitoCentral, int taxaLeituraSensorDireito)
{

  if (taxaLeituraSensorEsquerdo < linha &&
      (taxaLeituraSensorEsquerdoCentral > linha || taxaLeituraSensorEsquerdoCentral < linha) &&
      (taxaLeituraSensorDireitoCentral > linha || taxaLeituraSensorDireitoCentral < linha) &&
      taxaLeituraSensorDireito > linha)
  {
    //Faz a curva para esquerda
    CurvaEsquerdaFechada();
  }
  else if (taxaLeituraSensorEsquerdo > linha &&
           (taxaLeituraSensorEsquerdoCentral > linha || taxaLeituraSensorEsquerdoCentral < linha) &&
           (taxaLeituraSensorDireitoCentral > linha || taxaLeituraSensorDireitoCentral < linha) &&
           taxaLeituraSensorDireito < linha)
  {
    //Faz a curva para esquerda
    CurvaDireitaFechada();
  }
  else if (taxaLeituraSensorEsquerdo > linha &&
           taxaLeituraSensorEsquerdoCentral > linha &&
           taxaLeituraSensorDireitoCentral < linha &&
           taxaLeituraSensorDireito > linha)
  {
      FrenteAjustarParaDireita();
  }
  else if (taxaLeituraSensorEsquerdo > linha &&
           taxaLeituraSensorEsquerdoCentral < linha &&
           taxaLeituraSensorDireitoCentral > linha &&
           taxaLeituraSensorDireito > linha)
  {
      FrenteAjustarParaEsquerda();
  }
  else if ((taxaLeituraSensorEsquerdo < linha &&
            taxaLeituraSensorEsquerdoCentral < linha &&
            taxaLeituraSensorDireitoCentral < linha &&
            taxaLeituraSensorDireito < linha) || (taxaLeituraSensorEsquerdoCentral < linha && taxaLeituraSensorDireitoCentral < linha))
  {
    Frente();
  }
}

//Rotação da roda para frente
void RotacionarFrente() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Frente() {
  analogWrite(MotorEsquerdo, velocidadeAlta);
  analogWrite(MotorDireito, velocidadeAlta);
}

void FrenteAjustarParaEsquerda() {
  analogWrite(MotorEsquerdo, velocidadeAlta - 40);
  analogWrite(MotorDireito, velocidadeAlta);
}

void FrenteAjustarParaDireita() {
  analogWrite(MotorEsquerdo, velocidadeAlta);
  analogWrite(MotorDireito, velocidadeAlta - 40);
}

void CurvaEsquerdaFechada() {
  analogWrite(MotorEsquerdo, velocidadeZero);
  analogWrite(MotorDireito, velocidadeAlta);
}

void CurvaDireitaFechada() {
  analogWrite(MotorEsquerdo, velocidadeAlta);
  analogWrite(MotorDireito, velocidadeZero);
}

void Parar() {
  analogWrite(MotorEsquerdo, velocidadeZero);
  analogWrite(MotorDireito, velocidadeZero);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
