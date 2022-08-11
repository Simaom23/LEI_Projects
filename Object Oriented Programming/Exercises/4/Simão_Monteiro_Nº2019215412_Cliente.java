package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nª2019215412
 */
import java.util.ArrayList;

public class Cliente {

    private String nome;
    private String email;
    private ArrayList<Livro> colecao;

    public Cliente() {
    }

    public Cliente(String nome, String email) {
        this.nome = nome;
        this.email = email;
        this.colecao = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public String getEmail() {
        return email;
    }

    public void addCollection(Livro newCollection) {
        colecao.add(newCollection);
    }

    public ArrayList<Livro> getColecao() {
        return colecao;
    }

    public double getDesconto() {
        return 1;
    }
}
