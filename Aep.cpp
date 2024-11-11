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
  printf("Adicionar usuário\n");    
  printf("-------------\n");
  printf("Insira o usuário: ");
  scanf("%s", usuario);

  while (true) {
    printf("\nInsira a senha: ");
    scanf("%s", senha);
    if (verificaSenha(senha)) {
      break;
    } else {
      printf("\n- Senha Inválida -");
      printf("\n- 8 a 12 caracteres");
      printf("\n- Deve ter maiúscula e minúscula");
      printf("\n- Deve ter número");
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
    
  fprintf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuario, senha);
  fclose(arquivo);
  printf("\nUsuário adicionado com sucesso!\n");

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch(); 
}

void lista() {
  char linha[100];
  FILE *arquivo;

  system("cls");
  printf("Lista de usuáriosn\n");

  arquivo = fopen("usuarios.txt", "r");
  if (arquivo == NULL) {
    printf("Nenhum usuário encontrado!\n");
    printf("\nPara voltar ao menu, pressione qualquer tecla...");
    getch();
    return;
  }

  printf("Usuários criptografados:\n");
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
  printf("Remover usuário\n");
  printf("-------------\n");
  printf("Digite o usuário que deseja remover: ");
  scanf("%s", usuario);

  criptografar(usuario);

  while (fscanf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;
      printf("\nUsuário removido com sucesso!\n");
    } else {
      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuarios.txt");
  rename("temp.txt", "usuarios.txt");

  if (!usuarioEncontrado) {
    printf("\nUsuário não encontrado.\n");
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
  printf("Alterar usuário\n");
  printf("-------------\n");
  printf("Digite o usuário que deseja alterar: ");
  scanf("%s", usuario);

  criptografar(usuario);

  while (fscanf(arquivo, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo) != EOF) {
    if (strcmp(usuarioArquivo, usuario) == 0) {
      usuarioEncontrado = true;

      descriptografar(usuarioArquivo);
      descriptografar(senhaArquivo);

      printf("\nUsuário encontrado!\n");
      printf("Insira o novo usuário: ");
      scanf("%s", novoUsuario);

      while (true) {
        printf("\nInsira a nova senha: ");
        scanf("%s", novaSenha);
        if (verificaSenha(novaSenha)) {
          break;
        } else {
          printf("\n- Senha Inválida -");
          printf("\n- 8 a 12 caracteres");
          printf("\n- Deve ter maiúscula e minúscula");
          printf("\n- Deve ter número");
          printf("\n- Deve ter caractere especial\n");
        }
      }

      criptografar(novoUsuario);
      criptografar(novaSenha);

      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", novoUsuario, novaSenha);
      printf("\nUsuário e senha atualizados com sucesso!\n");
    } else {
      fprintf(temp, "Usuário: %s\nSenha: %s\n\n", usuarioArquivo, senhaArquivo);
    }
  }

  fclose(arquivo);
  fclose(temp);

  remove("usuarios.txt");
  rename("temp.txt", "usuarios.txt");

  if (!usuarioEncontrado) {
    printf("\nUsuário não encontrado.\n");
  }

  printf("\nPara voltar ao menu, pressione qualquer tecla...");
  getch();
}

void menu() {
  int opcao;

  do {
  	system("cls");
    printf("MENU \n");
    printf("1 - Adicionar usuário\n");
    printf("2 - Remover usuário\n");
    printf("3 - Alterar usuário\n");
    printf("4 - Lista de usuários\n");
    printf("5 - Sair\n");
    printf("-------------------------------\n");
    printf("Opção: ");
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
        printf("Opção inválida! Tente novamente.\n");
    }
  } while(opcao != 5);
}

