Procedimento

```bash
# Criando o ambiente de desenvolvimento
get_idf

# Criando um projeto 
idf.py create-project -p . <nome do projeto>

# Definindo o dispositivo alvo
idf.py set-target esp32

# Acessando o menu de configuração
idf.py menuconfig
```

```bash
# Compilando o projeto
idf.py build

# Gravando o projeto
idf.py -p <port> flash


# Monitorando o projeto
idf.py -p <port> monitor

# Sair do monitoramento
# Ctrl+[ ou Ctrl+]

# Limpeza da compilação
idf.py fullclean
```