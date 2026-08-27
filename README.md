
# FastBoot

> Um mod AML para **GTA: SA Android** que reduz drasticamente o tempo entre iniciar o jogo e realmente começar a jogar.

FastBoot é a terceira geração deste projeto, desenvolvido para assumir controle total da sequência de inicialização do jogo — pulando telas desnecessárias e entrando direto em um jogo novo, no menu de carregar jogo, ou no seu save mais recente.

---

## Recursos

- Pula a tela do Social Club
- Comportamento de inicialização configurável
- Resolução automática de slots de salvamento
- Retoma instantaneamente o último save válido
- Inicia um novo jogo automaticamente
- Abre o menu Carregar Jogo automaticamente
- Leve, sem dependências

---

## Requisitos

- [GTA: SA Android (AML)](https://discord.gg/aml-android-mod-loader-877187821511794730)

---

## Instalação

1. Copie `libFastBoot.so` para o diretório de mods do AML.
2. Configure o FastBoot através do arquivo de configuração gerado.
3. Inicie o jogo.

---

## Configuração

O FastBoot gera um arquivo de configuração no primeiro lançamento:

```
net.deviceblack.fastboot.ini
```

Exemplo:

```ini
[Preferences]

; Ignora a tela do Social Club.
Remove Social Club = 1

; Comportamento de inicialização.
Start Mode = auto

; Slots de salvamento verificados da esquerda para a direita.
Slot List = GTASAsf9.b GTASAsf10.b
```

---

## Modos de Inicialização

O FastBoot suporta múltiplos modos de inicialização via a chave `Start Mode`.

| Mode | Comportamento |
|------|---------------|
| `none` | Desativa toda automação de inicialização. |
| `newgame` | Inicia um novo jogo automaticamente. |
| `loadgame` | Abre automaticamente o **menu Carregar Jogo**. |
| `loadslot` | Carrega o primeiro slot de salvamento válido encontrado na lista de slots configurada. |
| `auto` | Tenta retomar um save válido. Se nenhum for encontrado, inicia um novo jogo. |
| `auto2` | Tenta retomar um save válido. Se nenhum for encontrado, abre o menu Carregar Jogo. |

---

## Resolução de Slots de Salvamento

O FastBoot avalia os slots de salvamento configurados **da esquerda para a direita**. O primeiro slot válido encontrado determina a ação a ser executada.

```ini
Slot List = GTASAsf9.b GTASAsf10.b
Slot List = GTASAsf1.b GTASAsf5.b GTASAsf10.b
```

---

## Histórico de Versões

| Geração | Nome |
|---------|------|
| 1ª | SCAndSkip |
| 2ª | SmartBoot |
| 3ª | **FastBoot** |

---

## Licença

Este projeto é fornecido **como está** para fins educacionais e de modding.

Use por sua própria responsabilidade.
```

— GitHub Copilot Chat Assistant