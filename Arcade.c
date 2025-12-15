#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

// Constantes para jogo do galo
#define TAM 3


// Constantes para cores

#define COR_RESET "\033[0m"
#define COR_CINZENTO "\033[90m"
#define COR_AZUL "\033[94m"
#define COR_VERDE "\033[92m"
#define COR_AMARELO "\033[93m"
#define COR_VERMELHO "\033[91m"
#define COR_ROSA "\033[95m"
#define COR_PRETO    "\033[30m"

// Constantes para campo minado
#define MINAS 5
#define COL 5
#define LIN 5

//Constantes para a batalha naval
#define BN_LIN 5
#define BN_COL 5
#define NAVIOS 3

int scoreX = 0;
int scoreO = 0;
// Protótipos das funções dos jogos
void jogo1();
void jogo2();
void jogo3();
void jogo4();
void jogo5();


// Protótipos do menu
void mostrarMenu();
int lerOpcao();

// Protótipos do Jogo do Galo
void inicializarTabuleiro(char tab[TAM][TAM]);
void mostrarTabuleiro(char tab[TAM][TAM]);
int jogada(char tab[TAM][TAM], char jogador);
int verificarVitoria(char tab[TAM][TAM], char jogador);
int verificarEmpate(char tab[TAM][TAM]);

// Protótipos do Campo Minado
void inicializarCampo(char campo[LIN][COL], char visivel[LIN][COL]);
void colocarMinas(char campo[LIN][COL]);
int contarMinasAdj(char campo[LIN][COL], int l, int c);
void mostrarCampo(char visivel[LIN][COL]);

// Protótipos do Jogo da Forca

//Propótipos da batalha naval
void inicializarBN(char mar[BN_LIN][BN_COL], char visivel[BN_LIN][BN_COL]);
void colocarNavios(char mar[BN_LIN][BN_COL]);
void mostrarBN(char visivel[BN_LIN][BN_COL]);


int main() {
    int opcao;

    printf("=== BEM-VINDO AO ARCADE ===\n\n");

    while (1) {
        mostrarMenu();
        opcao = lerOpcao();
        setlocale(LC_ALL, "Portuguese");
        switch (opcao) {
            case 1:
                printf("\nIniciando Jogo do Galo...\n");
                jogo1();
                break;
            case 2:
                printf("\nIniciando Campo Minado...\n");
                jogo2();
                break;
            case 3:
                printf("\nIniciando Forca...\n");
                jogo3();
                break;
            case 4:
                printf("\nIniciando Batalha Naval...\n");
                jogo4();
                break;
            case 5:
                printf("\nIniciando Roleta...\n");
                jogo5();
                break;
            case 6:
                printf("\nObrigado por jogar! Saindo...\n");
                exit(0);
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
        system("cls");
    }

    return 0;
}

// ---------------- MENU ----------------

void mostrarMenu() {
    setlocale(LC_ALL, "Portuguese");
    printf("======= MENU PRINCIPAL =======\n");
    printf("Jogo 1 - Galo\n");
    printf("Jogo 2 - Campo Minado\n");
    printf("Jogo 3 - Forca\n");
    printf("Jogo 4 - Batalha Naval\n");
    printf("Jogo 5 - Roleta\n");
    printf("Jogo 6 - Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção (1-6): ");
}

int lerOpcao() {
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

// ---------------- JOGO 1 – JOGO DO GALO ----------------

void jogo1() {
    char tabuleiro[TAM][TAM];
    char jogador = 'X';
    int fim = 0;

    printf("\n*** JOGO DO GALO ***\n");
    printf("SCORE ATUAL -> X: %d | O: %d\n\n" , scoreX, scoreO);

    inicializarTabuleiro(tabuleiro);

    while (!fim) {
        mostrarTabuleiro(tabuleiro);

        if (!jogada(tabuleiro, jogador))
            continue;

        if (verificarVitoria(tabuleiro, jogador)) {
            mostrarTabuleiro(tabuleiro);
            printf("Jogador %c venceu!\n", jogador);

            if (jogador == 'X')
                scoreX++;
            else
                scoreO++;

            printf("\nSCORE ATUALIZADO ->  X: %d | O: %d\n" , scoreX, scoreO);
            fim = 1;

        } else if (verificarEmpate(tabuleiro)) {
            mostrarTabuleiro(tabuleiro);
            printf("Empate!\n");
            printf("\nSCORE MANTÉM -> X: %d | O: %d\n", scoreX, scoreO);
            fim = 1;

        } else {
            jogador = (jogador == 'X') ? 'O' : 'X';
        }
    }
}


// ---------------- FUNÇÕES DO JOGO DO GALO ----------------

void inicializarTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = ' ';
}

void mostrarTabuleiro(char tab[TAM][TAM]) {
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tab[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("---+---+---\n");
    }
}

int jogada(char tab[TAM][TAM], char jogador) {
    int linha, coluna;

    printf("\nJogador %c - Linha (1-3): ", jogador);
    scanf("%d", &linha);
    printf("Jogador %c - Coluna (1-3): ", jogador);
    scanf("%d", &coluna);

    linha--;
    coluna--;

    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
        printf("Posição inválida!\n");
        return 0;
    }

    if (tab[linha][coluna] != ' ') {
        printf("Posição ocupada!\n");
        return 0;
    }

    tab[linha][coluna] = jogador;
    return 1;
}

