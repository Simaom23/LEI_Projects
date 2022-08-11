package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class Livro {

    private String autor;
    private String titulo;
    private int preco;

    public Livro() {
    }

    public Livro(String autor, String titulo, int preco) {
        this.autor = autor;
        this.titulo = titulo;
        this.preco = preco;
    }

    public String getAutor() {
        return autor;
    }

    public String getTitulo() {
        return titulo;
    }

    public int getPreco() {
        return preco;
    }

    @Override
    public String toString() {
        return "\"" + titulo + "\"";
    }

}
