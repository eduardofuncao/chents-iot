
![svgviewer-png-output](https://github.com/user-attachments/assets/ba33daa8-328e-4046-a94a-7ac4edfca4f3)
# Sistema de Monitoramento de Enchentes

## Visão Geral

O Chents é um sistema de monitoramento de enchentes desenvolvido com o microcontrolador ESP32. O sistema é capaz de monitorar o nível da água, temperatura, umidade e condições de iluminação do ambiente, enviando alertas quando os níveis de água ultrapassam um limite predefinido.

## Funcionalidades

- 📊 Monitoramento em tempo real do nível da água
- 🌡️ Leitura de temperatura e umidade através do sensor DHT22
- 💡 Detecção de condições de iluminação (dia/noite) usando um sensor LDR
- ⚠️ Sistema de alerta com LED e buzzer quando o nível da água excede o limite
- 📱 Integração com a plataforma Thinger.io para visualização e controle remoto
- 📈 Dashboard customizável para acompanhamento dos dados

## Componentes de Hardware

- ESP32 (Microcontrolador)
- Sensor de nível de água (Analógico)
- Sensor DHT22 (Temperatura e Umidade)
- LED (Indicador visual de alerta)
- Buzzer (Alerta sonoro)
- Sensor LDR (Fotoresistor para detecção de luminosidade)

## Estrutura do Projeto

```
chents-iot/
├── main.ino              # Código principal do ESP32
├── diagram.json          # Conexões dos componentes de hardware
├── libraries.txt         # Lista de bibliotecas necessárias
```



## Instalação e Configuração
Obs. Caso esteja utilizando Wokwi para simulação, basta copiar os arquivos .ino e .json nos locais designados, instalar as bibliotecas necessárias e compilar o projeto.

### Bibliotecas:
  - DHT sensor library
  - ThingerCore32
  - thinger.io
  - WiFi.h

### 1. Configuração do Hardware

![diagrama wokwi](https://github.com/user-attachments/assets/c641c348-d98c-4513-8757-7ae7d872772b)
Monte o circuito conforme as seguintes conexões:
- Sensor de nível de água → Pino 34 (analógico)
- Sensor DHT22 → Pino 15 (digital)
- LED → Pino 4 (digital)
- Buzzer → Pino 2 (digital)
- Sensor LDR → Pino 35 (analógico)

### 2. Configuração do Software

1. Clone o repositório:
   ```bash
   git clone https://github.com/eduardofuncao/chents-iot.git
   cd chents-iot
   ```

2. Abra o arquivo `main.ino` na Arduino IDE.

3. Instale as bibliotecas necessárias:
   - No menu, acesse `Sketch > Incluir Biblioteca > Gerenciar Bibliotecas...`
   - Instale as bibliotecas listadas em `libraries.txt`.

4. Configure suas credenciais:
   - Altere as constantes de WiFi no arquivo `main.ino`:
     ```cpp
     thing.add_wifi("SEU_SSID", "SUA_SENHA");
     ```
   - Atualize suas credenciais do Thinger.io:
     ```cpp
     #define USERNAME "seu_usuario"
     #define DEVICE_ID "seu_device_id"
     #define DEVICE_CREDENTIAL "sua_credencial"
     ```

6. Compile e faça o upload do código para o ESP32.

### 3. Configuração da Plataforma Thinger.io

1. Adicione um novo dispositivo com o mesmo DEVICE_ID configurado no código.
2. Configure o dashboard para visualizar os dados:
   - Adicione widgets para temperatura, umidade, nível de água e status de alerta.
   - Configure um botão para controlar o buzzer remotamente.

## Uso

Após a instalação e configuração, o sistema irá:

1. Inicializar todos os sensores e estabelecer conexão com o WiFi.
2. Começar a monitorar os parâmetros ambientais a cada 2 segundos.
3. Enviar dados para a plataforma Thinger.io.
4. Ativar o LED quando o nível da água ultrapassar o limite configurado.
5. Permitir o controle remoto do buzzer através da plataforma Thinger.io.

O dashboard no Thinger.io pode ser utilizado para:

![dashboard](https://github.com/user-attachments/assets/66461c7e-83e3-4e63-9868-2cd82ff57e92)

- Visualizar os dados em tempo real
- Verificar o histórico de leituras
- Controlar o buzzer remotamente
- Configurar notificações adicionais

## Fluxo de Dados

O sistema funciona com o seguinte fluxo:

1. Os sensores coletam dados (nível de água, temperatura, umidade, luminosidade).
2. O ESP32 processa esses dados e verifica se o nível da água excede o threshold.
3. Se o nível for excedido, o LED é ativado e o status de alerta é atualizado.
4. Todos os dados são enviados para a plataforma Thinger.io através da Internet.
5. O usuário pode visualizar os dados e controlar o buzzer através do dashboard.

## Personalização

### Ajustando Thresholds

Para ajustar a sensibilidade do sistema:

1. Modifique o valor de `WATER_LEVEL_THRESHOLD` no código para adequar à sensibilidade do seu sensor de nível de água
2. Ajuste o valor de `LDR_NIGHT_THRESHOLD` conforme as condições de iluminação do ambiente de instalação

## Contato
    Eduardo Função - RM553362
    Artur Fiorindo - RM553481
    Jhoe Hashimoto - RM553831


Link do projeto: [https://github.com/eduardofuncao/chents-iot](https://github.com/eduardofuncao/chents-iot)
