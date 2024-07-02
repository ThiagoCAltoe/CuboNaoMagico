# Projeto de Dados de LED com Acelerômetro

Este projeto foi desenvolvido como um desafio da FACULDADE UCL no PROJETO INTERDISCIPLINAR. O objetivo era criar um jogo que pudesse ser facilmente higienizado, destinado a crianças hospitalizadas em situação de UTI, utilizando uma tira de LEDs NeoPixel e um sensor de aceleração MMA8452Q para criar um jogo interativo. O objetivo é virar o dispositivo de modo que o lado iluminado pelos LEDs fique voltado para cima, o que, por sua vez, acende outro lado aleatório. O jogo testa a capacidade do usuário de manipular o dispositivo com precisão para atender às demandas de orientação.

## Componentes

- Arduino UNO
- Tira de LEDs RGB endereçáveis
- Sensor de aceleração MMA8452Q (Acelerômetro)
- Resistores, cabos, bateria recarregável e módulo de carregamento por indução

## Funcionamento

O código inicia configurando a comunicação I2C para o sensor MMA8452Q e inicializa a tira de LEDs. Um lado do dado é escolhido aleatoriamente para ser iluminado. Quando o usuário ajusta o dispositivo para que o lado iluminado fique voltado para cima, outro lado é então escolhido aleatoriamente para ser iluminado, desafiando o usuário a continuar ajustando a posição do dispositivo.

## Configuração

1. Conecte a tira de LEDs ao pino definido como `LED_PIN`.
2. Ajuste o valor de `LED_COUNT` no código para corresponder ao número de LEDs na sua tira.
3. Conecte o sensor MMA8452Q ao Arduino usando conexões I2C.
4. Carregue o código no Arduino.

## Uso

Após a configuração, alimente o Arduino para iniciar o programa. O dispositivo iluminará um lado aleatoriamente. O usuário deve então virar o dispositivo para que o lado iluminado fique para cima. Quando isso é feito corretamente, outro lado será iluminado, desafiando o usuário a ajustar a posição do dispositivo novamente.

## Personalização

Você pode ajustar o número de LEDs (`LED_COUNT`), o pino de saída (`LED_PIN`), e o endereço I2C do sensor (`MMA8452_ADDRESS`) conforme necessário para o seu projeto específico.

## Contribuições

Todos que contribuíram para o desenvolvimento deste projeto:

- **Thiago Costa**;
- **Tales Mello**;
- **Gabriel Silva**;
- **Vicenzo Fernandes**;
- **Gustavo Motta**;

Contribuições para o projeto são bem-vindas. Sinta-se livre para clonar, modificar e enviar pull requests.

## Licença

Este projeto é distribuído sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
