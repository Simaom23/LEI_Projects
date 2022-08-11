package exercicioavaliacao3;
// Simão Monteiro Nº2019215412

/**
 *
 * @author Simão Monteiro
 */
import java.util.Scanner;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class ExercicioAvaliacao3 {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int maxProdutos = 0;
        boolean flagProdutos = false;
        while (!flagProdutos) {
            System.out.printf("Quer criar um controle de stocks com um máximo de quantos produtos? ");
            if (input.hasNextInt()) {
                flagProdutos = true;
                maxProdutos = input.nextInt();
            } else {
                System.out.println("Stock máximo inválido.");
            }
            input.nextLine();
        }
        Supermercado newStore = new Supermercado(maxProdutos);
        OUTER:
        while (true) {
            int escolha = 0;
            boolean flag = false;
            while (!flag) {
                System.out.printf("\nMenu:\n0 - Sair\n1 - Adicionar Produtos\n2 - Vender Produto\n"
                        + "3 - Lista de Produtos\n4 - Valor total dos Produtos em stock\nEscolha uma opção: ");
                if (input.hasNextInt()) {
                    flag = true;
                    escolha = input.nextInt();
                } else {
                    System.out.printf("Escolha inválida.");
                }
                input.nextLine();
            }
            System.out.println();
            switch (escolha) {
                case 1 -> {
                    System.out.printf("Produto: ");
                    String produto = input.nextLine();
                    String validade = null;
                    flag = false;
                    while (!flag) {
                        System.out.printf("Validade (dd/mm/aaaa): ");
                        validade = input.nextLine();
                        if (validade.length() == 10) {
                            if (Character.isDigit(validade.charAt(0)) & Character.isDigit(validade.charAt(1))
                                    & Character.isDigit(validade.charAt(3)) & Character.isDigit(validade.charAt(4)) & Character.isDigit(validade.charAt(6))
                                    & Character.isDigit(validade.charAt(7)) & Character.isDigit(validade.charAt(8)) & Character.isDigit(validade.charAt(9))) {
                                int diaConv = Integer.parseInt(validade.substring(0, 2));
                                int mesConv = Integer.parseInt(validade.substring(3, 5));
                                int anoConv = Integer.parseInt(validade.substring(6, 10));
                                if ((diaConv > 1 & diaConv < 32) & (mesConv > 0 & mesConv < 13) & (anoConv > 0)) {
                                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("ddMMyyyy");
                                    String dataHoje = LocalDate.now().format(formatter);
                                    int diaHoje = Integer.parseInt(dataHoje.substring(0, 2));
                                    int mesHoje = Integer.parseInt(dataHoje.substring(2, 4));
                                    int anoHoje = Integer.parseInt(dataHoje.substring(4, 8));
                                    if (anoHoje > anoConv) {
                                        System.out.println("Produto fora de validade.");
                                    } else if (anoHoje == anoConv) {
                                        if (mesHoje > mesConv) {
                                            System.out.println("Produto fora de validade.");
                                        } else if (mesHoje < mesConv) {
                                            flag = true;
                                        } else if (mesHoje == mesConv) {
                                            if (diaHoje > diaConv) {
                                                System.out.println("Produto fora de validade.");
                                            } else {
                                                flag = true;
                                            }
                                        }
                                    } else {
                                        flag = true;
                                    }
                                } else {
                                    System.out.println("Introduza uma data válida.");
                                }
                            } else {
                                System.out.println("Introduza uma data válida.");
                            }
                        } else {
                            System.out.println("Introduza uma data válida.");
                        }
                    }
                    float preco = 0;
                    flag = false;
                    while (!flag) {
                        System.out.printf("Preço: ");
                        if (input.hasNextFloat()) {
                            flag = true;
                            preco = input.nextFloat();
                        } else {
                            System.out.println("Introduza um preço (euros,centimos).");
                        }
                        input.nextLine();
                    }
                    int stock = 0;
                    flag = false;
                    while (!flag) {
                        System.out.printf("Stock: ");
                        if (input.hasNextInt()) {
                            flag = true;
                            stock = input.nextInt();
                        } else {
                            System.out.println("Introduza o stock.");
                        }
                        input.nextLine();
                    }
                    Produto newProduto = new Produto(produto, validade, preco, stock);
                    newStore.addSupermercado(newProduto);
                }
                case 2 -> {
                    System.out.printf("Produto que deseja vender: ");
                    String produto = input.nextLine();
                    int quantProduto = 0;
                    flag = false;
                    while (!flag) {
                        System.out.printf("Quantidade: ");
                        if (input.hasNextInt()) {
                            flag = true;
                            quantProduto = input.nextInt();
                        } else {
                            System.out.println("Introduza uma quantidade.");
                        }
                        input.nextLine();
                    }
                    newStore.sellProduto(produto, quantProduto);
                }
                case 3 -> {
                    newStore.showSupermercado();
                }
                case 4 -> {
                    newStore.showValor();
                }
                case 0 -> {
                    System.out.println("Programa terminado.");
                    break OUTER;
                }
                default -> {
                    System.out.printf("Escolha inválida.");
                }
            }
        }
    }
}
