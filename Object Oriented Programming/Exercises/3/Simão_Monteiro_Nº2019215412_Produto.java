package exercicioavaliacao3;
// Simão Monteiro Nº2019215412

/**
 *
 * @author Simão Monteiro
 */
public class Produto {

    private String nomeProduto;
    private float precoProduto;
    private String validadeProduto;
    private int stockProduto;

    public Produto() {
    }

    public Produto(String nomeProduto, String validadeProduto, float precoProduto, int stockProduto) {
        this.nomeProduto = nomeProduto;
        this.validadeProduto = validadeProduto;
        this.precoProduto = precoProduto;
        this.stockProduto = stockProduto;
    }

    public String getNomeProduto() {
        return nomeProduto;
    }

    public float getPrecoProduto() {
        return precoProduto;
    }

    public String getValidadeProduto() {
        return validadeProduto;
    }

    public int getStockProduto() {
        return stockProduto;
    }

    public void removeStock(int quantProduto) {
        stockProduto -= quantProduto;
    }

}
