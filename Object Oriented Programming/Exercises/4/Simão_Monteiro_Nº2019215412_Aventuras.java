package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class Aventuras extends Livro {

    private int idadeMin;

    public Aventuras() {
    }

    public Aventuras(String autor, String titulo, int preco, int idadeMin) {
        super(autor, titulo, preco);
        this.idadeMin = idadeMin;
    }

    public int getIdadeMin() {
        return idadeMin;
    }

    @Override
    public String toString() {
        return getTitulo() + ", Livro de aventuras para maiores de " + idadeMin + " anos";
    }
}
