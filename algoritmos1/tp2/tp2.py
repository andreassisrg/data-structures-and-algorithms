import sys
from math import sqrt

def parte1_triangulo_dp(n, blocos):
    """
    Parte 1: Encontrar a altura máxima de um triângulo isósceles
    Estratégia Gulosa O(N)
    """
    if n == 0:
        return 0

    # esq[i] = max altura da "pirâmide" da esquerda terminando em i
    esq = [0] * n
    esq[0] = 1 # A pirâmide em i=0 tem altura 1 (se b[0] >= 1)
    for i in range(1, n):
        # A altura é limitada pela pilha atual (blocos[i])
        # ou pela altura anterior + 1
        esq[i] = min(blocos[i], esq[i-1] + 1)

    # dir[i] = max altura da "pirâmide" da direita começando em i
    dir = [0] * n
    dir[n-1] = 1 # A pirâmide em i=n-1 tem altura 1
    for i in range(n - 2, -1, -1):
        # A altura é limitada pela pilha atual (blocos[i])
        # ou pela altura seguinte + 1
        dir[i] = min(blocos[i], dir[i+1] + 1)

    # A altura max é o max(min(esq[i], dir[i])) para todo i
    max_altura = 0
    for i in range(n):
        h = min(esq[i], dir[i])
        if h > max_altura:
            max_altura = h
            
    return max_altura

def distancia(p1, p2):
    # Calcula a distância euclidiana entre dois pontos
    return sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def perimetro_triangulo(p1, p2, p3):
    # Calcula o perímetro de um triângulo dados 3 pontos
    return distancia(p1, p2) + distancia(p2, p3) + distancia(p1, p3)

def pontos_colineares(p1, p2, p3):
    # Verifica se três pontos são colineares usando produto vetorial
    area = abs((p2[0] - p1[0]) * (p3[1] - p1[1]) - (p3[0] - p1[0]) * (p2[1] - p1[1]))
    return area < 1e-9

def forca_bruta_triangulo(arvores):
    """ Força bruta para encontrar o menor perímetro Otimizado para evitar cálculos desnecessários """
    z = len(arvores)
    menor_perimetro = float('inf')
    melhor_trio = (0, 1, 2)

    for i in range(z):
        for j in range(i + 1, z):
            d_ij = distancia(arvores[i], arvores[j])
            
            # Poda: se já temos 2 lados >= menor_perimetro, skip
            if d_ij >= menor_perimetro:
                continue
                
            for k in range(j + 1, z):
                # Verificar se não são colineares
                if pontos_colineares(arvores[i], arvores[j], arvores[k]):
                    continue
                
                d_ik = distancia(arvores[i], arvores[k])
                if d_ij + d_ik >= menor_perimetro:
                    continue
                    
                d_jk = distancia(arvores[j], arvores[k])
                perimetro = d_ij + d_ik + d_jk
                
                if perimetro < menor_perimetro:
                    menor_perimetro = perimetro
                    melhor_trio = (i, j, k)

    return menor_perimetro, melhor_trio

def verificar_faixa(faixa, melhor_perim):
    """ Verifica triângulos que podem cruzar a linha divisória """
    if len(faixa) < 3:
        return float('inf'), (0, 0, 0)

    # Ordenar por y para otimizar busca
    faixa_y = sorted(faixa, key=lambda x: x[1][1])

    menor = melhor_perim
    melhor = (0, 0, 0)

    n_faixa = len(faixa_y)

    # Janela deslizante otimizada
    for i in range(n_faixa):
        for j in range(i + 1, min(i + 30, n_faixa)):  # Limitar busca
            if faixa_y[j][1][1] - faixa_y[i][1][1] >= menor:
                break
                
            d_ij = distancia(faixa_y[i][1], faixa_y[j][1])
            if d_ij >= menor:
                continue
                
            for k in range(j + 1, min(j + 30, n_faixa)):
                if faixa_y[k][1][1] - faixa_y[i][1][1] >= menor:
                    break
                
                if pontos_colineares(faixa_y[i][1], faixa_y[j][1], faixa_y[k][1]):
                    continue
                
                perim = perimetro_triangulo(faixa_y[i][1], faixa_y[j][1], faixa_y[k][1])
                
                if perim < menor:
                    menor = perim
                    indices = sorted([faixa_y[i][0], faixa_y[j][0], faixa_y[k][0]])
                    melhor = tuple(indices)

    return menor, melhor

def dc_menor_triangulo(pontos_x):
    """ Divisão e Conquista para encontrar menor triângulo """
    n = len(pontos_x)

    # Caso base: usar força bruta
    if n <= 100:
        arvores_temp = [p[1] for p in pontos_x]
        indices_map = {i: pontos_x[i][0] for i in range(n)}
        perim, (i, j, k) = forca_bruta_triangulo(arvores_temp)
        return perim, (indices_map[i], indices_map[j], indices_map[k])

    # Dividir
    meio = n // 2
    x_meio = pontos_x[meio][1][0]

    esquerda = pontos_x[:meio]
    direita = pontos_x[meio:]

    # Conquistar
    perim_esq, trio_esq = dc_menor_triangulo(esquerda)
    perim_dir, trio_dir = dc_menor_triangulo(direita)

    # Melhor até agora
    if perim_esq < perim_dir:
        menor_perim = perim_esq
        melhor_trio = trio_esq
    else:
        menor_perim = perim_dir
        melhor_trio = trio_dir

    # Verificar triângulos que cruzam a divisão
    # Pontos na faixa delta ao redor da linha divisória
    delta = menor_perim / 2  # Otimização: só precisamos verificar pontos próximos

    faixa = [p for p in pontos_x if abs(p[1][0] - x_meio) < delta]

    # Verificar combinações na faixa
    perim_faixa, trio_faixa = verificar_faixa(faixa, menor_perim)

    if perim_faixa < menor_perim:
        return perim_faixa, trio_faixa
    else:
        return menor_perim, melhor_trio

def parte2_menor_perimetro_dividir_conquistar(arvores):
    """
    Parte 2: Encontrar o triângulo com menor perímetro usando Divisão e Conquista
    Estratégia: Algoritmo baseado em divisão e conquista similar ao algoritmo de par de pontos mais próximo
    """
    z = len(arvores)

    # Caso base pequeno: força bruta otimizada
    if z <= 100:
        return forca_bruta_triangulo(arvores)

    # Ordenar pontos por x para divisão e conquista
    pontos_x = sorted(enumerate(arvores), key=lambda x: (x[1][0], x[1][1]))

    # Dividir e conquistar
    return dc_menor_triangulo(pontos_x)

def main():
    # Leitura da entrada usando stdin
    linhas = []
    for linha in sys.stdin:
        linhas.append(linha.strip())
    
    idx = 0

    # Parte 1
    n = int(linhas[idx])
    idx += 1

    blocos = list(map(int, linhas[idx].split()))
    idx += 1

    altura_max = parte1_triangulo_dp(n, blocos)
    print(f"Parte 1: {altura_max}")

    # Parte 2
    z = int(linhas[idx])
    idx += 1

    arvores = []
    for i in range(z):
        x, y = map(int, linhas[idx].split())
        arvores.append((x, y))
        idx += 1

    perimetro, (a1, a2, a3) = parte2_menor_perimetro_dividir_conquistar(arvores)

    # Ajustar índices para 1-based e ordenar
    indices = sorted([a1 + 1, a2 + 1, a3 + 1])

    print(f"Parte 2: {perimetro:.4f} {indices[0]} {indices[1]} {indices[2]}")


if __name__ == "__main__":
    main()