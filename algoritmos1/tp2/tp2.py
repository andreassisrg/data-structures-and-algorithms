def main():
    # Número de pilhas
    n = int(input())

    # Coletando o número de blocos de cada nível (B_i)
    blocks = input().split(" ")
    blocks = [int(i) for i in blocks]

    # Número de árvores
    z = int(input())

    # Coordenada das árvores
    tree_coordinates = list()
    for i in range(int(z)):
        z_x, z_y = input().split(" ")
        z_x, z_y = int(z_x), int(z_y)

        tree_coordinates.append((z_x, z_y))

    # Solving part 1:
    height = 0
    for i in range(1, n + 1):
        if blocks[i - 1] < i:
            break
            
        height += 1

    print(f'Parte 1: {height}')

    # Solving part 2:


    return

if __name__ == '__main__':
    main()

'''

'''