#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define MAX 100
#define MAX_PROD_NOTA 20
#define TRUE 1
#define FALSE 0
#define SENTINELA 0
/*------------------------------------------------------------------------------
Variaveis Globais
------------------------------------------------------------------------------*/
typedef struct
{
  int cod_cliente;
  char nome[40];
  char endereco[50];
  int telefone;
}tipo_clientes;

typedef struct
{
  int cod_produto;
  char descricao[25];
  char unidade[6];
  float preco_unitario;
  int qt_stock;
}tipo_produtos;

typedef struct
{
  int cod_nota;
  int cod_cliente;
  float total_geral;
}tipo_notas;

typedef struct
{
  int cod_nota;
  int cod_produto[MAX_PROD_NOTA];
  int quantidade[MAX_PROD_NOTA];
  float preco_venda[MAX_PROD_NOTA];
  int plivre;
  int tipo;
}tipo_itens;

tipo_clientes cliente[MAX];
tipo_notas nota[MAX];
tipo_itens  itens[MAX];
tipo_produtos produto[MAX];
int plivre_cli, plivre_not, plivre_produt;
/*------------------------------------------------------------------------------
Prótotipo de Funções
------------------------------------------------------------------------------*/
void alterar_cliente();
void alterar_produto();
void barra();
int busca_cliente(int cod);
int busca_cliente_nota(int cod);
int busca_produto(int cod);
int busca_produto_itens(int cod, int nota);
int busca_produto_itensnota(int cod);
int busca_itens(int cod);
void carregar_cliente(tipo_clientes *buffer);
void carregar_produto(tipo_produtos *buffer);
int cheio(int plivre);
void compras();
int consistencia_clientes(tipo_clientes buffer);
int consistencia_produtos(tipo_produtos buffer);
int consulta_valor(float min, float max);
void consultar_por_valores();
void consulta_talao_cliente();
void entrada();
void excluir_cliente();
void excluir_produto();
void excluir_produto_nota();
void gravar_clientes(tipo_clientes buffer);
void gravar_produtos(tipo_produtos buffer);
void imprimir_cliente(int pos);
void imprimir_produto(int pos);
void imprimir_notas(int pos);
void inclusao_cliente();
void inclusao_produto();
void inicializador();
void menu_cadastro();
void menu_consultas();
void menu_manutencoes(int categoria);
void menu_movimentacoes();
void menu_principal();
void remove_cliente (int pos);
void remove_produto(int pos);
void remove_produto_nota(int pos_nota,int pos_prod);
int taloes_cliente(int cod);
int vazio(int plivre);
int ver_consistencia_itens(int indice_pro);
/*------------------------------------------------------------------------------
Objectivo: Apresentar a "Barra de Titulo" do Programa.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void barra()
{
  system("cls");
  printf("=====================================================\n");
  printf("=                  GESTÃO DE STOCK            =\n");
  printf("=====================================================");
}
/*------------------------------------------------------------------------------
Objectivo: Inicializar os vectores para armazenar os dados.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void inicializador()
{
     plivre_cli=plivre_not=plivre_produt=0;
}
/*------------------------------------------------------------------------------
Objectivo: Verificar se um vector está cheio
Parametros por valor: Posição livre do vector que se quer verificar
------------------------------------------------------------------------------*/
int cheio(int plivre)
{
    return plivre==MAX;
}
/*------------------------------------------------------------------------------
Objectivo: Verificar se um vector está vazio
Parametros por valor: Posição livre do vector que se quer verificar
------------------------------------------------------------------------------*/
int vazio(int plivre)
{
   return !(plivre);
}
/*------------------------------------------------------------------------------
Objectivo: Procurar um determinado Cliente
Parametros por valor: Código do Cliente
Retorno: Posição do cliente no vector ou -1 se não encontrar
------------------------------------------------------------------------------*/
int busca_cliente(int cod)
{
    int i;
    for(i=0; i<plivre_cli;i++)
       if (cod==cliente[i].cod_cliente)
          return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Buscar um cliente numa nota fiscal
Parametros: Nenhum
------------------------------------------------------------------------------*/
int busca_cliente_nota(int cod)
{
    int i;
    for(i=0; i<plivre_not;i++)
     if (cod==nota[i].cod_cliente)
       return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Remover um cliente do vector com os dados.
Parametrospor valor: posição do cliente a ser removido.
------------------------------------------------------------------------------*/
void remove_cliente (int pos)
{
    int i;
    for (i=pos;i<plivre_cli-1;i++)
      cliente[i]=cliente[i+1];
    plivre_cli--;
}
/*------------------------------------------------------------------------------
Objectivo: Carregar os dados de um cliente
Parametros por referência: registro com os dados do cliente
------------------------------------------------------------------------------*/
void carregar_cliente(tipo_clientes *buffer)
{
       fflush(stdin);
       printf("Nome do Cliente:");
       gets(buffer->nome);
       printf("Endereço do Cliente:");
       gets(buffer->endereco);
       printf("Número de Telefone:");
       scanf("%d", &buffer->telefone);
}
/*------------------------------------------------------------------------------
Objectivo: Verificar a consistência dos dados de um cliente
Parametros por valor: registro com os dados do cliente
------------------------------------------------------------------------------*/
int consistencia_clientes(tipo_clientes buffer)
{
    int consistente;
    consistente=TRUE;
    if(buffer.cod_cliente<0)
    {
        printf("Erro: Código do cliente inválido\n");
        consistente=FALSE;
    }
    if (!strlen(buffer.nome))
    {
        printf("Erro: Nome do cliente inválido\n");
        consistente=FALSE;
    }
    if (!strlen(buffer.endereco))
    {
        printf("Erro: Endereço do cliente inválido\n");
        consistente=FALSE;
    }
    if (buffer.telefone<0)
    {
        printf("Erro: Núumero de telefone do cliente inválido\n");
        consistente=FALSE;
    }
    return consistente;
}
/*------------------------------------------------------------------------------
Objectivo: Gravar um cliente no vector com os dados
Parametros por valor: registro com os dados do cliente
------------------------------------------------------------------------------*/
void gravar_clientes(tipo_clientes buffer)
{
    cliente[plivre_cli]=buffer;
    plivre_cli++;
}
/*------------------------------------------------------------------------------
Objectivo: Incluir  Clientes
Parametros: Nenhum
------------------------------------------------------------------------------*/
void inclusao_cliente()
{
    tipo_clientes buffer;
    printf("Entre com os Dados do Cliente\n");
    printf("Código do cliente:");
    scanf("%d", &buffer.cod_cliente);

     while(!cheio(plivre_cli)&& (buffer.cod_cliente !=SENTINELA ))
     {
       if (busca_cliente(buffer.cod_cliente)!=-1)
           printf("Erro: O Cliente já foi Cadastrado\n");
       else
       {
            carregar_cliente(&buffer);
            if(consistencia_clientes(buffer))
            {
               gravar_clientes(buffer);
               printf("Entre com os dados do próximo Cliente\n");
           }
         else
           printf("Entre com os dados do cliente novamente\n");
       }
       system("pause");
       barra();
       printf("Código do cliente:");
       scanf("%d", &buffer.cod_cliente);
     }
     if (buffer.cod_cliente==SENTINELA)
        printf("Inclusão Terminada com sucesso\n");
    else
        printf("Erro: Vector cheio\n");
    system("pause");
    menu_manutencoes(1);
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir os dados de um cliente
Parametros por valor: posição do cliente no vector com os dados
------------------------------------------------------------------------------*/
void imprimir_cliente(int pos)
{
   printf("Código do Cliente: %d\n", cliente[pos].cod_cliente);
   printf("Nome do Cliente: %s\n",cliente[pos].nome);
   printf("Endereço do Cliente: %s\n",cliente[pos].endereco);
   printf("Telefone do Cliente: %d\n",cliente[pos].telefone);
}
/*------------------------------------------------------------------------------
Objectivo: Alterar os dados de um cliente
Parametros: Nenhum
------------------------------------------------------------------------------*/
void alterar_cliente()
{
    tipo_clientes buffer;
    int  pos;
    printf("Entre com o Código do cliente:");
    scanf("%d", &buffer.cod_cliente);

    pos=busca_cliente(buffer.cod_cliente);
    if (pos!=-1)
    {
        printf("Dados actuais\n");
        imprimir_cliente(pos);
        printf("\nEntre com os Novos Dados\n\n");
        carregar_cliente(&buffer);
        while (!(consistencia_clientes(buffer)))
        {
            printf("Entre com os dados novamente\n");
            system("pause");
            carregar_cliente(&buffer);
        }
       cliente[pos]= buffer;
       printf("Dados Alterados com Sucesso\n");
    }
    else
      printf("Erro: Cliente não Cadastrado\n");
    system("pause");
    menu_manutencoes(1);
}
/*------------------------------------------------------------------------------
Objectivo: Excluir um cliente
Parametros: Nenhum
------------------------------------------------------------------------------*/
void excluir_cliente()
{
    int cod, pos;
    if(!vazio(plivre_cli))
    {
        printf("Entre com o Código do cliente");
        scanf("%d", &cod);
        pos=busca_cliente(cod);
        if (pos!=-1)
        {
          if(busca_cliente_nota(cod)!=-1)
            printf("Erro: Cliente com Notas Fiscais\n");
          else
          {
            printf("Dados do Cliente:\n\n");
            imprimir_cliente(pos);
            system("pause");
            remove_cliente(pos);
            printf("Cliente Excluido com Sucesso\n");
          }
        }
        else
           printf("Erro: Cliente não Cadastrado\n");
    }
    else
      printf("Erro:O Vector está vazio\n");
    system("pause");
    menu_manutencoes(1);
}
/*------------------------------------------------------------------------------
Objectivo: Procurar um determinado Produto
Parametros por valor: Código do Produto
Retorno: Posição do produto no vector ou -1 se não encontrar
------------------------------------------------------------------------------*/
int busca_produto(int cod)
{
    int i;
    for(i=0; i<plivre_produt;i++)
       if (cod==produto[i].cod_produto)
          return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Remover um produdo do vector com os dados.
Parametros: posição do produto a remover
------------------------------------------------------------------------------*/
void remove_produto(int pos)
{
    int i;
    for (i=pos;i<plivre_produt-1;i++)
       produto[i]=produto[i+1];
    plivre_produt--;
}
/*------------------------------------------------------------------------------
Objectivo: Carregar os dados de um produto
Parametros por referência: registro com os dados do produto
------------------------------------------------------------------------------*/
void carregar_produto(tipo_produtos *buffer)
{
    fflush(stdin);
    printf("Descrição do Produto:");
    gets(buffer->descricao);
    printf("Unidade do Produto:");
    gets(buffer->unidade);
    printf("Preço Unitário do Produto:");
    scanf("%f", &buffer->preco_unitario);
    printf("Quantidade em Stock do Produto:");
    scanf("%d", &buffer->qt_stock);
}
/*------------------------------------------------------------------------------
Objectivo: Verificar a consistência dos dados de um produto
Parametros por valor: registro com os dados do produto
------------------------------------------------------------------------------*/
int consistencia_produtos(tipo_produtos buffer)
{
    int consistente;
    consistente=TRUE;
    if(buffer.cod_produto<0)
    {
        printf("Erro: Código do produto inválido\n");
        consistente=FALSE;
    }
    if (!strlen(buffer.descricao))
    {
        printf("Erro: Descrição do produto inválida\n");
        consistente=FALSE;
    }
    if (!strlen(buffer.unidade))
    {
        printf("Erro: Unidade do produto inválida\n");
        consistente=FALSE;
    }
    if (buffer.preco_unitario<=0.00)
    {
        printf("Erro: Preço Unitário do produto inválido\n");
        consistente=FALSE;
    }
    if (buffer.qt_stock<0)
    {
        printf("Erro:Quantidade em Stock do produto inválida\n");
        consistente=FALSE;
    }
    return consistente;
}
/*------------------------------------------------------------------------------
Objectivo: Gravar um produto no vector com os dados
Parametros por valor: registro com os dados do produto
------------------------------------------------------------------------------*/
void gravar_produtos(tipo_produtos buffer)
{
    produto[plivre_produt]=buffer;
    plivre_produt++;
}
/*------------------------------------------------------------------------------
Objectivo: Incluir produtos
Parametros:Nenhum
------------------------------------------------------------------------------*/
void inclusao_produto()
{
    tipo_produtos buffer;
    printf("Código do Produto:");
    scanf("%d", &buffer.cod_produto);
    while(!cheio(plivre_produt)&& (buffer.cod_produto !=SENTINELA ))
     {
        if (busca_produto(buffer.cod_produto)!=-1)
            printf("Erro: O Produto já foi Cadastrado\n");
        else
          {
              carregar_produto(&buffer);
              if(consistencia_produtos(buffer))
              {
                 gravar_produtos(buffer);
                 printf("Entre com os dados do próximo Produto\n");
              }
             else
                printf("Entre com os dados do produto novamente\n");
          }
          system("pause");
          barra();
          printf("Código do Produto:");
          scanf("%d", &buffer.cod_produto);
     }
     if (buffer.cod_produto==SENTINELA)
        printf("Inclusão Terminada com sucesso\n");
    else
        printf("Erro: Vector cheio\n");
    system("pause");
    menu_manutencoes(2);
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir os dados de um produto.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void imprimir_produto(int pos)
{
   printf("\nCódigo do Produto: %d\n", produto[pos].cod_produto);
   printf("Descrição do Produto: %s\n",produto[pos].descricao);
   printf("Unidade do Produto: %s\n",produto[pos].unidade);
   printf("Preço Unitário do Produto: %.2f\n",produto[pos].preco_unitario);
   printf("Quantidade em Stock do Produto: %d\n",produto[pos].qt_stock);
}
/*------------------------------------------------------------------------------
Objectivo: Alterar os dados de um produto
Parametros: Nenhum
------------------------------------------------------------------------------*/
void alterar_produto()
{
    tipo_produtos buffer;
    int pos;
    printf("Entre com o Código do produto:");
    scanf("%d", &buffer.cod_produto);

    pos=busca_produto(buffer.cod_produto);
    if (pos!=-1)
    {
        printf("Dados actuais:\n");
        imprimir_produto(pos);
        printf("\nEntre com os Novos Dados\n\n");
        carregar_produto(&buffer);
        while (!(consistencia_produtos(buffer)))
        {
            printf("Entre com os dados novamente\n");
            system("pause");
            carregar_produto(&buffer);
        }
       produto[pos]= buffer;
       printf("Dados Alterados com Sucesso\n");
    }
    else
      printf("Erro: Produto não Cadastrado\n");
    system("pause");
    menu_manutencoes(2);
}
/*------------------------------------------------------------------------------
Objectivo: Excluir um produto
Parametros: Nenhum
------------------------------------------------------------------------------*/
void excluir_produto()
{
    int cod, pos,i;
    if(!vazio(plivre_produt))
    {
        printf("Entre com o Código do produto: ");
        scanf("%d", &cod);
        pos=busca_produto(cod);
        if (pos!=-1)
        {
            if(busca_produto_itensnota(cod)==-1)
            {
                 printf("Dados do Produto:\n\n");
                 imprimir_produto(pos);
                 system("pause");
                 remove_produto(pos);
                 printf("Produto Excluido com Sucesso\n");
            }
           else
              printf("Erro: O Produto se encontra numa nota fiscal\n");
        }
        else
           printf("Erro: Produto não Cadastrado\n");
    }
    else
      printf("Erro:O Vector está vazio\n");
    system("pause");
    menu_manutencoes(2);
}
/*------------------------------------------------------------------------------
Objectivo: Procurar uma determinada nota fiscal
Parametros por valor: Código da nota
Retorno: Posição da nota no vector ou -1 se não encontrar
------------------------------------------------------------------------------*/
int busca_itens(int cod)
{
    int i;
    for(i=0; i<plivre_not;i++)
       if (cod==itens[i].cod_nota)
          return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Procurar um determinado produto numa nota fiscal
Parametros por valor: Código do produto, posição da nota
Retorno: Posição do produto na nota ou -1 se não encontrar
------------------------------------------------------------------------------*/
int busca_produto_itens(int cod, int nota)
{
    int i;
    for(i=0; i<itens[nota].plivre;i++)
       if (cod==itens[nota].cod_produto[i])
          return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Procurar um determinado produto em todas as notas fiscais
Parametros por valor: Código do produto
Retorno: Posição da 1ª nota que contenha o produto ou -1 se não encontrar
------------------------------------------------------------------------------*/
int busca_produto_itensnota(int cod)
{
    int i;
    for(i=0; i<plivre_not;i++)
       if (busca_produto_itens(cod, i)!=-1)
          return i;
    return -1;
}
/*------------------------------------------------------------------------------
Objectivo: Verificar a consistência dos dados de uma nota fiscal
Parametros por valor: posição do produto na nota
------------------------------------------------------------------------------*/
int ver_consistencia_itens(int indice_pro)
{
    int consist=TRUE;
    if (itens[plivre_not].cod_produto[indice_pro]<0)
    {
        printf("Erro: Código do Produto Inválido\n");
        consist=FALSE;
    }
    if (itens[plivre_not].quantidade[indice_pro]<=0)
    {
        printf("Erro: Quantidade do Produto Inválida\n");
        consist=FALSE;
    }
    if (itens[plivre_not].preco_venda[indice_pro]<=0.0)
    {
        printf("Erro: Preço da compra do Produto Inválido\n");
        consist=FALSE;
    }
    return consist;
}
/*------------------------------------------------------------------------------
Objectivo: Realizar a Entrada de produtos.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void entrada()
{
    int  pos_prod;
    if(cheio(plivre_not))
      printf("Erro: Vetor Cheio\n");
    else
    {
        nota[plivre_not].cod_nota=itens[plivre_not].cod_nota=plivre_not+1;
        itens[plivre_not].tipo=2;
        nota[plivre_not].cod_cliente=0;
         itens[plivre_not].plivre=0;
        nota[plivre_not].total_geral=0.0;
        printf("Código da nota:%d\n",itens[plivre_not].cod_nota);
        printf("Código do %dº Produto:",itens[plivre_not].plivre+1);
        scanf("%d",&itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
        while(itens[plivre_not].cod_produto[itens[plivre_not].plivre]!=SENTINELA && itens[plivre_not].plivre<MAX_PROD_NOTA)
        {
          pos_prod=busca_produto(itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
          if(pos_prod ==-1)
             printf("Erro: O produto não foi Cadastrado.\n");
          else
            if(busca_produto_itens(itens[plivre_not].cod_produto[itens[plivre_not].plivre],plivre_not)!=-1)
                printf("Erro: O produto já foi inserido na nota.\n");
            else
            {
              printf("Quantidade do %dº Produto:",itens[plivre_not].plivre+1);
              scanf("%d",&itens[plivre_not].quantidade[itens[plivre_not].plivre]);
              printf("Preço da compra %dº Produto:",itens[plivre_not].plivre+1);
              scanf("%f",&itens[plivre_not].preco_venda[itens[plivre_not].plivre]);
              if (ver_consistencia_itens(itens[plivre_not].plivre))
              {
                produto[pos_prod].qt_stock+=itens[plivre_not].quantidade[itens[plivre_not].plivre];
                nota[plivre_not].total_geral+=(itens[plivre_not].quantidade[itens[plivre_not].plivre]*itens[plivre_not].preco_venda[itens[plivre_not].plivre]);
                itens[plivre_not].plivre++;
                printf("Entre com os dados do próximo Produto\n");
              }
              else
                printf("Entre com os dados do mesmo Produto\n");
             }
           system("pause");
           barra();
           printf("Código do %dº Produto:",itens[plivre_not].plivre+1);
           scanf("%d",&itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
        }

        if(itens[plivre_not].plivre==MAX_PROD_NOTA)
          printf("Erro: Nota cheia entre com outra nota\n");
        else
          printf("Nota carregada com sucesso\n");

        if(itens[plivre_not].plivre!=SENTINELA)
          plivre_not++;
    }

   system("pause");
   menu_movimentacoes();
}
/*------------------------------------------------------------------------------
Objectivo: Realizar a Compra de produtos.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void compras()
{
    int  pos_prod;
    if(cheio(plivre_not))
      printf("Erro: Vetor Cheio\n");
    else
    {
        nota[plivre_not].cod_nota=itens[plivre_not].cod_nota=plivre_not+1;
        itens[plivre_not].tipo=1;
        itens[plivre_not].plivre=0;
        nota[plivre_not].total_geral=0.0;
        printf("Código da nota:%d\n",itens[plivre_not].cod_nota);

        printf("Código do Cliente:");
        scanf("%d",&nota[plivre_not].cod_cliente);
        if (busca_cliente(nota[plivre_not].cod_cliente)!=-1)
        {
            printf("Código do %dº Produto:",itens[plivre_not].plivre+1);
            scanf("%d",&itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
            while(itens[plivre_not].cod_produto[itens[plivre_not].plivre]!=SENTINELA && itens[plivre_not].plivre<MAX_PROD_NOTA)
           {
               pos_prod=busca_produto(itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
              if(pos_prod ==-1)
                 printf("Erro: O produto não foi Cadastrado.\n");
             else
                if(busca_produto_itens(itens[plivre_not].cod_produto[itens[plivre_not].plivre],plivre_not)!=-1)
                    printf("Erro: O produto já foi inserido na nota.\n");
               else
              {
                  printf("Quantidade do %dº Produto:",itens[plivre_not].plivre+1);
                  scanf("%d",&itens[plivre_not].quantidade[itens[plivre_not].plivre]);
                  itens[plivre_not].preco_venda[itens[plivre_not].plivre]=produto[pos_prod].preco_unitario;
                  if (ver_consistencia_itens(itens[plivre_not].plivre))
                  {
                     if(produto[pos_prod].qt_stock>=itens[plivre_not].quantidade[itens[plivre_not].plivre])
                    {
                      produto[pos_prod].qt_stock-=itens[plivre_not].quantidade[itens[plivre_not].plivre];
                      nota[plivre_not].total_geral+=(itens[plivre_not].quantidade[itens[plivre_not].plivre]*itens[plivre_not].preco_venda[itens[plivre_not].plivre]);
                      itens[plivre_not].plivre++;
                      printf("Entre com os dados do próximo Produto\n");
                    }
                    else
                      printf("Erro: Quantidade em Stock insuficiente\n");
                  }
                  else
                    printf("Entre com os dados do mesmo Produto\n");
               }
               system("pause");
               barra();
               printf("Código do %dº Produto:",itens[plivre_not].plivre+1);
               scanf("%d",&itens[plivre_not].cod_produto[itens[plivre_not].plivre]);
            }

           if(itens[plivre_not].plivre==MAX_PROD_NOTA)
              printf("Erro: Nota cheia entre com outra nota\n");
           else
              printf("Nota carregada com sucesso\n");
           if(itens[plivre_not].plivre!=SENTINELA)
             plivre_not++;
        }
        else
            printf("Erro: Cliente Não Cadastrado\n");
    }

   system("pause");
   menu_movimentacoes();
}
/*------------------------------------------------------------------------------
Objectivo: Remover um produdo de uma nota fiscal.
Parametros por valor: posição da nota no vector,Posição do produto na nota
------------------------------------------------------------------------------*/
void remove_produto_nota(int pos_nota,int pos_prod)
{
    int i;
    nota[pos_nota].total_geral-=itens[pos_nota].preco_venda[pos_prod]*itens[pos_nota].quantidade[pos_prod];
    if(itens[pos_nota].tipo==1)
      produto[busca_produto(itens[pos_nota].cod_produto[pos_prod])].qt_stock+=itens[pos_nota].quantidade[pos_prod];
    else
      produto[busca_produto(itens[pos_nota].cod_produto[pos_prod])].qt_stock-=itens[pos_nota].quantidade[pos_prod];

    for (i=pos_prod;i<itens[pos_nota].plivre-1;i++)
    {
      itens[pos_nota].cod_produto[i]=itens[pos_nota].cod_produto[i+1];
      itens[pos_nota].quantidade[i]=itens[pos_nota].quantidade[i+1];
      itens[pos_nota].preco_venda[i]=itens[pos_nota].preco_venda[i+1];
    }
    itens[pos_nota].plivre--;
}
/*------------------------------------------------------------------------------
Objectivo: Excluir um produto de uma nota
Parametros: Nenhum
------------------------------------------------------------------------------*/
void excluir_produto_nota()
{
    int cod_nota,cod_prod, pos_nota,pos_prod;
    if(!vazio(plivre_not))
    {
        printf("Entre com o Código da nota:");
        scanf("%d", &cod_nota);
        pos_nota=busca_itens(cod_nota);
        if (pos_nota!=-1)
        {
          printf("Entre com o Código do produto:");
          scanf("%d", &cod_prod);
          pos_prod=busca_produto_itens(cod_prod, pos_nota);
          if(pos_prod!=-1)
          {
            barra();
            imprimir_notas(pos_nota);
            system("pause");
            remove_produto_nota(pos_nota,pos_prod);
            printf("Produto Excluido da nota com Sucesso\n");
          }
          else
            printf("Erro: Produto não Inserido na nota\n");
        }
        else
           printf("Erro: Nota não Encontrada\n");
    }
    else
      printf("Erro:O Vector está vazio\n");
    system("pause");
    menu_movimentacoes();
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir todos os produtos cujo preço está entre dois valores
Parametros por valor: Intervalo  de valores
------------------------------------------------------------------------------*/
int consulta_valor(float min, float max)
{
     int i,qt=0;
     for(i=0;i<plivre_produt;i++)
      if(produto[i].preco_unitario>=min)
       if(produto[i].preco_unitario<=max)
         {
            imprimir_produto(i);
            qt++;
         }
     return qt;
}
/*------------------------------------------------------------------------------
Objectivo: Consultar todos os produtos cujo preço está entre dois valores.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void consultar_por_valores()
{
     float val1, val2;
     do
     {
       printf("Entre com o primeiro valor:");
       scanf("%f",&val1);
       printf("Entre com o segundo valor:");
       scanf("%f",&val2);
       if(val1<=0.0 || val2<0.0)
         printf("Erro: valores inválidos Digite novamente\n");
     }
     while(val1<=0.0 || val2<0.0);

     if (val2>val1)
      printf("\n%d Produtos encontrados\n\n",consulta_valor(val1,val2));
     else
        printf("\n%d Produtos encontrados\n\n",consulta_valor(val2,val1));
     system("pause");
     menu_consultas();
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir uma nota fiscal.
Parametros por valor: Posição da nota no vector
------------------------------------------------------------------------------*/
void imprimir_notas(int pos)
{
   int i;
   printf("-----------------NOTA FISCAL-----------------------\n");
   printf("---------------------------------------------------\n");
   printf("Código da nota: %03d\n", nota[pos].cod_nota);
   printf("Código do Cliente: %04d\n", nota[pos].cod_cliente);
   printf("---------------------------------------------------\n");
   printf("Produtos\n");
   printf("---------------------------------------------------\n");
   for(i=0;i<itens[pos].plivre;i++)
   {
     printf("%3d X ",itens[pos].quantidade[i]);
     printf("%s",produto[busca_produto(itens[pos].cod_produto[i])].descricao);
     printf("(%.2f $)\n",itens[pos].preco_venda[i]);
    }
   printf("---------------------------------------------------\n");
   printf("Total da Nota:%.2f\n\n",nota[pos].total_geral);
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir todos os talões de um cliente
Parametros por valor: código do cliente
Retorno: Número de talões encontrados
------------------------------------------------------------------------------*/
int taloes_cliente(int cod)
{
   int i, qt=0;
   for(i=0; i<plivre_not;i++)
     if (cod==nota[i].cod_cliente)
     {
       imprimir_notas(i);
       qt++;
     }
   return qt++;
}
/*------------------------------------------------------------------------------
Objectivo: Consultar os talões de um cliente
Parametros: Nenhum
------------------------------------------------------------------------------*/
void consulta_talao_cliente()
{
    int i, cod_cliente, encontrados;
    printf("Entre com o código do cliente:\n");
    scanf("%d",&cod_cliente);
    barra();
    printf("\n%d Talões encontrados\n", taloes_cliente(cod_cliente));
    system("pause");
    menu_consultas();
}
/*------------------------------------------------------------------------------
Objectivo: Imprimir um determinado talão.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void consulta_talao()
{
     int  pos, cod_nota;
     printf("Entre com o código da nota:");
     scanf("%d",&cod_nota);
     pos=busca_itens(cod_nota);
     if (pos!=-1)
     {
       barra();
       imprimir_notas(pos);
     }
     else
       printf("Erro código da nota não encontrado\n");
     system("pause");
     menu_consultas();
}
/*------------------------------------------------------------------------------
Objectivo: Apresentar na tela as opções de menu Principal do programa.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void menu_principal()
{
      int op;
      barra();
      do
      {
          printf("\n\nMENU DE OPÇÕES\n\n");
          printf("\t1->CADASTROS\n");
          printf("\t2->MOVIMENTAÇÕES\n");
          printf("\t3->CONSULTAS\n");
          printf("\t4->TERMINAR\n");
          printf("\nEntre com a opção:");
          scanf("%d", &op);
          switch(op)
          {
                case 1:
                     menu_cadastro();
                     break;
                case 2:
                     menu_movimentacoes();
                     break;
                 case 3:
                     menu_consultas();
                     break;
                 case 4:
                     exit(0);
                     break;
                 default:
                     printf("Opção Inválida\n");
                     system("pause");
          }
     }
    while(op<1 || op>4);
    }
/*------------------------------------------------------------------------------
Objectivo: Apresentar na tela as opções de menu Cadastro.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void menu_cadastro()
{
  int op;
  do
  {
      barra();
      printf("\nMENU CADASTROS\n\n");
      printf("\t1->MANUTENÇÃO DE CLIENTES\n");
      printf("\t2->MANUTENÇÃO DE PRODUTOS\n");
      printf("\t3->VOLTAR\n");
      printf("\nSua Escolha:");
      scanf("%d", &op);

      switch(op)
      {
        case 1:
        case 2:
             menu_manutencoes(op);
             break;
        case 3:
             menu_principal();
             break;
        default:
             printf("Opção Inválida\n");
             system("pause");
      }
  }
  while(op<1 || op>3);
}
/*-------------------------------------------------------------------------------------------------
Objectivo: Apresentar na tela as opções de menu Cadastro\Manutenção(Clientes ou Produtos).
Parametros: categoria(1-Clientes, 2-Produtos)
--------------------------------------------------------------------------------------------------*/
void menu_manutencoes(int categoria)
{
  int op;
  do
  {
      barra();
      if (categoria==1)
         printf("\nMENU CADASTROS\\MANUTENÇÃO DE CLIENTES\n\n");
      else
         printf("\nMENU CADASTROS\\MANUTENÇÃO DE PRODUTOS\n\n");
      printf("\t1->INCLUSÃO\n");
      printf("\t2->ALTERAÇÃO\n");
      printf("\t3->EXCLUSÃO\n");
      printf("\t4->VOLTAR\n");
      printf("\nSua Escolha:");
      scanf("%d", &op);

      switch(op)
      {
        case 1:
             barra();
             if (categoria==1)
                 inclusao_cliente();
             else
                 inclusao_produto();
             break;
        case 2:
             barra();
             if (categoria==1)
                 alterar_cliente();
              else
                 alterar_produto();
             break;
        case 3:
             barra();
             if (categoria==1)
               excluir_cliente();
            else
               excluir_produto();
             break;
        case 4:
             menu_cadastro();
             break;
        default:
             printf("Opção Inválida\n");
             system("pause");
      }
  }
  while(op<1 || op>4);
}
/*------------------------------------------------------------------------------
Objectivo: Apresentar na tela as opções do menu Consultas.
Parametros: Nenhum
------------------------------------------------------------------------------*/
void menu_consultas()
{
  int op;
  do
  {
      barra();
      printf("\nMENU CONSULTAS\n\n");
      printf("\t1->CONSULTA POR VALORES\n");
      printf("\t2->CONSULTA POR CLIENTE\n");
      printf("\t3->CONSULTA POR TALÃO\n");
      printf("\t4->VOLTAR\n");
      printf("\nSua Escolha:");
      scanf("%d", &op);

      switch(op)
      {

        case 1:
             barra();
             consultar_por_valores();
             break;
        case 2:
             barra();
             consulta_talao_cliente();
             break;
        case 3:
             barra();
             consulta_talao();
             break;
        case 4:
             menu_principal();
             break;
        default:
             printf("Opção Inválida\n");
             system("pause");
      }
  }
  while(op<1 || op>4);
}
/*-------------------------------------------------------------------------------------------------
Objectivo: Apresentar na tela as opções de menu Movimentações.
Parametros: Nenhum
--------------------------------------------------------------------------------------------------*/
void menu_movimentacoes()
{
	int op;
	do
	{
		barra();
		printf("\nMENU MOVIMENTAÇÕES\n\n");
		printf("\t1->ENTRADAS\n");
		printf("\t2->COMPRAS\n");
		printf("\t3->EXCLUIR UM PRODUTO\n");
		printf("\t4->VOLTAR\n");
		printf("\nSua Escolha:");
		scanf("%d", &op);
		
		switch(op)
		{
			case 1:
			      barra();
			      entrada();
			      break;
			case 2:
			     barra();
			     compras();
			     break;
			case 3:
			     barra();
			     excluir_produto_nota();
			     break;
			case 4:
			     menu_principal();
			     break;
			default:
			     printf("Opção Inválida\n");
			     system("pause");
		}
	}
	while(op<1 || op>4);
}

/*------------------------------------------------------------------------------
Função Principal
------------------------------------------------------------------------------*/
int main()
{
    int op;
    inicializador();
    setlocale(LC_ALL, "Portuguese");
    menu_principal();
    return 0;
}