int verificarVitoria(char tab[TAM][TAM], char jogador) {
    for (int i = 0; i < TAM; i++) {
        if (tab[i][0] == jogador && tab[i][1] == jogador && tab[i][2] == jogador)
            return 1;
        if (tab[0][i] == jogador && tab[1][i] == jogador && tab[2][i] == jogador)
            return 1;
    }

    if (tab[0][0] == jogador && tab[1][1] == jogador && tab[2][2] == jogador)
        return 1;
    if (tab[0][2] == jogador && tab[1][1] == jogador && tab[2][0] == jogador)
        return 1;

    return 0;
}

int verificarEmpate(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tab[i][j] == ' ')
                return 0;
    return 1;
}

// ---------------- JOGO 2 – CAMPO MINADO ----------------

void jogo2() {
    char campo[LIN][COL];
    char visivel[LIN][COL];
    int linha, coluna;
    int jogadas = 0;
    int fim = 0;

    printf("\n*** CAMPO MINADO ***\n");

    inicializarCampo(campo, visivel);
    colocarMinas(campo);

    while (!fim) {
        mostrarCampo(visivel);

        printf("\nEscolha uma linha (1-%d): ", LIN);
        scanf("%d", &linha);
        printf("Escolha uma coluna (1-%d): ", COL);
        scanf("%d", &coluna);

        linha--;
        coluna--;

        if (linha < 0 || linha >= LIN || coluna < 0 || coluna >= COL) {
            printf("Posição inválida!\n");
            continue;
        }

        if (visivel[linha][coluna] != '.') {
            printf("Posição já aberta!\n");
            continue;
        }

        if (campo[linha][coluna] == '*') {
            printf(COR_VERDE "\n🎉 PARABÉNS! Limpaste o campo!\n" COR_RESET);


            // Mostrar todas as minas
            for (int i = 0; i < LIN; i++)
                for (int j = 0; j < COL; j++)
                    if (campo[i][j] == '*')
                        visivel[i][j] = '*';

            mostrarCampo(visivel);
            fim = 1;
        } else {
            int minas = contarMinasAdj(campo, linha, coluna);
            visivel[linha][coluna] = minas + '0';
            jogadas++;

            if (jogadas == (LIN * COL - MINAS)) {
                printf(COR_VERDE "\n🎉 PARABÉNS! Limpaste o campo!\n" COR_RESET);

                mostrarCampo(visivel);
                fim = 1;
            }
        }
    }
}
void inicializarCampo(char campo[LIN][COL], char visivel[LIN][COL]) {
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            campo[i][j] = ' ';
            visivel[i][j] = '.';
        }
    }
}

void colocarMinas(char campo[LIN][COL]) {
    int colocadas = 0;
    int l, c;

    srand(time(NULL));

    while (colocadas < MINAS) {
        l = rand() % LIN;
        c = rand() % COL;

        if (campo[l][c] != '*') {
            campo[l][c] = '*';
            colocadas++;
        }
    }
}

int contarMinasAdj(char campo[LIN][COL], int l, int c) {
    int count = 0;

    for (int i = l - 1; i <= l + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if (i >= 0 && i < LIN && j >= 0 && j < COL) {
                if (campo[i][j] == '*')
                    count++;
            }
        }
    }

    return count;
}

void mostrarCampo(char visivel[LIN][COL]) {
    printf("\n   ");
    for (int j = 0; j < COL; j++)
        printf(COR_ROSA "%d " COR_RESET, j + 1);
    printf("\n");

    for (int i = 0; i < LIN; i++) {
        printf(COR_ROSA "%d  " COR_RESET, i + 1);

        for (int j = 0; j < COL; j++) {
            char c = visivel[i][j];

            if (c == '.') {
                printf(COR_CINZENTO". " COR_RESET);
            }
            else if (c == '*') {
                printf(COR_VERMELHO "* " COR_RESET);
            }
            else {
                // números
                switch (c) {
                    case '1':
                        printf(COR_AZUL "1 " COR_RESET);
                        break;
                    case '2':
                        printf(COR_VERDE "2 " COR_RESET);
                        break;
                    case '3':
                        printf(COR_AMARELO "3 " COR_RESET);
                        break;
                    default:
                        printf(COR_VERMELHO "%c " COR_RESET, c);
                }
            }
        }
        printf("\n");
    }
}




