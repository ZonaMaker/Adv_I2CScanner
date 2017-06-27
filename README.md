# Adv_I2CScanner
Advanced I2CScanner sketch for Arduino (Ainda em desenvolvimento)

## Uso:
  - **`s - Escanear por dispositivos I2C`**
      - Faz uma busca por todos os dispositivos que estejam conectados ao barramento I2C utilizando endereçamento de 7-bit e armazenando os endereços válidos para uso futuro.
      
      
  - **`l - Listar todos dispositivos encotrados no último escaneamento`**
    - Retorna uma lista com todos os dispositivos encontrados no último escaneamento, caso seja necesário.
    
    
  - **`o - Requisitar dados de um dispositivo (limitado a conexão entre Arduinos)`**
    - Quando usando a comunicação entre Arduinos é possível testar sem carregar outro código, basta entrar com o comando `o` e escolher o dispositivo na lista para ele requistar os dados.
    
    
  - **`e - Habilitar ou desabilitar função echo`**
    - A função echo repete a entrada do usuário no terminal serial

