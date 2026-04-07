def busca_binaria_recursiva(lista, alvo, esquerda=0, direita=None):
    if direita is None:
        direita = len(lista) - 1

    if esquerda > direita:
        return -1

    meio = (esquerda + direita) // 2

    if lista[meio] == alvo:
        return meio
    elif lista[meio] < alvo:
        return busca_binaria_recursiva(lista, alvo, meio + 1, direita)
    else:
        return busca_binaria_recursiva(lista, alvo, esquerda, meio - 1)


alfabeto = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

palavra = input("Digite uma palavra: ")
palavra_minuscula = palavra.lower()

print("\nPosições das letras no alfabeto (usando busca binária):")
for letra in palavra_minuscula:
    if letra.isalpha():
        posicao = busca_binaria_recursiva(alfabeto, letra)
        if posicao != -1:
            print(f"'{letra}' está na posição {posicao} (índice) ou {posicao + 1}º lugar")
        else:
            print(f"'{letra}' não encontrada no alfabeto")
    else:
        print(f"'{letra}' não é uma letra")