// ---------------- JOGO 3 – FORCA ----------------

void jogo3() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // ----- TEMAS -----
    const char *tecnologia[] = {
        "programacao", "computador", "algoritmo",
        "linguagem", "software", "hardware"
    };

    const char *animais[] = {
        "cachorro", "gato", "elefante",
        "girafa", "tigre", "coelho"
    };

    const char *paises[] = {
        "portugal", "brasil", "espanha",
        "franca", "alemanha", "italia"
    };

    int opcaoTema;
    const char **palavras;
    int total;

    printf("\n*** JOGO DA FORCA ***\n");
    printf("Escolhe um tema:\n");
    printf("1 - Tecnologia\n2 - Animais\n3 - Países\nOpção: ");
    scanf("%d", &opcaoTema);

    switch (opcaoTema) {
        case 1: palavras = tecnologia; total = sizeof(tecnologia)/sizeof(tecnologia[0]); break;
        case 2: palavras = animais; total = sizeof(animais)/sizeof(animais[0]); break;
        case 3: palavras = paises; total = sizeof(paises)/sizeof(paises[0]); break;
        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            printf("\nTema inválido! Usando Tecnologia.\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            palavras = tecnologia;
            total = sizeof(tecnologia)/sizeof(tecnologia[0]);
    }

    srand(time(NULL));
    const char *palavra = palavras[rand() % total];

    int tamanho = strlen(palavra);
    char progresso[tamanho + 1];
    char letra;
    int tentativas = 6, acertou, ganhou = 0;

    char usadas[26] = {0};
    int usadasCount = 0;

    for (int i = 0; i < tamanho; i++) progresso[i] = '_';
    progresso[tamanho] = '\0';

    while (tentativas > 0) {
        // Mostrar progresso
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
        printf("\nPalavra: ");
        for (int i = 0; i < tamanho; i++) printf("%c ", progresso[i]);

        // Letras usadas
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); // azul
        printf("\nLetras usadas: ");
        for (int i = 0; i < usadasCount; i++) printf("%c ", usadas[i]);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
        printf("\nTentativas restantes: %d", tentativas);
        printf("\nDigite uma letra: ");
        scanf(" %c", &letra);

        // Verifica repetição
        int repetida = 0;
        for (int i = 0; i < usadasCount; i++)
            if (usadas[i] == letra) repetida = 1;

        if (repetida) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); // amarelo
            printf("\nJá usaste essa letra!\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
            continue;
        }

        usadas[usadasCount++] = letra;
        acertou = 0;

        for (int i = 0; i < tamanho; i++)
            if (palavra[i] == letra && progresso[i] == '_') { progresso[i] = letra; acertou = 1; }

        if (!acertou) {
            tentativas--;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // vermelho
            printf("\nLetra errada!\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
        }

        // Verifica vitória
        ganhou = 1;
        for (int i = 0; i < tamanho; i++)
            if (progresso[i] == '_') { ganhou = 0; break; }

        if (ganhou) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // verde
            printf("\n\n PARABÉNS! A palavra era: %s\n", palavra);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
            return;
        }
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // vermelho
    printf("\n\n PERDESTE! A palavra era: %s\n", palavra);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // branco
}


// ---------------- JOGO 4 – BATALHA NAVAL ----------------

void jogo4() {
    char mar[BN_LIN][BN_COL];
    char visivel[BN_LIN][BN_COL];
    int linha, coluna;
    int naviosRestantes = NAVIOS;

    printf("\n*** BATALHA NAVAL ***\n");

    inicializarBN(mar, visivel);
    colocarNavios(mar);

    while (naviosRestantes > 0) {
        mostrarBN(visivel);

        printf("\nEscolha uma linha (1-%d): ", BN_LIN);
        scanf("%d", &linha);
        printf("Escolha uma coluna (1-%d): ", BN_COL);
        scanf("%d", &coluna);

        linha--;
        coluna--;

        if (linha < 0 || linha >= BN_LIN || coluna < 0 || coluna >= BN_COL) {
            printf("Posição inválida!\n");
            continue;
        }

        if (visivel[linha][coluna] != '~') {
            printf("Já disparaste aqui!\n");
            continue;
        }

        if (mar[linha][coluna] == 'N') {
            printf("ACERTOU NUM NAVIO!\n");
            visivel[linha][coluna] = 'O';
            naviosRestantes--;
        } else {
            printf("Água!\n");
            visivel[linha][coluna] = 'X';
        }
    }

    mostrarBN(visivel);
    printf("\nVITÓRIA! Destruíste todos os navios!\n");
}
void inicializarBN(char mar[BN_LIN][BN_COL], char visivel[BN_LIN][BN_COL]) {
    for (int i = 0; i < BN_LIN; i++) {
        for (int j = 0; j < BN_COL; j++) {
            mar[i][j] = '~';
            visivel[i][j] = '~';
        }
    }
}

