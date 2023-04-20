// Autor: Bernardo de Brito Cruz
// Aluno do 3º Período do Curso de Engenharia da Computa��o na Universidade Veiga de Almeida
// Data de criação: 08/04/2023

// Bibliotecas utilizadas no desenvolvimento do código
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Declaração das duas funções
void dataHora();
void dataHoraArq();

int main()
{
    // Declaração das variáveis
    float precipitacao,
        umidade,
        temperatura,
        vento;
    int run = 1;

    char escalaTemp;
    char direcao[10];

    FILE *arq;

    while (run == 1) // condição para realizar varias medições sem precisar encerrar o programa
    {
        system("cls||clear");                       // limpa o terminal
        arq = fopen("historico-medicoes.txt", "a"); // abre/cria o arquivo de histórico de medições

        // Recepção dos dados meteorológicos
        printf("Precipitacao medida (em milimetros/hora): ");
        scanf("%f", &precipitacao);
        printf("Umidade do ar (em %c): ", 37);
        scanf("%f", &umidade);
        printf("Temperatura do ar: ");
        scanf("%f%c", &temperatura, &escalaTemp);
        printf("Velocidade do ar (em km/h): ");
        scanf("%f", &vento);
        printf("Direcao do vento: ");
        scanf("%s", direcao);

        system("cls||clear"); // limpa o terminal

        // Execução das duas funções declaradas
        dataHora();    // pega a data e hora do sistema e escreve na tela
        dataHoraArq(); // pega a data e hora do sistema e escreve no arquivo

        // De acordo com os dados meteorológicos analisa se é alguma condição de risco
        if (precipitacao >= 20 && precipitacao <= 30 && vento >= 40 && vento <= 60) // se a precipitação estiver entre 20mm e 30mm e a velocidade do ar entre 40km/h e 60km/h exibe 'ALERTA AMARELO'
        {
            printf("\nALERTA AMARELO - RISCO MODERADO\n");
            printf("Baixo risco de corte de energia eletrica, queda de galhos de arvores, alagamentos e de descargas eletricas.\n\n");
            fputs("ALERTA AMARELO\n", arq);
        }
        else if (precipitacao >= 30 && precipitacao <= 60 && vento >= 60 && vento <= 100) // se a precipitação estiver entre 30mm e 60mm e a velocidade ao ar entre 60km/h e 100km/h exibe 'ALERTA LARANJA'
        {
            printf("\nALERTA LARANJA - RISCO ALTO\n");
            printf("Risco efetivo de corte de energia eletrica, queda de galhos de arvores, alagamentos e de descargas eletricas.\n\n");
            fputs("ALERTA LARANJA\n", arq);
        }
        else if (precipitacao > 60 && vento > 100) // se a precipitação estiver maior que 60mm e a velocidade do ar maior que 100km/h exibe 'ALERTA VERMELHO'
        {
            printf("\nALERTA VERMELHO - RISCO MUITO ALTO\n");
            printf("Risco eminente de grandes alagamentos e transbordamentos de rios, grandes deslizamentos de encostas, em cidades com tais areas de risco.\n\n");
            fputs("ALERTA VERMELHO\n", arq);
        }

        // Exibe os dados meteorológicos recebidos na tela
        printf("\nMedicao Final:\n");
        printf("Precipitacao: %.1fmm\n", precipitacao);
        printf("Umidade do ar: %.0f%c\n", umidade, 37);
        printf("Temperatura do ar: %.1f%c%c\n", temperatura, 248, toupper(escalaTemp));
        printf("Velocidade do ar: %.0f km/h\n", vento);
        printf("Direcao do vento: %s\n", direcao);

        // Escreve os dados meteorológicos recebidos no arquivo "historico-medicoes"
        fprintf(arq, "Precipitacao: %.1fmm\n", precipitacao);
        fprintf(arq, "Umidade do ar: %.0f%c\n", umidade, 37);
        fprintf(arq, "Temperatura do ar: %.1f%c%c\n", temperatura, 248, toupper(escalaTemp));
        fprintf(arq, "Velocidade do ar: %.0f km/h\n", vento);
        fprintf(arq, "Direcao do vento: %s\n", direcao);

        printf("\nDeseja realizar outra leitura?\n"); // pergunta se deseja realizar outra medição (sem encerrar o programa)
        printf("(0)Nao (1)Sim - ");
        scanf("%d", &run);

        fclose(arq); // fecha o arquivo "historico-medicoes"
    }

    system("notepad.exe historico-medicoes.txt"); // Abre a janela do arquivo "historico-medicoes.txt" na tela com todas as medições já feitas registradas
    return 0;
}

void dataHora() // Função que pega a data e hora atual do sistema e escreve na tela
{
    // estrutura que pega a data e hora atual
    struct tm *dataHoraAtual;
    time_t segundos;
    time(&segundos);
    dataHoraAtual = localtime(&segundos);

    // escreve na tela a data e hora atual
    printf("Data da Medicao: ");
    printf("%02d/%02d/%d\n", dataHoraAtual->tm_mday, dataHoraAtual->tm_mon + 1, dataHoraAtual->tm_year + 1900);
    printf("Horario da Medicao: ");
    printf("%02d:%02d:%02d\n", dataHoraAtual->tm_hour, dataHoraAtual->tm_min, dataHoraAtual->tm_sec);
}

void dataHoraArq() // Função que pega a data e hora atual do sistema e escreve no arquivo "historico-medicoes.txt"
{
    // estrutura que pega a data e hora atual do sistema
    struct tm *dataHoraAtual; // struct tm que 'aponta' para a 'variável'
    time_t segundos;          // variável do tipo 'time_t' (bilbioteca time.h)
    time(&segundos);
    dataHoraAtual = localtime(&segundos);

    FILE *arq;                                  // ponteiro do arquivo para "arq"
    arq = fopen("historico-medicoes.txt", "a"); // abre o arquivo "historico-medicoes"

    // escreve no arquivo a data e hora atual
    fprintf(arq, "______________________________\n");
    fprintf(arq, "Data da Medicao: ");
    fprintf(arq, "%02d/%02d/%02d\n", dataHoraAtual->tm_mday, dataHoraAtual->tm_mon + 1, dataHoraAtual->tm_year + 1900); // escreve no arquivo a data atual do sistema no formato: dd/mm/yyyy (dia/mes/ano)
    fprintf(arq, "Hora da Medicao: ");
    fprintf(arq, "%02d:%02d:%02d\n\n", dataHoraAtual->tm_hour, dataHoraAtual->tm_min, dataHoraAtual->tm_sec); // escreve no arquivo o horário atual do sistema no formato: hh:mm:ss (horas:minutos:segundos)

    fclose(arq); // fecha o arquivo "historico-medicoes"
}
