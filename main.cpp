#include "functions.h"
#include "sort.h"

int main()
{
    int sizeArray = 149; // Número primo
    int count = 0;
    int key;
    dados municipios[sizeArray];
    dados hashArray[sizeArray];
    char ans;
    // testar com a abertura do arquivo
    loadFile(municipios, "database.dat", sizeArray, count);
    gerarHash(municipios, hashArray, sizeArray);
    system("clear || cls");
    while ((ans = menu()) != 'S')
    {
        system("clear || cls");
        switch (ans)
        {
        case 'C':
            system("clear || cls");
            cadastrar(municipios, sizeArray);
            break;

        case 'L':
            getchar(); // Pega o enter de selecao
            listar(municipios, sizeArray);
            getchar(); // Espera outra tecla ser teclada
            break;

        case 'O':
            quickSort(municipios, 0, sizeArray - 1);
            getchar();
            cout << "Ordenado com sucesso!\n";
            getchar();
            break;

        case 'G':
            gerarHash(municipios, hashArray, sizeArray);
            listar(hashArray, sizeArray);
            getchar();
            getchar();
            break;

        case 'D':
            //gerarHash(municipios, hashArray, sizeArray);
            listar(hashArray, sizeArray);
            cout << "\nDigitando 0 cancela a exclusao";
            cout << "\nInforme o codigo(key) do cadastro que deseja excluir: ";
            cin >> key;
            deleta(hashArray, sizeArray, key);
            getchar();
            getchar();
            break;

        case 'E':
            getchar();
            cout << "Easter egg kkkk\n";
            cout << "\nOBRIGADO A TODOS!!!\n";
            getchar();
            getchar();
            exit(0);
            break;

        case 'A':
            int key;
            //gerarHash(municipios, hashArray, sizeArray);
            listar(hashArray, sizeArray);
            cout << "\nDigitar 0 cancela a atualizacao e volta!";
            cout << "\nInforme o codigo(key) do cadastro que deseja atualizar: ";
            cin >> key;
            system("clear || cls");
            if (key != 0 && key != -1)
                if (update(hashArray, sizeArray, key))
                {
                    system("clear || cls");
                    int pos = search(hashArray, sizeArray, key);
                    cout << "Atualizado com sucesso!!!\n";
                    listar(pos, hashArray);
                    getchar();
                    getchar();
                }
            break;

        case 'X':
            saveFile(municipios, "database.dat", sizeArray);
            saveFile(hashArray, "hashBase.dat", sizeArray);
            exit(0);

        default:
            getchar();
            cout << "Opcao invalida!\n";
            getchar();
            break;
        }

        system("clear || cls");

        saveFile(municipios, "database.dat", sizeArray);
        saveFile(hashArray, "hashBase.dat", sizeArray);
    }

    // Caso o cliente pressione S
    system("clear || cls");
    cout << "Abrindo o GHCI...\n";
    gerarBaseHaskell(hashArray, "dbHaskell", sizeArray);
    abrirGhci();
    getchar();
    getchar();

    return 0;
}