void colocarNavios(char mar[BN_LIN][BN_COL]) {
    int colocados = 0;
    int l, c;

    srand(time(NULL));

    while (colocados < NAVIOS) {
        l = rand() % BN_LIN;
        c = rand() % BN_COL;

        if (mar[l][c] != 'N') {
            mar[l][c] = 'N';
            colocados++;
        }
    }
}

void mostrarBN(char visivel[BN_LIN][BN_COL]) {
    printf("\n   ");
    for (int j = 0; j < BN_COL; j++)
        printf("%d ", j + 1);
    printf("\n");

    for (int i = 0; i < BN_LIN; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < BN_COL; j++) {
            printf("%c ", visivel[i][j]);
        }
        printf("\n");
    }
}



// ---------------- JOGO 5 – ROLETA ----------------

void jogo5() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));

    int numeros[37];
    int cores[37]; // cores da roleta
    for (int i = 0; i < 37; i++) {
        numeros[i] = i;
        if (i == 0) cores[i] = FOREGROUND_GREEN | FOREGROUND_INTENSITY;         // Verde
        else if (i % 2 == 0) cores[i] = FOREGROUND_RED | FOREGROUND_INTENSITY; // Vermelho
        else cores[i] = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;    // Preto
    }

    int escolha;
    printf("Escolha sua aposta:\n");
    printf("1 - Apostar em número\n");
    printf("2 - Apostar em cor\n");
    printf("3 - Apostar em terço\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    int aposta_num = -1;
    int aposta_cor = -1; // 0 = verde, 1 = vermelho, 2 = preto
    int aposta_terco = -1; // 1 = 1º terço, 2 = 2º, 3 = 3º

    if (escolha == 1) {
        printf("Escolha um número (0-36): ");
        scanf("%d", &aposta_num);
        if (aposta_num < 0 || aposta_num > 36) {
            printf("Número inválido!\n");
            return 0;
        }
    } else if (escolha == 2) {
        printf("Escolha uma cor:\n");
        printf("0 - Verde\n1 - Vermelho\n2 - Preto\nCor: ");
        scanf("%d", &aposta_cor);
        if (aposta_cor < 0 || aposta_cor > 2) {
            printf("Cor inválida!\n");
            return 0;
        }
    } else if (escolha == 3) {
        printf("Escolha um terço:\n");
        printf("1 - 1º terço (1-12)\n2 - 2º terço (13-24)\n3 - 3º terço (25-36)\nTerço: ");
        scanf("%d", &aposta_terco);
        if (aposta_terco < 1 || aposta_terco > 3) {
            printf("Terço inválido!\n");
            return 0;
        }
    } else {
        printf("Opção inválida!\n");
        return 0;
    }

    printf("\nGirando a roleta...\n\n");

    int exibidos[37] = {0}; // marcar números já exibidos
    int total_exibidos = 0;
    int giro;

    while (total_exibidos < 20) { // mostrar 20 números sem repetição
        giro = rand() % 37;
        if (!exibidos[giro]) { // ainda não foi exibido
            SetConsoleTextAttribute(hConsole, cores[giro]);
            printf("%2d ", numeros[giro]);
            fflush(stdout);
            exibidos[giro] = 1;
            total_exibidos++;
            Sleep(100);
        }
    }

    // Número final sorteado
    printf("\n\nNúmero sorteado: ");
    giro = rand() % 37;
    printf("%2d\n", numeros[giro]);

    // Determinar cor do número sorteado
    int cor_sorteada;
    if (numeros[giro] == 0) cor_sorteada = 0;       // Verde
    else if (numeros[giro] % 2 == 0) cor_sorteada = 1; // Vermelho
    else cor_sorteada = 2;                           // Preto

    // Determinar terço do número sorteado
    int terco_sorteado = 0;
    if (numeros[giro] >= 1 && numeros[giro] <= 12) terco_sorteado = 1;
    else if (numeros[giro] >= 13 && numeros[giro] <= 24) terco_sorteado = 2;
    else if (numeros[giro] >= 25 && numeros[giro] <= 36) terco_sorteado = 3;

    // Resultado
    if (escolha == 1 && aposta_num == numeros[giro]) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Parabéns! Você acertou o número!\n");
    } else if (escolha == 2 && aposta_cor == cor_sorteada) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Parabéns! Você acertou a cor!\n");
    } else if (escolha == 3 && aposta_terco == terco_sorteado) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Parabéns! Você acertou o terço!\n");
    } else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Você perdeu. Tente novamente!\n");
    }

    // Reset para cor padrão
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return 0;
}
































































































































































