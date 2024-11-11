#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX 100


void criptografar(char senha[15]);
void descriptografar(char senha [15]);
bool verificaSenha(char senha[15]);
void menu();
void inserir();
void remover();
void alterar();
void lista();

int main() {
  setlocale(LC_ALL, "Portuguese");
	menu();

  return 0;
}

void criptografar(char senha[15]) {
	int i = 0;
    while (senha[i]) {
        int adicionar = 7;
        senha[i] += adicionar; 
        i++;
        adicionar++;
    }
}

void descriptografar(char senha[15]) {
	int i = 0;
    int decremento = 7;

    while (senha[i]) {
        senha[i] -= decremento;
        i++;
        decremento++;
    }
  
}

bool verificaSenha(char senha[15]) {
	bool v1,v2,v3,v4,v5;
	v1=v2=v3=v4=v5 = false;
	int comprimento = strlen(senha);
	
	if(comprimento >= 8 && comprimento <=12) v1 = true;
	for(int i = 0; i < comprimento; i++) {
		if (senha[i] >= 'a' && senha[i] <= 'z') v2 = true;
    if (senha[i] >= 'A' && senha[i] <= 'Z') v3 = true;
    if (senha[i] >= '0' && senha[i] <= '9') v5 = true;
    if ((senha[i] >= 32 && senha[i] <= 47) || 
      (senha[i] >= 58 && senha[i] <= 64) ||
      (senha[i] >= 91 && senha[i] <= 96) || 
      (senha[i] >= 123 && senha[i] <= 126)) {
    	v4 = true; 
    }
	}
	
	return v1 && v2 && v3 && v4 && v5;
}

void inserir() {
  char usuario[15], senha[15];
  FILE *arquivo;

  system("cls");
  printf("Adicionar usu�rio\n");    
  printf("-------------\n");
  printf("Insira o usu�rio: ");
  scanf("%s", usuario);

  while (true) {
    printf("\nInsira a senha: ");
    scanf("%s", senha);
    if (verificaSenha(senha)) {
      break;
    } else {
      printf("\n- Senha Inv�lida -");
      printf("\n- 8 a 12 caracteres");
      printf("\n- Deve ter mai�scula e min�scula");
      printf("\n- Deve ter n�mero");
      printf("\n- Deve ter caractere especial\n");
    }
  }

  criptografar(usuario);
  criptografar(senha);

  arquivo = fopen("usuarios.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
    
  fprintf(arquivo, "Usu�rio: %s\nSenha: %s\n\n", usuario, senha);
  fclose(arquivo);
  printf("\nUsu�rio adicionado com sucesso!\n");

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch(); 
}

void lista() {
  char linha[100];
  FILE *arquivo;

  system("cls");
  printf("Lista de usu�riosn\n");

  arquivo = fopen("usuarios.txt", "r");
  if (arquivo == NULL) {
    printf("Nenhum usu�rio encontrado!\n");
    printf("\nPara voltar ao menu, pressione qualquer tecla...");
    getch();
    return;
  }

  printf("Usu�rios criptografados:\n");
  printf("------------------------------\n");

  while (fgets(linha, 100, arquivo) != NULL) {
    printf("%s", linha);
  }

  fclose(arquivo);
  printf("\n\nPara voltar ao menu, pressione qualquer tecla...");
  getch(); 
}

void remover() {
  char usuario[15], usuarioArquivo[15], senhaArquivo[15];
  bool usuarioEncontrado = false;

  FILE *arquivo = fopen("usuarios.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (arquivo == NULL || temp == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  system("cls");
  printf("Remover usu�rio\n");
  printf("-------------\n");
  printf("Digite o usu�rio que deseja remover: ");
  scanf("%s", usuario);

  criptografar(usuario);

  while (fscanf(arquivo, "Usu�rio: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;
      printf("\nUsu�rio removido com sucesso!\n");
    } else {
      fprintf(temp, "Usu�rio: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuarios.txt");
  rename("temp.txt", "usuarios.txt");

  if (!usuarioEncontrado) {
    printf("\nUsu�rio n�o encontrado.\n");
  }

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}


void alterar() {
  char usuario[15], novoUsuario[15], novaSenha[15], linha[MAX];
  char usuarioArquivo[15], senhaArquivo[15];
  bool usuarioEncontrado = false;

  FILE *arquivo = fopen("usuarios.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (arquivo == NULL || temp == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  system("cls");
  printf("Alterar usu�rio\n");
  printf("-------------\n");
  printf("Digite o usu�rio que deseja alterar: ");
  scanf("%s", usuario);

  criptografar(usuario);

  while (fscanf(arquivo, "Usu�rio: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;

      descriptografar(usuarioArquivo);
      descriptografar(senhaArquivo);

      printf("\nUsu�rio encontrado!\n");
      printf("Insira o novo usu�rio: ");
      scanf("%s", novoUsuario);

      while (true) {
        printf("\nInsira a nova senha: ");
        scanf("%s", novaSenha);
        if (verificaSenha(novaSenha)) {
          break;
        } else {
          printf("\n- Senha Inv�lida -");
          printf("\n- 8 a 12 caracteres");
          printf("\n- Deve ter mai�scula e min�scula");
          printf("\n- Deve ter n�mero");
          printf("\n- Deve ter caractere especial\n");
        }
      }

      criptografar(novoUsuario);
      criptografar(novaSenha);

      fprintf(temp, "Usu�rio: %s\nSenha: %s\n\n", novoUsuario, novaSenha);
      printf("\nUsu�rio e senha atualizados com sucesso!\n");
    } else {
      fprintf(temp, "Usu�rio: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuarios.txt");
  rename("temp.txt", "usuarios.txt");

  if (!usuarioEncontrado) {
    printf("\nUsu�rio n�o encontrado.\n");
  }

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void menu() {
  int opcao;

  do {
  	system("cls");
    printf("MENU \n");
    printf("1 - Adicionar usu�rio\n");
    printf("2 - Remover usu�rio\n");
    printf("3 - Alterar usu�rio\n");
    printf("4 - Lista de usu�rios\n");
    printf("5 - Sair\n");
    printf("-------------------------------\n");
    printf("Op��o: ");
    scanf("%d", &opcao);
    
    switch(opcao) {
      case 1: 
        inserir();
        break;
      case 2:
        remover();
        break;
      case 3: 
        alterar();
        break;
      case 4:
        lista();
        break;
      case 5:
        printf("Saindo...\n");
        break;
      default:
        printf("Op��o inv�lida! Tente novamente.\n");
    }
  } while(opcao != 5);
}

