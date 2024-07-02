#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_MMA8452Q.h>

#define LED_PIN A0           // Define o pino de saída para a tira de LEDs
#define LED_COUNT 30         // Define o número de LEDs na tira
#define MMA8452_ADDRESS 0x1D // Endereço I2C do sensor MMA8452

// Cria uma instância da tira de LEDs NeoPixel
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Cria uma instância do sensor MMA8452
MMA8452Q accelerometer;

// Inicializa as variáveis para armazenar o lado atual e o lado anterior
int currentSide = 0;
int timing = 0;
int roundCount = 0;

void setup()
{
    Wire.begin();              // Iniciar I2C
    Serial.begin(9600);        // Iniciar a comunicação serial
    strip.begin();             // Inicia a tira de LEDs
    strip.show();              // Atualiza a tira de LEDs
    randomSeed(analogRead(5)); // Trocar a SEED random

    // Inicia o sensor
    if (accelerometer.begin(Wire, MMA8452_ADDRESS))
    {
        Serial.println("MMA8452 found!");
    }
    else
    {
        Serial.println("No MMA8452 found. Check connections, and try again.");
        while (1)
            ;
    }

    // Escolhe um lado para acender
    currentSide = random(1, 7);

    timing = 1100; // Inicializa o tempo de espera em 1 segundo
    roundCount = 0;

    // Acende os LEDs correspondentes ao currentSide
    for (int i = (currentSide - 1) * 5; i < currentSide * 5; i++)
    {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }

    // Atualiza a tira de LEDs
    strip.show();

    // Imprime o lado inicial do LED
    Serial.print("Lado inicial do LED aceso: ");
    Serial.println(currentSide);
}
void loop()
{
    // Atualiza as leituras do sensor
    if (accelerometer.available())
    {
        accelerometer.read();

        // Obtém os ângulos de inclinação nos eixos X, Y e Z
        float angleX = accelerometer.cx;
        float angleY = accelerometer.cy;
        float angleZ = accelerometer.cz;

        // Determina qual lado está para cima com base nos ângulos de inclinação
        int upSide;
        if (angleX > 0.7)
        {
            upSide = 2;
        }
        else if (angleX < -0.7)
        {
            upSide = 1;
        }
        else if (angleY > 0.7)
        {
            upSide = 6;
        }
        else if (angleY < -0.7)
        {
            upSide = 4;
        }
        else if (angleZ > 0.7)
        {
            upSide = 3;
        }
        else if (angleZ < -0.7)
        {
            upSide = 5;
        }

        // Se o lado para cima é o mesmo que o lado atual (o lado aceso)
        if (upSide == currentSide)
        {
            // Apaga todos os LEDs
            for (int i = 0; i < strip.numPixels(); i++)
            {
                strip.setPixelColor(i, strip.Color(0, 0, 0));
            }

            strip.show();

            // Escolhe um novo lado para acender
            currentSide = random(1, 7); // Gera um número aleatório entre 1 e 6

            // Acende os LEDs correspondentes ao novo lado
            for (int i = (currentSide - 1) * 5; i < currentSide * 5; i++)
            {
                strip.setPixelColor(i, strip.Color(255, 255, 255));
            }

            // Atualiza a tira de LEDs
            strip.show();

            if (timing > 500) // Verifica se o tempo de espera é maior que 500 ms (0,5 segundos)
            {
                if (roundCount % 5 == 0) // Cada 5 rodadas, diminui o tempo de espera em 100 ms
                {
                    timing = (timing - 100);
                }
            }
            roundCount++; // Incrementa o contador de rodadas
        }
        // debug
        // Serial.println("=================================================");
        // Serial.println("currentSide: ");
        // Serial.println(currentSide);
        // Serial.println("=================================================");
        // Serial.println("Upside: ");
        // Serial.println(upSide);
        // Serial.println("=================================================");
        // Serial.println("X: ");
        // Serial.println(angleX);
        // Serial.println("Y: ");
        // Serial.println(angleY);
        // Serial.println("Z: ");
        // Serial.println(angleZ);
        // Serial.println(roundCount);
        // Serial.println(timing);
        // Serial.println("=================================================");

        delay(timing); // Espera um tempo antes de verificar novamente
    }
}