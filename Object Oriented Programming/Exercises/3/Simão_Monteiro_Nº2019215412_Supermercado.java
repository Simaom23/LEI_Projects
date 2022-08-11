package exercicioavaliacao3;
// Simão Monteiro Nº2019215412

/**
 *
 * @author Simão Monteiro
 */
import java.util.ArrayList;

public class Supermercado {

    private int nProdutos;
    private int maxProdutos;
    private ArrayList<Produto> listaProdutos;

    public Supermercado() {
    }

    public Supermercado(int maxProdutos) {
        this.maxProdutos = maxProdutos;
        nProdutos = 0;
        listaProdutos = new ArrayList<>();
    }

    public void addSupermercado(Produto newProduto) {
        for (int i = 0; i < listaProdutos.size(); i++) {
            if (newProduto.getNomeProduto().toLowerCase().equals(listaProdutos.get(i).getNomeProduto().toLowerCase())) {
                System.out.println("\nProduto com o mesmo nome.");
                return;
            }
        }
        if (nProdutos < maxProdutos) {
            listaProdutos.add(newProduto);
            nProdutos++;
            System.out.printf("\n\nProduto adicionado com sucesso.\nProduto adicionado ao Supermercado:\n");
            System.out.printf("Produto: %s\nValidade: %s\nPreço: %.2f€\nStock: %d\n", newProduto.getNomeProduto(), newProduto.getValidadeProduto(),
                    newProduto.getPrecoProduto(), newProduto.getStockProduto());
        } else {
            System.out.println("\nNão é possível adiconar novos produtos.");
        }
    }

    public void sellProduto(String nomeProduto, int quantProduto) {
        Produto produto = listaProdutos.get(0);
        int indice = -1;
        for (int i = 0; i < listaProdutos.size(); i++) {
            produto = listaProdutos.get(i);
            if (produto.getNomeProduto().toLowerCase().equals(nomeProduto.toLowerCase())) {
                indice = i;
                break;
            }
        }
        if (indice == -1) {
            System.out.printf("\nProduto inexistente.\n");
        } else {
            if (produto.getStockProduto() >= quantProduto) {
                produto.removeStock(quantProduto);
                if (produto.getStockProduto() == 0) {
                    listaProdutos.remove(indice);
                    nProdutos--;
                }
                System.out.printf("\nVendido: %s - %d undidades no valor de %.2f€.\n", produto.getNomeProduto(), quantProduto, (produto.getPrecoProduto() * quantProduto));
                System.out.printf("Restam %d unidades de %s.\n", produto.getStockProduto(), produto.getNomeProduto());
            } else {
                System.out.printf("\nStock insuficiente!\n");
            }
        }
    }

    public void showSupermercado() {
        System.out.printf("PRODUTOS DISPONÍVEIS:\n");
        for (int i = 0; i < listaProdutos.size(); i++) {
            System.out.println("--------------------");
            Produto showProduto = listaProdutos.get(i);
            System.out.printf("Produto: %s\nValidade: %s\nPreço: %.2f€\nStock: %d\n", showProduto.getNomeProduto(), showProduto.getValidadeProduto(),
                    showProduto.getPrecoProduto(), showProduto.getStockProduto());
        }
    }

    public void showValor() {
        float valorTotal = 0;
        for (int i = 0; i < listaProdutos.size(); i++) {
            Produto showProduto = listaProdutos.get(i);
            float preco = showProduto.getPrecoProduto();
            int stock = showProduto.getStockProduto();
            valorTotal += (preco * stock);
        }
        System.out.printf("Valor total dos produtos existentes: %.2f\n", valorTotal);
    }
}
