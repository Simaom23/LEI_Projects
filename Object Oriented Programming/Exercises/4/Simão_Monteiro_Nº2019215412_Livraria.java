package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nªº2019215412
 */
import java.util.ArrayList;

public class Livraria {

    final private ArrayList<Cliente> listaClientes;
    final private ArrayList<Livro> stock;
    private double valorVendas;

    public Livraria() {
        this.listaClientes = new ArrayList<>();
        this.stock = new ArrayList<>();
        this.valorVendas = 0;
    }

    public double getValorVendas() {
        return valorVendas;
    }

    public void addCliente(Cliente newCliente) {
        int indiceC = listaClientes.indexOf(newCliente);
        if (indiceC == -1) {
            listaClientes.add(newCliente);
        } else {
            System.out.printf("Cliente já estava registado.");
        }
    }

    public void addLivro(Livro newLivro) {
        stock.add(newLivro);
    }

    public void showStock() {
        System.out.printf("Stock:\n");
        for (Livro l : stock) {
            System.out.println(l.getAutor() + ", " + l.getTitulo());
        }
    }

    public String venda(Livro sellLivro, Cliente toCliente) {
        int indiceL = stock.indexOf(sellLivro);
        int indiceC = listaClientes.indexOf(toCliente);
        if (indiceL != -1 && indiceC != -1) {
            double desconto = toCliente.getDesconto();
            double preco = sellLivro.getPreco() * desconto;
            stock.remove(indiceL);
            valorVendas += preco;
            toCliente.addCollection(sellLivro);
            return toCliente.getNome() + " comprou " + sellLivro.toString() + " por " + preco + "€";
        } else if (indiceL == -1 & indiceC != -1) {
            return "Não existe o livro pretendido em stock.";
        } else if (indiceL != -1 & indiceC == -1) {
            return "O Cliente não está registado.";
        } else {
            return "O Cliente não está registado e não existe o livro pretendido em stock.";
        }
    }

    public String livrosCliente(Cliente showLivros) {
        String toPrint = showLivros.getNome() + " comprou: ";
        for (Livro l : showLivros.getColecao()) {
            toPrint += l.getTitulo() + ". ";
        }
        return toPrint;
    }
}
