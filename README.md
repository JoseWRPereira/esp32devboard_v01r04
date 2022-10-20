# Procedimento de instalação : ESP-IDF
O procedimento para instalação pode ser encontrado na 
[Documentação](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html)
fornecida pela Espressif.

## Passo 1: Instalação no Linux - Debian-based
```bash
# Instalação de dependências
sudo apt-get install git wget flex bison gperf python3 python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```

## Passo 2: Obtendo ESP-IDF

```bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```
## Passo 3: Instalando a ferramenta
```bash
cd ~/esp/esp-idf
./install.sh esp32
```

## Passo 4: Carregando o ambiente de desenvolvimento
```bash
# Incluindo alias (pseudônimo) para a exportação do ambiente de desenvolvimento
echo "alias get_idf='. $HOME/esp/esp-idf/export.sh'" >> ~/.bashrc

# Recarregando as definições do bashrc para permitir a chamada local do alias
source ~/.bashrc
```


# Criando um projeto com ESP-IDF

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